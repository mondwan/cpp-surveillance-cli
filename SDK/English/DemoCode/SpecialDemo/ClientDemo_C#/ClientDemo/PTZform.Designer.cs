namespace ClientDemo
{
    partial class PTZForm
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
            this.buttonMenu = new System.Windows.Forms.Button();
            this.buttonDown = new System.Windows.Forms.Button();
            this.buttonRight = new System.Windows.Forms.Button();
            this.buttonLeft = new System.Windows.Forms.Button();
            this.buttonUp = new System.Windows.Forms.Button();
            this.buttonZoomIn = new System.Windows.Forms.Button();
            this.buttonZoomOut = new System.Windows.Forms.Button();
            this.buttonFocusOut = new System.Windows.Forms.Button();
            this.buttonFocusIn = new System.Windows.Forms.Button();
            this.buttonApertureReduce = new System.Windows.Forms.Button();
            this.buttonApertureAdd = new System.Windows.Forms.Button();
            this.buttonScanStop = new System.Windows.Forms.Button();
            this.buttonScanStart = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonMenu
            // 
            this.buttonMenu.Location = new System.Drawing.Point(81, 75);
            this.buttonMenu.Name = "buttonMenu";
            this.buttonMenu.Size = new System.Drawing.Size(44, 23);
            this.buttonMenu.TabIndex = 9;
            this.buttonMenu.Text = "MENU";
            this.buttonMenu.UseVisualStyleBackColor = true;
            this.buttonMenu.MouseLeave += new System.EventHandler(this.buttonMenu_MouseLeave);
            this.buttonMenu.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonMenu_MouseDown);
            this.buttonMenu.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonMenu_MouseUp);
            // 
            // buttonDown
            // 
            this.buttonDown.Location = new System.Drawing.Point(81, 124);
            this.buttonDown.Name = "buttonDown";
            this.buttonDown.Size = new System.Drawing.Size(44, 23);
            this.buttonDown.TabIndex = 8;
            this.buttonDown.Text = "DOWN";
            this.buttonDown.UseVisualStyleBackColor = true;
            this.buttonDown.MouseLeave += new System.EventHandler(this.buttonDown_MouseLeave);
            this.buttonDown.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonDown_MouseDown);
            this.buttonDown.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonDown_MouseUp);
            // 
            // buttonRight
            // 
            this.buttonRight.Location = new System.Drawing.Point(141, 76);
            this.buttonRight.Name = "buttonRight";
            this.buttonRight.Size = new System.Drawing.Size(44, 23);
            this.buttonRight.TabIndex = 7;
            this.buttonRight.Text = "RIGHT";
            this.buttonRight.UseVisualStyleBackColor = true;
            this.buttonRight.MouseLeave += new System.EventHandler(this.buttonRight_MouseLeave);
            this.buttonRight.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonRight_MouseDown);
            this.buttonRight.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonRight_MouseUp);
            // 
            // buttonLeft
            // 
            this.buttonLeft.Location = new System.Drawing.Point(20, 77);
            this.buttonLeft.Name = "buttonLeft";
            this.buttonLeft.Size = new System.Drawing.Size(44, 23);
            this.buttonLeft.TabIndex = 6;
            this.buttonLeft.Text = "LEFT";
            this.buttonLeft.UseVisualStyleBackColor = true;
            this.buttonLeft.MouseLeave += new System.EventHandler(this.buttonLeft_MouseLeave);
            this.buttonLeft.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonLeft_MouseDown);
            this.buttonLeft.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonLeft_MouseUp);
            // 
            // buttonUp
            // 
            this.buttonUp.Location = new System.Drawing.Point(81, 25);
            this.buttonUp.Name = "buttonUp";
            this.buttonUp.Size = new System.Drawing.Size(44, 23);
            this.buttonUp.TabIndex = 5;
            this.buttonUp.Text = "UP";
            this.buttonUp.UseVisualStyleBackColor = true;
            this.buttonUp.MouseLeave += new System.EventHandler(this.buttonUp_MouseLeave);
            this.buttonUp.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonUp_MouseDown);
            this.buttonUp.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonUp_MouseUp);
            // 
            // buttonZoomIn
            // 
            this.buttonZoomIn.Location = new System.Drawing.Point(33, 154);
            this.buttonZoomIn.Name = "buttonZoomIn";
            this.buttonZoomIn.Size = new System.Drawing.Size(29, 23);
            this.buttonZoomIn.TabIndex = 10;
            this.buttonZoomIn.Text = "+";
            this.buttonZoomIn.UseVisualStyleBackColor = true;
            this.buttonZoomIn.MouseLeave += new System.EventHandler(this.buttonZoomIn_MouseLeave);
            this.buttonZoomIn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonZoomIn_MouseDown);
            this.buttonZoomIn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonZoomIn_MouseUp);
            // 
            // buttonZoomOut
            // 
            this.buttonZoomOut.Location = new System.Drawing.Point(139, 154);
            this.buttonZoomOut.Name = "buttonZoomOut";
            this.buttonZoomOut.Size = new System.Drawing.Size(29, 23);
            this.buttonZoomOut.TabIndex = 11;
            this.buttonZoomOut.Text = "-";
            this.buttonZoomOut.UseVisualStyleBackColor = true;
            this.buttonZoomOut.MouseLeave += new System.EventHandler(this.buttonZoomOut_MouseLeave);
            this.buttonZoomOut.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonZoomOut_MouseDown);
            this.buttonZoomOut.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonZoomOut_MouseUp);
            // 
            // buttonFocusOut
            // 
            this.buttonFocusOut.Location = new System.Drawing.Point(139, 183);
            this.buttonFocusOut.Name = "buttonFocusOut";
            this.buttonFocusOut.Size = new System.Drawing.Size(29, 23);
            this.buttonFocusOut.TabIndex = 13;
            this.buttonFocusOut.Text = "-";
            this.buttonFocusOut.UseVisualStyleBackColor = true;
            this.buttonFocusOut.MouseLeave += new System.EventHandler(this.buttonFocusOut_MouseLeave);
            this.buttonFocusOut.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonFocusOut_MouseDown);
            this.buttonFocusOut.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonFocusOut_MouseUp);
            // 
            // buttonFocusIn
            // 
            this.buttonFocusIn.Location = new System.Drawing.Point(33, 183);
            this.buttonFocusIn.Name = "buttonFocusIn";
            this.buttonFocusIn.Size = new System.Drawing.Size(29, 23);
            this.buttonFocusIn.TabIndex = 12;
            this.buttonFocusIn.Text = "+";
            this.buttonFocusIn.UseVisualStyleBackColor = true;
            this.buttonFocusIn.MouseLeave += new System.EventHandler(this.buttonFocusIn_MouseLeave);
            this.buttonFocusIn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonFocusIn_MouseDown);
            this.buttonFocusIn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonFocusIn_MouseUp);
            // 
            // buttonApertureReduce
            // 
            this.buttonApertureReduce.Location = new System.Drawing.Point(139, 212);
            this.buttonApertureReduce.Name = "buttonApertureReduce";
            this.buttonApertureReduce.Size = new System.Drawing.Size(29, 23);
            this.buttonApertureReduce.TabIndex = 15;
            this.buttonApertureReduce.Text = "-";
            this.buttonApertureReduce.UseVisualStyleBackColor = true;
            this.buttonApertureReduce.MouseLeave += new System.EventHandler(this.buttonApertureReduce_MouseLeave);
            this.buttonApertureReduce.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonApertureReduce_MouseDown);
            this.buttonApertureReduce.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonApertureReduce_MouseUp);
            // 
            // buttonApertureAdd
            // 
            this.buttonApertureAdd.Location = new System.Drawing.Point(33, 212);
            this.buttonApertureAdd.Name = "buttonApertureAdd";
            this.buttonApertureAdd.Size = new System.Drawing.Size(29, 23);
            this.buttonApertureAdd.TabIndex = 14;
            this.buttonApertureAdd.Text = "+";
            this.buttonApertureAdd.UseVisualStyleBackColor = true;
            this.buttonApertureAdd.MouseLeave += new System.EventHandler(this.buttonApertureAdd_MouseLeave);
            this.buttonApertureAdd.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonApertureAdd_MouseDown);
            this.buttonApertureAdd.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonApertureAdd_MouseUp);
            // 
            // buttonScanStop
            // 
            this.buttonScanStop.Location = new System.Drawing.Point(125, 247);
            this.buttonScanStop.Name = "buttonScanStop";
            this.buttonScanStop.Size = new System.Drawing.Size(43, 23);
            this.buttonScanStop.TabIndex = 17;
            this.buttonScanStop.Text = "Stop";
            this.buttonScanStop.UseVisualStyleBackColor = true;
            this.buttonScanStop.MouseClick += new System.Windows.Forms.MouseEventHandler(this.buttonScanStop_MouseClick);
            // 
            // buttonScanStart
            // 
            this.buttonScanStart.Location = new System.Drawing.Point(33, 247);
            this.buttonScanStart.Name = "buttonScanStart";
            this.buttonScanStart.Size = new System.Drawing.Size(43, 23);
            this.buttonScanStart.TabIndex = 16;
            this.buttonScanStart.Text = "Start";
            this.buttonScanStart.UseVisualStyleBackColor = true;
            this.buttonScanStart.MouseClick += new System.Windows.Forms.MouseEventHandler(this.buttonScanStart_MouseClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(86, 160);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 18;
            this.label1.Text = "Zoom";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(84, 188);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 19;
            this.label2.Text = "Focus";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(76, 217);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 20;
            this.label3.Text = "Aperture";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(86, 253);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 21;
            this.label4.Text = "Scan";
            // 
            // PTZForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(198, 304);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonScanStop);
            this.Controls.Add(this.buttonScanStart);
            this.Controls.Add(this.buttonApertureReduce);
            this.Controls.Add(this.buttonApertureAdd);
            this.Controls.Add(this.buttonFocusOut);
            this.Controls.Add(this.buttonFocusIn);
            this.Controls.Add(this.buttonZoomOut);
            this.Controls.Add(this.buttonZoomIn);
            this.Controls.Add(this.buttonMenu);
            this.Controls.Add(this.buttonDown);
            this.Controls.Add(this.buttonRight);
            this.Controls.Add(this.buttonLeft);
            this.Controls.Add(this.buttonUp);
            this.Name = "PTZForm";
            this.Text = "PTZForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonMenu;
        private System.Windows.Forms.Button buttonDown;
        private System.Windows.Forms.Button buttonRight;
        private System.Windows.Forms.Button buttonLeft;
        private System.Windows.Forms.Button buttonUp;
        private System.Windows.Forms.Button buttonZoomIn;
        private System.Windows.Forms.Button buttonZoomOut;
        private System.Windows.Forms.Button buttonFocusOut;
        private System.Windows.Forms.Button buttonFocusIn;
        private System.Windows.Forms.Button buttonApertureReduce;
        private System.Windows.Forms.Button buttonApertureAdd;
        private System.Windows.Forms.Button buttonScanStop;
        private System.Windows.Forms.Button buttonScanStart;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
    }
}