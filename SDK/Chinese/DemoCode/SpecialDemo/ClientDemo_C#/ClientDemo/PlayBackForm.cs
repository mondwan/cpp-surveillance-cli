using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using System.Threading;
namespace ClientDemo
{
    public class ComboxItem
    {
        public string Text = "";

        public object Value = new object() ;
        public ComboxItem(string _Text, object _Value)
        {
            Text = _Text;
            Value = _Value;
        }

        public override string ToString()
        {
            return Text;
        }
    }


    public partial class PlayBackForm : Form
    {
        enum PlayBackFileType
        {
            SDK_RECORD_ALL = 0,
            SDK_RECORD_ALARM = 1, //外部报警录像
            SDK_RECORD_DETECT,	  //视频侦测录像
            SDK_RECORD_REGULAR,	  //普通录像
            SDK_RECORD_MANUAL,	  //手动录像
            SDK_PIC_ALL = 10,
            SDK_PIC_ALARM,		  //外部报警录像
            SDK_PIC_DETECT,		  //视频侦测录像
            SDK_PIC_REGULAR,      //普通录像
            SDK_PIC_MANUAL,       //手动录像
            SDK_TYPE_NUM
        }

        enum PlayBackAction
        {
            SDK_PLAY_BACK_PAUSE,		/*<! 暂停回放 */
            SDK_PLAY_BACK_CONTINUE,		/*<! 继续回放 */
            SDK_PLAY_BACK_SEEK,			/*<! 回放定位，时间s为单位 */
            SDK_PLAY_BACK_FAST,	        /*<! 加速回放 */
            SDK_PLAY_BACK_SLOW,	        /*<! 减速回放 */
            SDK_PLAY_BACK_SEEK_PERCENT, /*<! 回放定位百分比 */
        };

        int m_lLoginID = 0;
        static int PLAYBACK_MAX_FILE_NUM = 100;
        System.Timers.Timer timerLocalPlayBack = new System.Timers.Timer(200);
        System.Timers.Timer timerNetPlayBack = new System.Timers.Timer(200);
        System.Timers.Timer timerDownload = new System.Timers.Timer(200);

        bool m_bPauseLocalPlay = false;  // 暂停标志
        bool m_bPauseNetPlay = false;
        int m_nFastTypeLocal = 0; //本地快播速度    
        int m_nFastTypeNet = 0; //网络快播速度  
        int m_nSlowTypeLocal = 0;  // 网络慢波速度
        int m_nSlowTypeNet = 0;  // 网络慢波速度
       
	    bool m_bDownloadByTime = false;
	    bool m_bDownloadByName = true;
	    uint m_nPlaybackDecHandle = 0;
        int m_nLocalplayHandle = 0;   
	    int m_nNetPlayHandle = 0;
	    int m_DownLoadFileHandle = 0;
        Thread thread;
	   // bool m_bPause = false;
	    int m_nCurRecNum=0;	
	    int m_ListFindNum=0;
        int m_SliderPos = 0;
	    long m_PreTime = 0;
        
        H264_DVR_FINDINFO m_nSearchInfo = new H264_DVR_FINDINFO();
        List<H264_DVR_FILE_DATA> m_listFile = new List<H264_DVR_FILE_DATA>();
        List<H264_DVR_FINDINFO> m_listFindInfo = new List<H264_DVR_FINDINFO>();
             

        int   m_nGetPage = 0;
        int   m_nCurPage = -1;
        int   m_nTotalPage = -1;
      
        bool m_bOpenAudio = false;



        public delegate int NetDataCallBack_V2(int lRealHandle, ref PACKET_INFO_EX pFrame, int dwUser);
        public delegate void SDKDownLoadPosCallback( int lPlayHandle, int lTotalSize, int lDownLoadSize, int dwUser );

        private int NetCallBack_V2(int lRealHandle, ref PACKET_INFO_EX pFrame, int dwUser)
        {	

            //bool bResult = ;
            //try
            //{

            //        if (bResult)
            //        {
            //            return bResult;
            //        }	
            //}

            return 0;
        	
        }

         private void DownLoadPosCallback ( int lPlayHandle, 
														   int lTotalSize, 
														   int lDownLoadSize, 
														   int dwUser)
        {	         	
	        if ( 0xfffffff == lDownLoadSize )
	        {
                this.pictureBoxNetVideoWnd.Refresh();	
		        progressBarDownloadPos.Value = 0;
                timerDownload.Stop();
	        }
        }

        private int RealDataCallBack(int lRealHandle, int dwDataType, string strBuf, int lbufsize, int dwUser)
        {
            m_nNetPlayHandle = 0;
            return 0;
        }

        public PlayBackForm()
        {
            InitializeComponent();
            trackBarLocalPlayPos.SetRange(0, 1000);
            trackBarNetPlayPos.SetRange(0, 1000);
            beginTime.Value = System.DateTime.Now.Date;
            
        }


        void FileEndCallBack(uint lPlayHand, uint nUser)
        {
            if (XMSDK.H264_DVR_StopLocalPlay(m_nLocalplayHandle))
            {
                m_nLocalplayHandle = 0;
            }
            timerLocalPlayBack.Enabled = false;
            trackBarLocalPlayPos.Value = 0;
        }

