// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
extern "C"
{
int __declspec(dllexport) nMaxConnects = 5; //Максимальное количесвто связей к и от вершины
int __declspec(dllexport) nOneGenNodes = 5; //Количество вершин в поколении
int __declspec(dllexport) nGenNumber = 7; //Максимальное количество поколений
int __declspec(dllexport) nMaxFlow = 10; //Максимальное значение пропускной способности
struct __declspec(dllexport) Node;
struct __declspec(dllexport) Edge;

struct __declspec(dllexport) Edge //Ребро
{
    int nFlow; //Максимальный транспортный поток
    int nFlowLeft; //Остаточный поток
    int aEndId[2]; //Id конечной вершины
};

struct __declspec(dllexport) Node //Вершина
{
    int aId[2]; //Индивидуальный номер вершины
    int nMark[2]; //Метка источника потока для алгоритма Форда-Фалкерсона
    int nMarkFlow; //Метка приходящего потока для алгоритма Форда-Фалкерсона
    int nFlow; //Поток приходящий на вершину в данную Итерацию алгоритма Форда-Фалкерсона
    Edge aNext[nMaxConnects]; //Ребра идущие от вершины
};

__declspec(dllexport) Node aNodes[nGenNumber + 2][nOneGenNodes]; //Массив хранящий все вершины

void __declspec(dllexport) ConnectNode(Node &vCurrent, int nNextGen) //Соединяем вершину с дргуими
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