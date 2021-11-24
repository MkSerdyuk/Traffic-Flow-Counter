// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
const int nMaxConnects = 5; //Максимальное количесвто связей к и от вершины
const int nMaxVertexes = 25; //Максимальное количество вершин
struct Vertex;
typedef Vertex* pVertex;
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
Vertex CreateNetwork() //Создание сети
{
    for (int i; i <= rand() % (nMaxConnects + 1); i++)
    {

    }
}
int main()
{
    std::cout << "Hello World!\n";
}
