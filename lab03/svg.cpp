#include "svg.h"
#include "histogram.h"
#include <iostream>
using namespace std;

string
make_info_text(){
    stringstream buffer;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD mask_2 = 0x0000ff;
    if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_2;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer<< "Windows v"<<version_major<<"."<<version_minor<<"(build "<<build<<")  ";
    }
    char Comp_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(Comp_name);
    GetComputerName(Comp_name, &size);
    buffer<<" Computer name:"<<Comp_name;

    return buffer.str();
}
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




void
svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout << "<rect x='" << x << "' y='" <<y<< "' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"'></rect>";
}
/*
void
show_histogram_svg(const vector<size_t>& bins){
const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
for (size_t bin : bins) {
    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
    top += BIN_HEIGHT;
}
    svg_end();
}*/
///




/*size_t
height_s(const vector<size_t>& bins){
const auto BIN_HEIGHT = 30;
size_t max_count = bins[0]; //поиск max из корзин
    for (size_t bin : bins)
        if (bin > max_count)
            max_count = bin;
size_t height = max_count* BIN_HEIGHT +50;
return height;

}
*/

///


void
show_histogram_svg(const vector<size_t>& bins){
    const auto IMAGE_WIDTH = 500;
    const auto TEXT_TOP = 20;
    const auto TEXT_LEFT = 20;
        const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 30;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 20;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_count = bins[0]; //поиск max из корзин
        for (size_t bin : bins)
            if (bin > max_count)
                max_count = bin;

    size_t IMAGE_HEIGHT = height_sp(bins);

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        double top = 0;
    for (size_t bin : bins) {
        const double bin_height = BIN_HEIGHT * bin;
        svg_text(TEXT_LEFT +top, TEXT_BASELINE+TEXT_TOP, to_string(bin));
        svg_rect(TEXT_LEFT +top, TEXT_WIDTH+TEXT_TOP, BLOCK_WIDTH, bin_height);
        top+=BLOCK_WIDTH;
    }
    svg_text(0,TEXT_TOP, make_info_text());


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
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
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
}*/
