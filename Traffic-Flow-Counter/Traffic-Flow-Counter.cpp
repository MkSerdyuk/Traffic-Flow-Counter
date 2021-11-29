// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
const int nMaxConnects = 5; //Максимальное количесвто связей к и от вершины
const int nOneGenVertexes = 5; //Количество вершин в поколении
const int nGenNumber = 7; //Максимальное количество поколений
const int nMaxFlow = 10; //Максимальное значение пропускной способности
struct Vertex;
struct Edge;
struct Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
    int nStartId; //Id конечной вершины
    int nEndId; //Id стартовой вершины
};
struct Vertex //Вершина
{
    int nId; //Индивидуальный номер вершины
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
Vertex aVertexes[nGenNumber][nOneGenVertexes]; //Массив хранящий все вершины
int aLengths[nGenNumber]; //Количество вершин в каждом поколении
int nIdCounter;
void ConnectVertex(Vertex vCurrent, int nGenCounter) //Соединяем вершину с дргуими
{

}
void CreateNetwork() //Создание сети
{
   for (int i1 = 0; i1 <= nGenNumber - 1; i1++)
   {
       int nVertexesLimit = 1 + rand() % (nOneGenVertexes - 1);
       for (int i2 = 0; i2 <= nVertexesLimit; i2++)
       {
           nIdCounter++;
           aVertexes[i1][i2].nId = nIdCounter;
       }
       aLengths[i1] = nVertexesLimit;
   }
}
int main()
{
    std::cout << "Hello World!\n";
}
