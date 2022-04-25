#include "histogram.h"
#include "SVG.h"
#include <iostream>

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative()           //отрицательные
{
    double min = -1000;
    double max = -1000;
    find_minmax({-1, -2, -3}, min, max);

    assert(min == -3);
    assert(max == -1);
}

void test_same(){             //одинаковые
    double min = -1000;
    double max = -1000;
    find_minmax({1, 1, 1}, min, max);

    assert(min == 1);
    assert(max == 1);
}

void test_one(){        //одно число
    double min = -1000;
    double max = -1000;
    find_minmax({1}, min, max);

    assert(min == 1);
    assert(max == 1);
}

void test_empty() {        //пустой массив
    double min = -1000;
    double max = -1000;
    find_minmax({}, min, max);

    assert(min == -1000);
    assert(max == -1000);
}

void test_proverka_positive(){        //
    assert (proverka("#red") == true);
    assert (proverka("dhfv dfvbdf") == false);
    assert (proverka("green") == true);
}

void test_svg_text(){
    double left = 50;
    double baseline = 100;
    string text = "Histogram";
    svg_text(left, baseline, text);
    assert (left == 50);
    assert (baseline == 100);
    assert (text == "Histogram");
}

int
main() {
    test_positive();
    test_negative();
    test_same();
    test_one();
    test_empty();
    test_proverka_positive();
    test_svg_text();
}
