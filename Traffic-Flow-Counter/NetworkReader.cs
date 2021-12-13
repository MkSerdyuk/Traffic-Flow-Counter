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
            public Edge[] aNext;//Ребра идущие от вершины
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
        private Node MakeNode(string nodeCodedNode, int intMaxEdges)
        {
            string[] stringsData = nodeCodedNode.Split(new char[] {';'});
            Node nodeResult = new Node();
            nodeResult.aId = new int[2] {Convert.ToInt32(stringsData[0]), Convert.ToInt32(stringsData[1])};
            string[] stringsCodedEdges = stringsData[3].Split(new char[] {'{', '}'});
            nodeResult.aNext = new Edge[intMaxEdges];
            for (int i = 0; i <= intMaxEdges - 1; i++)
            {
                nodeResult.aNext[i] = new Edge();
                if (i <= stringsCodedEdges.Length - 1)
                {
                    nodeResult.aNext[i] = MakeEdge(stringsCodedEdges[i]);
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
            _processNetwork.StartInfo.FileName = "Traffic-Flow-Counter.exe";
            _processNetwork.Start();
            return _processNetwork.StandardOutput.ReadToEnd();
        }

        private void AnalizeNetwork()
        {
            string stringData = ReadNetwotk();
            string[] stringsDataSplit = stringData.Split(new char[] {'|'});
            int intMaxGenerations = Convert.ToInt32(stringsDataSplit[0]);
            int intMaxNodesInGeneration = Convert.ToInt32(stringsDataSplit[1]);
            int intMaxEdges = Convert.ToInt32(stringsDataSplit[2]);
            string[] stringsCodedNodes = stringsDataSplit[3].Split(new char[] {'[', ']'});
            Node[] nodesDecodedNodes = new Node[stringsCodedNodes.Length];
            int intCounter = 0;
            foreach (string stringCodedNode in stringsCodedNodes)
            {
                nodesDecodedNodes[intCounter] = MakeNode(stringCodedNode, intMaxEdges);
                intCounter++;
            }
            Node[,] nodesNetwork = new Node[intMaxEdges,intMaxNodesInGeneration];
            foreach (Node nodeNode in nodesDecodedNodes)
            {
                nodesNetwork[nodeNode.aId[0] - 1, nodeNode.aId[1] - 1] = nodeNode;
            }
        }
        #endregion
    }
}