namespace CSharp1200.CSharp1200II.IIChapter2
{
    partial class Chapter003
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("034 获取系统时间");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("035 获取计算机系统信息");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("036 获取计算机名称");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("037 获取当前程序运行目录");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("038 获得操作系统版本号");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("039 获取系统启动后经过的时间");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("040 获取任务栏尺寸");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("041 改变系统提示信息");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("042 获取系统环境变量");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("3.1 获取计算机系统信息", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3,
            treeNode4,
            treeNode5,
            treeNode6,
            treeNode7,
            treeNode8,
            treeNode9});
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("获取系统相关信息", new System.Windows.Forms.TreeNode[] {
            treeNode10});
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Font = new System.Drawing.Font("宋体", 12F);
            this.treeView1.Location = new System.Drawing.Point(13, 13);
            this.treeView1.Name = "treeView1";
            treeNode1.Name = "034";
            treeNode1.Text = "034 获取系统时间";
            treeNode2.Name = "035";
            treeNode2.Text = "035 获取计算机系统信息";
            treeNode3.Name = "036";
            treeNode3.Text = "036 获取计算机名称";
            treeNode4.Name = "037";
            treeNode4.Text = "037 获取当前程序运行目录";
            treeNode5.Name = "038";
            treeNode5.Text = "038 获得操作系统版本号";
            treeNode6.Name = "039";
            treeNode6.Text = "039 获取系统启动后经过的时间";
            treeNode7.Name = "040";
            treeNode7.Text = "040 获取任务栏尺寸";
            treeNode8.Name = "041";
            treeNode8.Text = "041 改变系统提示信息";
            treeNode9.Name = "042";
            treeNode9.Text = "042 获取系统环境变量";
            treeNode10.Name = "节点2";
            treeNode10.Text = "3.1 获取计算机系统信息";
            treeNode11.Name = "root";
            treeNode11.Text = "获取系统相关信息";
            this.treeView1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode11});
            this.treeView1.Size = new System.Drawing.Size(303, 536);
            this.treeView1.TabIndex = 0;
            this.treeView1.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeView1_NodeMouseClick);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(323, 13);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(450, 176);
            this.richTextBox1.TabIndex = 1;
            this.richTextBox1.Text = "";
            // 
            // Chapter003
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(785, 561);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.treeView1);
            this.Name = "Chapter003";
            this.Text = "Chapter003";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.RichTextBox richTextBox1;
    }
}