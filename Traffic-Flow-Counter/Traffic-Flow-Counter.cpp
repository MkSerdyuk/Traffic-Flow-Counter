// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
#include <deque>
#include <cstdlib>
#include <chrono>

using namespace std;
const int nMaxConnects = 3; //Максимальное количесвто связей к и от вершины
const int nOneGenNodes = 5; //Количество вершин в поколении
const int nGenNumber = 15; //Максимальное количество поколений
const int nMaxFlow = 20; //Максимальное значение пропускной способности
const int nPossibility = 3; //Чем больше, тем больше шанс, что появится ребро
struct Node;
struct Edge;

struct Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
    int nFlowLeft; //Остаточный поток
    int aEndId[2]; //Id конечной вершины
    bool bBlocked;
};

struct Node //Вершина
{
    int aId[2]; //Индивидуальный номер вершины
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
int seed = 1;
Node aNodes[nGenNumber + 2][nOneGenNodes]; //Массив хранящий все вершины
deque<deque<deque<int>>> Paths(0, deque<deque<int>> (0, deque<int>(0)));
deque<deque<deque<int>>> SortedPaths(0, deque<deque<int>> (0, deque<int>(0)));
deque<deque<deque<int>>> BlockingPaths(0, deque<deque<int>> (0, deque<int>(0))); //пути найденные поиском в ширину

int Random(int limit)
{
    auto now = std::chrono::system_clock::now(); //создание сложного стда для рандома
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long duration = value.count();
    seed = seed/13*21+duration;
    srand(seed);
    return rand() % limit;
}

void ConnectNode(Node &vCurrent, int nNextGen) //Соединяем вершину с дргуими
{
    int nCounter = 0;
    int nRemember = nNextGen;
    if (nRemember <= nGenNumber + 1) {
        for (int i1 = 0; i1 < nOneGenNodes; i1++) {
            nNextGen = nRemember + Random(nGenNumber + 2 - nRemember);
            if ((Random(nPossibility) != 0) && nCounter <= nMaxConnects - 1) {
                if (aNodes[nNextGen - 1][i1].aId[0] == 0) {

                    aNodes[nNextGen - 1][i1].aId[0] = nNextGen;
                    aNodes[nNextGen - 1][i1].aId[1] = i1 + 1;
                }
                vCurrent.aNext[nCounter].aEndId[0] = aNodes[nNextGen - 1][i1].aId[0];
                vCurrent.aNext[nCounter].aEndId[1] = aNodes[nNextGen - 1][i1].aId[1];
                vCurrent.aNext[nCounter].nFlow = 1 + Random(nMaxFlow);
                vCurrent.aNext[nCounter].nFlowLeft = vCurrent.aNext[nCounter].nFlow;
                ConnectNode(aNodes[nNextGen - 1][i1], nNextGen + 1);
                nCounter++;
            }
        }
    }
}

void RebuildNodes() //восстанавливаем остаточные пропускные способности
{
    for (int i1 = 0; i1 < nGenNumber+2; i1++)
    {
        for (int i2 = 0; i2 < nOneGenNodes; i2++)
        {
            for (int i3 = 0; i3 < nMaxConnects; i3++)
            {
                aNodes[i1][i2].aNext[i3].nFlowLeft = aNodes[i1][i2].aNext[i3].nFlow;
            }
        }
    }
}

int FordFalkersonAlgorithm();

void OutputEdge(Edge eEdge)
{
    if (eEdge.aEndId[0] != 0) {
        cout << '{';
        cout << eEdge.nFlow;
        cout << ',';
        cout << eEdge.aEndId[0];
        cout << ',';
        cout << eEdge.aEndId[1];
        cout << '}';
    }
}

void OutputEdges(Edge eEdges[])
{
    for (int i = 0; i < nMaxConnects; i++)
    {
        if (eEdges[i].nFlow != 0)
        {
            OutputEdge(eEdges[i]);
        }
    }
}

void OutputNode(Node nNode)
{

    cout << nNode.aId[0];
    cout << ';';
    cout << nNode.aId[1];
    cout << ';';
    OutputEdges(nNode.aNext);
}

void OutputNodes()
{
    for (int i1 = 0; i1 < nGenNumber + 2; i1++)
    {
        for (int i2 = 0; i2 < nOneGenNodes; i2++)
        {
            if (aNodes[i1][i2].aId[0] != 0)
            {
                cout << '[';
                OutputNode(aNodes[i1][i2]);
                cout << ']';
            }
        }
    }
}

void ClearPaths()
{
    while(Paths.size())
    {
        Paths.pop_back();
    }
}

void Output() //Вывод сети для отрисовки
{
    cout << nMaxConnects;
    cout << '|';
    OutputNodes();
}

deque<int> SetId(int aId[2], int nEdgeNum) //создание deque с Id
{
    deque<int> result(0);
    result.push_back(aId[0]);
    result.push_back(aId[1]);
    result.push_back(nEdgeNum);
    return result;
}

void CopyPath(deque<deque<int>> original, deque<deque<int>> &copy) //копирование пути
{
    for (int i = 0; i < original.size(); i++)
    {
        copy.push_back(original[i]);
    }

}

