namespace ClientDemo
{
    partial class AddDevForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AddDevForm));
            this.textBoxport = new System.Windows.Forms.TextBox();
            this.labelport = new System.Windows.Forms.Label();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.labelIP = new System.Windows.Forms.Label();
            this.labelpassword = new System.Windows.Forms.Label();
            this.labelUsername = new System.Windows.Forms.Label();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.textBoxUsername = new System.Windows.Forms.TextBox();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonSearch = new System.Windows.Forms.Button();
            this.labelDevName = new System.Windows.Forms.Label();
            this.textBoxDevName = new System.Windows.Forms.TextBox();
            this.listViewDevSearched = new System.Windows.Forms.ListView();
            this.columnHeaderNo = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderIP = new System.Windows.Forms.ColumnHeader();
            this.columnHeaderPort = new System.Windows.Forms.ColumnHeader();
            this.SuspendLayout();
            // 
            // textBoxport
            // 
            resources.ApplyResources(this.textBoxport, "textBoxport");
            this.textBoxport.Name = "textBoxport";
            // 
            // labelport
            // 
            resources.ApplyResources(this.labelport, "labelport");
            this.labelport.Name = "labelport";
            // 
            // textBoxIP
            // 
            resources.ApplyResources(this.textBoxIP, "textBoxIP");
            this.textBoxIP.Name = "textBoxIP";
            // 
            // labelIP
            // 
            resources.ApplyResources(this.labelIP, "labelIP");
            this.labelIP.Name = "labelIP";
            // 
            // labelpassword
            // 
            resources.ApplyResources(this.labelpassword, "labelpassword");
            this.labelpassword.Name = "labelpassword";
            // 
            // labelUsername
            // 
            resources.ApplyResources(this.labelUsername, "labelUsername");
            this.labelUsername.Name = "labelUsername";
            // 
            // textBoxPassword
            // 
            resources.ApplyResources(this.textBoxPassword, "textBoxPassword");
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.UseSystemPasswordChar = true;
            // 
            // textBoxUsername
            // 
            resources.ApplyResources(this.textBoxUsername, "textBoxUsername");
            this.textBoxUsername.Name = "textBoxUsername";
            // 
            // buttonOK
            // 
            resources.ApplyResources(this.buttonOK, "buttonOK");
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonCancel
            // 
            resources.ApplyResources(this.buttonCancel, "buttonCancel");
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonSearch
            // 
            resources.ApplyResources(this.buttonSearch, "buttonSearch");
            this.buttonSearch.Name = "buttonSearch";
            this.buttonSearch.UseVisualStyleBackColor = true;
            this.buttonSearch.Click += new System.EventHandler(this.buttonSearch_Click);
            // 
            // labelDevName
            // 
            resources.ApplyResources(this.labelDevName, "labelDevName");
            this.labelDevName.Name = "labelDevName";
            // 
            // textBoxDevName
            // 
            resources.ApplyResources(this.textBoxDevName, "textBoxDevName");
            this.textBoxDevName.Name = "textBoxDevName";
            // 
            // listViewDevSearched
            // 
            this.listViewDevSearched.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeaderNo,
            this.columnHeaderIP,
            this.columnHeaderPort});
            this.listViewDevSearched.FullRowSelect = true;
            resources.ApplyResources(this.listViewDevSearched, "listViewDevSearched");
            this.listViewDevSearched.Name = "listViewDevSearched";
            this.listViewDevSearched.UseCompatibleStateImageBehavior = false;
            this.listViewDevSearched.View = System.Windows.Forms.View.Details;
            this.listViewDevSearched.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listViewDevSearched_MouseDoubleClick);
            this.listViewDevSearched.SelectedIndexChanged += new System.EventHandler(this.listViewDevSearched_SelectedIndexChanged);
            // 
            // columnHeaderNo
            // 
            resources.ApplyResources(this.columnHeaderNo, "columnHeaderNo");
            // 
            // columnHeaderIP
            // 
            resources.ApplyResources(this.columnHeaderIP, "columnHeaderIP");
            // 
            // columnHeaderPort
            // 
            resources.ApplyResources(this.columnHeaderPort, "columnHeaderPort");
            // 
            // AddDevForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.listViewDevSearched);
            this.Controls.Add(this.textBoxDevName);
            this.Controls.Add(this.labelDevName);
            this.Controls.Add(this.buttonSearch);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.textBoxport);
            this.Controls.Add(this.labelport);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.labelIP);
            this.Controls.Add(this.labelpassword);
            this.Controls.Add(this.labelUsername);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.textBoxUsername);
            this.MaximizeBox = false;
            this.Name = "AddDevForm";
            this.ShowInTaskbar = false;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxport;
        private System.Windows.Forms.Label labelport;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Label labelIP;
        private System.Windows.Forms.Label labelpassword;
        private System.Windows.Forms.Label labelUsername;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.TextBox textBoxUsername;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonSearch;
        private System.Windows.Forms.Label labelDevName;
        private System.Windows.Forms.TextBox textBoxDevName;
        private System.Windows.Forms.ListView listViewDevSearched;
        private System.Windows.Forms.ColumnHeader columnHeaderNo;
        private System.Windows.Forms.ColumnHeader columnHeaderIP;
        private System.Windows.Forms.ColumnHeader columnHeaderPort;
    }
}