        public void recordTime(object source,System.Timers.ElapsedEventArgs e)
        {
            if (!m_bPauseLocalPlay)
            { 
                float pos = XMSDK.H264_DVR_GetPlayPos(m_nLocalplayHandle);
                trackBarLocalPlayPos.Value = Convert.ToInt32(pos*1000);
            }
 
            if (!m_bPauseNetPlay)
            {
                float pos = XMSDK.H264_DVR_GetPlayPos(m_nNetPlayHandle);
                trackBarNetPlayPos.Value = Convert.ToInt32(pos * 1000);
            }

            if (m_DownLoadFileHandle != 0)
            {
                int nPos = XMSDK.H264_DVR_GetDownloadPos(m_DownLoadFileHandle);
                if (nPos < 0)		//fail
                {
                    XMSDK.H264_DVR_StopGetFile(m_DownLoadFileHandle);
                    progressBarDownloadPos.Value = 0;
                    m_DownLoadFileHandle = 0;
                    btnDownload.Text = "Download";
                    MessageBox.Show("Get download process fail !");
                    timerDownload.Stop();
                    
                }
                if (nPos == 100)		//download end
                {
                    XMSDK.H264_DVR_StopGetFile(m_DownLoadFileHandle);
                    m_DownLoadFileHandle = 0;

                    timerDownload.Stop();
                    progressBarDownloadPos.Value = 0;
                    btnDownload.Text = "Download";
                    MessageBox.Show("Download Finished");
                    return;

                }
                if (nPos > 100)		//abnormal
                {
                    XMSDK.H264_DVR_StopGetFile(m_DownLoadFileHandle);
                    m_DownLoadFileHandle = 0;
                    progressBarDownloadPos.Value = 0;
                    btnDownload.Text = "Download";
                    MessageBox.Show("Download Error");
                }
                else
                {
                    progressBarDownloadPos.Value = nPos;
                }
            }
            
         }


        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            // fileDialog.InitialDirectory = "d:\\";
            fileDialog.Title = "选择文件";
            fileDialog.Filter = "h264 files (*.h264)|*.h264";
            fileDialog.FilterIndex = 1;
            fileDialog.RestoreDirectory = true;

            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                String fileName = fileDialog.FileName;
                // 使用文件名
                m_nLocalplayHandle =  Convert.ToInt32(XMSDK.H264_DVR_StartLocalPlay( fileName, pictureBoxVideoWnd.Handle,null,Convert.ToUInt32(0) ));
                if ( m_nLocalplayHandle > 0)
                {
                 //   MessageBox.Show("success");
                    timerLocalPlayBack.Elapsed += new System.Timers.ElapsedEventHandler(recordTime);
                    timerLocalPlayBack.AutoReset = true;
                    timerLocalPlayBack.Enabled = true;
                    XMSDK.fLocalPlayFileCallBack fileEndCallBack = new XMSDK.fLocalPlayFileCallBack(FileEndCallBack);
                    XMSDK.H264_DVR_SetFileEndCallBack(m_nLocalplayHandle,fileEndCallBack, this.Handle );
                }
                else
                {
                    MessageBox.Show("failed");
                }
            }
            else
            {
                // 没有选择文件时的操作
            } 

        }

        private void btnLocalStop_Click(object sender, EventArgs e)
        {
            if (XMSDK.H264_DVR_StopLocalPlay(m_nLocalplayHandle))
            {
                m_nLocalplayHandle = 0;
            }
            timerLocalPlayBack.Enabled = false;
            trackBarLocalPlayPos.Value = 0;
        }

        private void btnLocalPause_Click(object sender, EventArgs e)
        {
            if (XMSDK.H264_DVR_LocalPlayCtrl(m_nLocalplayHandle, SDK_LoalPlayAction.SDK_Local_PLAY_PAUSE, 0))
            {
                m_bPauseLocalPlay = true;
            }
        }

        private void btnLocalFast_Click(object sender, EventArgs e)
        {
            if (++m_nFastTypeLocal > 4)
            {
                m_nFastTypeLocal = 1;
            }
            m_nSlowTypeLocal = 0;
            XMSDK.H264_DVR_LocalPlayCtrl(m_nLocalplayHandle, SDK_LoalPlayAction.SDK_Local_PLAY_FAST, Convert.ToUInt32(m_nFastTypeLocal));	
        }

        private void btnLocalSlow_Click(object sender, EventArgs e)
        {
            if (++m_nSlowTypeLocal > 4)
            {
                m_nSlowTypeLocal = 1;
            }
            m_nFastTypeLocal = 0;
            XMSDK.H264_DVR_LocalPlayCtrl(m_nLocalplayHandle, SDK_LoalPlayAction.SDK_Local_PLAY_SLOW, Convert.ToUInt32(m_nSlowTypeLocal));	
        }

        private void btnLocalPlay_Click(object sender, EventArgs e)
        {
            if (m_bPauseLocalPlay)
            {
                XMSDK.H264_DVR_LocalPlayCtrl(m_nLocalplayHandle, SDK_LoalPlayAction.SDK_Local_PLAY_CONTINUE, 0);
                m_bPauseLocalPlay = false;
            }

            if (m_nSlowTypeLocal != 0)
            {
                XMSDK.H264_DVR_LocalPlayCtrl(m_nLocalplayHandle, SDK_LoalPlayAction.SDK_Local_PLAY_SLOW, 0);
            }
            if (m_nFastTypeLocal != 0)
            {
                XMSDK.H264_DVR_LocalPlayCtrl(m_nLocalplayHandle, SDK_LoalPlayAction.SDK_Local_PLAY_FAST, 0);
            }
            m_nSlowTypeLocal = 0;
            m_nFastTypeLocal = 0;
	
        }

        private void trackBarPlayPos_Scroll(object sender, EventArgs e)
        {
            int value = trackBarLocalPlayPos.Value;
            XMSDK.H264_DVR_SetPlayPos(m_nLocalplayHandle, (float)(value / 1000.0));
        }


        // 点击网网络的选项卡
        private void tabControlPlayBack_Click(object sender, EventArgs e)
        {
            if (tabControlPlayBack.SelectedTab.Name == "tabPageRemovePlayBack")
            {
                comboDev.Items.Clear();
                ClientDemo clientForm = new ClientDemo();

                foreach (Form form in Application.OpenForms)
                {
                    if (form.Name == "ClientDemo")
                    {
                        clientForm = (ClientDemo)form;
                        break;
                    }
                }

                foreach (TreeNode node in clientForm.devForm.DevTree.Nodes)
                {
                    ComboxItem item = new ComboxItem(node.Text,node.Tag);
                    comboDev.Items.Add(item);
                }

                comboRecordType.Items.Clear();

                comboRecordType.Items.Add("全部录像");
                comboRecordType.Items.Add("外部报警");
                comboRecordType.Items.Add("视频检测");
                comboRecordType.Items.Add("普通录像");
                comboRecordType.Items.Add("手动录像");
                comboRecordType.Items.Add("全部图片");
                comboRecordType.Items.Add("外部报警图片");
                comboRecordType.Items.Add("视频检测图片");
                comboRecordType.Items.Add("普通图片");
                comboRecordType.Items.Add("手动抓图");
                comboRecordType.SelectedIndex = 0;
                
                checkFile.Checked = true;
            }
            else
            {

            }
           
        }

        private void checkFile_CheckedChanged(object sender, EventArgs e)
        {
            if (checkFile.Checked == true)
            {
                checkTime.Checked = false;
                m_bDownloadByTime = false;
                m_bDownloadByName = true;
            }
        }

        private void checkTime_CheckedChanged(object sender, EventArgs e)
        {
            if (checkTime.Checked == true)
            {
                m_bDownloadByTime = true;
                m_bDownloadByName = false;
                checkFile.Checked = false;
            } 

        }

        private void btnSearch_Click(object sender, EventArgs e)
        {


            // 条件检测
           if(comboDev.SelectedIndex < 0)
           {
               MessageBox.Show("Select a Device!");
               return;
           }
           if (!checkFile.Checked && !checkTime.Checked)
           {
               MessageBox.Show("Select a Search mode!");
               return;
           }


           ClearResult();

           H264_DVR_TIME StartTime;
           H264_DVR_TIME StopTime;

           int nChannel = comboChannel.SelectedIndex;	//channel No.
           int nFileType = comboRecordType.SelectedIndex;		//file type

           StartTime.dwYear = beginDate.Value.Year;
           StartTime.dwMonth = beginDate.Value.Month;
           StartTime.dwDay = beginDate.Value.Day;
           StartTime.dwHour = beginTime.Value.Hour;
           StartTime.dwMinute = beginTime.Value.Minute;
           StartTime.dwSecond = beginTime.Value.Second;

           StopTime.dwYear = endDate.Value.Year;
           StopTime.dwMonth = endDate.Value.Month;
           StopTime.dwDay = endDate.Value.Day;
           StopTime.dwHour =endDate.Value.Hour;
           StopTime.dwMinute = endDate.Value.Minute;
           StopTime.dwSecond = endDate.Value.Second;
           H264_DVR_FILE_DATA[] szSend = new H264_DVR_FILE_DATA[100];

           ComboxItem item = (ComboxItem)comboDev.SelectedItem;
         
           if (item.Value != null)
           {
               DEV_INFO devInfo = (DEV_INFO)item.Value;


               int lLoginID = devInfo.lLoginID;
               int nMaxLen = 100;
               int waitTime = 4000;
               int nNum = 0;
               H264_DVR_FINDINFO searchInfo = new H264_DVR_FINDINFO();
               searchInfo.startTime = StartTime;
               searchInfo.endTime = StopTime;
               searchInfo.nChannelN0 = nChannel;
               searchInfo.nFileType = nFileType;


               IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * 100);



               int nRet = XMSDK.H264_DVR_FindFile(lLoginID, ref searchInfo, ptr, nMaxLen, out nNum, waitTime);
               m_nCurRecNum = nNum;

               for (int index = 0; index < 100; index++)
               {
                   unsafe
                   {
                       int* pDev = (int*)ptr.ToPointer();
                       pDev += Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * index / 4;

                       IntPtr ptrTemp = new IntPtr(pDev);
                       szSend[index] = (H264_DVR_FILE_DATA)Marshal.PtrToStructure(ptrTemp, typeof(H264_DVR_FILE_DATA));
                   }

               }

               if ( nRet > 0 )
               {
                   if ( nNum > 0) 
                   {
                       m_nGetPage++;
                       m_nCurPage = 1;
                       if (m_nCurRecNum > m_listFile.Capacity)
                       {
                           m_listFile.Capacity = m_nCurRecNum;
                       }
                       

                       for (int i = 0; i < m_nCurRecNum; i++)
                       {
                           m_listFile.Add(szSend[i]);
                       }

                       m_nSearchInfo.nChannelN0 = nChannel;
                       m_nSearchInfo.nFileType = nFileType;
                       m_nSearchInfo.startTime.dwYear = szSend[m_nCurRecNum - 1].stEndTime.year;
                       m_nSearchInfo.startTime.dwMonth = szSend[m_nCurRecNum - 1].stEndTime.month;
                       m_nSearchInfo.startTime.dwDay = szSend[m_nCurRecNum - 1].stEndTime.day;
                       m_nSearchInfo.startTime.dwHour = szSend[m_nCurRecNum - 1].stEndTime.hour;
                       m_nSearchInfo.startTime.dwMinute = szSend[m_nCurRecNum - 1].stEndTime.minute;
                       m_nSearchInfo.startTime.dwSecond = szSend[m_nCurRecNum - 1].stEndTime.second;
                       m_nSearchInfo.endTime = searchInfo.endTime;

                       if (nNum < PLAYBACK_MAX_FILE_NUM)
                       {
                           m_nTotalPage = m_nGetPage;
                       }

                       AddFileListInfo(m_nCurRecNum);//add list item
                       SetPageBtnState();
                   }
                   else
                   {
                       MessageBox.Show("No File");
                   }
               }
               else
               {
                   MessageBox.Show("SearchFail");
               }
           }

        }
        private void AddFileListInfo(int iNum)
        {
	        if ( m_bDownloadByTime )
	        {
		        iNum = 1;
		        m_nCurPage=1;
	            m_nTotalPage=1;
	        }
            int count = listFile.Items.Count;

	        for ( int i = 0; i < iNum ; i++)
	        {
		     
        		string tempstring = string.Format("{0}", i + 1);


                ListViewItem.ListViewSubItem subitem1 = new ListViewItem.ListViewSubItem();
                subitem1.Text = tempstring;
                subitem1.Name = "No.";

		        string strBtme,strEtime;
		        if ( m_bDownloadByTime )
		        {
                    strBtme = string.Format("{0}-{1}-{2}-{3}:{4}:{5}", beginDate.Value.Year,
                        beginDate.Value.Month,
                        beginDate.Value.Day,
                        beginTime.Value.Hour,
                        beginTime.Value.Minute,
                        beginTime.Value.Second);

                    strEtime = string.Format("{0}-{1}-{2}-{3}:{4}:{5}", endDate.Value.Year, 
				        endDate.Value.Month,
                        endDate.Value.Day,
				        endTime.Value.Hour,
                        endTime.Value.Minute,
                        endTime.Value.Second);
        			
			        tempstring = string.Format("{0}-{1}", strBtme, strEtime);
		        }else
		        {
                    strBtme = string.Format("{0}-{1}-{2}-{3}:{4}:{5}", m_listFile[i].stBeginTime.year, 
				        m_listFile[i].stBeginTime.month,
                        m_listFile[i].stBeginTime.day,
                        m_listFile[i].stBeginTime.hour,
                        m_listFile[i].stBeginTime.minute,
                        m_listFile[i].stBeginTime.second);

                    strEtime = string.Format("{0}-{1}-{2}-{3}:{4}:{5}",
                        m_listFile[i].stEndTime.year,
                        m_listFile[i].stEndTime.month,
                        m_listFile[i].stEndTime.day,
                        m_listFile[i].stEndTime.hour,
                        m_listFile[i].stEndTime.minute,
                        m_listFile[i].stEndTime.second);

                    tempstring = string.Format("{0}-{1}({2}KB)", strBtme, strEtime, m_listFile[i].size);
		        }


        		ListViewItem item = new ListViewItem();
               
                ListViewItem.ListViewSubItem subitem2 = new ListViewItem.ListViewSubItem();
                subitem2.Text = tempstring;
                subitem2.Name = "FileTime";

                item.SubItems.Insert(0,subitem1);
                item.SubItems.Insert(1,subitem2);
                item.Tag = m_listFile[i];

                listFile.Items.Insert(count + i, item); 
 
	        }
        }

        private void SetPageBtnState()
        {
	        if ( m_nTotalPage == -1 || m_nGetPage < m_nTotalPage)
	        {
		        btnNextPage.Enabled = false;
	        }
	        else
	        {
		        if ( m_nCurPage < m_nGetPage )
		        {
                    btnNextPage.Enabled = true;
		        }
		        else
		        {
                    btnNextPage.Enabled = false;
		        }
	        }
        	
	        if ( m_nCurPage > 1 )
	        {
                btnPrePage.Enabled = true;
	        }
	        else
	        {
		        btnPrePage.Enabled = false;
	        }
        }

        private void btnDownload_Click(object sender, EventArgs e)
        {
            int nSelectedIndex = comboDev.SelectedIndex;
            if (nSelectedIndex < 0)
            {
                MessageBox.Show("SelectDevice!");
                return;
            }


            if (!listFile.FocusedItem.Focused)
            {
                MessageBox.Show("Select a File !");
                return;
            }

            timerDownload.Elapsed += new System.Timers.ElapsedEventHandler(recordTime);
            timerDownload.AutoReset = true;
            timerDownload.Enabled = true;


            if (m_bDownloadByTime)
            {
                DownloadByTime();
            }
            else
            {
                DownloadByName();
            }
        }

        private void btnPrePage_Click(object sender, EventArgs e)
        {
            if (m_nGetPage <= 1 || m_nCurPage <= 1)
            {
                return;
            }

            m_nCurPage--;
            m_nGetPage--;

            ClearResult();

            m_ListFindNum = m_ListFindNum - 1;

            if (GetNextPageInfo( m_listFindInfo[--m_ListFindNum]) > 0 )
            {
                H264_DVR_FILE_DATA[] szSend = new H264_DVR_FILE_DATA[100];

                int nNum = 0;

                H264_DVR_FINDINFO findinfo = m_listFindInfo[m_ListFindNum];

                IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * 100);


                int nRet = XMSDK.H264_DVR_FindFile(m_lLoginID,ref findinfo, ptr, 100, out nNum, 5000);

                for (int index = 0; index < 100; index++)
                {
                    unsafe
                    {
                        int* pDev = (int*)ptr.ToPointer();
                        pDev += Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * index / 4;

                        IntPtr ptrTemp = new IntPtr(pDev);
                        szSend[index] = (H264_DVR_FILE_DATA)Marshal.PtrToStructure(ptrTemp, typeof(H264_DVR_FILE_DATA));
                    }

                }


                m_nCurRecNum = nNum;

                if (nRet > 0 && nNum > 0) //处理没有录象的情况
                {
                    if (m_nCurRecNum > m_listFile.Capacity)
                    {
                        m_listFile.Capacity = m_nCurRecNum;
                    }
                    

                    for (int i = 0; i < m_nCurRecNum; i++)
                    {
                        m_listFile.Add(szSend[i]);
                    }
                    //m_nSearchInfo.nChannelN0 = m_nSearchInfo.nChannelN0;
                    //m_nSearchInfo.nFileType = m_nSearchInfo.nFileType;
                    m_nSearchInfo.startTime.dwYear = szSend[m_nCurRecNum - 1].stEndTime.year;
                    m_nSearchInfo.startTime.dwMonth = szSend[m_nCurRecNum - 1].stEndTime.month;
                    m_nSearchInfo.startTime.dwDay = szSend[m_nCurRecNum - 1].stEndTime.day;
                    m_nSearchInfo.startTime.dwHour = szSend[m_nCurRecNum - 1].stEndTime.hour;
                    m_nSearchInfo.startTime.dwMinute = szSend[m_nCurRecNum - 1].stEndTime.minute;
                    m_nSearchInfo.startTime.dwSecond = szSend[m_nCurRecNum - 1].stEndTime.second;
                    m_nSearchInfo.endTime = m_listFindInfo[m_ListFindNum].endTime;

                    m_ListFindNum++;
                }
                else
                {
                   
                }
                AddFileListInfo(m_nCurRecNum);
                SetPageBtnState();
            }
        }
        private int GetNextPageInfo(H264_DVR_FINDINFO searchInfo)
        {
	        H264_DVR_FILE_DATA[] szSend = new H264_DVR_FILE_DATA[100];
	        int nNum=0;


            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * 100);


            int ret = XMSDK.H264_DVR_FindFile(m_lLoginID, ref searchInfo, ptr ,100, out nNum, 5000);

            //for (int index = 0; index < 100; index++)
            //{
            //    unsafe
            //    {
            //        int* pDev = (int*)ptr.ToPointer();
            //        pDev += Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * index / 4;

            //        IntPtr ptrTemp = new IntPtr(pDev);
            //        szSend[index] = (H264_DVR_FILE_DATA)Marshal.PtrToStructure(ptrTemp, typeof(H264_DVR_FILE_DATA));
            //    }

            //}
	       
        	
	        return ret;
        }

        private void btnNextPage_Click(object sender, EventArgs e)
        {
            if (m_nGetPage <= 0)
            {
                return;
            }

            if ((m_nTotalPage != -1) && (m_nCurPage == m_nTotalPage))
            {
                SetPageBtnState();
                return;
            }

            ClearResult();

            if (GetNextPageInfo(m_nSearchInfo) > 0 && (m_nCurPage == m_nGetPage))
            {
                H264_DVR_FILE_DATA[] szSend = new H264_DVR_FILE_DATA[100];

                int nNum = 0;

                IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * 100);

                int nRet = XMSDK.H264_DVR_FindFile(m_lLoginID, ref m_nSearchInfo, ptr, 100, out nNum, 5000);

                for (int index = 0; index < 100; index++)
                {
                    unsafe
                    {
                        int* pDev = (int*)ptr.ToPointer();
                        pDev += Marshal.SizeOf(typeof(H264_DVR_FILE_DATA)) * index / 4;

                        IntPtr ptrTemp = new IntPtr(pDev);
                        szSend[index] = (H264_DVR_FILE_DATA)Marshal.PtrToStructure(ptrTemp, typeof(H264_DVR_FILE_DATA));
                    }

                }
	       
          
                m_nCurRecNum = nNum;

                if (nRet > 0 && nNum > 0)  //处理没有录象的情况
                {
                    m_nGetPage++;

                    m_listFindInfo[m_ListFindNum++] = m_nSearchInfo;

                    if (m_nCurRecNum > m_listFile.Capacity)
                    {
                        m_listFile.Capacity = m_nCurRecNum;
                    }
                    

                    for (int i = 0; i < m_nCurRecNum; i++)
                    {
                        m_listFile.Add(szSend[i]);
                    }

                    //m_nSearchInfo.nChannelN0 = m_nSearchInfo.nChannelN0;
                    //m_nSearchInfo.nFileType = m_nSearchInfo.nFileType;
                    m_nSearchInfo.startTime.dwYear = szSend[m_nCurRecNum - 1].stEndTime.year;
                    m_nSearchInfo.startTime.dwMonth = szSend[m_nCurRecNum - 1].stEndTime.month;
                    m_nSearchInfo.startTime.dwDay = szSend[m_nCurRecNum - 1].stEndTime.day;
                    m_nSearchInfo.startTime.dwHour = szSend[m_nCurRecNum - 1].stEndTime.hour;
                    m_nSearchInfo.startTime.dwMinute = szSend[m_nCurRecNum - 1].stEndTime.minute;
                    m_nSearchInfo.startTime.dwSecond = szSend[m_nCurRecNum - 1].stEndTime.second;
                    //m_nSearchInfo.endTime = m_nSearchInfo.endTime;

                    if (m_nCurRecNum < PLAYBACK_MAX_FILE_NUM)
                    {
                        m_nTotalPage = m_nGetPage;
                    }

                    m_nCurPage++;

                    AddFileListInfo(m_nCurRecNum);

                    SetPageBtnState();
                }
                else
                {
                   
                }
            }
        }
        
        private void DownloadByName() 
        {

            if (m_DownLoadFileHandle > 0)
	        {
                timerDownload.Stop();
                XMSDK.H264_DVR_StopGetFile(m_DownLoadFileHandle);
                m_DownLoadFileHandle = 0;
		        progressBarDownloadPos.Value = 0;
        		
		        btnDownload.Text = "Download";
        		
		        return;
	        }
        	
	        string csFileName;
        	
            //inCount;
            //if ( nSelected < 0 )
            //{
            //    MessageBox.Show("SelectFile !");
            //    return;
            //}
        	

	        H264_DVR_FILE_DATA FileInfo = (H264_DVR_FILE_DATA)listFile.FocusedItem.Tag;
	      
        	
	        string strSaveName;
	        //strSaveName.Format("c:\\record\\record.h264");
	        int nSelectedIndex = comboDev.SelectedIndex;
	        if ( nSelectedIndex < 0)
	        {
		        MessageBox.Show("SelectDevice !");
		        return;
	        }
            DEV_INFO DevTemp = (DEV_INFO)((ComboxItem)comboDev.SelectedItem).Value;
        	
	        string strInitDir;

            strInitDir = Application.StartupPath;
	        if (strInitDir.EndsWith("\\")) 
	        {
		        strInitDir += "Download";
	        }
	        else
	        {
		        strInitDir += "\\Download";
	        }

            DirectoryInfo dir = new DirectoryInfo(strInitDir);

	        //if ( dir.Attributes ) 
	        {
		        dir.Create();
	        }
        	
	        string strFileTpye = "h264";
            string strFileName = FileInfo.sFileName;
	        if ( strFileName.EndsWith(".h264") )
	        {
		        strFileTpye = "h264";
	        }
	        else
	        {
		        strFileTpye = "jpg";
	        }
	        strFileName = string.Format("{0}_{1}_{2}{3}_{4}{5}{6}.{7}",
                DevTemp.szDevName, FileInfo.ch + 1, 
		        FileInfo.stBeginTime.year, FileInfo.stBeginTime.month,
		        FileInfo.stBeginTime.day, FileInfo.stBeginTime.hour,
		        FileInfo.stBeginTime.minute, FileInfo.stBeginTime.second, strFileTpye);

            SaveFileDialog dlg = new SaveFileDialog();
            dlg.AddExtension = true;
            dlg.CheckPathExists = true;
            dlg.DefaultExt = ".h264";
            dlg.Filter = "All File(*.h264;*.jpg)|*.*||";
            dlg.InitialDirectory = strInitDir;		//默认路径
            dlg.ShowDialog();
            
            if( dlg.DereferenceLinks )
            {
            
		        strSaveName = dlg.FileName;
		        //m_lSaveHandle = H264_DVR_GetFileByName(m_lLoginID, pstrFileInfo,strSaveName.GetBuffer(0),SDKDownLoadPosCallback,(DWORD)this);
                m_DownLoadFileHandle = XMSDK.H264_DVR_GetFileByName(m_lLoginID, ref FileInfo, strSaveName, null, 0);
                if (m_DownLoadFileHandle >= 0)
		        {
			        progressBarDownloadPos.Value = 0;
			        btnDownload.Text = "Stop";
			        //update the progress control
                    //SetTimer(1,0,NULL);
		        }
		        else
		        {
		            string sTemp =  string.Format("dowload fail ERROR = {0}",XMSDK.H264_DVR_GetLastError());
                    MessageBox.Show(sTemp);
		        }
            }
        }

        private void DownloadByTime() 
        {

            if (m_DownLoadFileHandle > 0)
	        {
                timerDownload.Stop();
                XMSDK.H264_DVR_StopGetFile(m_DownLoadFileHandle);
                m_DownLoadFileHandle = 0;
                progressBarDownloadPos.Value = 0;
        		
		        btnDownload.Text = "Download";
        		
		        return;
	        }
        	
	        string strSaveName = "";
	        //strSaveName.Format("c:\\record");
	        strSaveName = BrowseForFolder(this.Handle) ;
        	
	        if ( strSaveName == "")  //未选择路径时退出
	        {
		        return;
	        }

	        H264_DVR_FINDINFO info = new H264_DVR_FINDINFO();
        
	        info.nChannelN0 = comboChannel.SelectedIndex;	//channel No.
	        info.nFileType = comboRecordType.SelectedIndex;		//file type
	        info.startTime.dwYear = beginDate.Value.Year;
            info.startTime.dwMonth = beginDate.Value.Month;
            info.startTime.dwDay = beginDate.Value.Day;
	        info.startTime.dwHour = beginTime.Value.Hour;
            info.startTime.dwMinute = beginTime.Value.Minute;
            info.startTime.dwSecond = beginTime.Value.Second;
	        info.endTime.dwYear = endDate.Value.Year;
            info.endTime.dwMonth = endDate.Value.Month;
	        info.endTime.dwDay = endDate.Value.Day;
	        info.endTime.dwHour = endTime.Value.Hour;
            info.endTime.dwMinute = endTime.Value.Minute;
            info.endTime.dwSecond = endTime.Value.Second;
	        int nRecordFileType = comboRecordType.SelectedIndex;
            info.nFileType = (nRecordFileType <= (int)PlayBackFileType.SDK_RECORD_MANUAL) ? nRecordFileType : ((int)PlayBackFileType.SDK_PIC_ALL + nRecordFileType - (int)PlayBackFileType.SDK_RECORD_MANUAL - 1);

            m_DownLoadFileHandle = XMSDK.H264_DVR_GetFileByTime(m_lLoginID, ref info, strSaveName, false, null, 0);
            if (m_DownLoadFileHandle > 0)
	        {
              progressBarDownloadPos.Value = 0;
        		
		      btnDownload.Text = "Stop";
        		
		        //update the progress control
              timerDownload.Start();
	        }
	        else
	        {
		        string sTemp;
		        sTemp = string.Format("dowload fail ERROR = {0}",XMSDK.H264_DVR_GetLastError());
                MessageBox.Show(sTemp);
	        }
        }

        private string BrowseForFolder(IntPtr ptrWnd)
        {
            string strTitle = "Select a folder";
            string strDisplayName = "";
            string strPath  = "";

            FolderBrowserDialog folderDlg = new FolderBrowserDialog();
            folderDlg.ShowNewFolderButton = true;
            folderDlg.ShowDialog();
            
            return folderDlg.SelectedPath;
        }
        private void comboChannel_SelectedIndexChanged(object sender, EventArgs e)
        {
            //DEV_INFO devInfo = new DEV_INFO();
            //ListViewItem selecteditem = (ListViewItem)comboDev.SelectedItem;

            //devInfo = (DEV_INFO)selecteditem.Tag;

            //for (int i = 0; i < devInfo.NetDeviceInfo.byChanNum + devInfo.NetDeviceInfo.iDigChannel; i++)
            //{
            //    comboChannel.Items.Add(i + 1);
            //}
            //comboChannel.SelectedIndex = 0;
        }

        private void btnNetPlayStop_Click(object sender, EventArgs e)
        {
            timerNetPlayBack.Enabled = false;
            if (m_nNetPlayHandle >= 0)
            {
                XMSDK.H264_DVR_StopPlayBack(m_nNetPlayHandle);
                m_nNetPlayHandle = 0;
            }
            trackBarNetPlayPos.Value = 0;
            m_bOpenAudio = false;
            m_bPauseNetPlay = false;    
        }

        private void btnNetPlay_Click(object sender, EventArgs e)
        {
            int nSelectedIndex = comboDev.SelectedIndex;
            if (nSelectedIndex < 0)
            {
                MessageBox.Show("SelectDevice !");
                return;
            }
            timerNetPlayBack.Elapsed += new System.Timers.ElapsedEventHandler(recordTime);
            timerNetPlayBack.AutoReset = true;
            timerNetPlayBack.Enabled = true;

            if (m_bDownloadByTime)
            {
                PlayByTime();
            }
            else
            {
                PlayByName();
            }
        }
        private void  PlayByTime() 
        {
            m_nFastTypeNet = 0;
            m_nSlowTypeNet = 0;

	        if(m_nNetPlayHandle == 0)
	        {
		        H264_DVR_FINDINFO info = new H264_DVR_FINDINFO();
        		
		        info.nChannelN0 = comboChannel.SelectedIndex;	//channel No.
		        info.nFileType = comboRecordType.SelectedIndex;		//file type
                info.startTime.dwYear = beginDate.Value.Year;
                info.startTime.dwMonth = beginDate.Value.Month;
                info.startTime.dwDay = beginDate.Value.Day;

                info.startTime.dwHour = beginTime.Value.Hour;
                info.startTime.dwMinute = beginTime.Value.Minute;
                info.startTime.dwSecond = beginTime.Value.Second;
		        info.endTime.dwYear = endDate.Value.Year;
                info.endTime.dwMonth = endDate.Value.Month;
                info.endTime.dwDay = endDate.Value.Day;
                info.endTime.dwHour = endTime.Value.Hour;
                info.endTime.dwMinute = endTime.Value.Minute;
                info.endTime.dwSecond = endTime.Value.Second;
                info.hWnd = (uint)pictureBoxNetVideoWnd.Handle;

                XMSDK.fDownLoadPosCallBack DownloadCallback = new XMSDK.fDownLoadPosCallBack(DownLoadPosCallback);
                XMSDK.fRealDataCallBack realDataCallBack = new XMSDK.fRealDataCallBack(RealDataCallBack);

                m_nNetPlayHandle = XMSDK.H264_DVR_PlayBackByTimeEx(m_lLoginID, ref info, null, this.Handle.ToInt32(),
                    null, this.Handle.ToInt32());

                if (m_nNetPlayHandle <= 0)
                {
                    MessageBox.Show("Playback fail");
                    m_nNetPlayHandle = 0;
                    return;
                }
                timerNetPlayBack.Start();
	        }
	        else
	        {

                if (m_bPauseNetPlay)
		        {
			        XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_CONTINUE, 0 );
                    m_bPauseNetPlay = !m_bPauseNetPlay;
		        }
                XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_FAST, 0);
                m_nFastTypeNet = 0;
                m_nSlowTypeNet = 0;
	        }
        }
        private void PlayByName() 
        {
            m_nFastTypeNet = 0;
            m_nSlowTypeNet = 0;
	        if(m_nNetPlayHandle == 0)
	        {
		        string csFileName = "";
        		
		        int nSelected = listFile.SelectedItems.Count;
		        if ( nSelected == 0 )
		        {
			        MessageBox.Show("SelectFile");
			        return;
		        }
        		
		        H264_DVR_FILE_DATA FileInfo = (H264_DVR_FILE_DATA)listFile.FocusedItem.Tag;
                FileInfo.hWnd = (uint)pictureBoxNetVideoWnd.Handle;


                XMSDK.fDownLoadPosCallBack downloadCallBack = new XMSDK.fDownLoadPosCallBack(DownLoadPosCallback);
                XMSDK.fRealDataCallBack_V2 netdatacallbackv2 = new XMSDK.fRealDataCallBack_V2(NetCallBack_V2);

                m_nNetPlayHandle = XMSDK.H264_DVR_PlayBackByName_V2(m_lLoginID, ref  FileInfo, downloadCallBack, netdatacallbackv2, this.Handle.ToInt32());
		        if(m_nNetPlayHandle <= 0 )
		        {
			        MessageBox.Show("Playback fail");
			        return;
		        }
                timerNetPlayBack.Start();
	        }
	        else
	        {
                if (m_bPauseNetPlay)
		        {
			        XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_CONTINUE, 0 );//暂停恢复正常		
                    m_bPauseNetPlay = !m_bPauseNetPlay;
		        }
                XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_FAST, 0);	//快慢放恢复正常	
                m_nFastTypeNet = 0;
                m_nSlowTypeNet = 0;
	        }
        }

        private void btnNetFast_Click(object sender, EventArgs e)
        {
            if (++m_nFastTypeNet > 4)
            {
                m_nFastTypeNet = 1;
            }
            m_nSlowTypeNet = 0;
            XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_FAST, m_nFastTypeNet);
        }

        private void btnNetSlow_Click(object sender, EventArgs e)
        {
            if (++m_nSlowTypeNet > 4)
            {
                m_nSlowTypeNet = 1;
            }
            m_nFastTypeNet = 0;
            XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_SLOW, m_nSlowTypeNet);
        }

        private void btnNetPause_Click(object sender, EventArgs e)
        {
            if (!m_bPauseNetPlay)
                XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_PAUSE, 0);
            else
                XMSDK.H264_DVR_PlayBackControl(m_nNetPlayHandle, (int)PlayBackAction.SDK_PLAY_BACK_CONTINUE, 0);
            m_bPauseNetPlay = !m_bPauseNetPlay;
        }

        private void PlayBackForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_nNetPlayHandle > 0 )
            {
                XMSDK.H264_DVR_StopPlayBack(m_nNetPlayHandle);
                m_nNetPlayHandle = -1;
            }


            ClearResult();
            //ClearMapResult();
            timerLocalPlayBack.Stop();
            timerDownload.Stop();
            timerNetPlayBack.Stop();
        }

        private void ClearResult()
        {
            listFile.Items.Clear();
            //comboChannel.Items.Clear();
           // m_mapTemp.clear();
            m_ListFindNum = 0;
	        //m_pstrFileVector.clear();
        }

        private void btnOpenAudio_Click(object sender, EventArgs e)
        {
            if (m_nNetPlayHandle > 0)
            {
                if (!m_bOpenAudio)
                {
                    if (XMSDK.H264_DVR_OpenSound(m_nNetPlayHandle))
                    {

                        btnOpenAudio.Text = "CloseAudio";
                        m_bOpenAudio = true;
                    }
                }
                else
                {
                    if (XMSDK.H264_DVR_CloseSound(m_nNetPlayHandle))
                    {
                       btnOpenAudio.Text = "OpenAudio";
                        m_bOpenAudio = false;
                    }
                }


            }

        }

        private void trackBarPos_DragDrop(object sender, DragEventArgs e)
        {
            m_SliderPos = trackBarNetPlayPos.Value;
            m_PreTime = System.DateTime.Now.Ticks;
            XMSDK.H264_DVR_SetPlayPos(m_nNetPlayHandle, m_SliderPos / (float)1000.0);
        }

        private void SetSliderPos(int nplaypos)
        {
	        if ( m_PreTime > 0 )
	        {
                long nTime = System.DateTime.Now.Ticks;
                if ((nTime - m_PreTime) >= 2000)
		        {
			        trackBarLocalPlayPos.Value= nplaypos * 1000;
        			
			        m_PreTime = 0;
		        }
	        }
	        else
	        {
		         trackBarLocalPlayPos.Value = nplaypos * 1000;
	        }
        }

        private void comboDev_SelectedIndexChanged(object sender, EventArgs e)
        {
            DEV_INFO devInfo = new DEV_INFO();
            ComboxItem selecteditem = (ComboxItem)comboDev.SelectedItem;

            devInfo = (DEV_INFO)selecteditem.Value;

            for (int i = 0; i < devInfo.NetDeviceInfo.byChanNum + devInfo.NetDeviceInfo.iDigChannel; i++)
            {
                comboChannel.Items.Add(i + 1);
            }
            comboChannel.SelectedIndex = 0;
            m_lLoginID = devInfo.lLoginID;

        }

        private void listFile_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void listFile_DoubleClick(object sender, EventArgs e)
        {
            btnNetPlay_Click(null,null);
        }

    }
}