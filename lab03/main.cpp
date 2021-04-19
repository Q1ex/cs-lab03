#include <iostream>

#include <iostream>
#include <vector>
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void
find_minmax(vector<double> numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers)
    {
        if (x < min) min = x;
        else if (x > max) max = x;
    }
}

vector<size_t>
make_histogram(vector<double> numbers, size_t bin_count){
    double min, max;
    find_minmax(numbers,min,max);
    double bin_size = (max-min)/bin_count;

    vector<size_t> bins(bin_count);
    size_t number_count = numbers.size();
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }

        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void
show_histogram_text(vector<size_t> bins){

    size_t max_count = bins[0];
    for (size_t x : bins)
        if (x > max_count)
            max_count = x;
    size_t bin_count = bins.size();
    for (size_t i = 0; i < max_count; i++)
    {
        for (size_t j = 0; j < bin_count; j++)
        {
            if (bins[j] > i)
                cout << "*";
            else cout << " ";
        }
        cout << endl;
    }

}


int main()
{

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);


    size_t bin_count;
    cerr << "bin_count: ";
    cin >> bin_count;
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_text(bins);
}
