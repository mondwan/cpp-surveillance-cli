namespace ClientDemo
{
    partial class DevForm
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

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.DevTree = new System.Windows.Forms.TreeView();
            this.contextMenuStripDevTree = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addDeviceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.labelDevTree = new System.Windows.Forms.Label();
            this.contextMenuStripDevTree.SuspendLayout();
            this.SuspendLayout();
            // 
            // DevTree
            // 
            this.DevTree.ContextMenuStrip = this.contextMenuStripDevTree;
            this.DevTree.Location = new System.Drawing.Point(18, 16);
            this.DevTree.Name = "DevTree";
            this.DevTree.Size = new System.Drawing.Size(198, 420);
            this.DevTree.TabIndex = 0;
            this.DevTree.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.DevTree_NodeMouseDoubleClick);
            // 
            // contextMenuStripDevTree
            // 
            this.contextMenuStripDevTree.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addDeviceToolStripMenuItem});
            this.contextMenuStripDevTree.Name = "contextMenuStrip1";
            this.contextMenuStripDevTree.Size = new System.Drawing.Size(131, 26);
            // 
            // addDeviceToolStripMenuItem
            // 
            this.addDeviceToolStripMenuItem.Name = "addDeviceToolStripMenuItem";
            this.addDeviceToolStripMenuItem.Size = new System.Drawing.Size(130, 22);
            this.addDeviceToolStripMenuItem.Text = "Add Device";
            this.addDeviceToolStripMenuItem.Click += new System.EventHandler(this.addDeviceToolStripMenuItem_Click);
            // 
            // labelDevTree
            // 
            this.labelDevTree.AutoSize = true;
            this.labelDevTree.Location = new System.Drawing.Point(97, 1);
            this.labelDevTree.Name = "labelDevTree";
            this.labelDevTree.Size = new System.Drawing.Size(47, 12);
            this.labelDevTree.TabIndex = 1;
            this.labelDevTree.Text = "DevTree";
            // 
            // DevForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ContextMenuStrip = this.contextMenuStripDevTree;
            this.Controls.Add(this.labelDevTree);
            this.Controls.Add(this.DevTree);
            this.Name = "DevForm";
            this.Size = new System.Drawing.Size(231, 453);
            this.contextMenuStripDevTree.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip contextMenuStripDevTree;
        private System.Windows.Forms.ToolStripMenuItem addDeviceToolStripMenuItem;
        public System.Windows.Forms.TreeView DevTree;
        private System.Windows.Forms.Label labelDevTree;
    }
}
