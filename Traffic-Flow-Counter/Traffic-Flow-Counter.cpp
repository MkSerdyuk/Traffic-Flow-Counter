﻿// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
#include <deque>
const int nMaxConnects = 3; //Максимальное количесвто связей к и от вершины
const int nOneGenNodes = 4; //Количество вершин в поколении
const int nGenNumber = 7; //Максимальное количество поколений
const int nMaxFlow = 10; //Максимальное значение пропускной способности
struct Node;
struct Edge;
int nIdCounter = 1;
struct Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
    int nFlowLeft; //Остаточный поток
    int aEndId[2]; //Id конечной вершины
};

struct Node //Вершина
{
    int aId[2]; //Индивидуальный номер вершины
    int aMark[3]; //Метка для алгоритма Форда-Фалкерсона, первые 2 числа - источник потока в вершины, последнее число - количество потока
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
Node aNodes[nGenNumber + 2][nOneGenNodes]; //Массив хранящий все вершины
std::deque<std::deque<std::deque<int>>> Paths(0, std::deque<std::deque<int>> (0, std::deque<int>(0)));

void ConnectNode(Node &vCurrent, int nNextGen) //Соединяем вершину с дргуими
{
    int nCounter = 0;
    if (nNextGen <= nGenNumber + 1) {
        for (int i1 = 0; i1 < nOneGenNodes; i1++) {
            if ((rand() % 5 != 3 && rand() % 5 != 2) && nCounter <= nMaxConnects - 1) {
                if (aNodes[nNextGen - 1][i1].aId[0] == 0) {

                    aNodes[nNextGen - 1][i1].aId[0] = nNextGen;
                    aNodes[nNextGen - 1][i1].aId[1] = i1 + 1;
                }
                vCurrent.aNext[nCounter].aEndId[0] = aNodes[nNextGen - 1][i1].aId[0];
                vCurrent.aNext[nCounter].aEndId[1] = aNodes[nNextGen - 1][i1].aId[1];
                vCurrent.aNext[nCounter].nFlow = 1 + rand() % nMaxFlow;
                vCurrent.aNext[i1].nFlowLeft = vCurrent.aNext[i1].nFlow;
                ConnectNode(aNodes[nNextGen - 1][i1], nNextGen + 1);
                nCounter++;
            }
        }
    }
}

int FordFalkersonAlgorithm();

void OutputEdge(Edge eEdge)
{
    if (eEdge.aEndId[0] != 0) {
        std::cout << '{';
        std::cout << eEdge.nFlow;
        std::cout << ',';
        std::cout << eEdge.aEndId[0];
        std::cout << ',';
        std::cout << eEdge.aEndId[1];
        std::cout << '}';
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

    std::cout << nNode.aId[0];
    std::cout << ';';
    std::cout << nNode.aId[1];
    std::cout << ';';
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
                std::cout << '[';
                OutputNode(aNodes[i1][i2]);
                std::cout << ']';
            }
        }
    }
}

std::deque<int> SetId(int aId[2])
{
    std::deque<int> result(0);
    result.push_back(aId[0]);
    result.push_back(aId[1]);
    return result;
}

std::deque<std::deque<int>> CopyPath(std::deque<std::deque<int>> original)
{
    std::deque<std::deque<int>> result(0, std::deque<int>(0));
    for (int i = 0; i < original.size(); i++)
    {
        result.push_back(original[i]);
    }
}

int[2] GetId(std::deque<int> path, int number)
{
   return {path[number*2], path[number*2]+1};
}


void Output() //Вывод сети для отрисовки
{
    std::cout << nMaxConnects;
    std::cout << '|';
    OutputNodes();
    std::cout << '|';
    std::cout << FordFalkersonAlgorithm();
}

 void FindPaths(std::deque<std::deque<int>> &currentPath)
{
    int nConnectCounter = 0;

    std::deque<std::deque<int>> memorizedPath (0, std::deque<int>(0));
    int l = currentPath.size() - 1;
    for (int i = 0; i < nMaxConnects; i++)
    {
       if (aNodes[currentPath[l][0]][currentPath[l][1]].aNext[i].aEndId[0] != 0)
        {
            nConnectCounter++;
            if (nConnectCounter == 1)
            {
               // memorizedPath = currentPath;
                //currentPath.push_back(aNodes[currentPath[l][0]][currentPath[l][1]].aNext[i].aEndId);
                FindPaths(currentPath);
            }
            else
            {
               // Paths.push_back(memorizedPath);
              //  Paths[Paths.size() - 1].push_back(aNodes[currentPath[l][0]][currentPath[l][1]].aNext[i].aEndId);
           //     FindPaths(Paths[Paths.size() - 1]);
            }
        }
    }

}

int FordFalkersonAlgorithm()
{
        return 0;
}

int main()
{
    aNodes[0][0].aId[0] = 1;
    aNodes[0][0].aId[1] = 1;
    aNodes[0][0].aMark[0] = 0;
    aNodes[0][0].aMark[1] = 0;
    aNodes[0][0].aMark[3] = 1000000; //вместо бесконечности
    ConnectNode(aNodes[0][0], 2);
    aNodes[nGenNumber + 1][0].aId[0] = nGenNumber + 2;
    aNodes[nGenNumber + 1][0].aId[1] = 1;
    for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++)
    {
        if (aNodes[nGenNumber][i1].aId[0] != 0)
        {
            aNodes[nGenNumber][i1].aNext[0].nFlow = 1 + rand() % nMaxFlow;
            aNodes[nGenNumber][i1].aNext[0].aEndId[0] = aNodes[nGenNumber + 1][0].aId[0];
            aNodes[nGenNumber][i1].aNext[0].aEndId[1] = aNodes[nGenNumber + 1][0].aId[1];
        }
    }
    Output();
}
