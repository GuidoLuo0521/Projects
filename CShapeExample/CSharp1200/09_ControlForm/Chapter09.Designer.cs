namespace CSharp1200._09_ControlForm
{
    partial class Chapter09
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
            this.label3 = new System.Windows.Forms.Label();
            this.button200 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button204 = new System.Windows.Forms.Button();
            this.button205 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(101, 12);
            this.label3.TabIndex = 7;
            this.label3.Text = "拖动图片到窗口上";
            // 
            // button200
            // 
            this.button200.Location = new System.Drawing.Point(240, 9);
            this.button200.Name = "button200";
            this.button200.Size = new System.Drawing.Size(75, 23);
            this.button200.TabIndex = 6;
            this.button200.Text = "200";
            this.button200.UseVisualStyleBackColor = true;
            this.button200.Click += new System.EventHandler(this.button200_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "托盘图标闪烁";
            // 
            // button204
            // 
            this.button204.Location = new System.Drawing.Point(240, 54);
            this.button204.Name = "button204";
            this.button204.Size = new System.Drawing.Size(75, 23);
            this.button204.TabIndex = 8;
            this.button204.Text = "204";
            this.button204.UseVisualStyleBackColor = true;
            this.button204.Click += new System.EventHandler(this.button204_Click);
            // 
            // button205
            // 
            this.button205.Location = new System.Drawing.Point(240, 97);
            this.button205.Name = "button205";
            this.button205.Size = new System.Drawing.Size(75, 23);
            this.button205.TabIndex = 8;
            this.button205.Text = "205";
            this.button205.UseVisualStyleBackColor = true;
            this.button205.Click += new System.EventHandler(this.button205_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 108);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 9;
            this.label2.Text = "托盘图标";
            // 
            // Chapter09
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button205);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button204);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button200);
            this.Name = "Chapter09";
            this.Text = "Chapter09";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button200;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button204;
        private System.Windows.Forms.Button button205;
        private System.Windows.Forms.Label label2;
    }
}