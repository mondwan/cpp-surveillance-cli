using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
namespace ClientDemo
{
    public partial class DevConfigForm : Form
    {
        public DevConfigForm()
        {
            InitializeComponent();
        }

        private void DevConfigForm_Shown(object sender, EventArgs e)
        {
            comboBoxDevice.ResetText();
            ClientDemo clientForm = (ClientDemo)this.Owner;
            TreeNodeCollection nodeCollection = clientForm.devForm.DevTree.Nodes;
            foreach (TreeNode node in nodeCollection)
            {
                if ( node.Name == "Device" )
                {
                    comboBoxDevice.Items.Add(node);
                }
            }
            if ( comboBoxDevice.Items.Count > 0 )
            {
                comboBoxDevice.SelectedIndex = 0;
            }
        }

        private void comboBoxDevice_SelectedIndexChanged(object sender, EventArgs e)
        {
            TreeNode node = (TreeNode)comboBoxDevice.SelectedItem;
            if ( node.Tag !=null )
            {
                DEV_INFO devInfo = (DEV_INFO)node.Tag;
                int nLoginID = devInfo.lLoginID;

                ///获取系统能力集



                int nChannel = -1;
                TabPage tab = tabControlConfigs.SelectedTab;
                uint nConfig = 0;
                if (tab.Name == "tabPageGeneral")
                {
                    nConfig = (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_SYSNORMAL;
                }
                if (nConfig != 0)
                {
                    UpdateConfig(nLoginID, nChannel, nConfig);
                }
            }   
        }

        SDK_NetDHCPConfigAll curDHCPcfgAll = new SDK_NetDHCPConfigAll();

        private void UpdateConfig(int nLoginID, int nChannel, uint nConfig)
        {
            if ( nLoginID > 0 )
            {
                IntPtr bufPtr;
                uint nBufSize = 0;
                uint nOutSize = 0;
                switch(nConfig)
                {
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_SYSNORMAL:
                        {
                            
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_CONFIG_NORMAL));
                            bufPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_CONFIG_NORMAL)));
                            int nRet = XMSDK.H264_DVR_GetDevConfig(nLoginID, nConfig, nChannel, bufPtr, nBufSize, out nOutSize, 1000);
                            if ( nRet < 0 )
                            {
                                MessageBox.Show("Get config error!");
                                return;
                            }

                            SDK_CONFIG_NORMAL cfgNormal = new SDK_CONFIG_NORMAL();
                            cfgNormal = (SDK_CONFIG_NORMAL)Marshal.PtrToStructure(bufPtr, typeof(SDK_CONFIG_NORMAL));