 void BFS(deque<deque<int>> &currentPath, Node currentNetwork[nGenNumber + 2][nOneGenNodes]) //поиск в ширину всех путей в графе
{
    bool bConnected = false;
    deque<deque<int>> memorizedPath (0, deque<int>(0));
    int length = currentPath.size() - 1;
    for (int i = 0; i < nMaxConnects; i++)
    {
       if (currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId[0] != 0)
        {
            if (!bConnected)
            {
                bConnected = true;
                CopyPath(currentPath,memorizedPath);
                currentPath.push_back(SetId(currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId, i));
                BFS(currentPath, currentNetwork);
            }
            else
            {
                Paths.push_back(memorizedPath);
                Paths[Paths.size() - 1].push_back(SetId(currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId, i));
                BFS(Paths[Paths.size() - 1], currentNetwork);
            }
        }
    }
}

void ModifiedBFS(deque<deque<int>> currentPath, Node currentNetwork[nGenNumber + 2][nOneGenNodes]) //поиск в ширину всех путей в графе (модифицирован для алгоритма Эдмондса-Карпа)
{
    bool bConnected = false;
    deque<deque<int>> memorizedPath (0, deque<int>(0));
    int length = currentPath.size() - 1;
    if (currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aId[0] == nGenNumber + 2)
    {
        SortedPaths.push_back(currentPath); //таким образом получем пути, упорядоченные по длине
    }
    for (int i = 0; i < nMaxConnects; i++)
    {
        if (currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId[0] != 0)
        {
            if (!bConnected)
            {
                bConnected = true;
                CopyPath(currentPath,memorizedPath);
                currentPath.push_back(SetId(currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId, i));
                ModifiedBFS(currentPath, currentNetwork);
            }
            else
            {
                Paths.push_back(memorizedPath);
                Paths[Paths.size() - 1].push_back(SetId(currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId, i));
                ModifiedBFS(Paths[Paths.size() - 1], currentNetwork);
            }
        }
    }
}

deque<deque<int>> toUnblock(0, deque<int>(0)); //список вершин, которые надо разблокировать
void GreedyDFS(deque<deque<int>> &currentPath, Node currentNetwork[nGenNumber + 2][nOneGenNodes]) //"Жадный" поиск в глубину всех путей в графе
{
    int length = currentPath.size() - 1;
    if (currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aId[0] == nGenNumber + 2)
    {
        BlockingPaths.push_back(currentPath);
        deque<deque<int>> newPath(0, deque<int>(0));
        newPath.push_back(SetId(aNodes[0][0].aId, 0));
        GreedyDFS(newPath, currentNetwork);
    }
    else
    {
        for (int i = 0; i < nMaxConnects; i++) {
            if (currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId[0] != 0 &&
                !currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].bBlocked) {
                currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].bBlocked = true;
                currentPath.push_back(
                        SetId(currentNetwork[currentPath[length][0] - 1][currentPath[length][1] - 1].aNext[i].aEndId,
                              i));
                GreedyDFS(currentPath, currentNetwork);
            }
        }
    }
}

