#include <iostream>

#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "histogram.h"
#include "svg.h"
using namespace std;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


/*vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
*/
vector<double>
input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;

}



Input
read_input(istream& in, bool prompt) {
    Input data;
    if (prompt){


    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
        in >> data.bin_count;
    }
    else{
     size_t number_count;
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;

    }

    return data;
}

vector<size_t>
make_histogram(Input a){
    double min, max;
    find_minmax(a.numbers,min,max);
    double bin_size = (max-min)/a.bin_count;

    vector<size_t> bins(a.bin_count);
    size_t number_count = a.numbers.size();
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < a.bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if ((lo <= a.numbers[i]) && (a.numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }

        }
        if (!found)
        {
            bins[a.bin_count - 1]++;
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

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
     if (argc>1)
    {
        CURL *curl = curl_easy_init();
        if(curl){
             CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if (res)
            {
                cerr << curl_easy_strerror(res) << endl;
                exit(1);
            }

        }
    }


    const auto  input = read_input(cin, true);
    /*size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(cin, number_count);*/


   /* size_t bin_count;
    cerr << "bin_count: ";
    cin >> bin_count;*/
    const auto bins = make_histogram(input);
    //show_histogram_text(bins);
    show_histogram_svg(bins);
}











/*
///SVG///////////////////////////////////////////////////////////////
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" <<baseline<< "'>" << text << "</text>";
}




void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "maroon"){
    cout << "<rect x='" << x << "' y='" <<y<< "' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"'></rect>";
}


void
show_histogram_svg(const vector<size_t>& bins){
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    double top = 0;
    size_t max_count = bins[0]; //поиск max из корзин
    for (size_t bin : bins)
        if (bin > max_count)
            max_count = bin;

    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        top += BIN_HEIGHT;
    }

    top=0;
    if (max_count > MAX_ASTERISK ){
        for(size_t bin : bins){
            const double bin_width = static_cast <double> (IMAGE_WIDTH - TEXT_LEFT)/max_count * bin;
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top+=BIN_HEIGHT;
        }
    }
    else{
        for(size_t bin : bins){
            const double bin_width = BLOCK_WIDTH * bin;
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
            top+=BIN_HEIGHT;

        }
    }


    svg_end();
}

/*void
show_histogram_svg(const vector<size_t>& bins){
const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
for (size_t bin : bins) {
    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
    top += BIN_HEIGHT;
}
    svg_end();
}


///SVG/////////////////////////////////////////////////////////////////

*/
