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
    CreateNetwork();
    drawNetwork();
    std::cout << "Done";
}
