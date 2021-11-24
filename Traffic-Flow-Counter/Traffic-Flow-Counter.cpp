// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
const int nMaxConnects = 5; //Максимальное количесвто связей к и от вершины
const int nOneGenVertexes = 5; //Количество вершин в поколении
const int nGenNumber = 7; //Максимальное количество поколений
const int nMaxFlow = 10; //Максимальное значение пропускной способности
struct Vertex;
struct Edge;
typedef Vertex* pVertex;
typedef Edge* pEdge;
struct Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
    pVertex pStart, pEnd; //Указатели на начальную и конечную вершину
};
struct Vertex //Вершина
{
    int nId;
    Edge aLast[nMaxConnects]; //Ребра идущие к вершине
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};
Vertex aGenerations[nGenNumber][nOneGenVertexes];
int nIdCounter;
pVertex ConnectVertex(Vertex vCurrent, int nGenCounter) //Соединяем вершину с дргуими
{
    nIdCounter++;
    if (nGenCounter <= nOneGenVertexes)
    {
        vCurrent.nId = nIdCounter;
        for (int i = 0; i <= rand() % nMaxConnects; i++)
        {
            vCurrent.aNext[i].nFlow = rand() % (nMaxFlow + 1);
            vCurrent.aNext[i].pStart = &vCurrent;
            for (int j = 0; j <= nOneGenVertexes; j++)
                if (rand() % 2 == 1)
                {

                }
            vCurrent.aNext[i].pEnd = &(aGenerations[nGenCounter][rand() % nOneGenVertexes]);
            *(vCurrent.aNext[i].pEnd)->aLast = vCurrent

        }        
    }
    else
        return nullptr;
}
void CreateNetwork() //Создание сети
{
   
}
int main()
{
    std::cout << "Hello World!\n";
}
