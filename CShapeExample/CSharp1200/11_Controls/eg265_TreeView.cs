using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace CSharp1200._11_Controls
{
    public partial class eg265_TreeView : Form
    {
        public eg265_TreeView()
        {
            InitializeComponent();
        }


        private void RecuresionTree(XmlNode xmlNodes, TreeNodeCollection treeNodes )
        {
            foreach(XmlNode node in xmlNodes.ChildNodes)
            {
                string str = node.Value != null ? node.Value :
                    (node.Attributes != null && node.Attributes.Count > 0) ? node.Attributes[0].Value : node.Name;

                TreeNode treeNode = new TreeNode(str);
                treeNodes.Add(treeNode);
                RecuresionTree(node, treeNode.Nodes);
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            this.treeView1.Nodes.Clear();

            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Filter = "xml 文件(*.xml)|*.xml";
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                this.Text = fileDialog.FileName;

                XmlDocument xmlDocument = new XmlDocument();
                xmlDocument.Load(this.Text);
                RecuresionTree(xmlDocument, this.treeView1.Nodes); 
            }
        }
    }
}
