using System;
using System.Diagnostics;

namespace Traffic_Flow_Counter
{
    public class NetworkReader
    {
        public Node[] NodesNetwork;
        public int[] AlgorithmResults;
        
        #region Network Parts
        public struct Edge
        {
            public int nFlow; //Максимальный транспортный поток
            public int[] aEndId;//Id конечной вершины
        }
        
        public struct Node
        {
            public int[] aId;//Индивидуальный номер вершины
            public Edge[] aNext;//Ребра идущие от вершины
        }
        
        #endregion
        
        #region Structure Construction

        private Edge MakeEdge(string edgeCodedEdge)
        {
            string[] stringsData = edgeCodedEdge.Split(new char[] {','});
            Edge edgeResult = new Edge();
            edgeResult.nFlow = Convert.ToInt32(stringsData[0]);
            edgeResult.aEndId = new int[2];
            edgeResult.aEndId[0] = Convert.ToInt32(stringsData[1]);
            edgeResult.aEndId[1] = Convert.ToInt32(stringsData[2]);
            return edgeResult;
        }
        private Node MakeNode(string nodeCodedNode, int intMaxEdges)
        {
            string[] stringsData = nodeCodedNode.Split(new char[] {';'});
            Node nodeResult = new Node();
            int x = Convert.ToInt32(stringsData[0]);
            int y = Convert.ToInt32(stringsData[1]);
            nodeResult.aId = new int[2];
            nodeResult.aId[0] = x;
            nodeResult.aId[1] = y;
            string[] stringsCodedEdges = stringsData[2].Split(new char[] {'{', '}'});
            nodeResult.aNext = new Edge[intMaxEdges];
            int intCounter = 0;
            foreach (string stringCodedEdge in stringsCodedEdges)
            {
                if (stringCodedEdge != "")
                {
                    nodeResult.aNext[intCounter] = new Edge();
                    nodeResult.aNext[intCounter] = MakeEdge(stringCodedEdge);
                    intCounter++;
                }
            }
            return nodeResult;
        }

        #endregion
        
        #region Network Analize
        private Process _processNetwork = new Process();
        
        private string ReadNetwotk()
        {
          _processNetwork.StartInfo.UseShellExecute = false;
          _processNetwork.StartInfo.RedirectStandardOutput = true;
          _processNetwork.StartInfo.FileName = "Traffic_Flow_Counter_script.exe";
          _processNetwork.Start();
          return _processNetwork.StandardOutput.ReadToEnd();
        }

        public void AnalizeNetwork()
        {
            string stringData = ReadNetwotk();
            string[] stringsDataSplit = stringData.Split('|');
            AlgorithmResults = new int[1];
            AlgorithmResults[0] = Convert.ToInt32(stringsDataSplit[2]);
            int intMaxEdges = Convert.ToInt32(stringsDataSplit[0]);
            string[] stringsCodedNodes = stringsDataSplit[1].Split(new char[] {'[', ']'});
            NodesNetwork = new Node[stringsCodedNodes.Length];
            int intCounter = 0;
            foreach (string stringCodedNode in stringsCodedNodes)
            {
                if (stringCodedNode != "")
                {
                    NodesNetwork[intCounter] = MakeNode(stringCodedNode, intMaxEdges);
                    intCounter++;
                }
            }
        }
        #endregion
    }
}