namespace CSharp1200._08_SpecialForm
{
    partial class Chapter08
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
            this.label1 = new System.Windows.Forms.Label();
            this.button176 = new System.Windows.Forms.Button();
            this.button181 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.button182 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(33, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "导航栏可拉动";
            // 
            // button176
            // 
            this.button176.Location = new System.Drawing.Point(261, 22);
            this.button176.Name = "button176";
            this.button176.Size = new System.Drawing.Size(75, 23);
            this.button176.TabIndex = 4;
            this.button176.Text = "176";
            this.button176.UseVisualStyleBackColor = true;
            this.button176.Click += new System.EventHandler(this.button176_Click);
            // 
            // button181
            // 
            this.button181.Location = new System.Drawing.Point(261, 66);
            this.button181.Name = "button181";
            this.button181.Size = new System.Drawing.Size(75, 23);
            this.button181.TabIndex = 4;
            this.button181.Text = "181";
            this.button181.UseVisualStyleBackColor = true;
            this.button181.Click += new System.EventHandler(this.button181_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(33, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "可分割窗体";
            // 
            // button182
            // 
            this.button182.Location = new System.Drawing.Point(261, 111);
            this.button182.Name = "button182";
            this.button182.Size = new System.Drawing.Size(75, 23);
            this.button182.TabIndex = 4;
            this.button182.Text = "182";
            this.button182.UseVisualStyleBackColor = true;
            this.button182.Click += new System.EventHandler(this.button182_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(33, 111);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "动画窗体";
            // 
            // Chapter08
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button182);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button181);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button176);
            this.Name = "Chapter08";
            this.Text = "Chapter08";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button176;
        private System.Windows.Forms.Button button181;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button182;
        private System.Windows.Forms.Label label3;
    }
}