namespace ClientDemo
{
    partial class ClientDemo
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
            this.btnTransparent = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.btnPTZ = new System.Windows.Forms.Button();
            this.btncolor = new System.Windows.Forms.Button();
            this.btnplayback = new System.Windows.Forms.Button();
            this.btnDevConfig = new System.Windows.Forms.Button();
            this.btnNetAlarm = new System.Windows.Forms.Button();
            this.btnNetKeyboard = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnTransparent
            // 
            this.btnTransparent.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnTransparent.Location = new System.Drawing.Point(993, 527);
            this.btnTransparent.Name = "btnTransparent";
            this.btnTransparent.Size = new System.Drawing.Size(99, 31);
            this.btnTransparent.TabIndex = 1;
            this.btnTransparent.Text = "TransparentCom";
            this.btnTransparent.UseVisualStyleBackColor = true;
            this.btnTransparent.Click += new System.EventHandler(this.btnTransparent_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "1",
            "4",
            "9",
            "16"});
            this.comboBox1.Location = new System.Drawing.Point(938, 617);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(103, 20);
            this.comboBox1.TabIndex = 3;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // btnPTZ
            // 
            this.btnPTZ.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnPTZ.Location = new System.Drawing.Point(993, 452);
            this.btnPTZ.Name = "btnPTZ";
            this.btnPTZ.Size = new System.Drawing.Size(98, 30);
            this.btnPTZ.TabIndex = 13;
            this.btnPTZ.Text = "PTZ";
            this.btnPTZ.UseVisualStyleBackColor = true;
            this.btnPTZ.Click += new System.EventHandler(this.btnPTZ_Click);
            // 
            // btncolor
            // 
            this.btncolor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btncolor.Enabled = false;
            this.btncolor.Location = new System.Drawing.Point(886, 488);
            this.btncolor.Name = "btncolor";
            this.btncolor.Size = new System.Drawing.Size(100, 31);
            this.btncolor.TabIndex = 14;
            this.btncolor.Text = "Color";
            this.btncolor.UseVisualStyleBackColor = true;
            // 
            // btnplayback
            // 
            this.btnplayback.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnplayback.Location = new System.Drawing.Point(993, 489);
            this.btnplayback.Name = "btnplayback";
            this.btnplayback.Size = new System.Drawing.Size(98, 30);
            this.btnplayback.TabIndex = 15;
            this.btnplayback.Text = "Playback";
            this.btnplayback.UseVisualStyleBackColor = true;
            this.btnplayback.Click += new System.EventHandler(this.btnplayback_Click);
            // 
            // btnDevConfig
            // 
            this.btnDevConfig.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnDevConfig.Location = new System.Drawing.Point(886, 527);
            this.btnDevConfig.Name = "btnDevConfig";
            this.btnDevConfig.Size = new System.Drawing.Size(100, 31);
            this.btnDevConfig.TabIndex = 16;
            this.btnDevConfig.Text = "DevConfig";
            this.btnDevConfig.UseVisualStyleBackColor = true;
            this.btnDevConfig.Click += new System.EventHandler(this.btnDevConfig_Click);
            // 
            // btnNetAlarm
            // 
            this.btnNetAlarm.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnNetAlarm.Enabled = false;
            this.btnNetAlarm.Location = new System.Drawing.Point(886, 564);
            this.btnNetAlarm.Name = "btnNetAlarm";
            this.btnNetAlarm.Size = new System.Drawing.Size(100, 31);
            this.btnNetAlarm.TabIndex = 17;
            this.btnNetAlarm.Text = "NetAlarm";
            this.btnNetAlarm.UseVisualStyleBackColor = true;
            // 
            // btnNetKeyboard
            // 
            this.btnNetKeyboard.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnNetKeyboard.Enabled = false;
            this.btnNetKeyboard.Location = new System.Drawing.Point(993, 564);
            this.btnNetKeyboard.Name = "btnNetKeyboard";
            this.btnNetKeyboard.Size = new System.Drawing.Size(99, 31);
            this.btnNetKeyboard.TabIndex = 18;
            this.btnNetKeyboard.Text = "NetKeyboard";
            this.btnNetKeyboard.UseVisualStyleBackColor = true;
            // 
            // ClientDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1123, 664);
            this.Controls.Add(this.btnNetKeyboard);
            this.Controls.Add(this.btnNetAlarm);
            this.Controls.Add(this.btnDevConfig);
            this.Controls.Add(this.btnplayback);
            this.Controls.Add(this.btncolor);
            this.Controls.Add(this.btnPTZ);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.btnTransparent);
            this.Name = "ClientDemo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ClientDemo";
            this.Load += new System.EventHandler(this.ClientDemo_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ClientDemo_Paint);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ClientDemo_FormClosed);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.ClientDemo_KeyUp);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ClientDemo_FormClosing);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnTransparent;
        public System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button btnPTZ;
        private System.Windows.Forms.Button btncolor;
        private System.Windows.Forms.Button btnplayback;
        private System.Windows.Forms.Button btnDevConfig;
        private System.Windows.Forms.Button btnNetAlarm;
        private System.Windows.Forms.Button btnNetKeyboard;
        public DevForm devForm;
    }
}