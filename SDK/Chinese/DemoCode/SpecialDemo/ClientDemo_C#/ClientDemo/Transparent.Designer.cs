namespace ClientDemo
{
    partial class Form_Transpanrent
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
            this.groupBox_login = new System.Windows.Forms.GroupBox();
            this.button_login = new System.Windows.Forms.Button();
            this.textBox_password = new System.Windows.Forms.TextBox();
            this.textBox_port = new System.Windows.Forms.TextBox();
            this.textBox_username = new System.Windows.Forms.TextBox();
            this.textBox_ip = new System.Windows.Forms.TextBox();
            this.label_password = new System.Windows.Forms.Label();
            this.label_ = new System.Windows.Forms.Label();
            this.label_port = new System.Windows.Forms.Label();
            this.label_username_ip = new System.Windows.Forms.Label();
            this.groupBox_OpenTransparent = new System.Windows.Forms.GroupBox();
            this.button_write = new System.Windows.Forms.Button();
            this.button_open = new System.Windows.Forms.Button();
            this.button_close = new System.Windows.Forms.Button();
            this.comboBox_rate = new System.Windows.Forms.ComboBox();
            this.comboBox_check = new System.Windows.Forms.ComboBox();
            this.comboBox_stop = new System.Windows.Forms.ComboBox();
            this.comboBox_data = new System.Windows.Forms.ComboBox();
            this.label_rate = new System.Windows.Forms.Label();
            this.label_check = new System.Windows.Forms.Label();
            this.stopbit = new System.Windows.Forms.Label();
            this.label_databit = new System.Windows.Forms.Label();
            this.label_write = new System.Windows.Forms.Label();
            this.label_read = new System.Windows.Forms.Label();
            this.textBox_write = new System.Windows.Forms.TextBox();
            this.textBox_read = new System.Windows.Forms.TextBox();
            this.button_clear = new System.Windows.Forms.Button();
            this.groupBox_login.SuspendLayout();
            this.groupBox_OpenTransparent.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox_login
            // 
            this.groupBox_login.Controls.Add(this.button_login);
            this.groupBox_login.Controls.Add(this.textBox_password);
            this.groupBox_login.Controls.Add(this.textBox_port);
            this.groupBox_login.Controls.Add(this.textBox_username);
            this.groupBox_login.Controls.Add(this.textBox_ip);
            this.groupBox_login.Controls.Add(this.label_password);
            this.groupBox_login.Controls.Add(this.label_);
            this.groupBox_login.Controls.Add(this.label_port);
            this.groupBox_login.Controls.Add(this.label_username_ip);
            this.groupBox_login.Location = new System.Drawing.Point(22, 12);
            this.groupBox_login.Name = "groupBox_login";
            this.groupBox_login.Size = new System.Drawing.Size(585, 130);
            this.groupBox_login.TabIndex = 0;
            this.groupBox_login.TabStop = false;
            this.groupBox_login.Text = "Login";
            // 
            // button_login
            // 
            this.button_login.Location = new System.Drawing.Point(473, 21);
            this.button_login.Name = "button_login";
            this.button_login.Size = new System.Drawing.Size(96, 65);
            this.button_login.TabIndex = 2;
            this.button_login.Text = "Login";
            this.button_login.UseVisualStyleBackColor = true;
            this.button_login.Click += new System.EventHandler(this.button_login_Click);
            // 
            // textBox_password
            // 
            this.textBox_password.Location = new System.Drawing.Point(315, 65);
            this.textBox_password.Name = "textBox_password";
            this.textBox_password.Size = new System.Drawing.Size(119, 21);
            this.textBox_password.TabIndex = 1;
            // 
            // textBox_port
            // 
            this.textBox_port.Location = new System.Drawing.Point(308, 18);
            this.textBox_port.Name = "textBox_port";
            this.textBox_port.Size = new System.Drawing.Size(126, 21);
            this.textBox_port.TabIndex = 1;
            this.textBox_port.Text = "34567";
            // 
            // textBox_username
            // 
            this.textBox_username.Location = new System.Drawing.Point(94, 59);
            this.textBox_username.Name = "textBox_username";
            this.textBox_username.Size = new System.Drawing.Size(131, 21);
            this.textBox_username.TabIndex = 1;
            this.textBox_username.Text = "admin";
            // 
            // textBox_ip
            // 
            this.textBox_ip.Location = new System.Drawing.Point(81, 21);
            this.textBox_ip.Name = "textBox_ip";
            this.textBox_ip.Size = new System.Drawing.Size(144, 21);
            this.textBox_ip.TabIndex = 1;
            this.textBox_ip.Text = "10.2.4.55";
            // 
            // label_password
            // 
            this.label_password.AutoSize = true;
            this.label_password.Location = new System.Drawing.Point(256, 68);
            this.label_password.Name = "label_password";
            this.label_password.Size = new System.Drawing.Size(53, 12);
            this.label_password.TabIndex = 0;
            this.label_password.Text = "password";
            // 
            // label_
            // 
            this.label_.AutoSize = true;
            this.label_.Location = new System.Drawing.Point(35, 68);
            this.label_.Name = "label_";
            this.label_.Size = new System.Drawing.Size(53, 12);
            this.label_.TabIndex = 0;
            this.label_.Text = "username";
            // 
            // label_port
            // 
            this.label_port.AutoSize = true;
            this.label_port.Location = new System.Drawing.Point(256, 21);
            this.label_port.Name = "label_port";
            this.label_port.Size = new System.Drawing.Size(29, 12);
            this.label_port.TabIndex = 0;
            this.label_port.Text = "port";
            // 
            // label_username_ip
            // 
            this.label_username_ip.AutoSize = true;
            this.label_username_ip.Location = new System.Drawing.Point(35, 21);
            this.label_username_ip.Name = "label_username_ip";
            this.label_username_ip.Size = new System.Drawing.Size(17, 12);
            this.label_username_ip.TabIndex = 0;
            this.label_username_ip.Text = "ip";
            // 
            // groupBox_OpenTransparent
            // 
            this.groupBox_OpenTransparent.Controls.Add(this.button_write);
            this.groupBox_OpenTransparent.Controls.Add(this.button_open);
            this.groupBox_OpenTransparent.Controls.Add(this.button_close);
            this.groupBox_OpenTransparent.Controls.Add(this.comboBox_rate);
            this.groupBox_OpenTransparent.Controls.Add(this.comboBox_check);
            this.groupBox_OpenTransparent.Controls.Add(this.comboBox_stop);
            this.groupBox_OpenTransparent.Controls.Add(this.comboBox_data);
            this.groupBox_OpenTransparent.Controls.Add(this.label_rate);
            this.groupBox_OpenTransparent.Controls.Add(this.label_check);
            this.groupBox_OpenTransparent.Controls.Add(this.stopbit);
            this.groupBox_OpenTransparent.Controls.Add(this.label_databit);
            this.groupBox_OpenTransparent.Location = new System.Drawing.Point(22, 149);
            this.groupBox_OpenTransparent.Name = "groupBox_OpenTransparent";
            this.groupBox_OpenTransparent.Size = new System.Drawing.Size(459, 146);
            this.groupBox_OpenTransparent.TabIndex = 1;
            this.groupBox_OpenTransparent.TabStop = false;
            this.groupBox_OpenTransparent.Text = "OpenTransparent485";
            // 
            // button_write
            // 
            this.button_write.Location = new System.Drawing.Point(338, 105);
            this.button_write.Name = "button_write";
            this.button_write.Size = new System.Drawing.Size(96, 41);
            this.button_write.TabIndex = 2;
            this.button_write.Text = "Write";
            this.button_write.UseVisualStyleBackColor = true;
            this.button_write.Click += new System.EventHandler(this.button_write_Click);
            // 
            // button_open
            // 
            this.button_open.Location = new System.Drawing.Point(338, 13);
            this.button_open.Name = "button_open";
            this.button_open.Size = new System.Drawing.Size(96, 41);
            this.button_open.TabIndex = 2;
            this.button_open.Text = "Open";
            this.button_open.UseVisualStyleBackColor = true;
            this.button_open.Click += new System.EventHandler(this.button_open_Click);
            // 
            // button_close
            // 
            this.button_close.Location = new System.Drawing.Point(338, 60);
            this.button_close.Name = "button_close";
            this.button_close.Size = new System.Drawing.Size(96, 41);
            this.button_close.TabIndex = 2;
            this.button_close.Text = "Close";
            this.button_close.UseVisualStyleBackColor = true;
            this.button_close.Click += new System.EventHandler(this.button_close_Click);
            // 
            // comboBox_rate
            // 
            this.comboBox_rate.FormattingEnabled = true;
            this.comboBox_rate.Location = new System.Drawing.Point(150, 97);
            this.comboBox_rate.Name = "comboBox_rate";
            this.comboBox_rate.Size = new System.Drawing.Size(121, 20);
            this.comboBox_rate.TabIndex = 1;
            // 
            // comboBox_check
            // 
            this.comboBox_check.FormattingEnabled = true;
            this.comboBox_check.Location = new System.Drawing.Point(150, 71);
            this.comboBox_check.Name = "comboBox_check";
            this.comboBox_check.Size = new System.Drawing.Size(121, 20);
            this.comboBox_check.TabIndex = 1;
            // 
            // comboBox_stop
            // 
            this.comboBox_stop.FormattingEnabled = true;
            this.comboBox_stop.Location = new System.Drawing.Point(150, 50);
            this.comboBox_stop.Name = "comboBox_stop";
            this.comboBox_stop.Size = new System.Drawing.Size(121, 20);
            this.comboBox_stop.TabIndex = 1;
            // 
            // comboBox_data
            // 
            this.comboBox_data.FormattingEnabled = true;
            this.comboBox_data.Location = new System.Drawing.Point(150, 18);
            this.comboBox_data.Name = "comboBox_data";
            this.comboBox_data.Size = new System.Drawing.Size(121, 20);
            this.comboBox_data.TabIndex = 1;
            // 
            // label_rate
            // 
            this.label_rate.AutoSize = true;
            this.label_rate.Location = new System.Drawing.Point(22, 113);
            this.label_rate.Name = "label_rate";
            this.label_rate.Size = new System.Drawing.Size(47, 12);
            this.label_rate.TabIndex = 0;
            this.label_rate.Text = "RateBit";
            // 
            // label_check
            // 
            this.label_check.AutoSize = true;
            this.label_check.Location = new System.Drawing.Point(22, 79);
            this.label_check.Name = "label_check";
            this.label_check.Size = new System.Drawing.Size(53, 12);
            this.label_check.TabIndex = 0;
            this.label_check.Text = "CheckBit";
            // 
            // stopbit
            // 
            this.stopbit.AutoSize = true;
            this.stopbit.Location = new System.Drawing.Point(22, 50);
            this.stopbit.Name = "stopbit";
            this.stopbit.Size = new System.Drawing.Size(77, 12);
            this.stopbit.TabIndex = 0;
            this.stopbit.Text = "StopBit(1,2)";
            // 
            // label_databit
            // 
            this.label_databit.AutoSize = true;
            this.label_databit.Location = new System.Drawing.Point(22, 21);
            this.label_databit.Name = "label_databit";
            this.label_databit.Size = new System.Drawing.Size(101, 12);
            this.label_databit.TabIndex = 0;
            this.label_databit.Text = "DataBit(5,6,7,8)";
            // 
            // label_write
            // 
            this.label_write.AutoSize = true;
            this.label_write.Location = new System.Drawing.Point(22, 302);
            this.label_write.Name = "label_write";
            this.label_write.Size = new System.Drawing.Size(35, 12);
            this.label_write.TabIndex = 2;
            this.label_write.Text = "Write";
            // 
            // label_read
            // 
            this.label_read.AutoSize = true;
            this.label_read.Location = new System.Drawing.Point(251, 302);
            this.label_read.Name = "label_read";
            this.label_read.Size = new System.Drawing.Size(29, 12);
            this.label_read.TabIndex = 2;
            this.label_read.Text = "Read";
            // 
            // textBox_write
            // 
            this.textBox_write.Location = new System.Drawing.Point(24, 332);
            this.textBox_write.Name = "textBox_write";
            this.textBox_write.Size = new System.Drawing.Size(192, 21);
            this.textBox_write.TabIndex = 3;
            this.textBox_write.Text = "abc";
            // 
            // textBox_read
            // 
            this.textBox_read.Location = new System.Drawing.Point(264, 332);
            this.textBox_read.Name = "textBox_read";
            this.textBox_read.ReadOnly = true;
            this.textBox_read.Size = new System.Drawing.Size(192, 21);
            this.textBox_read.TabIndex = 3;
            // 
            // button_clear
            // 
            this.button_clear.Location = new System.Drawing.Point(495, 323);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(75, 30);
            this.button_clear.TabIndex = 4;
            this.button_clear.Text = "Clear";
            this.button_clear.UseVisualStyleBackColor = true;
            // 
            // Form_Transpanrent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(614, 385);
            this.Controls.Add(this.button_clear);
            this.Controls.Add(this.textBox_read);
            this.Controls.Add(this.textBox_write);
            this.Controls.Add(this.label_read);
            this.Controls.Add(this.label_write);
            this.Controls.Add(this.groupBox_OpenTransparent);
            this.Controls.Add(this.groupBox_login);
            this.Name = "Form_Transpanrent";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Transparent";
            this.groupBox_login.ResumeLayout(false);
            this.groupBox_login.PerformLayout();
            this.groupBox_OpenTransparent.ResumeLayout(false);
            this.groupBox_OpenTransparent.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox_login;
        private System.Windows.Forms.TextBox textBox_username;
        private System.Windows.Forms.TextBox textBox_ip;
        private System.Windows.Forms.Label label_password;
        private System.Windows.Forms.Label label_;
        private System.Windows.Forms.Label label_port;
        private System.Windows.Forms.Label label_username_ip;
        private System.Windows.Forms.TextBox textBox_password;
        private System.Windows.Forms.TextBox textBox_port;
        private System.Windows.Forms.GroupBox groupBox_OpenTransparent;
        private System.Windows.Forms.Label label_rate;
        private System.Windows.Forms.Label label_check;
        private System.Windows.Forms.Label stopbit;
        private System.Windows.Forms.Label label_databit;
        private System.Windows.Forms.ComboBox comboBox_rate;
        private System.Windows.Forms.ComboBox comboBox_check;
        private System.Windows.Forms.ComboBox comboBox_stop;
        private System.Windows.Forms.ComboBox comboBox_data;
        private System.Windows.Forms.Label label_write;
        private System.Windows.Forms.Label label_read;
        private System.Windows.Forms.TextBox textBox_write;
        private System.Windows.Forms.TextBox textBox_read;
        private System.Windows.Forms.Button button_login;
        private System.Windows.Forms.Button button_write;
        private System.Windows.Forms.Button button_open;
        private System.Windows.Forms.Button button_close;
        private System.Windows.Forms.Button button_clear;
    }
}

