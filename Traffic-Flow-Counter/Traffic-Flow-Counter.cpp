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
    int nEndId; //Id конечной вершины
};

struct Node //Вершина
{
    int nId; //Индивидуальный номер вершины
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
Node First; //Исток
Node aNodes[nGenNumber][nOneGenNodes]; //Массив хранящий все вершины
Node Last; //Исход


void ConnectNode(Node &vCurrent, int nNextGen) //Соединяем вершину с дргуими
{
    if (nNextGen <= nGenNumber + 1) {
        for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++) {
            if (rand() % 2 == 1) {
                if (aNodes[nNextGen - 1][i1].aId == 0) {

                    aNodes[nNextGen - 1][i1].aId[0] = nNextGen;
                    aNodes[nNextGen - 1][i1].aId[1] = i1 + 1;

                }

                vCurrent.aNext[i1].aEndId[0] = aNodes[nNextGen - 1][i1].aId[0];
                vCurrent.aNext[i1].aEndId[1] = aNodes[nNextGen - 1][i1].aId[1];
                vCurrent.aNext[i1].nFlow = 1 + rand() % nMaxFlow;
                vCurrent.aNext[i1].nFlowLeft = vCurrent.aNext[i1].nFlow;
                ConnectNode(aNodes[nNextGen - 1][i1], nNextGen + 1);
            }
        }
    }
}

void __declspec(dllexport) CreateNetwork() //Создание сети
    if (nNextGen <= nGenNumber)
    {
    for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++)
    {
        if (rand() % 2 == 1)
        {
            if (aNodes[nNextGen - 1][i1].nId != 0)
            {
                nIdCounter++;
                aNodes[nNextGen - 1][i1].nId = nIdCounter;
            }

            vCurrent.aNext[i1].nEndId = aNodes[nNextGen - 1][i1].nId;
            vCurrent.aNext[i1].nFlow = 1 + rand() % nMaxFlow;
            ConnectNode(aNodes[nNextGen - 1][i1], nNextGen + 1);
        }
    }
    }
}

void CreateNetwork() //Создание сети
{
   First.nId = 1;
   ConnectNode(First, 1);
   nIdCounter++;
   Last.nId = nIdCounter;
}

void drawNetwork() //Отрисовка сети
{
    //    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
}

int main()
{
    aNodes[0][0].aId[0] = 1;
    aNodes[0][0].aId[1] = 1;
    aNodes[0][0].nMark[0] = aNodes[0][0].aId[0];
    aNodes[0][0].nMark[1] = aNodes[0][0].aId[1];
    ConnectNode(aNodes[0][0], 2);
    aNodes[nGenNumber + 1][0].aId[0] = nGenNumber + 2;
    aNodes[nGenNumber + 1][0].aId[1] = 1;
    for (int i1 = 0; i1 <= nOneGenNodes - 1; i1++) {
        if (aNodes[nGenNumber][i1].aId[0] != 0) {
            aNodes[nGenNumber][i1].aId[0] = aNodes[nGenNumber + 1][0].aId[0];
            aNodes[nGenNumber][i1].aId[1] = aNodes[nGenNumber + 1][0].aId[1];
        }
    }
}
}