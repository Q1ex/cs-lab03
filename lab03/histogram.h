#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>
using namespace std;
struct Input {
    vector<double> numbers;
    size_t bin_count;
};
struct Indiv
{
    bool verbose;
    bool help;
    char* urladress;
};


void
find_minmax(vector<double> numbers, double& min, double& max);

size_t height_sp(const vector<size_t>& bins);






#endif // HISTOGRAM_H_INCLUDED