int IsIncreasing(deque<deque<int>> currentPath) //проверка на увеличивающий путь и возвращение максимального потока в сети
{
    int result = 0;
    for (int i = 0; i < currentPath.size() - 1; i++)
    {
        if (aNodes[currentPath[i][0] - 1][currentPath[i][1] - 1].aNext[currentPath[i+1][2]].nFlowLeft > result)
        {
            result = aNodes[currentPath[i][0] - 1][currentPath[i][1] - 1].aNext[currentPath[i+1][2]].nFlowLeft;
        }
    }
    return result;
}

void IncreaseFlow(deque<deque<int>> currentPath) //увеличние потока в данном пути
{
    int nMaxFlowLeft = IsIncreasing(currentPath);
    if (nMaxFlowLeft > 0)
    {
        for (int i = 0; i < currentPath.size() - 1; i++)
        {
            aNodes[currentPath[i][0] - 1][currentPath[i][1] - 1].aNext[currentPath[i+1][2]].nFlowLeft = aNodes[currentPath[i][0] - 1][currentPath[i][1] - 1].aNext[currentPath[i+1][2]].nFlowLeft - nMaxFlowLeft;
        }
    }
}

int FordFalkersonCore(deque<deque<deque<int>>> usedPaths)
{
    int result = 0;
    for (int i = 0; i < usedPaths.size(); i++)
    {
        IncreaseFlow(usedPaths[i]);
    }
    for (int i1 = 0; i1 < nOneGenNodes; i1++)
    {
        for (int i2 = 0; i2 < nMaxConnects; i2++)
        {
            result = result + aNodes[nGenNumber][i1].aNext[i2].nFlow - aNodes[nGenNumber][i1].aNext[i2].nFlowLeft;
        }
    }
    return result;
}

int FordFalkersonAlgorithm()
{
    deque<deque<int>> first_path(0, deque<int>(0));
    first_path.push_back(SetId(aNodes[0][0].aId, 0));
    Paths.push_back(first_path);
    BFS(Paths[0], aNodes);
    return FordFalkersonCore(Paths);
}

int EdmondsKarpAlgorithm() //отличие от алгортма Форда-Фалкерсона в нахождении кратчайших увеличивающих путей
{
    deque<deque<int>> first_path(0, deque<int>(0));
    first_path.push_back(SetId(aNodes[0][0].aId, 0));
    Paths.push_back(first_path);
    ModifiedBFS(Paths[0], aNodes);
    return FordFalkersonCore(SortedPaths);
}


int EphimDinicAlgorithm()
{
    return 0;
}

int main()
{
    aNodes[0][0].aId[0] = 1;
    aNodes[0][0].aId[1] = 1;
    ConnectNode(aNodes[0][0], 2);
    aNodes[nGenNumber + 1][0].aId[0] = nGenNumber + 2;
    aNodes[nGenNumber + 1][0].aId[1] = 1;
    for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++)
    {
        aNodes[nGenNumber][i1].aNext[0].nFlowLeft = 0;
        if (aNodes[nGenNumber][i1].aId[0] != 0)
        {
            aNodes[nGenNumber][i1].aNext[0].nFlow = 1 + Random(nMaxFlow);
            aNodes[nGenNumber][i1].aNext[0].nFlowLeft = aNodes[nGenNumber][i1].aNext[0].nFlow;
            aNodes[nGenNumber][i1].aNext[0].aEndId[0] = aNodes[nGenNumber + 1][0].aId[0];
            aNodes[nGenNumber][i1].aNext[0].aEndId[1] = aNodes[nGenNumber + 1][0].aId[1];
        }
    }
    Output();
    auto fStartTime = chrono::high_resolution_clock::now(); //ед. измерения - микросекунды
    cout << '|' << FordFalkersonAlgorithm() << '|' << chrono::duration_cast<chrono::microseconds>( chrono::high_resolution_clock::now()- fStartTime).count() << '|' << nGenNumber + 2;
    RebuildNodes();
    ClearPaths();
    fStartTime = chrono::high_resolution_clock::now();
    cout << '|' << EdmondsKarpAlgorithm() << '|' << chrono::duration_cast<chrono::microseconds>( chrono::high_resolution_clock::now()- fStartTime).count();
    deque<deque<int>> first_path_for_dinic(0, deque<int>(0));
    first_path_for_dinic.push_back(SetId(aNodes[0][0].aId, 0));
    GreedyDFS(first_path_for_dinic, aNodes);
}
