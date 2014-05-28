using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
namespace ClientDemo
{
    public partial class AddDevForm : Form
    {
        [DllImport("NetSdk.dll")]
        public static extern int H264_DVR_SearchDevice(IntPtr ptr, int nBufLen, ref int nRetLength, int nSearchTime);

        private int m_nDevNum = 0;
     
        System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        [MarshalAs(UnmanagedType.ByValArray,SizeConst=100)]
        SDK_CONFIG_NET_COMMON[] m_Device = new SDK_CONFIG_NET_COMMON[100];
        Thread searchThread;

        public AddDevForm()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
   
            for (int i = 0; i < 100;i++ )
            {
                m_Device[i] = new SDK_CONFIG_NET_COMMON();
            }
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
           
            
            if ( textBoxDevName.Text.Trim() != "" 
                && textBoxIP.Text.Trim() != "" 
                && textBoxport.Text.Trim() != ""
                && textBoxUsername.Text.Trim() != "")
            {
                H264_DVR_DEVICEINFO dvrdevInfo = new H264_DVR_DEVICEINFO();
                int nError;
                int nLoginID = XMSDK.H264_DVR_Login(textBoxIP.Text.Trim(), ushort.Parse(textBoxport.Text.Trim()), textBoxUsername.Text, textBoxPassword.Text, out dvrdevInfo, out nError, SocketStyle.TCPSOCKET);
                DEV_INFO devInfo = new DEV_INFO();
                if ( nLoginID > 0 )
                {
                    ClientDemo clientForm = new ClientDemo();

                    foreach( Form form in  Application.OpenForms)
                    {
                        if ( form.Name == "ClientDemo" )
                        {
                            clientForm = (ClientDemo)form;
                            break;
                        }
                    }

                        
                    TreeNode nodeDev = new TreeNode();
                    nodeDev.Text = textBoxDevName.Text;
                    devInfo.szDevName = textBoxDevName.Text;
                    devInfo.lLoginID = nLoginID;
                    devInfo.nPort = Int32.Parse(textBoxport.Text.Trim());
                    devInfo.szIpaddress = textBoxIP.Text.Trim();
                    devInfo.szUserName = textBoxUsername.Text;
                    devInfo.szPsw = textBoxPassword.Text;
                    devInfo.NetDeviceInfo = dvrdevInfo;
                //  nodeDev.Tag = nLoginID;
                    nodeDev.Tag = devInfo;
                    nodeDev.Name = "Device";
                    for (int i = 0; i < devInfo.NetDeviceInfo.byChanNum + devInfo.NetDeviceInfo.iDigChannel; i++ )
                    {
                         TreeNode nodeChannel = new TreeNode(string.Format("CAM{0}",i));
                         nodeChannel.Name = "Channel";
                         CHANNEL_INFO ChannelInfo = new CHANNEL_INFO();
                         ChannelInfo.nChannelNo = i;
                         ChannelInfo.nWndIndex = -1;
                         nodeChannel.Tag = ChannelInfo;
                         nodeDev.Nodes.Add(nodeChannel);
                    }
                   
                    clientForm.devForm.DevTree.Nodes.Add(nodeDev);
                    ClientDemo.dictDevInfo.Add(devInfo.lLoginID, devInfo);
                }
                else
                {
                    
                }
                 this.Close();
            }
            else
            {
                MessageBox.Show("Please input all data!");
            }
          
           
        }

