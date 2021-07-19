namespace CSharp1200._21_Graphics
{
    partial class Chapter21
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnHer = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.btnOfficialStamp = new System.Windows.Forms.Button();
            this.btnDoubleBuffer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Location = new System.Drawing.Point(13, 13);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(820, 496);
            this.panel1.TabIndex = 0;
            // 
            // btnHer
            // 
            this.btnHer.Location = new System.Drawing.Point(13, 516);
            this.btnHer.Name = "btnHer";
            this.btnHer.Size = new System.Drawing.Size(75, 23);
            this.btnHer.TabIndex = 1;
            this.btnHer.Text = "绘制";
            this.btnHer.UseVisualStyleBackColor = true;
            this.btnHer.Click += new System.EventHandler(this.btnDrawLine_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 516);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "绘制";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btnDrawLine_Click);
            // 
            // btnOfficialStamp
            // 
            this.btnOfficialStamp.Location = new System.Drawing.Point(94, 516);
            this.btnOfficialStamp.Name = "btnOfficialStamp";
            this.btnOfficialStamp.Size = new System.Drawing.Size(75, 23);
            this.btnOfficialStamp.TabIndex = 1;
            this.btnOfficialStamp.Text = "绘制公章";
            this.btnOfficialStamp.UseVisualStyleBackColor = true;
            this.btnOfficialStamp.Click += new System.EventHandler(this.btnOfficialStamp_Click);
            // 
            // btnDoubleBuffer
            // 
            this.btnDoubleBuffer.Location = new System.Drawing.Point(175, 516);
            this.btnDoubleBuffer.Name = "btnDoubleBuffer";
            this.btnDoubleBuffer.Size = new System.Drawing.Size(75, 23);
            this.btnDoubleBuffer.TabIndex = 1;
            this.btnDoubleBuffer.Text = "双缓冲绘图";
            this.btnDoubleBuffer.UseVisualStyleBackColor = true;
            this.btnDoubleBuffer.Click += new System.EventHandler(this.btnDoubleBuffer_Click);
            // 
            // Chapter21
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(845, 631);
            this.Controls.Add(this.btnDoubleBuffer);
            this.Controls.Add(this.btnOfficialStamp);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnHer);
            this.Controls.Add(this.panel1);
            this.Name = "Chapter21";
            this.Text = "Chapter21";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnHer;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button btnOfficialStamp;
        private System.Windows.Forms.Button btnDoubleBuffer;
    }
}