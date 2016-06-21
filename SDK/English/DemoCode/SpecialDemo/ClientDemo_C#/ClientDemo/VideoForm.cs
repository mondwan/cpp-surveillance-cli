using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
namespace ClientDemo
{

    public partial class VideoForm : UserControl
    {
	    int m_nIndex;	//index	
	    bool m_bRecord;	//is recording or not
	    bool m_bSound;

	    public int m_iPlayhandle;	//play handle
	    public int m_lLogin; //login handle
	    public int m_iChannel; //play channel
        public int m_iTalkhandle;

	    public void SetWndIndex(int nIndex)
	    {
		    m_nIndex = nIndex;
	    }
	    public int ConnectRealPlay( ref DEV_INFO pDev, int nChannel)
        {
            if(m_iPlayhandle != -1)
	        {

                if (0 != XMSDK.H264_DVR_StopRealPlay(m_iPlayhandle, (uint)this.Handle))
		        {
			        //TRACE("H264_DVR_StopRealPlay fail m_iPlayhandle = %d", m_iPlayhandle);
		        }
		        if(m_bSound)
		        {
			        OnCloseSound();
		        }
	        }

	        H264_DVR_CLIENTINFO playstru = new H264_DVR_CLIENTINFO();

	        playstru.nChannel = nChannel;
	        playstru.nStream = 0;
	        playstru.nMode = 0;
	        playstru.hWnd=this.Handle;
            m_iPlayhandle = XMSDK.H264_DVR_RealPlay(pDev.lLoginID, ref playstru);	
	        if(m_iPlayhandle <= 0 )
	        {
                Int32 dwErr = XMSDK.H264_DVR_GetLastError();
                    StringBuilder sTemp = new StringBuilder("");
			        sTemp.AppendFormat("access {0} channel{1} fail, dwErr = {2}",pDev.szDevName,nChannel, dwErr);
			        MessageBox.Show(sTemp.ToString());
	        }
	        else
	        {
                XMSDK.H264_DVR_MakeKeyFrame(pDev.lLoginID, nChannel, 0);		
	        }
	        m_lLogin = pDev.lLoginID;
	        m_iChannel = nChannel;
	        return m_iPlayhandle;
        }

        public void GetColor(out int nBright, out int nContrast, out int nSaturation, out int nHue)
        {
            if (m_iPlayhandle <= 0)
            {
                nBright = -1;
                nContrast = -1;
                nSaturation = -1;
                nHue = -1;
                return;
            }
            uint nRegionNum = 0;
            XMSDK.H264_DVR_LocalGetColor(m_iPlayhandle, nRegionNum, out nBright, out nContrast, out nSaturation, out nHue);
        }
	    public void SetColor(int nBright, int nContrast, int nSaturation, int nHue)
        {
            XMSDK.H264_DVR_LocalSetColor(m_iPlayhandle, 0, nBright, nContrast, nSaturation, nHue);
        }

	    public int GetHandle()
	    {
		    return m_iPlayhandle;
	    }
	    public bool OnOpenSound()
        {
            if (XMSDK.H264_DVR_OpenSound(m_iPlayhandle))
            {
                m_bSound = true;
                return true;
            }
            return false;
        }
        public bool OnCloseSound()
        {
            if (XMSDK.H264_DVR_CloseSound(m_iPlayhandle))
            {
                m_bSound = false;
                return true;
            }
            return false;
        }
	    public bool SaveRecord()
        {
            if ( m_iPlayhandle <= 0 )
	        {
		        return false;
	        }
	
            DateTime time = DateTime.Now;
            String cFilename = String.Format(@"{0}\\record\\{1}{2}{3}_{4}{5}{6}.h264",
                                                        "c:",
                                                        time.Year,
                                                        time.Month,
                                                        time.Day,
                                                        time.Hour,
                                                        time.Minute,
                                                        time.Second);
	        if ( m_bRecord )
	        {

                if (XMSDK.H264_DVR_StopLocalRecord(m_iPlayhandle))
		        {
			        m_bRecord = false;
			        MessageBox.Show(@"stop record OK.");
		        }
	        }
	        else
	        {
                int nTemp = 0;
                string strPr = "\\";
		        for(;;)
		        {
                    int nIndex = cFilename.IndexOfAny(strPr.ToCharArray(), nTemp);
                    if (nIndex == -1)
                    {
                        break;
                    }
                    String str = cFilename.Substring(0,nIndex+1);
                    nTemp = nIndex + 1; nTemp = nIndex + 1;
                    DirectoryInfo dir = new DirectoryInfo(str);
                    if ( !dir.Exists )
                    {
                        dir.Create();
                    }

		        }

                if (XMSDK.H264_DVR_StartLocalRecord(m_iPlayhandle, cFilename, (int)MEDIA_FILE_TYPE.MEDIA_FILE_NONE))
		        {
			        m_bRecord = true ;
			        MessageBox.Show(@"start record OK.");
		        }
		        else
		        {
			        MessageBox.Show(@"start record fail.");
		        }
	        }

	        return true;
        }

        public int GetLoginHandle()
        {
            return m_lLogin;
        }
        public void OnDisconnct()
        {
            if (m_iPlayhandle > 0)
            {
                XMSDK.H264_DVR_StopRealPlay(m_iPlayhandle, (uint)this.Handle);
                m_iPlayhandle = -1;

            }
            if (m_bSound)
            {
                OnCloseSound();
            }
            m_lLogin = -1;
        }


