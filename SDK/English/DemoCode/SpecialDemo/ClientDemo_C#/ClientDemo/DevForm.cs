using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Xml;
namespace ClientDemo
{
     
    public partial class DevForm : UserControl
    {

        Dictionary<int, DEV_INFO> m_devMap;
        Dictionary<int, DEV_INFO> m_devReconnetMap;
        DEV_INFO m_talkDevice;
        IntPtr m_lTalkHandle;		//Talk Handle
        IntPtr m_pTalkDecodeBuf;	//buffer the audio data
       
        public DevForm()
        {
            InitializeComponent();
        }
        public Dictionary<int, DEV_INFO> GetDeviceMap()
        {
            return m_devMap;
        }
        bool StartTalkPlay(int nPort)
        {
            return true;
        }
        bool StartTalk( ref DEV_INFO pDevice)
        {
            IntPtr pdev = new IntPtr();
            Marshal.StructureToPtr(pDevice, pdev, false);

            unsafe
            {
                if (pdev.ToPointer() == null)
                {
                    return false;
                }
             
                if (m_lTalkHandle.ToPointer() == null)
                {
                    return false;
                }
                else
                {
                    m_lTalkHandle = (IntPtr)XMSDK.H264_DVR_StartLocalVoiceCom(pDevice.lLoginID);
                    if (m_lTalkHandle!=(IntPtr)null)
                    {
                        return true;
                    }
                    else
                    {
                        m_lTalkHandle = (IntPtr)null; ;
                        return false;
                    }

                }

            }
          
           
        }
        bool StopTalk( ref DEV_INFO pDevice)
        {
            unsafe
            {
                if (m_lTalkHandle.ToPointer() != null)
                {
                    XMSDK.H264_DVR_StopVoiceCom(m_lTalkHandle.ToInt32());
                    m_lTalkHandle = (IntPtr)null;
                    return true;
                }
                return false;
            }
      
        }
        bool StopTalkPlay(int nPort)
        {
            return true;
        }
        bool SendTalkData(IntPtr pDataBuffer, uint dwDataLength)
        {
            return true;
        }
        bool InputTalkData(IntPtr pBuf, uint nBufLen)
        {
            return true;
        }
        DEV_INFO ReadXML()
        {
            XmlReader xml = XmlReader.Create("");
	        DEV_INFO devInfo = new DEV_INFO();
        	
	        devInfo.nPort=0;
	        devInfo.lLoginID=0;
	        devInfo.lID=0;
           
	        while(xml.ReadToFollowing("ip"))
	        {
		        //read the information from XML
		        string strIP,strUserName,strPsw,strDevName;
		        uint nPort;
		        int byChanNum=0,lID=0;

		        uint bSerialID,nSerPort;
		        string szSerIP,szSerialInfo;			
		        xml = xml.ReadSubtree();	

		        
		        strIP=xml.ReadElementString("ip2");
		      
		        strDevName= xml.ReadElementString("DEVICENAME");
		        
		        strUserName=xml.ReadElementString("username");
		       
		        nPort= Convert.ToUInt32(xml.ReadElementString("port"));
		        
		        strPsw=xml.ReadElementString("pwd");
		       
		        byChanNum= Convert.ToInt32(xml.ReadElementString("byChanNum"));
		       
		        lID= Convert.ToInt32(xml.ReadElementString("lID"));

		        
		        bSerialID= Convert.ToByte(xml.ReadElementString("bSerialID"));
		        
		        szSerIP=xml.ReadElementString("szSerIP");
		        
		        nSerPort=Convert.ToUInt32(xml.ReadElementString("nSerPort"));
		        
		        szSerialInfo=xml.ReadElementString("szSerialInfo");//新增ddns记录
	            
		        devInfo.nTotalChannel =byChanNum;
		        devInfo.nPort = (int)nPort;

		        devInfo.bSerialID= Convert.ToByte(bSerialID);		
		        devInfo.nSerPort=(int)nSerPort;
		        devInfo.szSerIP=szSerIP;		
		        devInfo.szSerialInfo=szSerialInfo;//新增ddns记录		
		        devInfo.szDevName=strDevName;
		        devInfo.szUserName=strUserName;
		        devInfo.szPsw=strPsw;
		        devInfo.szIpaddress= strIP;
		        DEV_INFO pDev = new DEV_INFO();
		        pDev = devInfo;
                IntPtr ptr = new IntPtr();
		        Marshal.StructureToPtr(pDev,ptr,false);
                pDev.lID =ptr.ToInt32();
		        m_devMap[pDev.lID] = pDev;
		        String strName;
                TreeNode node = new  TreeNode();
                node.Text = strDevName;
		        for ( int i = 0; i < byChanNum; i ++)
		        {
			        strName= String.Format("CAM {0}", i+1);
                    node.Nodes.Add(strName);
		        }
                DevTree.Nodes.Add(node);
	        }
	        return devInfo;
        }
        int DevLogin(ref DEV_INFO pdev)
        {
            if (Convert.ToBoolean(pdev.bSerialID))//如果之前是DDNS获取ip;这里先获取动态ip
            {
                int maxDeviceNum = 100;  //最大支持设备数量100
                DDNS_INFO[] pDDNSInfo = new DDNS_INFO[maxDeviceNum];
                SearchMode searchmode;
                int nReNum = 0;  //实际获得的设备数量		
                searchmode.nType = (int)SearchModeType.DDNS_SERIAL;
                searchmode.szSerIP = pdev.szSerIP;
                searchmode.nSerPort = pdev.nSerPort;
                searchmode.szSerialInfo = pdev.szSerialInfo;
                bool bret = Convert.ToBoolean(XMSDK.H264_DVR_GetDDNSInfo(ref searchmode, out pDDNSInfo, maxDeviceNum, out nReNum));
                if (!bret)
                {
                    return 0;
                }
                pdev.szIpaddress=pDDNSInfo[0].IP;
                pdev.nPort = pDDNSInfo[0].MediaPort;
            }

            H264_DVR_DEVICEINFO OutDev;
            int nError = 0;
            //设置尝试连接设备次数和等待时间
            XMSDK.H264_DVR_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s

            int lLogin = XMSDK.H264_DVR_Login(pdev.szIpaddress, Convert.ToUInt16(pdev.nPort), pdev.szUserName,
                pdev.szPsw, out OutDev,  out nError,SocketStyle.TCPSOCKET);
            if (lLogin <= 0)
            {
                int nErr = XMSDK.H264_DVR_GetLastError();
                if (nErr == (int)SDK_RET_CODE.H264_DVR_PASSWORD_NOT_VALID)
                {
                    MessageBox.Show("Error.PwdErr");
                }
                else
                {
                    MessageBox.Show("Error.NotFound");

                }
                return lLogin;
            }
            XMSDK.H264_DVR_SetupAlarmChan(lLogin);
            return lLogin;
        }
        void ReConnect(int lLoginID, string pchDVRIP, int nDVRPort)
        {

        }

        private void addDeviceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddDevForm addDevform = new AddDevForm();
            addDevform.Show();
        }

        private void DevTree_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Node.Name == "Channel")
            {
                TreeNode nodeDev = e.Node.Parent;
                DEV_INFO devinfo = (DEV_INFO)nodeDev.Tag;
                CHANNEL_INFO chanInfo = (CHANNEL_INFO)e.Node.Tag;
                int iRealHandle = ((ClientDemo)this.Parent).m_videoform[((ClientDemo)this.Parent).m_nCurIndex].ConnectRealPlay(ref devinfo, chanInfo.nChannelNo);
                if ( iRealHandle > 0 )
                {
                    CHANNEL_INFO chInfo = (CHANNEL_INFO)e.Node.Tag;
                    chInfo.nWndIndex = ((ClientDemo)this.Parent).m_nCurIndex;
                    e.Node.Tag = chInfo;
                }
            }
        }
    }
}
