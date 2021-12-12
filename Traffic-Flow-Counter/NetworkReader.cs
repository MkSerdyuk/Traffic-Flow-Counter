using System;
using System.Diagnostics;

namespace Traffic_Flow_Counter
{
    public class NetworkReader
    {
        #region Network Parts
        struct Edge
        {
            int nFlow; //Максимальный транспортный поток
            static int[] aEndId = new int[2]; //Id конечной вершины
        }
        
        struct Node
        {
            static int[] aId = new int[2]; //Индивидуальный номер вершины
            static Edge[] aNext; //Ребра идущие от вершины
        }
        
        #endregion
        
        #region Network Analize
        private Process _processNetwork = new Process();

        private string readNetwotk()
        {
            _processNetwork.StartInfo.UseShellExecute = false;
            _processNetwork.StartInfo.RedirectStandardOutput = true;
            _processNetwork.Start();
            return _processNetwork.StandardOutput.ReadToEnd();
        }

        private void analizeNetwork()
        {
            string sData = readNetwotk();
            string[] sDataSplit = sData.Split(new char[] {'|'});
            Node[,] aNetwork = new Node[Convert.ToInt32(sDataSplit[0]),Convert.ToInt32(sDataSplit[1])];
            
        }
        #endregion
    }
}