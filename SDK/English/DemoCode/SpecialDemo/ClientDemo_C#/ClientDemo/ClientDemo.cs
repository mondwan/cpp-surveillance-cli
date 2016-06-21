using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
namespace ClientDemo
{
    public partial class ClientDemo : Form
    {
        public PTZForm m_formPTZ;
        public DevConfigForm m_formCfg;
        public int m_nCurIndex = -1;
        public int m_nTotalWnd = 4;
        public DEV_INFO m_devInfo = new DEV_INFO();
        public VideoForm[] m_videoform = new VideoForm[32];
        public bool m_bArray;
        public static Dictionary<int , DEV_INFO> dictDevInfo = new Dictionary<int , DEV_INFO>();
        public static Dictionary<int, DEV_INFO> dictDiscontDev = new Dictionary<int, DEV_INFO>();

        private System.Timers.Timer timerDisconnect = new System.Timers.Timer(30000);

        private XMSDK.fDisConnect disCallback;

        private XMSDK.fMessCallBack msgcallback;

        private System.Timers.ElapsedEventHandler reconnect;

        bool  MessCallBack(int  lLoginID, string pBuf,uint dwBufLen, IntPtr dwUser)
        {
            ClientDemo form = new ClientDemo();
            Marshal.PtrToStructure(dwUser, form);
	        return form.DealwithAlarm(lLoginID,pBuf,dwBufLen);
        }
        void DisConnectBackCallFunc(int lLoginID, string pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            for (int i = 0; i < 16; i++)
            {
                if (lLoginID == m_videoform[i].GetLoginHandle())
                {
                    m_videoform[i].OnDisconnct();
                }
            }
           
          
            foreach (DEV_INFO devinfo in dictDevInfo.Values)
            {
                if (devinfo.lLoginID == lLoginID)
                {
                    XMSDK.H264_DVR_Logout(lLoginID);
                    dictDevInfo.Remove(devinfo.lLoginID);
			        dictDiscontDev.Add(devinfo.lLoginID,devinfo);
                    break;
                }
            }

            if ( dictDiscontDev.Count > 0 )
            {

                timerDisconnect.Enabled = true;
                timerDisconnect.Start();
            }
        }


        public ClientDemo()
        {
            for (int i = 0; i < 32; i++)
            {
                m_videoform[i] = new VideoForm();
                this.Controls.Add(this.m_videoform[i]);
                m_videoform[i].SetWndIndex(i);
            }
            InitializeComponent();
            devForm = new DevForm();
            this.Controls.Add(devForm);
            devForm.Location = new System.Drawing.Point(880, 10);
            devForm.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));  
            this.comboBox1.SelectedIndex = 1;
            InitSDK();
            reconnect = new System.Timers.ElapsedEventHandler(ReConnect);
            GC.KeepAlive(reconnect);
            timerDisconnect.Elapsed += new System.Timers.ElapsedEventHandler(reconnect); 
       
