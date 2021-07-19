namespace CSharp1200._19_Office
{
    partial class Chapter19
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
            this.btnWebBrowser = new System.Windows.Forms.Button();
            this.webBrowser1 = new System.Windows.Forms.WebBrowser();
            this.btnCreateWord = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnWebBrowser
            // 
            this.btnWebBrowser.Location = new System.Drawing.Point(12, 74);
            this.btnWebBrowser.Name = "btnWebBrowser";
            this.btnWebBrowser.Size = new System.Drawing.Size(144, 22);
            this.btnWebBrowser.TabIndex = 0;
            this.btnWebBrowser.Text = "WebBrowser";
            this.btnWebBrowser.UseVisualStyleBackColor = true;
            this.btnWebBrowser.Click += new System.EventHandler(this.btnWebBrowser_Click);
            // 
            // webBrowser1
            // 
            this.webBrowser1.Location = new System.Drawing.Point(12, 12);
            this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowser1.Name = "webBrowser1";
            this.webBrowser1.Size = new System.Drawing.Size(144, 56);
            this.webBrowser1.TabIndex = 1;
            // 
            // btnCreateWord
            // 
            this.btnCreateWord.Location = new System.Drawing.Point(199, 12);
            this.btnCreateWord.Name = "btnCreateWord";
            this.btnCreateWord.Size = new System.Drawing.Size(78, 84);
            this.btnCreateWord.TabIndex = 2;
            this.btnCreateWord.Text = "创建";
            this.btnCreateWord.UseVisualStyleBackColor = true;
            this.btnCreateWord.Click += new System.EventHandler(this.btnCreateWord_Click);
            // 
            // Chapter19
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnCreateWord);
            this.Controls.Add(this.webBrowser1);
            this.Controls.Add(this.btnWebBrowser);
            this.Name = "Chapter19";
            this.Text = "Chapter19";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnWebBrowser;
        private System.Windows.Forms.WebBrowser webBrowser1;
        private System.Windows.Forms.Button btnCreateWord;
    }
}