        public void drawOSD(int nPort, IntPtr hDc)
        {
            if (m_strInfoFrame[nPort] !="")
            {    
                //改变字体颜色
                FontFamily fontfamily = new FontFamily(@"Arial");
                Font newFont = new Font(fontfamily, 16,FontStyle.Bold);
                SolidBrush brush =  new SolidBrush(Color.Red);
       

                Graphics graphic = Graphics.FromHdc(hDc);
                graphic.DrawString("TEST", newFont,brush,10,10);            
            }
        }

        public int SetDevChnColor(ref SDK_CONFIG_VIDEOCOLOR pVideoColor)
        {
            IntPtr ptr = new IntPtr();
            Marshal.StructureToPtr(pVideoColor, ptr, true);
            return XMSDK.H264_DVR_SetDevConfig(m_lLogin, (uint)SDK_CONFIG_TYPE.E_SDK_VIDEOCOLOR, m_iChannel, ptr, (uint)Marshal.SizeOf(pVideoColor), 3000);
         
        }
        static void videoInfoFramCallback(int nPort, int nType, string pBuf,int nSize, IntPtr nUser)
        {
            //收到信息帧, 0x03 代表GPRS信息
      
            if (nType == 0x03)
            {
                VideoForm form = new VideoForm();
                Marshal.PtrToStructure(nUser, form);
                form.m_strInfoFrame[nPort] = pBuf;
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
	    public string[] m_strInfoFrame;


        public VideoForm()
        {
            InitializeComponent();
        }

        private void VideoForm_Click(object sender, EventArgs e)
        {
            ClientDemo clientdemo = (ClientDemo)this.Parent;
            clientdemo.SetActiveWnd(m_nIndex);
            clientdemo.comboBox1.Focus();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
           // MessageBox.Show("");
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ( -1 != m_nIndex)
            {
                XMSDK.H264_DVR_StopRealPlay(m_iPlayhandle,(uint)this.Handle);
                ClientDemo clientdemo = (ClientDemo)this.Parent;
                clientdemo.DrawActivePage(false);

                foreach (TreeNode node in clientdemo.devForm.DevTree.Nodes)
                {
                    if (node.Name == "Device")
                    {
                        foreach (TreeNode channelnode in node.Nodes)
                        {
                            if (channelnode.Name == "Channel")
                            {
                                CHANNEL_INFO chInfo = (CHANNEL_INFO)channelnode.Tag;
                                if (chInfo.nWndIndex == m_nIndex)
                                {
                                    chInfo.nWndIndex = -1;
                                    channelnode.Tag = chInfo;
                                    break;
                                }
                            }

                        }
                    }
                   
                }

            }
           
        }

        private void catchPictureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ( m_nIndex > -1 && m_iPlayhandle > 0)
            {
                String strPath;
                ClientDemo clientdemo = (ClientDemo)this.Parent;
                foreach (TreeNode node in clientdemo.devForm.DevTree.Nodes)
                {
                    if (node.Name == "Device")
                    {
                        foreach (TreeNode channelnode in node.Nodes)
                        {
                            if (channelnode.Name == "Channel")
                            {
                                CHANNEL_INFO chInfo = (CHANNEL_INFO)channelnode.Tag;
                                if (chInfo.nWndIndex == m_nIndex)
                                {
                                    int y = System.DateTime.Now.Year;
                                    int m = System.DateTime.Now.Month;
                                    int d = System.DateTime.Now.Day;
                                    int h = System.DateTime.Now.Hour;
                                    int min = System.DateTime.Now.Minute;
                                    int s = System.DateTime.Now.Second;
                                    strPath = String.Format(".\\Pictures\\{0}_{1}_{2}{3}{4}{5}{6}{7}.bmp", node.Text,chInfo.nChannelNo + 1, y, m, d, h, min, s );
                                    bool bCatch = XMSDK.H264_DVR_LocalCatchPic(m_iPlayhandle, strPath);

                                    if ( bCatch )
                                    {
                                        System.Diagnostics.Process.Start(strPath);
                                    }
                                    else
                                    {
                                        MessageBox.Show("Catch Picture error !");
                                    }
                                    break;
                                }
                            }

                        }
                    } 
                } 
            }
        }

        private void soundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ( m_iPlayhandle <= 0 )
            {
                return;
            }
            ToolStripMenuItem menuSound = (ToolStripMenuItem)sender;
            if ( menuSound.Checked )   
            {
                if (  XMSDK.H264_DVR_CloseSound(m_iPlayhandle) )
                {
                    menuSound.Checked = false;
                }
            }
            else
            {
                if (XMSDK.H264_DVR_OpenSound(m_iPlayhandle))
                {
                    menuSound.Checked = true;
                }
               
            }
        }

        private void talkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (m_iPlayhandle <= 0)
            {
                return;
            }
            ToolStripMenuItem menuTalk = (ToolStripMenuItem)sender;
            if (menuTalk.Checked)
            {
                if (XMSDK.H264_DVR_StopVoiceCom(m_iTalkhandle))
                {
                    menuTalk.Checked = false;
                }
            }
            else
            {
                m_iTalkhandle = XMSDK.H264_DVR_StartLocalVoiceCom(m_lLogin);
                if (m_iTalkhandle > 0)
                {
                    menuTalk.Checked = true;
                }

            }
        }

        private void VideoForm_Load(object sender, EventArgs e)
        {

        }
    }
}