            ArrayWindow(4);
            SetActiveWnd(0);   
        }

        private void btnTransparent_Click(object sender, EventArgs e)
        {
            Form_Transpanrent formTransparent = new Form_Transpanrent();
            formTransparent.Show();
        }
        public int InitSDK()
        {
            //initialize
            disCallback = new XMSDK.fDisConnect(DisConnectBackCallFunc);
            GC.KeepAlive(disCallback);
            int bResult = XMSDK.H264_DVR_Init(disCallback, this.Handle);

            //he messages received in SDK from DVR which need to upload， such as alarm information，diary information，may do through callback function
            msgcallback  = new XMSDK.fMessCallBack(MessCallBack);
            XMSDK.H264_DVR_SetDVRMessCallBack(msgcallback, this.Handle);

            XMSDK.H264_DVR_SetConnectTime(5000, 3);

            return bResult;
        }
        public bool ExitSDk()
        {
            return XMSDK.H264_DVR_Cleanup();
        }
        public void ArrayWindow(int iNumber)
        {
            m_nTotalWnd = iNumber;

            Rectangle rect = this.ClientRectangle;
            int  iWidth, iHeight;
            int nFullWidth = rect.Width;
            int nFullHeight = rect.Height;
            iWidth = (int)(nFullWidth * 0.75515625);
            iHeight = (int)(nFullHeight * 0.91);

            int i = 0;
            for (i = 0; i < 32; i++)   //MAXWNDNUM ==32
            {
                m_videoform[i].Hide();
            }
            
            int nNull = 3;

            switch (iNumber)
            {
                case 1:
                    m_videoform[0].SetBounds(3+0,0,iWidth,iHeight);
                    m_videoform[0].Show();
                    break;
                case 4:
                    for (i = 0; i < 2; i++)
                    {
                        m_videoform[i].SetBounds(3 + i * (iWidth / 2) + i * nNull, 0, (iWidth / 2), iHeight / 2);
                        m_videoform[i].Show();
                    }
                    for (i = 2; i < 4; i++)
                    {
                        m_videoform[i].SetBounds(3 + (i - 2) * (iWidth / 2) + (i - 2) * nNull, iHeight / 2 + nNull, (iWidth / 2), iHeight / 2);
                        m_videoform[i].Show();
                    }
                    break;
                case 9:
                    for (i = 0; i < 3; i++)
                    {
                        m_videoform[i].SetBounds(3 + i * (iWidth / 3) + i * nNull, 0, (iWidth / 3), iHeight / 3);
                        m_videoform[i].Show();
                    }
                    for (i = 3; i < 6; i++)
                    {
                        m_videoform[i].SetBounds(3 + (i - 3) * (iWidth / 3) + (i - 3) * nNull, iHeight / 3 + nNull, (iWidth / 3), iHeight / 3);
                        m_videoform[i].Show();
                    }
                    for (i = 6; i < 9; i++)
                    {
                        m_videoform[i].SetBounds(3 + (i - 6) * (iWidth / 3) + (i - 6) * nNull, 2 * iHeight / 3 + 2 * nNull, (iWidth / 3), iHeight / 3);
                        m_videoform[i].Show();
                    }
                    break;
                case 16:
                    for (i = 0; i < 4; i++)
                    {
                        m_videoform[i].SetBounds(3 + i * (iWidth / 4) + (i) * nNull, 0, (iWidth / 4), iHeight / 4);
                        m_videoform[i].Show();
                    }
                    for (i = 4; i < 8; i++)
                    {
                        m_videoform[i].SetBounds(3 + (i - 4) * (iWidth / 4) + (i - 4) * nNull, iHeight / 4 + nNull, (iWidth / 4), iHeight / 4);
                        m_videoform[i].Show();
                    }
                    for (i = 8; i < 12; i++)
                    {
                        m_videoform[i].SetBounds(3 + (i - 8) * (iWidth / 4) + (i - 8) * nNull, iHeight / 2 + 2 * nNull, (iWidth / 4), iHeight / 4);
                        m_videoform[i].Show();
                    }
                    for (i = 12; i < 16; i++)
                    {
                        m_videoform[i].SetBounds(3 + (i - 12) * (iWidth / 4) + (i - 12) * nNull, 3 * iHeight / 4 + 3 * nNull, (iWidth / 4), iHeight / 4);
                        m_videoform[i].Show();
                    }
                    break;
                default:
                    break;
            }
        }
        public void DrawActivePage(bool bActive)
        {
            Rectangle rt = new Rectangle(m_videoform[m_nCurIndex].Left,m_videoform[m_nCurIndex].Top, m_videoform[m_nCurIndex].Width, m_videoform[m_nCurIndex].Height);
            if (!bActive)
            {
                Rectangle rtInvalidate = new Rectangle(rt.X - 1, rt.Y - 1, rt.Width + 2, rt.Height + 2);
                Invalidate(rtInvalidate, true);
            }
            else
            {
                Graphics graphic = Graphics.FromHwnd(this.Handle);
                Pen pen = new Pen(Color.Red, 2);
                graphic.DrawRectangle(pen, rt);
            }
        }
        private void SetColor(int nIndex)
        {
            int nBright = 0;
            int nHue = 0;
            int nSaturation = 0;
            int nContrast = 0;

            IntPtr lPlayHandle = m_videoform[m_nCurIndex].Handle;
            if (lPlayHandle.ToInt32() <=0 )
            {
                return;
            }
            m_videoform[nIndex].GetColor(out nBright, out nContrast, out nSaturation, out nHue);
            //m_colorDLg.SetColor(nBright, nContrast, nSaturation, nHue);
        }
        public bool DealwithAlarm(int lDevcID, string pBuf, uint dwLen)
        {
            return true;
        }
        public bool SetDevChnColor(uint nBright, uint nContrast, uint nSaturation, uint nHue)
        {
            SDK_CONFIG_VIDEOCOLOR videocolor = new SDK_CONFIG_VIDEOCOLOR();

            for (int i = 0; i < 2; i++)
            {
                videocolor.dstVideoColor[i].tsTimeSection.enable = 1;
                videocolor.dstVideoColor[i].tsTimeSection.startHour = 0;
                videocolor.dstVideoColor[i].tsTimeSection.startMinute = 0;
                videocolor.dstVideoColor[i].tsTimeSection.startSecond = 0;
                videocolor.dstVideoColor[i].tsTimeSection.endHour = 24;
                videocolor.dstVideoColor[i].tsTimeSection.endMinute = 0;
                videocolor.dstVideoColor[i].tsTimeSection.endSecond = 0;
                videocolor.dstVideoColor[i].iEnable = 1;
                videocolor.dstVideoColor[i].dstColor.nBrightness = (int)nBright * 100 / 128;
                videocolor.dstVideoColor[i].dstColor.nHue = (int)nHue * 100 / 128;
                videocolor.dstVideoColor[i].dstColor.nSaturation = (int)nSaturation * 100 / 128;
                videocolor.dstVideoColor[i].dstColor.nContrast = (int)nContrast * 100 / 128;
                videocolor.dstVideoColor[i].dstColor.mGain = 0;
                videocolor.dstVideoColor[i].dstColor.mWhitebalance = 0;
            }

            m_videoform[m_nCurIndex].SetDevChnColor(ref videocolor);

            return true;
        }
        public void SetActiveWnd(int nIndex)
        {
            if (-1 != m_nCurIndex && m_nCurIndex != nIndex)
            {
                DrawActivePage(false);
            }
            if (m_nCurIndex!=nIndex)
            {
                   m_nCurIndex = nIndex;
            }
            

            DrawActivePage(true);

            SetColor(m_nCurIndex);

        }
        public int Connect(ref DEV_INFO pDev, int nChannel, int nWndIndex)
        {
            int nRet = 0;

            //if device did not login,login first
            if (pDev.lLoginID <= 0)
            {
                H264_DVR_DEVICEINFO OutDev;
                int nError = 0;
                //设置尝试连接设备次数和等待时间
                int lLogin = XMSDK.H264_DVR_Login(pDev.szIpaddress, (ushort)pDev.nPort, pDev.szUserName, pDev.szPsw, out OutDev, out nError, SocketStyle.TCPSOCKET);
                if (lLogin <= 0)
                {

                    int nErr = XMSDK.H264_DVR_GetLastError();
                    if (nErr == (int)SDK_RET_CODE.H264_DVR_PASSWORD_NOT_VALID)
                    {
                        MessageBox.Show(("Error.PwdErr"));
                    }
                    else
                    {
                        MessageBox.Show(("Error.NotFound"));
                    }

                    return nRet;
                }

                pDev.lLoginID = lLogin;
                XMSDK.H264_DVR_SetupAlarmChan(lLogin);
            }

            int nWnd = m_nCurIndex;
            if (nWndIndex >= 0)
            {
                nWnd = nWndIndex;
            }

            if (nWnd >= m_nTotalWnd)
            {
                return nRet;
            }

            return m_videoform[nWnd].ConnectRealPlay(ref pDev, nChannel);	
        }
        public void SetColor(uint nBright, uint nContrast, uint nSaturation, uint nHue)
        {
            IntPtr lPlayHandle = m_videoform[m_nCurIndex].Handle;
            unsafe
            {
                if (lPlayHandle.ToPointer() == null)
                {
                    return;
                }
            }
         
            m_videoform[m_nCurIndex].SetColor((int)nBright, (int)nContrast, (int)nSaturation, (int)nHue);
            SetDevChnColor(nBright, nContrast, nSaturation, nHue);
        }
        public void PtzControl(uint dwBtn, bool dwStop)
        {
            long lPlayHandle = m_videoform[m_nCurIndex].GetHandle();
            if (lPlayHandle <= 0)
            {
                return;
            }
        }
        public void KeyBoardMsg(uint dwValue, uint dwState)
        {
            IntPtr lPlayHandle = m_videoform[m_nCurIndex].Handle;
            unsafe
            {
                if (lPlayHandle.ToPointer() == null)
                {
                    return;
                }
            }
          
            SDK_NetKeyBoardData vKeyBoardData;
            vKeyBoardData.iValue = (int)dwValue;
            vKeyBoardData.iState = (int)dwState;
            m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
            if (!XMSDK.H264_DVR_ClickKey(m_videoform[m_nCurIndex].m_lLogin, ref vKeyBoardData))
               MessageBox.Show("AccountMSG.Failed");
        }
        public void NetAlarmMsg(uint dwValue, uint dwState)
        {
            if (m_devInfo.lLoginID > 0)
            {
                SDK_NetAlarmInfo vAlarmInfo;
                vAlarmInfo.iEvent = 0;
                vAlarmInfo.iState = (int)(dwState << (int)dwValue);
                m_nCurIndex = m_nCurIndex < 0 ? 0 : m_nCurIndex;
                if (!XMSDK.H264_DVR_SendNetAlarmMsg(m_devInfo.lLoginID, ref vAlarmInfo))
                    MessageBox.Show("AccountMSG.Failed");
            }
        }
        //public Dictionary<int,DEV_INFO> GetDeviceMap()
        //{
        //    return m_devDLg.GetDeviceMap();
        //}
        public void SetDevInfo(ref DEV_INFO pDev)
        {
            m_devInfo = pDev;
        }
        public void ReConnect(object source, System.Timers.ElapsedEventArgs e)
        {
                
        	foreach( DEV_INFO devinfo in dictDiscontDev.Values )
            {

                H264_DVR_DEVICEINFO OutDev = new H264_DVR_DEVICEINFO();
                int nError = 0;

                int lLogin = XMSDK.H264_DVR_Login(devinfo.szIpaddress, (ushort)devinfo.nPort, devinfo.szUserName, devinfo.szPsw, out OutDev, out nError, SocketStyle.TCPSOCKET);
                if (lLogin <= 0)
                {

                    int nErr = XMSDK.H264_DVR_GetLastError();
                    if (nErr == (int)SDK_RET_CODE.H264_DVR_PASSWORD_NOT_VALID)
                    {
                        MessageBox.Show(("Password Error"));
                    }
                    else if (nErr == (int)SDK_RET_CODE.H264_DVR_LOGIN_USER_NOEXIST)
                    {
                        MessageBox.Show(("User Not Exist"));
                    }

                    return;
                }
                dictDiscontDev.Remove(devinfo.lLoginID);

                ClientDemo clientForm = new ClientDemo();

                foreach (Form form in Application.OpenForms)
                {
                    if (form.Name == "ClientDemo")
                    {
                        clientForm = (ClientDemo)form;
                        break;
                    }
                }
                DEV_INFO devAdd = new DEV_INFO();
                devAdd = devinfo;
                devAdd.lLoginID = lLogin;
           

                foreach (TreeNode node in clientForm.devForm.DevTree.Nodes)
                {
                    if (node.Name == "Device")
                    {
                        DEV_INFO dev = (DEV_INFO)node.Tag;
                        if (dev.lLoginID == devinfo.lLoginID)
                        {
                            node.Text = devAdd.szDevName;
                            node.Tag = devAdd;
                            node.Name = "Device";

                            foreach (TreeNode channelnode in node.Nodes)
                            {
                                CHANNEL_INFO chInfo = (CHANNEL_INFO)channelnode.Tag;
                                if ( chInfo.nWndIndex > -1  )
                                {
                                    clientForm.m_videoform[chInfo.nWndIndex].ConnectRealPlay(ref devAdd, chInfo.nChannelNo);
                                    Thread.Sleep(10);
                                }
                                
                            }
                            break;
                        }

                    }

                }

                dictDevInfo.Add(lLogin, devAdd);
                XMSDK.H264_DVR_SetupAlarmChan(lLogin);
            }
            if (0 == dictDiscontDev.Count)
            {
                timerDisconnect.Enabled = false;
                timerDisconnect.Stop();
            }
        }

       

        private void ClientDemo_Paint(object sender, PaintEventArgs e)
        {
            SetActiveWnd(m_nCurIndex);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int nWndNum = 4;
            if (comboBox1.SelectedIndex == 0)
            {
                nWndNum = 1;
            }
            else if (comboBox1.SelectedIndex == 1)
            {
                nWndNum = 4;
            }
            else if (comboBox1.SelectedIndex == 2)
            {
                nWndNum = 9;
            }
            else if (comboBox1.SelectedIndex == 3)
            {
                nWndNum = 16;
            }
            ArrayWindow(nWndNum);
        }

        private void ClientDemo_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                 
    
            }
        }

        private void ClientDemo_FormClosing(object sender, FormClosingEventArgs e)
        {
            ExitSDk();
        }

        private void btnplayback_Click(object sender, EventArgs e)
        {
            PlayBackForm formPlayBack = new PlayBackForm();
            formPlayBack.Show();
            
        }

        private void ClientDemo_FormClosed(object sender, FormClosedEventArgs e)
        {

            foreach (DEV_INFO devinfo in dictDevInfo.Values)
            {
         
                XMSDK.H264_DVR_Logout(devinfo.lLoginID);   

            }

            timerDisconnect.Stop();
        }

        private void btnPTZ_Click(object sender, EventArgs e)
        {
            m_formPTZ = new PTZForm();
            m_formPTZ.StartPosition = FormStartPosition.CenterScreen;
            m_formPTZ.Owner = this;
            m_formPTZ.Show(); 
        }

        private void btnDevConfig_Click(object sender, EventArgs e)
        {
            m_formCfg = new DevConfigForm();
            m_formCfg.StartPosition = FormStartPosition.CenterScreen;
            m_formCfg.Owner = this;
            m_formCfg.Show();
        }

        private void ClientDemo_Load(object sender, EventArgs e)
        {

        }
    }
}