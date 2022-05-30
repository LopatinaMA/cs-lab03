#include "SVG.h"
#include "histogram.h"
#include <iostream>
#include <vector>
#include <curl/curl.h>

using namespace std;



vector <double> input_numbers (istream& in, size_t count)
{
    vector<double> result(count);
    for(size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}


Input read_input(istream& in, bool promt)
{
    Input data;

    size_t number_count;
    if (promt = true)
        cerr << "Enter number count: ";

    in >> number_count;

    if (promt = true)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);


    size_t bin_count;               //кол-во столбцов
    if (promt = true)
        cerr << "Enter bin count:" ;
    in >> bin_count;
    data.bin_count = bin_count;

    return data;
}

vector<size_t> make_histogram(Input data)
{
    double min, max;

    find_minmax(data.numbers, min, max) ;
    vector<size_t> bins(data.bin_count,0); //переменная показывающая количество чисел в заданном диапазоне
    double bin_size = (max - min)/ data.bin_count; //разме корзины
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



vector<string> input (size_t bin_count)
{
    vector<string> bin_colour(bin_count);
    for(int i = 0; i < bin_count; i++)
    {
        cerr << "Enter colour: ";
        cin >> bin_colour[i];
        while (!proverka(bin_colour[i]))
        {
            cin >> bin_colour[i];
        }
    }
    return bin_colour;
}

int main(int argc, char* argv[])
{

    if (argc > 1){
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();
        if(curl)
        {
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
        return 0;
    }


    curl_global_init(CURL_GLOBAL_ALL);
    Input data;

    //Ввод данных
    data = read_input(cin, true);
    /*
        vector<string> bin_colour = input(bin_count);
    */

    //Рассчет гистограммы
    const auto bins = make_histogram(data);

    //Вывод гистограммы
    /*
        show_histogram_svg(bins, bin_colour);
    */
    return 0;
}
