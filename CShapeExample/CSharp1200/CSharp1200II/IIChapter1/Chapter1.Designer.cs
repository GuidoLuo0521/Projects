namespace CSharp1200.CSharp1200II
{
    partial class _1200II_Chapter1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(_1200II_Chapter1));
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.btnGetDbClickTime = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(13, 13);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(303, 425);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = resources.GetString("richTextBox1.Text");
            // 
            // btnGetDbClickTime
            // 
            this.btnGetDbClickTime.Location = new System.Drawing.Point(323, 13);
            this.btnGetDbClickTime.Name = "btnGetDbClickTime";
            this.btnGetDbClickTime.Size = new System.Drawing.Size(75, 23);
            this.btnGetDbClickTime.TabIndex = 1;
            this.btnGetDbClickTime.Text = "001";
            this.btnGetDbClickTime.UseVisualStyleBackColor = true;
            this.btnGetDbClickTime.Click += new System.EventHandler(this.btnGetDbClickTime_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(323, 59);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(75, 100);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "鼠标活动区域";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(322, 165);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "012";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btn012_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(322, 194);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "013";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.btn013_Click);
            // 
            // IIChapter1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnGetDbClickTime);
            this.Controls.Add(this.richTextBox1);
            this.Name = "IIChapter1";
            this.Text = "Chapter1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button btnGetDbClickTime;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}