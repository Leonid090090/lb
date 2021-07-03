#include "C:\Users\w1thoutiq\Desktop\lb3\hisogram.h"

#include <cassert>

void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_niggative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void
test_repeat()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_once()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_empty()
{
    double min = -4;
    double max = 6;
    find_minmax({}, min, max);
    assert(min == -4);
    assert(max == 6);
}

int
main()
{
    test_positive();
    test_niggative();
    test_repeat();
    test_once();
    test_empty();

    }
