// Traffic-Flow-Counter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Поколение - все вершины находящиеся на одном уровне (создано во избежание зацикливания генерируемой сети
#include <iostream>
extern "C"
{
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
    Edge aNext[10]; //Ребра идущие от вершины
};

__declspec(dllexport) Node aNodes[10][10]; //Массив хранящий все вершины

void __declspec(dllexport) ConnectNode(Node &vCurrent, int nNextGen) //Соединяем вершину с дргуими
{
    if (nNextGen <= 9) {
        for (int i1 = 0; i1 <= 9; i1++) {
            if (rand() % 2 == 1) {
                if (aNodes[nNextGen - 1][i1].aId == 0) {

                    aNodes[nNextGen - 1][i1].aId[0] = nNextGen;
                    aNodes[nNextGen - 1][i1].aId[1] = i1 + 1;

                }

                vCurrent.aNext[i1].aEndId[0] = aNodes[nNextGen - 1][i1].aId[0];
                vCurrent.aNext[i1].aEndId[1] = aNodes[nNextGen - 1][i1].aId[1];
                vCurrent.aNext[i1].nFlow = 1 + rand() % 50;
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
    aNodes[9][0].aId[0] = 10;
    aNodes[9][0].aId[1] = 1;
    for (int i1 = 0; i1 <= 9; i1++) {
        if (aNodes[8][i1].aId[0] != 0) {
            aNodes[8][i1].aId[0] = aNodes[9][0].aId[0];
            aNodes[8][i1].aId[1] = aNodes[9][0].aId[1];
        }
    }
}
int __declspec(dllexport) Test()
{
    return 1;
}
}