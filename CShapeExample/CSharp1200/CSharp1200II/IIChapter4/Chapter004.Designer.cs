namespace CSharp1200.CSharp1200II.IIChapter4
{
    partial class Chapter004
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("069 进入Windows前发出警告");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("070 将计算机设置为休眠状态");
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("071 禁止用户关闭计算机");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("072 实现注销、关闭和重启计算机");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("073 定时关闭计算机");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("074 远程关闭与重启计算机");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("4.1 启动相关", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3,
            treeNode4,
            treeNode5,
            treeNode6});
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("第4章 系统控制应用", new System.Windows.Forms.TreeNode[] {
            treeNode7});
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Font = new System.Drawing.Font("宋体", 12F);
            this.treeView1.Location = new System.Drawing.Point(13, 13);
            this.treeView1.Name = "treeView1";
            treeNode1.Name = "069";
            treeNode1.Text = "069 进入Windows前发出警告";
            treeNode2.Name = "070";
            treeNode2.Text = "070 将计算机设置为休眠状态";
            treeNode3.Name = "071";
            treeNode3.Text = "071 禁止用户关闭计算机";
            treeNode4.Name = "072";
            treeNode4.Text = "072 实现注销、关闭和重启计算机";
            treeNode5.Name = "073";
            treeNode5.Text = "073 定时关闭计算机";
            treeNode6.Name = "074";
            treeNode6.Text = "074 远程关闭与重启计算机";
            treeNode7.Name = "节点1";
            treeNode7.Text = "4.1 启动相关";
            treeNode8.Name = "节点0";
            treeNode8.Text = "第4章 系统控制应用";
            this.treeView1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode8});
            this.treeView1.Size = new System.Drawing.Size(305, 597);
            this.treeView1.TabIndex = 0;
            this.treeView1.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeView1_NodeMouseClick);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(324, 13);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(676, 597);
            this.richTextBox1.TabIndex = 1;
            this.richTextBox1.Text = "";
            // 
            // Chapter004
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1004, 622);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.treeView1);
            this.Name = "Chapter004";
            this.Text = "Chapter004";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.RichTextBox richTextBox1;
    }
}