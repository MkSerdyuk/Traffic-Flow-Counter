using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Traffic_Flow_Counter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, System.Windows.Forms.PaintEventArgs pe)
        {
            int height = 75;
            int width = 100;
            Graphics graphics = pe.Graphics;
            Pen pen = new Pen(Color.FromArgb(0, 0, 0));
            NetworkReader networkNetworkReader= new NetworkReader();
            networkNetworkReader.AnalizeNetwork();
            foreach (NetworkReader.Node nodeNode in networkNetworkReader.NodesNetwork)
            {
                if (nodeNode.aId != null)
                {
                    if (nodeNode.aId[0] != 0)
                    {
                        graphics.DrawEllipse(pen, new Rectangle(nodeNode.aId[0]*width-10, nodeNode.aId[1]*height-10, 20, 20));
                        graphics.DrawString(Convert.ToString(nodeNode.aId[0])+";"+Convert.ToString(nodeNode.aId[1]), new Font("Times New Roman", 12.0f), new SolidBrush(Color.Black), nodeNode.aId[0]*width-10, nodeNode.aId[1]*height-10);
                        foreach (NetworkReader.Edge edgeEdge in nodeNode.aNext)
                        {
                            if (edgeEdge.aEndId != null)
                            {
                                graphics.DrawLine(pen, nodeNode.aId[0] * width + 10, nodeNode.aId[1] * height, edgeEdge.aEndId[0] * width - 10, edgeEdge.aEndId[1] * height);
                                graphics.DrawString(Convert.ToString(edgeEdge.nFlow), new Font("Times New Roman", 9.0f), new SolidBrush(Color.Black), nodeNode.aId[0]*width + (edgeEdge.aEndId[0] - nodeNode.aId[0])*width/2 , nodeNode.aId[1]*height + (edgeEdge.aEndId[1] - nodeNode.aId[1])*height/2);
                            }
                        }
                    }
                }
            }
        }
    }
}