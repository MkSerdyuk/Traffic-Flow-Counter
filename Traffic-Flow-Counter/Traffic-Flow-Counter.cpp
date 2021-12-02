// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
#include <SFML/Graphics.hpp>
const int nMaxConnects = 5; //Максимальное количесвто связей к и от вершины
const int nOneGenVertexes = 5; //Количество вершин в поколении
const int nGenNumber = 7; //Максимальное количество поколений
const int nMaxFlow = 10; //Максимальное значение пропускной способности
struct Vertex;
struct Edge;
struct Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
    int nEndId; //Id конечной вершины
};
struct Vertex //Вершина
{
    int nId; //Индивидуальный номер вершины
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
Vertex aVertexes[nGenNumber][nOneGenVertexes]; //Массив хранящий все вершины
int nIdCounter;
void ConnectVertex(Vertex &vCurrent, int nNextGen) //Соединяем вершину с дргуими
{
    for (int i1 = 0; i1 <= 1 + rand() % (nMaxConnects - 1); i1++)
    {
        vCurrent.aNext[i1].nEndId = aVertexes[nNextGen - 1][rand() % nOneGenVertexes].nId;
        vCurrent.aNext[i1].nFlow = 1 + rand() % nMaxFlow;
    }
}
void CreateNetwork() //Создание сети
{
   for (int i1 = nGenNumber - 1; i1 >= 0; i1--)
   {
       for (int i2 = 0; i2 <= nOneGenVertexes - 1; i2++)
       {
           nIdCounter++;
           aVertexes[i1][i2].nId = nIdCounter;
           if (i1 < nGenNumber - 1)
           {
               ConnectVertex(aVertexes[i1][i2], i1+1);
           }
       }
   }
}
int main()
{
    CreateNetwork();
    std::cout << "Done";
}
