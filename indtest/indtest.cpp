#include <iostream>
#include <vector>
#include "C:\Users\w1thoutiq\Desktop\lb3\svg.h"
#include <cassert>

using namespace std;

void tt1()  //������� ��������
{
    double x = 100;
    double xr = ind(x);
    assert(xr == 250);
}

void zero()     //���������� ������, ���� ����� ������� 0
{
    double x = 0;
    double xr = ind(x);
    assert(xr == 350);
}

void max()  // ���������� ������,���� ����� ������� ����������� (��-�� ��������������� �������� ������ ����� ����� ������ ����������� ��� ����� �������� ������, �� ���� 350)
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
