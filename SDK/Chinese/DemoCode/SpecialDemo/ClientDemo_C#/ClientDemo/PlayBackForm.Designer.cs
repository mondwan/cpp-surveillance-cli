namespace ClientDemo
{
    partial class PlayBackForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControlPlayBack = new System.Windows.Forms.TabControl();
            this.tabPageLocalPlayBack = new System.Windows.Forms.TabPage();
            this.btnLocalslow = new System.Windows.Forms.Button();
            this.btnLocalFast = new System.Windows.Forms.Button();
            this.btnLocalPause = new System.Windows.Forms.Button();
            this.btnLocalStop = new System.Windows.Forms.Button();
            this.btnLocalPlay = new System.Windows.Forms.Button();
            this.btnOpenFile = new System.Windows.Forms.Button();
            this.trackBarLocalPlayPos = new System.Windows.Forms.TrackBar();
            this.pictureBoxVideoWnd = new System.Windows.Forms.PictureBox();
            this.tabPageRemovePlayBack = new System.Windows.Forms.TabPage();
            this.endTime = new System.Windows.Forms.DateTimePicker();
            this.endDate = new System.Windows.Forms.DateTimePicker();
            this.label6 = new System.Windows.Forms.Label();
            this.beginTime = new System.Windows.Forms.DateTimePicker();
            this.beginDate = new System.Windows.Forms.DateTimePicker();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.checkTime = new System.Windows.Forms.CheckBox();
            this.checkFile = new System.Windows.Forms.CheckBox();
            this.btnNetStop = new System.Windows.Forms.Button();
            this.btnNetPause = new System.Windows.Forms.Button();
            this.btnNetFast = new System.Windows.Forms.Button();
            this.btnNetSlow = new System.Windows.Forms.Button();
            this.btnOpenAudio = new System.Windows.Forms.Button();
            this.btnNetPlay = new System.Windows.Forms.Button();
            this.trackBarNetPlayPos = new System.Windows.Forms.TrackBar();
            this.pictureBoxNetVideoWnd = new System.Windows.Forms.PictureBox();
            this.progressBarDownloadPos = new System.Windows.Forms.ProgressBar();
            this.btnDownload = new System.Windows.Forms.Button();
            this.btnSearch = new System.Windows.Forms.Button();
            this.btnNextPage = new System.Windows.Forms.Button();
            this.btnPrePage = new System.Windows.Forms.Button();
            this.listFile = new System.Windows.Forms.ListView();
            this.columnHeaderNo = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderFileName = new System.Windows.Forms.ColumnHeader();
            this.comboRecordType = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboChannel = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboDev = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabControlPlayBack.SuspendLayout();
            this.tabPageLocalPlayBack.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLocalPlayPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxVideoWnd)).BeginInit();
            this.tabPageRemovePlayBack.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarNetPlayPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxNetVideoWnd)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControlPlayBack
            // 
            this.tabControlPlayBack.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControlPlayBack.Controls.Add(this.tabPageLocalPlayBack);
            this.tabControlPlayBack.Controls.Add(this.tabPageRemovePlayBack);
            this.tabControlPlayBack.Location = new System.Drawing.Point(12, 2);
            this.tabControlPlayBack.Name = "tabControlPlayBack";
            this.tabControlPlayBack.SelectedIndex = 0;
            this.tabControlPlayBack.Size = new System.Drawing.Size(820, 559);
            this.tabControlPlayBack.TabIndex = 0;
            this.tabControlPlayBack.Click += new System.EventHandler(this.tabControlPlayBack_Click);
            // 
            // tabPageLocalPlayBack
            // 
            this.tabPageLocalPlayBack.Controls.Add(this.btnLocalslow);
            this.tabPageLocalPlayBack.Controls.Add(this.btnLocalFast);
            this.tabPageLocalPlayBack.Controls.Add(this.btnLocalPause);
            this.tabPageLocalPlayBack.Controls.Add(this.btnLocalStop);
            this.tabPageLocalPlayBack.Controls.Add(this.btnLocalPlay);
            this.tabPageLocalPlayBack.Controls.Add(this.btnOpenFile);
            this.tabPageLocalPlayBack.Controls.Add(this.trackBarLocalPlayPos);
            this.tabPageLocalPlayBack.Controls.Add(this.pictureBoxVideoWnd);
            this.tabPageLocalPlayBack.Location = new System.Drawing.Point(4, 21);
            this.tabPageLocalPlayBack.Name = "tabPageLocalPlayBack";
            this.tabPageLocalPlayBack.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageLocalPlayBack.Size = new System.Drawing.Size(812, 534);
            this.tabPageLocalPlayBack.TabIndex = 0;
            this.tabPageLocalPlayBack.Text = "LocalPlayBack";
            this.tabPageLocalPlayBack.UseVisualStyleBackColor = true;
            // 
            // btnLocalslow
            // 
            this.btnLocalslow.Location = new System.Drawing.Point(557, 427);
            this.btnLocalslow.Name = "btnLocalslow";
            this.btnLocalslow.Size = new System.Drawing.Size(75, 23);
            this.btnLocalslow.TabIndex = 7;
            this.btnLocalslow.Text = "Slow";
            this.btnLocalslow.UseVisualStyleBackColor = true;
            this.btnLocalslow.Click += new System.EventHandler(this.btnLocalSlow_Click);
            // 
            // btnLocalFast
            // 
            this.btnLocalFast.Location = new System.Drawing.Point(465, 427);
            this.btnLocalFast.Name = "btnLocalFast";
            this.btnLocalFast.Size = new System.Drawing.Size(75, 23);
            this.btnLocalFast.TabIndex = 6;
            this.btnLocalFast.Text = "Fast";
            this.btnLocalFast.UseVisualStyleBackColor = true;
            this.btnLocalFast.Click += new System.EventHandler(this.btnLocalFast_Click);
            // 
            // btnLocalPause
            // 
            this.btnLocalPause.Location = new System.Drawing.Point(373, 427);
            this.btnLocalPause.Name = "btnLocalPause";
            this.btnLocalPause.Size = new System.Drawing.Size(75, 23);
            this.btnLocalPause.TabIndex = 5;
            this.btnLocalPause.Text = "Pause";
            this.btnLocalPause.UseVisualStyleBackColor = true;
            this.btnLocalPause.Click += new System.EventHandler(this.btnLocalPause_Click);
            // 
            // btnLocalStop
            // 
            this.btnLocalStop.Location = new System.Drawing.Point(281, 427);
            this.btnLocalStop.Name = "btnLocalStop";
            this.btnLocalStop.Size = new System.Drawing.Size(75, 23);
            this.btnLocalStop.TabIndex = 4;
            this.btnLocalStop.Text = "Stop";
            this.btnLocalStop.UseVisualStyleBackColor = true;
            this.btnLocalStop.Click += new System.EventHandler(this.btnLocalStop_Click);
            // 
            // btnLocalPlay
            // 
            this.btnLocalPlay.Location = new System.Drawing.Point(189, 427);
            this.btnLocalPlay.Name = "btnLocalPlay";
            this.btnLocalPlay.Size = new System.Drawing.Size(75, 23);
            this.btnLocalPlay.TabIndex = 3;
            this.btnLocalPlay.Text = "Play";
            this.btnLocalPlay.UseVisualStyleBackColor = true;
            this.btnLocalPlay.Click += new System.EventHandler(this.btnLocalPlay_Click);
            // 
            // btnOpenFile
            // 
            this.btnOpenFile.Location = new System.Drawing.Point(97, 427);
            this.btnOpenFile.Name = "btnOpenFile";
            this.btnOpenFile.Size = new System.Drawing.Size(75, 23);
            this.btnOpenFile.TabIndex = 2;
            this.btnOpenFile.Text = "OpenFile";
            this.btnOpenFile.UseVisualStyleBackColor = true;
            this.btnOpenFile.Click += new System.EventHandler(this.btnOpenFile_Click);
            // 
            // trackBarLocalPlayPos
            // 
            this.trackBarLocalPlayPos.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBarLocalPlayPos.AutoSize = false;
            this.trackBarLocalPlayPos.BackColor = System.Drawing.SystemColors.Control;
            this.trackBarLocalPlayPos.Location = new System.Drawing.Point(98, 382);
            this.trackBarLocalPlayPos.Name = "trackBarLocalPlayPos";
            this.trackBarLocalPlayPos.Size = new System.Drawing.Size(538, 35);
            this.trackBarLocalPlayPos.TabIndex = 1;
            this.trackBarLocalPlayPos.Scroll += new System.EventHandler(this.trackBarPlayPos_Scroll);
            // 
            // pictureBoxVideoWnd
            // 
            this.pictureBoxVideoWnd.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBoxVideoWnd.Location = new System.Drawing.Point(98, 16);
            this.pictureBoxVideoWnd.Name = "pictureBoxVideoWnd";
            this.pictureBoxVideoWnd.Size = new System.Drawing.Size(538, 383);
            this.pictureBoxVideoWnd.TabIndex = 0;
            this.pictureBoxVideoWnd.TabStop = false;
            // 
            // tabPageRemovePlayBack
            // 
            this.tabPageRemovePlayBack.Controls.Add(this.endTime);
            this.tabPageRemovePlayBack.Controls.Add(this.endDate);
            this.tabPageRemovePlayBack.Controls.Add(this.label6);
            this.tabPageRemovePlayBack.Controls.Add(this.beginTime);
            this.tabPageRemovePlayBack.Controls.Add(this.beginDate);
            this.tabPageRemovePlayBack.Controls.Add(this.label5);
            this.tabPageRemovePlayBack.Controls.Add(this.label4);
            this.tabPageRemovePlayBack.Controls.Add(this.checkTime);
            this.tabPageRemovePlayBack.Controls.Add(this.checkFile);
            this.tabPageRemovePlayBack.Controls.Add(this.btnNetStop);
            this.tabPageRemovePlayBack.Controls.Add(this.btnNetPause);
            this.tabPageRemovePlayBack.Controls.Add(this.btnNetFast);
            this.tabPageRemovePlayBack.Controls.Add(this.btnNetSlow);
            this.tabPageRemovePlayBack.Controls.Add(this.btnOpenAudio);
            this.tabPageRemovePlayBack.Controls.Add(this.btnNetPlay);
            this.tabPageRemovePlayBack.Controls.Add(this.trackBarNetPlayPos);
            this.tabPageRemovePlayBack.Controls.Add(this.pictureBoxNetVideoWnd);
            this.tabPageRemovePlayBack.Controls.Add(this.progressBarDownloadPos);
            this.tabPageRemovePlayBack.Controls.Add(this.btnDownload);
            this.tabPageRemovePlayBack.Controls.Add(this.btnSearch);
            this.tabPageRemovePlayBack.Controls.Add(this.btnNextPage);
            this.tabPageRemovePlayBack.Controls.Add(this.btnPrePage);
            this.tabPageRemovePlayBack.Controls.Add(this.listFile);
            this.tabPageRemovePlayBack.Controls.Add(this.comboRecordType);
            this.tabPageRemovePlayBack.Controls.Add(this.label3);
            this.tabPageRemovePlayBack.Controls.Add(this.comboChannel);
            this.tabPageRemovePlayBack.Controls.Add(this.label2);
            this.tabPageRemovePlayBack.Controls.Add(this.comboDev);
            this.tabPageRemovePlayBack.Controls.Add(this.label1);
            this.tabPageRemovePlayBack.Location = new System.Drawing.Point(4, 21);
            this.tabPageRemovePlayBack.Name = "tabPageRemovePlayBack";
            this.tabPageRemovePlayBack.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageRemovePlayBack.Size = new System.Drawing.Size(812, 534);
            this.tabPageRemovePlayBack.TabIndex = 1;
            this.tabPageRemovePlayBack.Text = "RemovePlayBack";
            this.tabPageRemovePlayBack.UseVisualStyleBackColor = true;
            // 
            // endTime
            // 
            this.endTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.endTime.Location = new System.Drawing.Point(407, 32);
            this.endTime.Name = "endTime";
            this.endTime.Size = new System.Drawing.Size(82, 21);
            this.endTime.TabIndex = 28;
            // 
            // endDate
            // 
            this.endDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.endDate.Location = new System.Drawing.Point(311, 32);
            this.endDate.Name = "endDate";
            this.endDate.Size = new System.Drawing.Size(90, 21);
            this.endDate.TabIndex = 27;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(260, 37);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 12);
            this.label6.TabIndex = 26;
            this.label6.Text = "EndTime";
            // 
            // beginTime
            // 
            this.beginTime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.beginTime.Location = new System.Drawing.Point(168, 32);
            this.beginTime.Name = "beginTime";
            this.beginTime.Size = new System.Drawing.Size(82, 21);
            this.beginTime.TabIndex = 25;
            // 
            // beginDate
            // 
            this.beginDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.beginDate.Location = new System.Drawing.Point(72, 32);
            this.beginDate.Name = "beginDate";
            this.beginDate.Size = new System.Drawing.Size(90, 21);
            this.beginDate.TabIndex = 24;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 37);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 23;
            this.label5.Text = "BeginTime";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 67);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 12);
            this.label4.TabIndex = 22;
            this.label4.Text = "Playback Mode:";
            // 
            // checkTime
            // 
            this.checkTime.AutoSize = true;
            this.checkTime.Location = new System.Drawing.Point(180, 66);
            this.checkTime.Name = "checkTime";
            this.checkTime.Size = new System.Drawing.Size(60, 16);
            this.checkTime.TabIndex = 21;
            this.checkTime.Text = "ByTime";
            this.checkTime.UseVisualStyleBackColor = true;
            this.checkTime.CheckedChanged += new System.EventHandler(this.checkTime_CheckedChanged);
            // 
            // checkFile
            // 
            this.checkFile.AutoSize = true;
            this.checkFile.Location = new System.Drawing.Point(103, 66);
            this.checkFile.Name = "checkFile";
            this.checkFile.Size = new System.Drawing.Size(60, 16);
            this.checkFile.TabIndex = 20;
            this.checkFile.Text = "ByName";
            this.checkFile.UseVisualStyleBackColor = true;
            this.checkFile.CheckedChanged += new System.EventHandler(this.checkFile_CheckedChanged);
            // 
            // btnNetStop
            // 
            this.btnNetStop.Location = new System.Drawing.Point(479, 468);
            this.btnNetStop.Name = "btnNetStop";
            this.btnNetStop.Size = new System.Drawing.Size(55, 23);
            this.btnNetStop.TabIndex = 19;
            this.btnNetStop.Text = "Stop";
            this.btnNetStop.UseVisualStyleBackColor = true;
            this.btnNetStop.Click += new System.EventHandler(this.btnNetPlayStop_Click);
            // 
            // btnNetPause
            // 
            this.btnNetPause.Location = new System.Drawing.Point(540, 468);
            this.btnNetPause.Name = "btnNetPause";
            this.btnNetPause.Size = new System.Drawing.Size(55, 23);
            this.btnNetPause.TabIndex = 18;
            this.btnNetPause.Text = "Pause";
            this.btnNetPause.UseVisualStyleBackColor = true;
            this.btnNetPause.Click += new System.EventHandler(this.btnNetPause_Click);
            // 
            // btnNetFast
            // 
            this.btnNetFast.Location = new System.Drawing.Point(601, 468);
            this.btnNetFast.Name = "btnNetFast";
            this.btnNetFast.Size = new System.Drawing.Size(55, 23);
            this.btnNetFast.TabIndex = 17;
            this.btnNetFast.Text = "Fast";
            this.btnNetFast.UseVisualStyleBackColor = true;
            this.btnNetFast.Click += new System.EventHandler(this.btnNetFast_Click);
            // 
            // btnNetSlow
            // 
            this.btnNetSlow.Location = new System.Drawing.Point(662, 468);
            this.btnNetSlow.Name = "btnNetSlow";
            this.btnNetSlow.Size = new System.Drawing.Size(55, 23);
            this.btnNetSlow.TabIndex = 16;
            this.btnNetSlow.Text = "Slow";
            this.btnNetSlow.UseVisualStyleBackColor = true;
            this.btnNetSlow.Click += new System.EventHandler(this.btnNetSlow_Click);
            // 
            // btnOpenAudio
            // 
            this.btnOpenAudio.Location = new System.Drawing.Point(723, 468);
            this.btnOpenAudio.Name = "btnOpenAudio";
            this.btnOpenAudio.Size = new System.Drawing.Size(78, 23);
            this.btnOpenAudio.TabIndex = 15;
            this.btnOpenAudio.Text = "OpenAudio";
            this.btnOpenAudio.UseVisualStyleBackColor = true;
            this.btnOpenAudio.Click += new System.EventHandler(this.btnOpenAudio_Click);
            // 
            // btnNetPlay
            // 
            this.btnNetPlay.Location = new System.Drawing.Point(418, 468);
            this.btnNetPlay.Name = "btnNetPlay";
            this.btnNetPlay.Size = new System.Drawing.Size(55, 23);
            this.btnNetPlay.TabIndex = 14;
            this.btnNetPlay.Text = "Play";
            this.btnNetPlay.UseVisualStyleBackColor = true;
            this.btnNetPlay.Click += new System.EventHandler(this.btnNetPlay_Click);
            // 
            // trackBarNetPlayPos
            // 
            this.trackBarNetPlayPos.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBarNetPlayPos.AutoSize = false;
            this.trackBarNetPlayPos.BackColor = System.Drawing.SystemColors.Control;
            this.trackBarNetPlayPos.Location = new System.Drawing.Point(378, 411);
            this.trackBarNetPlayPos.Name = "trackBarNetPlayPos";
            this.trackBarNetPlayPos.Size = new System.Drawing.Size(423, 80);
            this.trackBarNetPlayPos.TabIndex = 13;
            this.trackBarNetPlayPos.DragDrop += new System.Windows.Forms.DragEventHandler(this.trackBarPos_DragDrop);
            // 
            // pictureBoxNetVideoWnd
            // 
            this.pictureBoxNetVideoWnd.Location = new System.Drawing.Point(388, 91);
            this.pictureBoxNetVideoWnd.Name = "pictureBoxNetVideoWnd";
            this.pictureBoxNetVideoWnd.Size = new System.Drawing.Size(413, 300);
            this.pictureBoxNetVideoWnd.TabIndex = 12;
            this.pictureBoxNetVideoWnd.TabStop = false;
            // 
            // progressBarDownloadPos
            // 
            this.progressBarDownloadPos.Location = new System.Drawing.Point(40, 468);
            this.progressBarDownloadPos.Name = "progressBarDownloadPos";
            this.progressBarDownloadPos.Size = new System.Drawing.Size(267, 23);
            this.progressBarDownloadPos.TabIndex = 11;
            // 
            // btnDownload
            // 
            this.btnDownload.Location = new System.Drawing.Point(246, 419);
            this.btnDownload.Name = "btnDownload";
            this.btnDownload.Size = new System.Drawing.Size(61, 23);
            this.btnDownload.TabIndex = 10;
            this.btnDownload.Text = "Download";
            this.btnDownload.UseVisualStyleBackColor = true;
            this.btnDownload.Click += new System.EventHandler(this.btnDownload_Click);
            // 
            // btnSearch
            // 
            this.btnSearch.Location = new System.Drawing.Point(174, 419);
            this.btnSearch.Name = "btnSearch";
            this.btnSearch.Size = new System.Drawing.Size(66, 23);
            this.btnSearch.TabIndex = 9;
            this.btnSearch.Text = "Search";
            this.btnSearch.UseVisualStyleBackColor = true;
            this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click);
            // 
            // btnNextPage
            // 
            this.btnNextPage.Location = new System.Drawing.Point(108, 419);
            this.btnNextPage.Name = "btnNextPage";
            this.btnNextPage.Size = new System.Drawing.Size(66, 23);
            this.btnNextPage.TabIndex = 8;
            this.btnNextPage.Text = "NextPage";
            this.btnNextPage.UseVisualStyleBackColor = true;
            this.btnNextPage.Click += new System.EventHandler(this.btnNextPage_Click);
            // 
            // btnPrePage
            // 
            this.btnPrePage.Location = new System.Drawing.Point(40, 419);
            this.btnPrePage.Name = "btnPrePage";
            this.btnPrePage.Size = new System.Drawing.Size(62, 23);
            this.btnPrePage.TabIndex = 7;
            this.btnPrePage.Text = "PrePage";
            this.btnPrePage.UseVisualStyleBackColor = true;
            this.btnPrePage.Click += new System.EventHandler(this.btnPrePage_Click);
            // 
            // listFile
            // 
            this.listFile.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderNo,
            this.columnHeaderFileName});
            this.listFile.FullRowSelect = true;
            this.listFile.Location = new System.Drawing.Point(3, 91);
            this.listFile.Name = "listFile";
            this.listFile.Size = new System.Drawing.Size(365, 300);
            this.listFile.TabIndex = 6;
            this.listFile.UseCompatibleStateImageBehavior = false;
            this.listFile.View = System.Windows.Forms.View.Details;
            this.listFile.SelectedIndexChanged += new System.EventHandler(this.listFile_SelectedIndexChanged);
            this.listFile.DoubleClick += new System.EventHandler(this.listFile_DoubleClick);
            // 
            // columnHeaderNo
            // 
            this.columnHeaderNo.Text = "No.";
            this.columnHeaderNo.Width = 38;
            // 
            // columnHeaderFileName
            // 
            this.columnHeaderFileName.Text = "FileName";
            this.columnHeaderFileName.Width = 275;
            // 
            // comboRecordType
            // 
            this.comboRecordType.FormattingEnabled = true;
            this.comboRecordType.Location = new System.Drawing.Point(562, 9);
            this.comboRecordType.Name = "comboRecordType";
            this.comboRecordType.Size = new System.Drawing.Size(121, 20);
            this.comboRecordType.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(505, 12);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "FileType";
            // 
            // comboChannel
            // 
            this.comboChannel.FormattingEnabled = true;
            this.comboChannel.Location = new System.Drawing.Point(317, 6);
            this.comboChannel.Name = "comboChannel";
            this.comboChannel.Size = new System.Drawing.Size(121, 20);
            this.comboChannel.TabIndex = 3;
            this.comboChannel.SelectedIndexChanged += new System.EventHandler(this.comboChannel_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(263, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Channel";
            // 
            // comboDev
            // 
            this.comboDev.FormattingEnabled = true;
            this.comboDev.Location = new System.Drawing.Point(67, 6);
            this.comboDev.Name = "comboDev";
            this.comboDev.Size = new System.Drawing.Size(121, 20);
            this.comboDev.TabIndex = 1;
            this.comboDev.SelectedIndexChanged += new System.EventHandler(this.comboDev_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Device:";
            // 
            // PlayBackForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(844, 558);
            this.Controls.Add(this.tabControlPlayBack);
            this.Name = "PlayBackForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PlayBackForm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.PlayBackForm_FormClosed);
            this.tabControlPlayBack.ResumeLayout(false);
            this.tabPageLocalPlayBack.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.trackBarLocalPlayPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxVideoWnd)).EndInit();
            this.tabPageRemovePlayBack.ResumeLayout(false);
            this.tabPageRemovePlayBack.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarNetPlayPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxNetVideoWnd)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControlPlayBack;
        private System.Windows.Forms.TabPage tabPageLocalPlayBack;
        private System.Windows.Forms.TabPage tabPageRemovePlayBack;
        private System.Windows.Forms.PictureBox pictureBoxVideoWnd;
        private System.Windows.Forms.TrackBar trackBarLocalPlayPos;
        private System.Windows.Forms.Button btnLocalslow;
        private System.Windows.Forms.Button btnLocalFast;
        private System.Windows.Forms.Button btnLocalPause;
        private System.Windows.Forms.Button btnLocalStop;
        private System.Windows.Forms.Button btnLocalPlay;
        private System.Windows.Forms.Button btnOpenFile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboDev;
        private System.Windows.Forms.ComboBox comboRecordType;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboChannel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox pictureBoxNetVideoWnd;
        private System.Windows.Forms.ProgressBar progressBarDownloadPos;
        private System.Windows.Forms.Button btnDownload;
        private System.Windows.Forms.Button btnSearch;
        private System.Windows.Forms.Button btnNextPage;
        private System.Windows.Forms.Button btnPrePage;
        private System.Windows.Forms.Button btnNetStop;
        private System.Windows.Forms.Button btnNetPause;
        private System.Windows.Forms.Button btnNetFast;
        private System.Windows.Forms.Button btnNetSlow;
        private System.Windows.Forms.Button btnOpenAudio;
        private System.Windows.Forms.Button btnNetPlay;
        private System.Windows.Forms.TrackBar trackBarNetPlayPos;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox checkTime;
        private System.Windows.Forms.DateTimePicker endTime;
        private System.Windows.Forms.DateTimePicker endDate;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.DateTimePicker beginTime;
        private System.Windows.Forms.DateTimePicker beginDate;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox checkFile;
        private System.Windows.Forms.ListView listFile;
        private System.Windows.Forms.ColumnHeader columnHeaderNo;
        private System.Windows.Forms.ColumnHeader columnHeaderFileName;
    }
}