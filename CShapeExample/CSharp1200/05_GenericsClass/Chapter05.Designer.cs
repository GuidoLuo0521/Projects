namespace CSharp1200._05_GenericsClass
{
    partial class Chapter05
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
            this.button126 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button126
            // 
            this.button126.Location = new System.Drawing.Point(262, 12);
            this.button126.Name = "button126";
            this.button126.Size = new System.Drawing.Size(75, 23);
            this.button126.TabIndex = 0;
            this.button126.Text = "126";
            this.button126.UseVisualStyleBackColor = true;
            this.button126.Click += new System.EventHandler(this.button126_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "泛型类";
            // 
            // Chapter05
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(515, 512);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button126);
            this.Name = "Chapter05";
            this.Text = "Chapter05";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button126;
        private System.Windows.Forms.Label label1;
    }
}