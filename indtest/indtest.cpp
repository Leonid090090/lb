#include <iostream>
#include <vector>
#include "C:\Users\w1thoutiq\Desktop\lb3\svg.h"
#include <cassert>

using namespace std;

void tt1()  //обычная проверка
{
    double x = 100;
    double xr = ind(x);
    assert(xr == 250);
}

void zero()     //рассмотрим случай, если длина столбца 0
{
    double x = 0;
    double xr = ind(x);
    assert(xr == 350);
}

void max()  // рассмотрим случай,если длина столбца максимальна (из-за масштабирования максимум всегда будет равен ширине изображения без учета размеров текста, то есть 350)
{
    double x = 350;
    double xr = ind(x);
    assert(xr == 0);
}

int main()
{
    tt1();
    zero();
    max();
    return 0;
}
