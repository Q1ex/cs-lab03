#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_one(){
    double min=0;
    double max =0;
    find_minmax({3}, min, max);
    assert( min == 3);
    assert (max == 3);
}

void
test_otric() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_equal() {
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
///Тесты инд. задания
void
test_img_empty(){
    double height = 0;
    height_sp({});
    assert( height == 0);
}

void
test_img_one(){
    size_t h = 0;
    h = height_sp({1,2});
    assert(h == 110);
}


int
main() {
    test_positive();
    test_one();
    test_otric();
    test_equal();
    test_empty();
    test_img_empty();
    test_img_one();
}