        private void buttonSearch_Click(object sender, EventArgs e)
        {
            m_nDevNum = 0;
            int count = this.listViewDevSearched.Items.Count;

            //for (int i = 0; i < count; i++)
            //{
            //    DEV_INFO* pData = (DEV_INFO*)m_listDevice.GetItemData(i);
            //    if (pData)
            //    {
            //        delete pData;
            //    }
            //}
            this.listViewDevSearched.Items.Clear();

            //清除Map
            // m_mapDev.clear();
            buttonSearch.Enabled = false;
            searchThread = new Thread(this.SearchDevice);
            //m_PromptDlg.ShowMsg(true);
            searchThread.Start();
            while (!searchThread.IsAlive) ;

            this.Cursor = Cursors.WaitCursor;
            this.Focus();
        }
        private void SearchDevice()
        {	        
            int nRetLength = 0;
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_CONFIG_NET_COMMON)) * 100);
      
            int bRet = H264_DVR_SearchDevice(ptr , Marshal.SizeOf(typeof(SDK_CONFIG_NET_COMMON)) * 100, ref nRetLength, 5000);

           
            for (int index = 0; index < 100; index++)
            {
                unsafe
                {
                    int* pDev = (int*)ptr.ToPointer();
                    pDev += Marshal.SizeOf(typeof(SDK_CONFIG_NET_COMMON)) * index / 4;

                    IntPtr ptrTemp = new IntPtr(pDev);
                    m_Device[index] = (SDK_CONFIG_NET_COMMON)Marshal.PtrToStructure(ptrTemp, typeof(SDK_CONFIG_NET_COMMON));
                }
                
               
            }
           
            if ( bRet > 0 && nRetLength > 0 )
            {
                this.m_nDevNum = nRetLength / Marshal.SizeOf(this.m_Device[0]);
            }

         
            searchThread.Interrupt();
	        buttonSearch.Enabled = true;
            this.Cursor = Cursors.Default;
		    //m_PromptDlg.ShowMsg(false);
    		
		    int count = listViewDevSearched.Items.Count;
		    int i = 0; 
		    //check
		    for ( i = 0; i < count; i ++ )
		    {
			    string strIp;
			    string strIp2;
			    int nPort;
			    int nPort2;
			    strIp = string.Format("{0}.{1}.{2}.{3}", m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1],m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
			    nPort=m_Device[i].TCPPort;
    			
			    for ( int j = i + 1; j < count; j ++ )
			    {
				    strIp2 = string.Format("{0}.{1}.{2}.{3}", m_Device[j].HostIP.c[0], m_Device[j].HostIP.c[1],
					    m_Device[j].HostIP.c[2], m_Device[j].HostIP.c[3]);
				    nPort2 = m_Device[j].TCPPort;
    				
				    if ( strIp2 == strIp && nPort2 == nPort )
				    {
                       // m_Device[j];
				    }
			    }
		    }
    		
		    int nIndex = 0;
		    for (i = 0 ; i < m_nDevNum; i ++ )
		    {
                int l = (m_Device[i].HostIP.c[0] << 3) | m_Device[i].HostIP.c[1]<<2 | m_Device[i].HostIP.c[2]<<1|m_Device[i].HostIP.c[3];
			    if ( m_Device[i].TCPPort == 0 || l == 0 )
			    {
				    continue;
			    }		
			    //Edit Device Information
    			
			    DEV_INFO pData = new DEV_INFO();
			    pData.nPort = m_Device[i].TCPPort;
			    pData.szIpaddress = String.Format("{0}.{1}.{2}.{3}", m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1],m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
                pData.szUserName = "admin";
			    pData.szPsw = "";
			    pData.NetComm =m_Device[i];
    			
			    //过滤已经存在的IP和mac相同的设备
                int nFlag = 1;
             
    			
			    if ( nFlag==0 )
			    {
                    //delete pData;
                    //pData = NULL;
				    continue;
			    }else
			    {
				  
                    ListViewItem item = new ListViewItem();
                    ListViewItem.ListViewSubItem subitem0= new ListViewItem.ListViewSubItem();
                    ListViewItem.ListViewSubItem subitem1 = new ListViewItem.ListViewSubItem();
                    ListViewItem.ListViewSubItem subitem2 = new ListViewItem.ListViewSubItem();

                    subitem0.Text = string.Format("{0}", count + nIndex + 1);
                    subitem0.Name = "NO";
                    subitem1.Text = string.Format("{0}.{1}.{2}.{3}", m_Device[i].HostIP.c[0], m_Device[i].HostIP.c[1], m_Device[i].HostIP.c[2], m_Device[i].HostIP.c[3]);
                    subitem1.Name = "IP";
                    subitem2.Text = string.Format("{0}", m_Device[i].TCPPort);
                    subitem2.Name = "Port";

                    item.SubItems.Insert(0, subitem0);
                    item.SubItems.Insert(1, subitem1);
                    item.SubItems.Insert(2, subitem2);
	
				    pData.nListNum = count + nIndex;
				    //m_mapDev[ nIndex ] = pData;

                    item.Tag = pData;
				    listViewDevSearched.Items.Insert(count + nIndex,item);
    				
				    nIndex ++;
    				
			    }
		    }
		    this.Capture = false;  //释放鼠标
         }

        private void listViewDevSearched_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.buttonOK_Click(null, null);
        }

        private void listViewDevSearched_SelectedIndexChanged(object sender, EventArgs e)
        {
            String strIP = new String('0', 20);
            String strPort = new String('0', 10);
            if (listViewDevSearched.SelectedItems.Count != 0)
            {
                ListView.SelectedListViewItemCollection itemSelected = listViewDevSearched.SelectedItems;

                foreach (ListViewItem items in itemSelected)
                {
                    ListViewItem.ListViewSubItemCollection subItems = new ListViewItem.ListViewSubItemCollection(items);

                    foreach (ListViewItem.ListViewSubItem subItem in subItems)
                    {
                        if (subItem.Name == "IP")
                        {
                            strIP = subItem.Text;
                        }
                        else if (subItem.Name == "Port")
                        {
                            strPort = subItem.Text;
                        }

                    }


                }
            }

            textBoxDevName.Text = strIP;
            textBoxIP.Text = strIP;
            textBoxport.Text = strPort;
        } 
    }
}