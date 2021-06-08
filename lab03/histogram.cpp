#include "histogram.h"
void
find_minmax(vector<double> numbers, double& min, double& max) {
    if(!numbers.size()==0){
        min = numbers[0];
        max= numbers[0];
        for (double x : numbers)
        {
            if (x < min) min = x;
            else if (x > max) max = x;
        }
    }

}

size_t
height_sp(const vector<size_t>&bins){
 const auto BIN_HEIGHT = 30;
 const auto TEXT_TOP = 20;

 size_t height;


    if(!(bins.size() == 0)){
        size_t max_count = bins[0]; //поиск max из корзин
            for (size_t bin : bins)
                if (bin > max_count)
                    max_count = bin;
         height = max_count* (BIN_HEIGHT) +50+ TEXT_TOP;
    }
return height;
}




