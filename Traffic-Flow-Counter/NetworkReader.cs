using System;
using System.Diagnostics;

namespace Traffic_Flow_Counter
{
    public class NetworkReader
    {
        #region Network Parts
        struct Edge
        {
            public int nFlow; //Максимальный транспортный поток
            public int[] aEndId;//Id конечной вершины
        }
        
        struct Node
        {
            public int[] aId;//Индивидуальный номер вершины
            public static Edge[] aNext;//Ребра идущие от вершины
        }
        
        #endregion
        
        #region Structure Construction

        private Edge MakeEdge(string edgeCodedEdge)
        {
            string[] stringsData = edgeCodedEdge.Split(new char[] {','});
            Edge edgeResult = new Edge();
            edgeResult.nFlow = Convert.ToInt32(stringsData[0]);
            edgeResult.aEndId = new int[2] {Convert.ToInt32(stringsData[1]),Convert.ToInt32(stringsData[2])};
            return edgeResult;
        }
        private Node MakeNode(string codedNode)
        {
            
        }

        #endregion
        
        #region Network Analize
        private Process _processNetwork = new Process();

        private string ReadNetwotk()
        {
            _processNetwork.StartInfo.UseShellExecute = false;
            _processNetwork.StartInfo.RedirectStandardOutput = true;
            _processNetwork.Start();
            return _processNetwork.StandardOutput.ReadToEnd();
        }

        private void AnalizeNetwork()
        {
            string stringData = ReadNetwotk();
            string[] stringsDataSplit = stringData.Split(new char[] {'|'});
            Node[,] aNetwork = new Node[Convert.ToInt32(stringsDataSplit[0]),Convert.ToInt32(stringsDataSplit[1])];
            string[] stringsCodeNodes = stringsDataSplit[2].Split(new char[] {'[', ']'});
        }
        #endregion
    }
}