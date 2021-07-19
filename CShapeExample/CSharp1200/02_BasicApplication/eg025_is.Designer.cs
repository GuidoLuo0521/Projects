namespace CSharp1200._02_BasicApplication
{
    partial class eg025_is
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rb_ObjectString = new System.Windows.Forms.RadioButton();
            this.rb_ObjectFile = new System.Windows.Forms.RadioButton();
            this.rb_TypeString = new System.Windows.Forms.RadioButton();
            this.rb_TypeFileInfo = new System.Windows.Forms.RadioButton();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rb_ObjectFile);
            this.groupBox1.Controls.Add(this.rb_ObjectString);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(220, 94);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "对象";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rb_TypeFileInfo);
            this.groupBox2.Controls.Add(this.rb_TypeString);
            this.groupBox2.Location = new System.Drawing.Point(265, 13);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(247, 94);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "类型";
            // 
            // rb_ObjectString
            // 
            this.rb_ObjectString.AutoSize = true;
            this.rb_ObjectString.Checked = true;
            this.rb_ObjectString.Location = new System.Drawing.Point(25, 21);
            this.rb_ObjectString.Name = "rb_ObjectString";
            this.rb_ObjectString.Size = new System.Drawing.Size(83, 16);
            this.rb_ObjectString.TabIndex = 0;
            this.rb_ObjectString.TabStop = true;
            this.rb_ObjectString.Text = "字符串对象";
            this.rb_ObjectString.UseVisualStyleBackColor = true;
            // 
            // rb_ObjectFile
            // 
            this.rb_ObjectFile.AutoSize = true;
            this.rb_ObjectFile.Location = new System.Drawing.Point(25, 60);
            this.rb_ObjectFile.Name = "rb_ObjectFile";
            this.rb_ObjectFile.Size = new System.Drawing.Size(71, 16);
            this.rb_ObjectFile.TabIndex = 0;
            this.rb_ObjectFile.TabStop = true;
            this.rb_ObjectFile.Text = "文件对象";
            this.rb_ObjectFile.UseVisualStyleBackColor = true;
            // 
            // rb_TypeString
            // 
            this.rb_TypeString.AutoSize = true;
            this.rb_TypeString.Checked = true;
            this.rb_TypeString.Location = new System.Drawing.Point(36, 21);
            this.rb_TypeString.Name = "rb_TypeString";
            this.rb_TypeString.Size = new System.Drawing.Size(59, 16);
            this.rb_TypeString.TabIndex = 0;
            this.rb_TypeString.TabStop = true;
            this.rb_TypeString.Text = "string";
            this.rb_TypeString.UseVisualStyleBackColor = true;
            // 
            // rb_TypeFileInfo
            // 
            this.rb_TypeFileInfo.AutoSize = true;
            this.rb_TypeFileInfo.Location = new System.Drawing.Point(36, 60);
            this.rb_TypeFileInfo.Name = "rb_TypeFileInfo";
            this.rb_TypeFileInfo.Size = new System.Drawing.Size(71, 16);
            this.rb_TypeFileInfo.TabIndex = 0;
            this.rb_TypeFileInfo.TabStop = true;
            this.rb_TypeFileInfo.Text = "FileInfo";
            this.rb_TypeFileInfo.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(157, 132);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(203, 49);
            this.button1.TabIndex = 1;
            this.button1.Text = "检查";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // eg025_is
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(557, 193);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "eg025_is";
            this.Text = "eg025_is";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton rb_ObjectFile;
        private System.Windows.Forms.RadioButton rb_ObjectString;
        private System.Windows.Forms.RadioButton rb_TypeFileInfo;
        private System.Windows.Forms.RadioButton rb_TypeString;
        private System.Windows.Forms.Button button1;
    }
}