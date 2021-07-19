namespace CSharp1200._11_Controls
{
    partial class Chapter11
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
            this.label2 = new System.Windows.Forms.Label();
            this.button265 = new System.Windows.Forms.Button();
            this.button307 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(95, 12);
            this.label2.TabIndex = 13;
            this.label2.Text = "树形控件显示xml";
            // 
            // button265
            // 
            this.button265.Location = new System.Drawing.Point(138, 29);
            this.button265.Name = "button265";
            this.button265.Size = new System.Drawing.Size(75, 23);
            this.button265.TabIndex = 12;
            this.button265.Text = "265";
            this.button265.UseVisualStyleBackColor = true;
            this.button265.Click += new System.EventHandler(this.button265_Click);
            // 
            // button307
            // 
            this.button307.Location = new System.Drawing.Point(138, 77);
            this.button307.Name = "button307";
            this.button307.Size = new System.Drawing.Size(75, 23);
            this.button307.TabIndex = 12;
            this.button307.Text = "307";
            this.button307.UseVisualStyleBackColor = true;
            this.button307.Click += new System.EventHandler(this.button306_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 77);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 13;
            this.label1.Text = "验证控件";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(138, 131);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 12;
            this.button1.Text = "384";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button384_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 131);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 13;
            this.label3.Text = "文件分割";
            // 
            // Chapter11
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button307);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button265);
            this.Name = "Chapter11";
            this.Text = "常用控件";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button265;
        private System.Windows.Forms.Button button307;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label3;
    }
}