                            nBufSize = (uint)Marshal.SizeOf(typeof(H264_DVR_DEVICEINFO));
                            bufPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(H264_DVR_DEVICEINFO)));
                            nRet = XMSDK.H264_DVR_GetDevConfig(nLoginID, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_SYSINFO, nChannel, bufPtr, nBufSize, out nOutSize, 1000);
                            H264_DVR_DEVICEINFO cfgSysInfo = new H264_DVR_DEVICEINFO();
                            cfgSysInfo = (H264_DVR_DEVICEINFO)Marshal.PtrToStructure(bufPtr, typeof(H264_DVR_DEVICEINFO));

                            textBoxSerial.Text = cfgSysInfo.sSerialNumber.ToString();
                            textBoxDeviceNo.Text = cfgNormal.iLocalNo.ToString();
                            textBoxDeviceName.Text = cfgNormal.sMachineName.ToString();
                            textBoxVideoOut.Text = cfgNormal.iVideoStartOutPut.ToString();
                            textBoxAlarmIn.Text = cfgSysInfo.byAlarmInPortNum.ToString();
                            textBoxAlarmOut.Text = cfgSysInfo.byAlarmOutPortNum.ToString();
                            comboBoxDiskFullTo.SelectedIndex = cfgNormal.iOverWrite;
                            comboBoxVideoStandard.SelectedIndex = cfgNormal.iVideoFormat;
                            comboBoxDateFormat.SelectedIndex = cfgNormal.iDateFormat;
                            comboBoxDateSeparator.SelectedIndex = cfgNormal.iDateSeparator;
                            textBoxStandbyTime.Text = cfgNormal.iWorkDay.ToString();
                            comboBoxTimeFormat.SelectedIndex = cfgNormal.iTimeFormat;

                            textBoxRecordChannel.Text = (cfgSysInfo.byChanNum + cfgSysInfo.iDigChannel).ToString();
                            textBoxAudioIn.Text = cfgSysInfo.iAudioInChannel.ToString();
                            textBoxTalkIn.Text = cfgSysInfo.iTalkInChannel.ToString();
                            textBoxTalkOut.Text = cfgSysInfo.iTalkOutChannel.ToString();
                            textBoxVideoOut.Text = cfgSysInfo.iTalkOutChannel.ToString();
                            textBoxExChannel.Text = cfgSysInfo.iExtraChannel.ToString();
                            textBoxDigitalChannel.Text = cfgSysInfo.iDigChannel.ToString();
                            textBox1SystemVersion.Text = cfgSysInfo.sSoftWareVersion;

                            StringBuilder strTime;
                            strTime = new StringBuilder();
                            strTime.AppendFormat("{0:d}-{1:d}-{2:d} {3:d}:{4:d}:{5:d}", cfgSysInfo.tmBuildTime.year,
                                cfgSysInfo.tmBuildTime.month, cfgSysInfo.tmBuildTime.day, cfgSysInfo.tmBuildTime.hour,
                                cfgSysInfo.tmBuildTime.minute, cfgSysInfo.tmBuildTime.second);

                            textBoxReleaseDate.Text = strTime.ToString();
                            break;
                        }
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI:
                        {
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_NetWifiConfig));
                            bufPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_NetWifiConfig)));
                            int nRet = XMSDK.H264_DVR_GetDevConfig(nLoginID, nConfig, nChannel, bufPtr, nBufSize, out nOutSize, 1000);
                            if (nRet < 0)
                            {
                                MessageBox.Show("Get config error!");
                                return;
                            }

                            curcfgWifi = (SDK_NetWifiConfig)Marshal.PtrToStructure(bufPtr, typeof(SDK_NetWifiConfig));

                            checkEnableWifi.Checked = Convert.ToBoolean(curcfgWifi.bEnable);

                            bool bWifiEnable = checkEnableWifi.Checked;
                            comboBoxWifiEntryType.Enabled = bWifiEnable;
                            if (!checkBoxDHCP.Checked)
                            {
                                textBoxWifiIP.Enabled = bWifiEnable;
                                textBoxWifiSubmask.Enabled = bWifiEnable;
                                textBoxWifiGateway.Enabled = bWifiEnable;
                            } 
                            

                            StringBuilder strIP, strSubMask, strGateway;
                            strIP = new StringBuilder();
                            strIP.AppendFormat("{0:d}.{1:d}.{2:d}.{3:d}", (int)curcfgWifi.HostIP.c[0], (int)curcfgWifi.HostIP.c[1], (int)curcfgWifi.HostIP.c[2], (int)curcfgWifi.HostIP.c[3]);
                            strSubMask = new StringBuilder();
                            strSubMask.AppendFormat("{0:d}.{1:d}.{2:d}.{3:d}", (int)curcfgWifi.Submask.c[0], (int)curcfgWifi.Submask.c[1], (int)curcfgWifi.Submask.c[2], (int)curcfgWifi.Submask.c[3]);
                            strGateway = new StringBuilder();
                            strGateway.AppendFormat("{0:d}.{1:d}.{2:d}.{3:d}", (int)curcfgWifi.Gateway.c[0], (int)curcfgWifi.Gateway.c[1], (int)curcfgWifi.Gateway.c[2], (int)curcfgWifi.Gateway.c[3]);

                            textBoxWifiIP.Text = strIP.ToString();
                            textBoxWifiSubmask.Text = strSubMask.ToString();
                            textBoxWifiGateway.Text = strGateway.ToString();
                            textBoxWifiPassword.Text = curcfgWifi.sKeys;
                            textBoxSSID.Text = curcfgWifi.sSSID;
                            comboBoxWifiEntryType.Items.Clear();
                            comboBoxWifiEntryType.Items.Add(curcfgWifi.sEncrypType);
                            comboBoxWifiEntryType.SelectedIndex = 0;
                            comboBoxWifiKeyType.SelectedIndex = 1;

                            if (curcfgWifi.sEncrypType == "WEP")
                            {
                                comboBoxWifiKeyType.SelectedIndex = curcfgWifi.nKeyType;
                                comboBoxWifiKeyType.Show();
                                labelKeyType.Show();
                            }
                            else
                            {
                                comboBoxWifiKeyType.Hide();
                                labelKeyType.Hide();
                            }

                            checkBoxDHCP.Checked = false;
                            textBoxWifiIP.Enabled = true;
                            textBoxWifiSubmask.Enabled = true;
                            textBoxWifiGateway.Enabled = true;
                            break;
                        }
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_DHCP:
                        {
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_NetDHCPConfigAll));
                            bufPtr = Marshal.AllocHGlobal((int)nBufSize);
                            int nRet = XMSDK.H264_DVR_GetDevConfig(nLoginID, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_DHCP, -1, bufPtr, nBufSize, out nOutSize, 1000);
                            if (nRet > 0)
                            {
                                SDK_NetDHCPConfigAll dhcpAll = new SDK_NetDHCPConfigAll();
                                dhcpAll = (SDK_NetDHCPConfigAll)Marshal.PtrToStructure(bufPtr, typeof(SDK_NetDHCPConfigAll));
                                curDHCPcfgAll = dhcpAll;

                                if (Convert.ToBoolean(dhcpAll.vNetDHCPConfig[2].bEnable))
                                {
                                    checkBoxDHCP.Checked = true;
                                    textBoxWifiIP.Enabled = false;
                                    textBoxWifiSubmask.Enabled = false;
                                    textBoxWifiGateway.Enabled = false;
                                }

                            }
                            break;
                        }
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI_AP_LIST:
                        {
                           
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_NetWifiDeviceAll));
                            bufPtr = Marshal.AllocHGlobal((int)nBufSize);
                            int nRet = XMSDK.H264_DVR_GetDevConfig(nLoginID, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI_AP_LIST, -1, bufPtr, nBufSize, out nOutSize, 5000);


                            if (nRet >= 0)
                            {
                                listViewWifi.Items.Clear();

                                SDK_NetWifiDeviceAll wifiDeviAll = new SDK_NetWifiDeviceAll();
                                wifiDeviAll = (SDK_NetWifiDeviceAll)Marshal.PtrToStructure(bufPtr, typeof(SDK_NetWifiDeviceAll));
                                for (int i = 0; i < wifiDeviAll.nDevNumber; i++)
                                {

                                    string strRSSI;
                                    switch (wifiDeviAll.vNetWifiDeviceAll[i].nRSSI)
                                    {
                                        case (int)SDK_RSSI_SINGNAL.SDK_RSSI_NO_SIGNAL:
                                            strRSSI = "ConfigNet.NoSignal";
                                            break;
                                        case (int)SDK_RSSI_SINGNAL.SDK_RSSI_VERY_LOW:
                                            strRSSI = "VeryLow";
                                            break;
                                        case (int)SDK_RSSI_SINGNAL.SDK_RSSI_LOW:
                                            strRSSI = "Low";
                                            break;
                                        case (int)SDK_RSSI_SINGNAL.SDK_RSSI_GOOD:
                                            strRSSI = "Good";
                                            break;
                                        case (int)SDK_RSSI_SINGNAL.SDK_RSSI_VERY_GOOD:
                                            strRSSI = "VeryGood";
                                            break;
                                        case (int)SDK_RSSI_SINGNAL.SDK_RSSI_EXCELLENT:
                                            strRSSI = "Excellent";
                                            break;
                                        default:
                                            strRSSI = "NoSignal";
                                            break;
                                    }

                                    SDK_NetWifiDevice wifi = new SDK_NetWifiDevice();
                                    wifi = wifiDeviAll.vNetWifiDeviceAll[i];
                                    ListViewItem item = new ListViewItem(new string[] { wifi.sSSID, wifi.sAuth, strRSSI });

                                    item.Tag = wifi;
                                    listViewWifi.Items.Add(item);
                                }
                            }
                            break;
                        }
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_ABILITY_SYSFUNC:
                        {
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_SystemFunction));
                            bufPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_SystemFunction)));
                            int nRet = XMSDK.H264_DVR_GetDevConfig(nLoginID, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_ABILITY_SYSFUNC, -1, bufPtr, nBufSize, out nOutSize, 2000);

                            if (nRet > 0)
                            {
                                SDK_SystemFunction sysFunction = new SDK_SystemFunction();
                                sysFunction = (SDK_SystemFunction)Marshal.PtrToStructure(bufPtr, typeof(SDK_SystemFunction));
                                if (!Convert.ToBoolean(sysFunction.vNetServerFunction[(int)SDK_NetServerTypes.SDK_NET_SERVER_TYPES_WIFI]))
                                {
                                    tabPageWifi.Hide();
                                }
                                else
                                {
                                    tabPageWifi.Show();
                                }

                            }
                            break;
                        }
                }
          
            }
        }
        SDK_NetWifiConfig curcfgWifi = new SDK_NetWifiConfig();
        private void SaveConfig(int nLoginID, int nChannel, uint nConfig)
        {
            if( nLoginID > 0 )
            {
                uint nBufSize = 0;
                uint nOutSize = 0;
                switch (nConfig)
                {
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_SYSNORMAL:
                        {
                             nBufSize = (uint)Marshal.SizeOf(typeof(SDK_CONFIG_NORMAL));
                            SDK_CONFIG_NORMAL configNormal = new SDK_CONFIG_NORMAL();
                            configNormal.iDateSeparator = comboBoxDateSeparator.SelectedIndex;
                            configNormal.iDSTRule = 0;
                           // configNormal.iLanguage = 0;
                            configNormal.iLocalNo = System.Int32.Parse(textBoxDeviceNo.Text);
                            configNormal.iOverWrite = comboBoxDiskFullTo.SelectedIndex;
                            configNormal.iVideoFormat = comboBoxVideoStandard.SelectedIndex;
                            configNormal.iVideoStartOutPut = 0;
                            configNormal.sMachineName = textBoxDeviceName.Text;
                            configNormal.iWorkDay = System.Int32.Parse(textBoxStandbyTime.Text);
                            configNormal.iTimeFormat = comboBoxTimeFormat.SelectedIndex;
                            configNormal.iDateFormat = comboBoxDateFormat.SelectedIndex;
                           
                            IntPtr ptrBuf =  Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_CONFIG_NORMAL)));


                            Marshal.StructureToPtr(configNormal, ptrBuf, false);
                            int nRet = XMSDK.H264_DVR_SetDevConfig(nLoginID, nConfig, nChannel, ptrBuf, nBufSize, 5000);
                            if (nRet < 0)
                            {
                                if (nRet == (int)SDK_RET_CODE.H264_DVR_OPT_REBOOT)
                                {
                                    MessageBox.Show("Need reboot device!");
                                }
                                else
                                {
                                    MessageBox.Show("Save config error!");
                                }
                            }
                            else
                            {
                                MessageBox.Show("Save config OK!");
                            }
                            break;
                        }

                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI:
                        {
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_NetWifiConfig));


                            curcfgWifi.bEnable = Convert.ToByte(checkEnableWifi.Checked);
                            curcfgWifi.sSSID = textBoxSSID.Text;
                            curcfgWifi.nKeyType = 1;  //默认是ASCII
                            curcfgWifi.sKeys = textBoxWifiPassword.Text;
                            curcfgWifi.nChannel = 0;

                            //对WEP加密方式，限制条件
                            if (Convert.ToBoolean(curcfgWifi.bEnable))
                            {
                                if (comboBoxWifiEntryType.SelectedItem != null)
                                {
                                    curcfgWifi.sEncrypType = comboBoxWifiEntryType.SelectedItem.ToString();
                                    if (curcfgWifi.sEncrypType == "WEP")
                                    {
                                        curcfgWifi.nKeyType = comboBoxWifiKeyType.SelectedIndex;
                                    }
                                }
                            }

                            string strIP, strMask, strGateway;
                            strIP = textBoxWifiIP.Text;
                            char[] ch = { '.' };
                            string[] arrIP = strIP.Split(ch, StringSplitOptions.RemoveEmptyEntries);
                            if (arrIP.GetLength(0) == 4)
                            {
                               
                                byte[] byIP = { byte.Parse(arrIP[0]), byte.Parse(arrIP[1]), byte.Parse(arrIP[2]),byte.Parse(arrIP[3])};
                                curcfgWifi.HostIP.c = byIP;
                            }
                            strMask = textBoxWifiSubmask.Text;
                            string[] arrMask = strMask.Split(ch, StringSplitOptions.RemoveEmptyEntries);
                            if (arrMask.GetLength(0) == 4)
                            {

                                byte[] byMask = { byte.Parse(arrMask[0]), byte.Parse(arrMask[1]), byte.Parse(arrMask[2]), byte.Parse(arrMask[3]) };
                                curcfgWifi.Submask.c = byMask;
                            }

                            strGateway = textBoxWifiGateway.Text;
                            string[] arrGateway = strGateway.Split(ch, StringSplitOptions.RemoveEmptyEntries);
                            if (arrGateway.GetLength(0) == 4)
                            {

                                byte[] byGateway = { byte.Parse(arrGateway[0]), byte.Parse(arrGateway[1]), byte.Parse(arrGateway[2]), byte.Parse(arrGateway[3]) };
                                curcfgWifi.Gateway.c = byGateway;
                            }


                            if (curWifiDevice.sAuth != null && curWifiDevice.sNetType != null) //有修改
                            {
                                curcfgWifi.sAuth = curWifiDevice.sAuth;
                                curcfgWifi.sNetType = curWifiDevice.sNetType;
                            }

                            IntPtr ptrBufWifi = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_NetWifiConfig)));


                            Marshal.StructureToPtr(curcfgWifi, ptrBufWifi, false);
                            int nRet = XMSDK.H264_DVR_SetDevConfig(nLoginID, nConfig, nChannel, ptrBufWifi, nBufSize, 5000);
                            if (nRet < 0)
                            {
                                if (nRet == (int)SDK_RET_CODE.H264_DVR_OPT_REBOOT)
                                {
                                    MessageBox.Show("Need reboot device!");
                                }
                                else
                                {
                                    MessageBox.Show("Save config error!");
                                }
                            }
                            else
                            {
                                MessageBox.Show("Save config OK!");
                            }
                            break;
                        }
                    case (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_DHCP:
                        {
                            nBufSize = (uint)Marshal.SizeOf(typeof(SDK_NetDHCPConfigAll));
                            SDK_NetWifiConfig cfgWifi = new SDK_NetWifiConfig();
                            //if( checkBoxDHCP.Enabled )
                            {
                                curDHCPcfgAll.vNetDHCPConfig[2].bEnable = Convert.ToByte(checkBoxDHCP.Checked);
                            }


                            IntPtr ptrBufDHCP = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(SDK_NetWifiConfig)));


                            Marshal.StructureToPtr(curDHCPcfgAll, ptrBufDHCP, false);
                            int nRet = XMSDK.H264_DVR_SetDevConfig(nLoginID, nConfig, nChannel, ptrBufDHCP, nBufSize, 1000);
                            if (nRet < 0)
                            {
                                if (nRet == (int)SDK_RET_CODE.H264_DVR_OPT_REBOOT)
                                {
                                    MessageBox.Show("Need reboot device!");
                                }
                                else
                                {
                                    MessageBox.Show("Save config error!");
                                }
                            }
                            else
                            {
                               // MessageBox.Show("Save config OK!");
                            }
                          
                            break;
                        }
                }
            }
            
        }

        private void buttongGeneralOk_Click(object sender, EventArgs e)
        {
            TreeNode node = (TreeNode)comboBoxDevice.SelectedItem;
            if ( node.Tag != null )
            {
                DEV_INFO devInfo = (DEV_INFO)node.Tag;
                int nLoginID = devInfo.lLoginID;
                int nChannel = -1;
                TabPage tab = tabControlConfigs.SelectedTab;
                uint nConfig = 0;
                if (tab.Name == "tabPageGeneral")
                {
                    nConfig = (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_SYSNORMAL;
                }
                if (nConfig != 0)
                {
                    SaveConfig(nLoginID, nChannel, nConfig);
                }
            }
        }

        private void tabControlConfigs_Selected(object sender, TabControlEventArgs e)
        {
            uint nConfig = 0;
            TreeNode node = (TreeNode)comboBoxDevice.SelectedItem;
            if (node.Tag != null)
            {
                DEV_INFO devInfo = (DEV_INFO)node.Tag;
                int nLoginID = devInfo.lLoginID;
                int nChannel = -1;

                TabPage tab = tabControlConfigs.SelectedTab;
                if (tab.Name == "tabPageGeneral")
                {
                    nConfig = (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_SYSNORMAL;
                }
                else if (tab.Name == "tabPageWifi")
                {
                    nConfig = (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI;
                    UpdateConfig(nLoginID, nChannel, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_DHCP);
                }

                if (nConfig != 0)
                {
                    UpdateConfig(nLoginID, nChannel, nConfig);
                }
            }
          
        }

        private void buttonSearchWifi_Click(object sender, EventArgs e)
        {
            TreeNode node = (TreeNode)comboBoxDevice.SelectedItem;
            if (node.Tag != null)
            {
                DEV_INFO devInfo = (DEV_INFO)node.Tag;
                int nLoginID = devInfo.lLoginID;
                int nChannel = -1;

                UpdateConfig(nLoginID, nChannel, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI_AP_LIST);
            }
        }

        private void checkBoxDHCP_CheckedChanged(object sender, EventArgs e)
        {
            bool bDHCPChecked= checkBoxDHCP.Checked;
            textBoxWifiIP.Enabled = !bDHCPChecked;
            textBoxWifiSubmask.Enabled = !bDHCPChecked;
            textBoxWifiGateway.Enabled = !bDHCPChecked;
        }

        private void checkEnableWifi_CheckedChanged(object sender, EventArgs e)
        {
            bool bWifiEnable = checkEnableWifi.Checked;
            comboBoxWifiEntryType.Enabled = bWifiEnable;
            if (!checkBoxDHCP.Checked)
            {
                textBoxWifiIP.Enabled = bWifiEnable;
                textBoxWifiSubmask.Enabled = bWifiEnable;
                textBoxWifiGateway.Enabled = bWifiEnable;
            } 
        }

        private void listViewWifi_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            ListView.SelectedListViewItemCollection itemcollection = listViewWifi.SelectedItems;
            foreach (ListViewItem itemseleted in itemcollection)
            {
               
                if (itemseleted.Tag != null)
                {
                    SDK_NetWifiDevice wifiDevice = (SDK_NetWifiDevice)itemseleted.Tag;
                    curWifiDevice = wifiDevice;

                    textBoxSSID.Text = wifiDevice.sSSID;
                    comboBoxWifiEntryType.Items.Clear();
                    comboBoxWifiEntryType.Items.Add(wifiDevice.sEncrypType);
                    comboBoxWifiEntryType.SelectedIndex = 0 ;
                    if (wifiDevice.sEncrypType == "WEP")
                    {
                        comboBoxWifiKeyType.SelectedIndex = 0;
                        comboBoxWifiKeyType.Show();
                        labelKeyType.Show();
                    }
                    else
                    {
                        labelKeyType.Hide();
                        comboBoxWifiKeyType.Hide();
                    }
                    break;
                }
            }
        }
        SDK_NetWifiDevice curWifiDevice;

        private void buttonWifiOK_Click(object sender, EventArgs e)
        {
             TreeNode node = (TreeNode)comboBoxDevice.SelectedItem;
            if ( node.Tag != null )
            {
                DEV_INFO devInfo = (DEV_INFO)node.Tag;
                int nLoginID = devInfo.lLoginID;
                int nChannel = -1;
                TabPage tab = tabControlConfigs.SelectedTab;
                uint nConfig = 0;
                if (tab.Name == "tabPageWifi")
                {
                    nConfig = (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_WIFI;
                    SaveConfig(nLoginID, nChannel, (uint)SDK_CONFIG_TYPE.E_SDK_CONFIG_NET_DHCP);
                }
                if (nConfig != 0)
                {
                    SaveConfig(nLoginID, nChannel, nConfig);
                }
            }
        }
    }
}