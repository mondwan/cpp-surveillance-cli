namespace ClientDemo
{
    partial class DevConfigForm
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
            this.tabControlConfigs = new System.Windows.Forms.TabControl();
            this.tabPageGeneral = new System.Windows.Forms.TabPage();
            this.buttongGeneralOk = new System.Windows.Forms.Button();
            this.comboBoxLanguage = new System.Windows.Forms.ComboBox();
            this.comboBoxTimeFormat = new System.Windows.Forms.ComboBox();
            this.comboBoxDateSeparator = new System.Windows.Forms.ComboBox();
            this.comboBoxDateFormat = new System.Windows.Forms.ComboBox();
            this.comboBoxVideoStandard = new System.Windows.Forms.ComboBox();
            this.comboBoxDiskFullTo = new System.Windows.Forms.ComboBox();
            this.textBoxDeviceName = new System.Windows.Forms.TextBox();
            this.textBoxStandbyTime = new System.Windows.Forms.TextBox();
            this.textBoxDeviceNo = new System.Windows.Forms.TextBox();
            this.textBoxReleaseDate = new System.Windows.Forms.TextBox();
            this.textBox1SystemVersion = new System.Windows.Forms.TextBox();
            this.textBoxDigitalChannel = new System.Windows.Forms.TextBox();
            this.textBoxExChannel = new System.Windows.Forms.TextBox();
            this.textBoxTalkOut = new System.Windows.Forms.TextBox();
            this.textBoxTalkIn = new System.Windows.Forms.TextBox();
            this.textBoxAlarmOut = new System.Windows.Forms.TextBox();
            this.textBoxAlarmIn = new System.Windows.Forms.TextBox();
            this.textBoxAudioIn = new System.Windows.Forms.TextBox();
            this.textBoxVideoOut = new System.Windows.Forms.TextBox();
            this.textBoxRecordChannel = new System.Windows.Forms.TextBox();
            this.textBoxSerial = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPageNetwork = new System.Windows.Forms.TabPage();
            this.tabPageWifi = new System.Windows.Forms.TabPage();
            this.listViewWifi = new System.Windows.Forms.ListView();
            this.columnHeaderSSID = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderAuth = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderRSSI = new System.Windows.Forms.ColumnHeader();
            this.textBoxWifiGateway = new System.Windows.Forms.TextBox();
            this.label27 = new System.Windows.Forms.Label();
            this.textBoxWifiSubmask = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.textBoxWifiIP = new System.Windows.Forms.TextBox();
            this.label25 = new System.Windows.Forms.Label();
            this.textBoxWifiPassword = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.comboBoxWifiEntryType = new System.Windows.Forms.ComboBox();
            this.label23 = new System.Windows.Forms.Label();
            this.textBoxSSID = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.checkBoxDHCP = new System.Windows.Forms.CheckBox();
            this.checkEnableWifi = new System.Windows.Forms.CheckBox();
            this.buttonSearchWifi = new System.Windows.Forms.Button();
            this.comboBoxDevice = new System.Windows.Forms.ComboBox();
            this.labelKeyType = new System.Windows.Forms.Label();
            this.comboBoxWifiKeyType = new System.Windows.Forms.ComboBox();
            this.buttonWifiOK = new System.Windows.Forms.Button();
            this.tabControlConfigs.SuspendLayout();
            this.tabPageGeneral.SuspendLayout();
            this.tabPageWifi.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControlConfigs
            // 
            this.tabControlConfigs.Controls.Add(this.tabPageGeneral);
            //this.tabControlConfigs.Controls.Add(this.tabPageNetwork);
            this.tabControlConfigs.Controls.Add(this.tabPageWifi);
            this.tabControlConfigs.Location = new System.Drawing.Point(28, 34);
            this.tabControlConfigs.Name = "tabControlConfigs";
            this.tabControlConfigs.SelectedIndex = 0;
            this.tabControlConfigs.Size = new System.Drawing.Size(614, 403);
            this.tabControlConfigs.TabIndex = 0;
            this.tabControlConfigs.Selected += new System.Windows.Forms.TabControlEventHandler(this.tabControlConfigs_Selected);
            // 
            // tabPageGeneral
            // 
            this.tabPageGeneral.Controls.Add(this.buttongGeneralOk);
            this.tabPageGeneral.Controls.Add(this.comboBoxLanguage);
            this.tabPageGeneral.Controls.Add(this.comboBoxTimeFormat);
            this.tabPageGeneral.Controls.Add(this.comboBoxDateSeparator);
            this.tabPageGeneral.Controls.Add(this.comboBoxDateFormat);
            this.tabPageGeneral.Controls.Add(this.comboBoxVideoStandard);
            this.tabPageGeneral.Controls.Add(this.comboBoxDiskFullTo);
            this.tabPageGeneral.Controls.Add(this.textBoxDeviceName);
            this.tabPageGeneral.Controls.Add(this.textBoxStandbyTime);
            this.tabPageGeneral.Controls.Add(this.textBoxDeviceNo);
            this.tabPageGeneral.Controls.Add(this.textBoxReleaseDate);
            this.tabPageGeneral.Controls.Add(this.textBox1SystemVersion);
            this.tabPageGeneral.Controls.Add(this.textBoxDigitalChannel);
            this.tabPageGeneral.Controls.Add(this.textBoxExChannel);
            this.tabPageGeneral.Controls.Add(this.textBoxTalkOut);
            this.tabPageGeneral.Controls.Add(this.textBoxTalkIn);
            this.tabPageGeneral.Controls.Add(this.textBoxAlarmOut);
            this.tabPageGeneral.Controls.Add(this.textBoxAlarmIn);
            this.tabPageGeneral.Controls.Add(this.textBoxAudioIn);
            this.tabPageGeneral.Controls.Add(this.textBoxVideoOut);
            this.tabPageGeneral.Controls.Add(this.textBoxRecordChannel);
            this.tabPageGeneral.Controls.Add(this.textBoxSerial);
            this.tabPageGeneral.Controls.Add(this.label16);
            this.tabPageGeneral.Controls.Add(this.label17);
            this.tabPageGeneral.Controls.Add(this.label18);
            this.tabPageGeneral.Controls.Add(this.label19);
            this.tabPageGeneral.Controls.Add(this.label20);
            this.tabPageGeneral.Controls.Add(this.label21);
            this.tabPageGeneral.Controls.Add(this.label13);
            this.tabPageGeneral.Controls.Add(this.label14);
            this.tabPageGeneral.Controls.Add(this.label15);
            this.tabPageGeneral.Controls.Add(this.label7);
            this.tabPageGeneral.Controls.Add(this.label8);
            this.tabPageGeneral.Controls.Add(this.label9);
            this.tabPageGeneral.Controls.Add(this.label10);
            this.tabPageGeneral.Controls.Add(this.label11);
            this.tabPageGeneral.Controls.Add(this.label12);
            this.tabPageGeneral.Controls.Add(this.label6);
            this.tabPageGeneral.Controls.Add(this.label5);
            this.tabPageGeneral.Controls.Add(this.label4);
            this.tabPageGeneral.Controls.Add(this.label3);
            this.tabPageGeneral.Controls.Add(this.label2);
            this.tabPageGeneral.Controls.Add(this.label1);
            this.tabPageGeneral.Location = new System.Drawing.Point(4, 22);
            this.tabPageGeneral.Name = "tabPageGeneral";
            this.tabPageGeneral.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGeneral.Size = new System.Drawing.Size(606, 377);
            this.tabPageGeneral.TabIndex = 0;
            this.tabPageGeneral.Text = "General";
            this.tabPageGeneral.UseVisualStyleBackColor = true;
            // 
            // buttongGeneralOk
            // 
            this.buttongGeneralOk.Location = new System.Drawing.Point(253, 348);
            this.buttongGeneralOk.Name = "buttongGeneralOk";
            this.buttongGeneralOk.Size = new System.Drawing.Size(75, 23);
            this.buttongGeneralOk.TabIndex = 42;
            this.buttongGeneralOk.Text = "OK";
            this.buttongGeneralOk.UseVisualStyleBackColor = true;
            this.buttongGeneralOk.Click += new System.EventHandler(this.buttongGeneralOk_Click);
            // 
            // comboBoxLanguage
            // 
            this.comboBoxLanguage.FormattingEnabled = true;
            this.comboBoxLanguage.Location = new System.Drawing.Point(370, 225);
            this.comboBoxLanguage.Name = "comboBoxLanguage";
            this.comboBoxLanguage.Size = new System.Drawing.Size(117, 20);
            this.comboBoxLanguage.TabIndex = 41;
            this.comboBoxLanguage.Hide() ;
            // 
            // comboBoxTimeFormat
            // 
            this.comboBoxTimeFormat.FormattingEnabled = true;
            this.comboBoxTimeFormat.Items.AddRange(new object[] {
            "24Hours",
            "12Hours"});
            this.comboBoxTimeFormat.Location = new System.Drawing.Point(370, 173);
            this.comboBoxTimeFormat.Name = "comboBoxTimeFormat";
            this.comboBoxTimeFormat.Size = new System.Drawing.Size(117, 20);
            this.comboBoxTimeFormat.TabIndex = 40;
            // 
            // comboBoxDateSeparator
            // 
            this.comboBoxDateSeparator.FormattingEnabled = true;
            this.comboBoxDateSeparator.Items.AddRange(new object[] {
            "\".\"",
            "\"-\"",
            "\"/\""});
            this.comboBoxDateSeparator.Location = new System.Drawing.Point(370, 149);
            this.comboBoxDateSeparator.Name = "comboBoxDateSeparator";
            this.comboBoxDateSeparator.Size = new System.Drawing.Size(117, 20);
            this.comboBoxDateSeparator.TabIndex = 39;
            // 
            // comboBoxDateFormat
            // 
            this.comboBoxDateFormat.FormattingEnabled = true;
            this.comboBoxDateFormat.Items.AddRange(new object[] {
            "YYYY-MM-DD",
            "MM-DD-YYYY",
            "DD-MM-YYYY"});
            this.comboBoxDateFormat.Location = new System.Drawing.Point(370, 123);
            this.comboBoxDateFormat.Name = "comboBoxDateFormat";
            this.comboBoxDateFormat.Size = new System.Drawing.Size(117, 20);
            this.comboBoxDateFormat.TabIndex = 38;
            // 
            // comboBoxVideoStandard
            // 
            this.comboBoxVideoStandard.FormattingEnabled = true;
            this.comboBoxVideoStandard.Items.AddRange(new object[] {
            "PAL",
            "NTSC"});
            this.comboBoxVideoStandard.Location = new System.Drawing.Point(370, 93);
            this.comboBoxVideoStandard.Name = "comboBoxVideoStandard";
            this.comboBoxVideoStandard.Size = new System.Drawing.Size(117, 20);
            this.comboBoxVideoStandard.TabIndex = 37;
            // 
            // comboBoxDiskFullTo
            // 
            this.comboBoxDiskFullTo.FormattingEnabled = true;
            this.comboBoxDiskFullTo.Items.AddRange(new object[] {
            "StopRecord",
            "Overwrite"});
            this.comboBoxDiskFullTo.Location = new System.Drawing.Point(370, 39);
            this.comboBoxDiskFullTo.Name = "comboBoxDiskFullTo";
            this.comboBoxDiskFullTo.Size = new System.Drawing.Size(117, 20);
            this.comboBoxDiskFullTo.TabIndex = 36;
            // 
            // textBoxDeviceName
            // 
            this.textBoxDeviceName.Location = new System.Drawing.Point(370, 198);
            this.textBoxDeviceName.Name = "textBoxDeviceName";
            this.textBoxDeviceName.Size = new System.Drawing.Size(166, 21);
            this.textBoxDeviceName.TabIndex = 35;
            // 
            // textBoxStandbyTime
            // 
            this.textBoxStandbyTime.Location = new System.Drawing.Point(370, 65);
            this.textBoxStandbyTime.Name = "textBoxStandbyTime";
            this.textBoxStandbyTime.Size = new System.Drawing.Size(166, 21);
            this.textBoxStandbyTime.TabIndex = 34;
            // 
            // textBoxDeviceNo
            // 
            this.textBoxDeviceNo.Location = new System.Drawing.Point(370, 14);
            this.textBoxDeviceNo.Name = "textBoxDeviceNo";
            this.textBoxDeviceNo.Size = new System.Drawing.Size(166, 21);
            this.textBoxDeviceNo.TabIndex = 33;
            // 
            // textBoxReleaseDate
            // 
            this.textBoxReleaseDate.Location = new System.Drawing.Point(118, 302);
            this.textBoxReleaseDate.Name = "textBoxReleaseDate";
            this.textBoxReleaseDate.ReadOnly = true;
            this.textBoxReleaseDate.Size = new System.Drawing.Size(316, 21);
            this.textBoxReleaseDate.TabIndex = 32;
            // 
            // textBox1SystemVersion
            // 
            this.textBox1SystemVersion.Location = new System.Drawing.Point(118, 275);
            this.textBox1SystemVersion.Name = "textBox1SystemVersion";
            this.textBox1SystemVersion.ReadOnly = true;
            this.textBox1SystemVersion.Size = new System.Drawing.Size(316, 21);
            this.textBox1SystemVersion.TabIndex = 31;
            // 
            // textBoxDigitalChannel
            // 
            this.textBoxDigitalChannel.Location = new System.Drawing.Point(118, 249);
            this.textBoxDigitalChannel.Name = "textBoxDigitalChannel";
            this.textBoxDigitalChannel.ReadOnly = true;
            this.textBoxDigitalChannel.Size = new System.Drawing.Size(145, 21);
            this.textBoxDigitalChannel.TabIndex = 30;
            // 
            // textBoxExChannel
            // 
            this.textBoxExChannel.Location = new System.Drawing.Point(118, 222);
            this.textBoxExChannel.Name = "textBoxExChannel";
            this.textBoxExChannel.ReadOnly = true;
            this.textBoxExChannel.Size = new System.Drawing.Size(145, 21);
            this.textBoxExChannel.TabIndex = 29;
            // 
            // textBoxTalkOut
            // 
            this.textBoxTalkOut.Location = new System.Drawing.Point(118, 196);
            this.textBoxTalkOut.Name = "textBoxTalkOut";
            this.textBoxTalkOut.ReadOnly = true;
            this.textBoxTalkOut.Size = new System.Drawing.Size(145, 21);
            this.textBoxTalkOut.TabIndex = 28;
            // 
            // textBoxTalkIn
            // 
            this.textBoxTalkIn.Location = new System.Drawing.Point(118, 171);
            this.textBoxTalkIn.Name = "textBoxTalkIn";
            this.textBoxTalkIn.ReadOnly = true;
            this.textBoxTalkIn.Size = new System.Drawing.Size(145, 21);
            this.textBoxTalkIn.TabIndex = 27;
            // 
            // textBoxAlarmOut
            // 
            this.textBoxAlarmOut.Location = new System.Drawing.Point(118, 146);
            this.textBoxAlarmOut.Name = "textBoxAlarmOut";
            this.textBoxAlarmOut.ReadOnly = true;
            this.textBoxAlarmOut.Size = new System.Drawing.Size(145, 21);
            this.textBoxAlarmOut.TabIndex = 26;
            // 
            // textBoxAlarmIn
            // 
            this.textBoxAlarmIn.Location = new System.Drawing.Point(118, 119);
            this.textBoxAlarmIn.Name = "textBoxAlarmIn";
            this.textBoxAlarmIn.ReadOnly = true;
            this.textBoxAlarmIn.Size = new System.Drawing.Size(145, 21);
            this.textBoxAlarmIn.TabIndex = 25;
            // 
            // textBoxAudioIn
            // 
            this.textBoxAudioIn.Location = new System.Drawing.Point(118, 93);
            this.textBoxAudioIn.Name = "textBoxAudioIn";
            this.textBoxAudioIn.ReadOnly = true;
            this.textBoxAudioIn.Size = new System.Drawing.Size(145, 21);
            this.textBoxAudioIn.TabIndex = 24;
            // 
            // textBoxVideoOut
            // 
            this.textBoxVideoOut.Location = new System.Drawing.Point(118, 65);
            this.textBoxVideoOut.Name = "textBoxVideoOut";
            this.textBoxVideoOut.ReadOnly = true;
            this.textBoxVideoOut.Size = new System.Drawing.Size(145, 21);
            this.textBoxVideoOut.TabIndex = 23;
            // 
            // textBoxRecordChannel
            // 
            this.textBoxRecordChannel.Location = new System.Drawing.Point(118, 41);
            this.textBoxRecordChannel.Name = "textBoxRecordChannel";
            this.textBoxRecordChannel.ReadOnly = true;
            this.textBoxRecordChannel.Size = new System.Drawing.Size(145, 21);
            this.textBoxRecordChannel.TabIndex = 22;
            // 
            // textBoxSerial
            // 
            this.textBoxSerial.Location = new System.Drawing.Point(118, 11);
            this.textBoxSerial.Name = "textBoxSerial";
            this.textBoxSerial.ReadOnly = true;
            this.textBoxSerial.Size = new System.Drawing.Size(145, 21);
            this.textBoxSerial.TabIndex = 21;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(22, 305);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(71, 12);
            this.label16.TabIndex = 20;
            this.label16.Text = "ReleaseDate";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(22, 279);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(83, 12);
            this.label17.TabIndex = 19;
            this.label17.Text = "SystemVersion";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(22, 253);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(89, 12);
            this.label18.TabIndex = 18;
            this.label18.Text = "DigitalChannel";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(22, 227);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(59, 12);
            this.label19.TabIndex = 17;
            this.label19.Text = "ExChannel";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(22, 201);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(47, 12);
            this.label20.TabIndex = 16;
            this.label20.Text = "TalkOut";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(22, 175);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(41, 12);
            this.label21.TabIndex = 15;
            this.label21.Text = "TalkIn";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(284, 227);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(53, 12);
            this.label13.TabIndex = 14;
            this.label13.Text = "Language";
            this.label13.Hide();
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(284, 201);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(65, 12);
            this.label14.TabIndex = 13;
            this.label14.Text = "DeviceName";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(284, 175);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(65, 12);
            this.label15.TabIndex = 12;
            this.label15.Text = "TimeFormat";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(284, 149);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(83, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = "DateSeparator";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(284, 123);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(65, 12);
            this.label8.TabIndex = 10;
            this.label8.Text = "DateFormat";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(284, 97);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(83, 12);
            this.label9.TabIndex = 9;
            this.label9.Text = "VideoStandard";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(284, 71);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(71, 12);
            this.label10.TabIndex = 8;
            this.label10.Text = "StandbyTime";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(284, 45);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(65, 12);
            this.label11.TabIndex = 7;
            this.label11.Text = "DiskFullTo";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(284, 19);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(53, 12);
            this.label12.TabIndex = 6;
            this.label12.Text = "DeviceNo";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(22, 149);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 5;
            this.label6.Text = "AlarmOut";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 123);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 4;
            this.label5.Text = "AarmIn";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(22, 97);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 3;
            this.label4.Text = "AudioIn";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 71);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "VideoOut";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "RecordChannel";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Serial";
            // 
            // tabPageNetwork
            // 
            this.tabPageNetwork.Location = new System.Drawing.Point(4, 22);
            this.tabPageNetwork.Name = "tabPageNetwork";
            this.tabPageNetwork.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageNetwork.Size = new System.Drawing.Size(606, 377);
            this.tabPageNetwork.TabIndex = 1;
            this.tabPageNetwork.Text = "Network";
            this.tabPageNetwork.UseVisualStyleBackColor = true;
            this.tabPageNetwork.Hide();
            // 
            // tabPageWifi
            // 
            this.tabPageWifi.Controls.Add(this.buttonWifiOK);
            this.tabPageWifi.Controls.Add(this.comboBoxWifiKeyType);
            this.tabPageWifi.Controls.Add(this.labelKeyType);
            this.tabPageWifi.Controls.Add(this.listViewWifi);
            this.tabPageWifi.Controls.Add(this.textBoxWifiGateway);
            this.tabPageWifi.Controls.Add(this.label27);
            this.tabPageWifi.Controls.Add(this.textBoxWifiSubmask);
            this.tabPageWifi.Controls.Add(this.label26);
            this.tabPageWifi.Controls.Add(this.textBoxWifiIP);
            this.tabPageWifi.Controls.Add(this.label25);
            this.tabPageWifi.Controls.Add(this.textBoxWifiPassword);
            this.tabPageWifi.Controls.Add(this.label24);
            this.tabPageWifi.Controls.Add(this.comboBoxWifiEntryType);
            this.tabPageWifi.Controls.Add(this.label23);
            this.tabPageWifi.Controls.Add(this.textBoxSSID);
            this.tabPageWifi.Controls.Add(this.label22);
            this.tabPageWifi.Controls.Add(this.checkBoxDHCP);
            this.tabPageWifi.Controls.Add(this.checkEnableWifi);
            this.tabPageWifi.Controls.Add(this.buttonSearchWifi);
            this.tabPageWifi.Location = new System.Drawing.Point(4, 22);
            this.tabPageWifi.Name = "tabPageWifi";
            this.tabPageWifi.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageWifi.Size = new System.Drawing.Size(606, 377);
            this.tabPageWifi.TabIndex = 2;
            this.tabPageWifi.Text = "Wifi";
            this.tabPageWifi.UseVisualStyleBackColor = true;
            // 
            // listViewWifi
            // 
            this.listViewWifi.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderSSID,
            this.columnHeaderAuth,
            this.columnHeaderRSSI});
            this.listViewWifi.FullRowSelect = true;
            this.listViewWifi.Location = new System.Drawing.Point(73, 6);
            this.listViewWifi.MultiSelect = false;
            this.listViewWifi.Name = "listViewWifi";
            this.listViewWifi.Size = new System.Drawing.Size(437, 134);
            this.listViewWifi.TabIndex = 16;
            this.listViewWifi.UseCompatibleStateImageBehavior = false;
            this.listViewWifi.View = System.Windows.Forms.View.Details;
            this.listViewWifi.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.listViewWifi_ItemSelectionChanged);
            // 
            // columnHeaderSSID
            // 
            this.columnHeaderSSID.Text = "SSID";
            this.columnHeaderSSID.Width = 100;
            // 
            // columnHeaderAuth
            // 
            this.columnHeaderAuth.Text = "Auth";
            this.columnHeaderAuth.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeaderAuth.Width = 205;
            // 
            // columnHeaderRSSI
            // 
            this.columnHeaderRSSI.Text = "RSSI";
            this.columnHeaderRSSI.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeaderRSSI.Width = 129;
            // 
            // textBoxWifiGateway
            // 
            this.textBoxWifiGateway.Location = new System.Drawing.Point(227, 327);
            this.textBoxWifiGateway.Name = "textBoxWifiGateway";
            this.textBoxWifiGateway.Size = new System.Drawing.Size(129, 21);
            this.textBoxWifiGateway.TabIndex = 15;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(166, 333);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(47, 12);
            this.label27.TabIndex = 14;
            this.label27.Text = "Gateway";
            // 
            // textBoxWifiSubmask
            // 
            this.textBoxWifiSubmask.Location = new System.Drawing.Point(227, 303);
            this.textBoxWifiSubmask.Name = "textBoxWifiSubmask";
            this.textBoxWifiSubmask.Size = new System.Drawing.Size(129, 21);
            this.textBoxWifiSubmask.TabIndex = 13;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(164, 308);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(47, 12);
            this.label26.TabIndex = 12;
            this.label26.Text = "SubMask";
            // 
            // textBoxWifiIP
            // 
            this.textBoxWifiIP.Location = new System.Drawing.Point(227, 274);
            this.textBoxWifiIP.Name = "textBoxWifiIP";
            this.textBoxWifiIP.Size = new System.Drawing.Size(129, 21);
            this.textBoxWifiIP.TabIndex = 11;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(164, 279);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(17, 12);
            this.label25.TabIndex = 10;
            this.label25.Text = "IP";
            // 
            // textBoxWifiPassword
            // 
            this.textBoxWifiPassword.Location = new System.Drawing.Point(227, 248);
            this.textBoxWifiPassword.Name = "textBoxWifiPassword";
            this.textBoxWifiPassword.PasswordChar = '*';
            this.textBoxWifiPassword.Size = new System.Drawing.Size(129, 21);
            this.textBoxWifiPassword.TabIndex = 9;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(162, 254);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(53, 12);
            this.label24.TabIndex = 8;
            this.label24.Text = "Password";
            // 
            // comboBoxWifiEntryType
            // 
            this.comboBoxWifiEntryType.FormattingEnabled = true;
            this.comboBoxWifiEntryType.Location = new System.Drawing.Point(227, 222);
            this.comboBoxWifiEntryType.Name = "comboBoxWifiEntryType";
            this.comboBoxWifiEntryType.Size = new System.Drawing.Size(129, 20);
            this.comboBoxWifiEntryType.TabIndex = 7;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(162, 230);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(59, 12);
            this.label23.TabIndex = 6;
            this.label23.Text = "EntryType";
            // 
            // textBoxSSID
            // 
            this.textBoxSSID.Location = new System.Drawing.Point(207, 193);
            this.textBoxSSID.Name = "textBoxSSID";
            this.textBoxSSID.ReadOnly = true;
            this.textBoxSSID.Size = new System.Drawing.Size(149, 21);
            this.textBoxSSID.TabIndex = 5;
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(162, 202);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(29, 12);
            this.label22.TabIndex = 4;
            this.label22.Text = "SSID";
            // 
            // checkBoxDHCP
            // 
            this.checkBoxDHCP.AutoSize = true;
            this.checkBoxDHCP.Location = new System.Drawing.Point(359, 176);
            this.checkBoxDHCP.Name = "checkBoxDHCP";
            this.checkBoxDHCP.Size = new System.Drawing.Size(48, 16);
            this.checkBoxDHCP.TabIndex = 3;
            this.checkBoxDHCP.Text = "DHCP";
            this.checkBoxDHCP.UseVisualStyleBackColor = true;
            this.checkBoxDHCP.CheckedChanged += new System.EventHandler(this.checkBoxDHCP_CheckedChanged);
            // 
            // checkEnableWifi
            // 
            this.checkEnableWifi.AutoSize = true;
            this.checkEnableWifi.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.checkEnableWifi.Location = new System.Drawing.Point(161, 176);
            this.checkEnableWifi.Name = "checkEnableWifi";
            this.checkEnableWifi.Size = new System.Drawing.Size(60, 16);
            this.checkEnableWifi.TabIndex = 2;
            this.checkEnableWifi.Text = "Enable";
            this.checkEnableWifi.UseVisualStyleBackColor = true;
            this.checkEnableWifi.CheckedChanged += new System.EventHandler(this.checkEnableWifi_CheckedChanged);
            // 
            // buttonSearchWifi
            // 
            this.buttonSearchWifi.Location = new System.Drawing.Point(249, 145);
            this.buttonSearchWifi.Name = "buttonSearchWifi";
            this.buttonSearchWifi.Size = new System.Drawing.Size(75, 23);
            this.buttonSearchWifi.TabIndex = 1;
            this.buttonSearchWifi.Text = "Search";
            this.buttonSearchWifi.UseVisualStyleBackColor = true;
            this.buttonSearchWifi.Click += new System.EventHandler(this.buttonSearchWifi_Click);
            // 
            // comboBoxDevice
            // 
            this.comboBoxDevice.FormattingEnabled = true;
            this.comboBoxDevice.Location = new System.Drawing.Point(202, 8);
            this.comboBoxDevice.Name = "comboBoxDevice";
            this.comboBoxDevice.Size = new System.Drawing.Size(237, 20);
            this.comboBoxDevice.TabIndex = 1;
            this.comboBoxDevice.SelectedIndexChanged += new System.EventHandler(this.comboBoxDevice_SelectedIndexChanged);
            // 
            // labelKeyType
            // 
            this.labelKeyType.AutoSize = true;
            this.labelKeyType.Location = new System.Drawing.Point(363, 229);
            this.labelKeyType.Name = "labelKeyType";
            this.labelKeyType.Size = new System.Drawing.Size(47, 12);
            this.labelKeyType.TabIndex = 17;
            this.labelKeyType.Text = "KeyType";
            // 
            // comboBoxWifiKeyType
            // 
            this.comboBoxWifiKeyType.FormattingEnabled = true;
            this.comboBoxWifiKeyType.Items.AddRange(new object[] {
            "Hex",
            "ASCII"});
            this.comboBoxWifiKeyType.Location = new System.Drawing.Point(407, 224);
            this.comboBoxWifiKeyType.Name = "comboBoxWifiKeyType";
            this.comboBoxWifiKeyType.Size = new System.Drawing.Size(121, 20);
            this.comboBoxWifiKeyType.TabIndex = 18;
            // 
            // buttonWifiOK
            // 
            this.buttonWifiOK.Location = new System.Drawing.Point(249, 348);
            this.buttonWifiOK.Name = "buttonWifiOK";
            this.buttonWifiOK.Size = new System.Drawing.Size(75, 23);
            this.buttonWifiOK.TabIndex = 19;
            this.buttonWifiOK.Text = "OK";
            this.buttonWifiOK.UseVisualStyleBackColor = true;
            this.buttonWifiOK.Click += new System.EventHandler(this.buttonWifiOK_Click);
            // 
            // DevConfigForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(677, 437);
            this.Controls.Add(this.comboBoxDevice);
            this.Controls.Add(this.tabControlConfigs);
            this.Name = "DevConfigForm";
            this.Text = "DevConfigForm";
            this.Shown += new System.EventHandler(this.DevConfigForm_Shown);
            this.tabControlConfigs.ResumeLayout(false);
            this.tabPageGeneral.ResumeLayout(false);
            this.tabPageGeneral.PerformLayout();
            this.tabPageWifi.ResumeLayout(false);
            this.tabPageWifi.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControlConfigs;
        private System.Windows.Forms.TabPage tabPageGeneral;
        private System.Windows.Forms.TabPage tabPageNetwork;
        private System.Windows.Forms.ComboBox comboBoxDevice;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.TextBox textBoxSerial;
        private System.Windows.Forms.TextBox textBoxReleaseDate;
        private System.Windows.Forms.TextBox textBox1SystemVersion;
        private System.Windows.Forms.TextBox textBoxDigitalChannel;
        private System.Windows.Forms.TextBox textBoxExChannel;
        private System.Windows.Forms.TextBox textBoxTalkOut;
        private System.Windows.Forms.TextBox textBoxTalkIn;
        private System.Windows.Forms.TextBox textBoxAlarmOut;
        private System.Windows.Forms.TextBox textBoxAlarmIn;
        private System.Windows.Forms.TextBox textBoxAudioIn;
        private System.Windows.Forms.TextBox textBoxVideoOut;
        private System.Windows.Forms.TextBox textBoxRecordChannel;
        private System.Windows.Forms.TextBox textBoxDeviceNo;
        private System.Windows.Forms.TextBox textBoxStandbyTime;
        private System.Windows.Forms.TextBox textBoxDeviceName;
        private System.Windows.Forms.ComboBox comboBoxDiskFullTo;
        private System.Windows.Forms.ComboBox comboBoxVideoStandard;
        private System.Windows.Forms.ComboBox comboBoxLanguage;
        private System.Windows.Forms.ComboBox comboBoxTimeFormat;
        private System.Windows.Forms.ComboBox comboBoxDateSeparator;
        private System.Windows.Forms.ComboBox comboBoxDateFormat;
        private System.Windows.Forms.Button buttongGeneralOk;
        private System.Windows.Forms.TabPage tabPageWifi;
        private System.Windows.Forms.Button buttonSearchWifi;
        private System.Windows.Forms.CheckBox checkEnableWifi;
        private System.Windows.Forms.CheckBox checkBoxDHCP;
        private System.Windows.Forms.TextBox textBoxSSID;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.ComboBox comboBoxWifiEntryType;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.TextBox textBoxWifiPassword;
        private System.Windows.Forms.TextBox textBoxWifiIP;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox textBoxWifiSubmask;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.TextBox textBoxWifiGateway;
        private System.Windows.Forms.ListView listViewWifi;
        private System.Windows.Forms.ColumnHeader columnHeaderSSID;
        private System.Windows.Forms.ColumnHeader columnHeaderAuth;
        private System.Windows.Forms.ColumnHeader columnHeaderRSSI;
        private System.Windows.Forms.Label labelKeyType;
        private System.Windows.Forms.ComboBox comboBoxWifiKeyType;
        private System.Windows.Forms.Button buttonWifiOK;
    }
}