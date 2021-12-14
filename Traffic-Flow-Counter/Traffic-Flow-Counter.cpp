// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
//#include <SFML/Graphics.hpp>
const int nMaxConnects = 5; //Максимальное количесвто связей к и от вершины
const int nOneGenNodes = 5; //Количество вершин в поколении
const int nGenNumber = 7; //Максимальное количество поколений
const int nMaxFlow = 10; //Максимальное значение пропускной способности
struct Node;
struct Edge;
int nIdCounter = 1;
struct Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
   // int nFlowLeft; //Остаточный поток
    int aEndId[2]; //Id конечной вершины
};

struct Node //Вершина
{
    int aId[2]; //Индивидуальный номер вершины
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
Node aNodes[nGenNumber + 2][nOneGenNodes]; //Массив хранящий все вершины


void ConnectNode(Node &vCurrent, int nNextGen) //Соединяем вершину с дргуими
{
    int nCounter = 0;
    if (nNextGen <= nGenNumber + 1) {
        for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++) {
            if (/*rand() % 10 != 0 &&*/ nCounter <= nMaxConnects - 1) {
                nCounter++;
                if (aNodes[nNextGen - 1][i1].aId[0] == 0) {

                    aNodes[nNextGen - 1][i1].aId[0] = nNextGen;
                    aNodes[nNextGen - 1][i1].aId[1] = i1 + 1;

                }
                vCurrent.aNext[nCounter].aEndId[0] = aNodes[nNextGen - 1][i1].aId[0];
                vCurrent.aNext[nCounter].aEndId[1] = aNodes[nNextGen - 1][i1].aId[1];
                vCurrent.aNext[nCounter].nFlow = 1 + rand() % nMaxFlow;
               // vCurrent.aNext[i1].nFlowLeft = vCurrent.aNext[i1].nFlow;
                ConnectNode(aNodes[nNextGen - 1][i1], nNextGen + 1);
            }
        }
    }
}

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
    for (int i = 0; i <= nMaxConnects; i++)
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
    for (int i1 = 0; i1 <= nGenNumber + 2 - 1; i1++)
    {
        for (int i2 = 0; i2 <= nOneGenNodes - 1; i2++)
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

void Output() //Вывод сети для отрисовки
{
    std::cout << nGenNumber;
    std::cout << '|';
    std::cout << nOneGenNodes;
    std::cout << '|';
    std::cout << nMaxConnects;
    std::cout << '|';
    OutputNodes();
}

int main()
{
    aNodes[0][0].aId[0] = 1;
    aNodes[0][0].aId[1] = 1;
   // aNodes[0][0].nMark[0] = aNodes[0][0].aId[0];
   // aNodes[0][0].nMark[1] = aNodes[0][0].aId[1];
    ConnectNode(aNodes[0][0], 2);
    aNodes[nGenNumber + 1][0].aId[0] = nGenNumber + 2;
    aNodes[nGenNumber + 1][0].aId[1] = 1;
    for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++)
    {
        if (aNodes[nGenNumber][i1].aId[0] != 0)
        {
            aNodes[nGenNumber][i1].aNext->nFlow = 1 + rand() % nMaxFlow;
            aNodes[nGenNumber][i1].aNext->aEndId[0] = aNodes[nGenNumber + 1][0].aId[0];
            aNodes[nGenNumber][i1].aNext->aEndId[1] = aNodes[nGenNumber + 1][0].aId[1];
        }
    }
    Output();
}
