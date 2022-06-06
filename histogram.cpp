#include "histogram.h"

#include <vector>

using namespace std;

void find_minmax(vector<double> numbers, double& min, double& max)
{
    if (numbers.size() == 0){
            return;
    }
    min = numbers[0];
    max = numbers[0];
    for(double number: numbers)
    {
        if (min > number)
        {
            min = number;
        }
        if (max < number)
        {
            max = number;
        }

    }
}

vector<size_t> make_histogram(Input data)
{
    double min, max;

    find_minmax(data.numbers, min, max) ;
    vector<size_t> bins(data.bin_count,0); //переменная показывающая количество чисел в заданном диапазоне
    double bin_size = (max - min)/ data.bin_count; //размеp корзины
    for(size_t i=0; i < data.numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < (data.bin_count-1) && !found; j++)
        {
            auto lo = min + j * bin_size;       //Нижняя граница корзины
            auto hi = min + (j + 1) * bin_size;     //Верхняя граница корзины
            if ((lo <= data.numbers[i]) && (data.numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)     //Для максимального числа
        {
            bins [data.bin_count-1]++;

        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH -3-1;

    size_t max_bin = bins[0];       //Максимальная высота столбца
    for (size_t bin: bins)
    {
        if(max_bin < bin)
        {
            max_bin = bin;
        }
    }
    for(size_t bin: bins)
    {
        size_t height = bin;
        //Проверить, нужно ли масштабировать данные, если нужно, пересчитать height
        if (max_bin > MAX_ASTERISK)
        {
            height = MAX_ASTERISK*(static_cast<double> (bin) / max_bin);
        }
        size_t procent = bin;
        if (procent < 100)
        {
            cout << " ";
        }
        if (procent < 10)
        {
            cout<< " ";
        }
        cout << procent << "|";
        for (size_t i = 0; i < height; i++)
        {
            cout<< "*";
        }
        cout << endl;
    }
}



bool proverka(string bin_colour){

    return (bin_colour[0] == '#') || (bin_colour.find(' ') == string::npos);
}
