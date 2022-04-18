#include "SVG.h"
#include "histogram.h"
#include <iostream>
#include <vector>


using namespace std;



// SVG


vector<double> input_numbers (size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    double min, max;

    find_minmax(numbers, min, max) ;
    vector<size_t> bins(bin_count,0); //���������� ������������ ���������� ����� � �������� ���������
    double bin_size = (max - min)/ bin_count; //����� �������
    for(size_t i=0; i < numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count-1) && !found; j++)
        {
            auto lo = min + j * bin_size;       //������ ������� �������
            auto hi = min + (j + 1) * bin_size;     //������� ������� �������
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)     //��� ������������� �����
        {
            bins [bin_count-1]++;

        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH -3-1;

    size_t max_bin = bins[0];       //������������ ������ �������
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
        //���������, ����� �� �������������� ������, ���� �����, ����������� height
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

vector<string> input (size_t bin_count){
    vector<string> bin_colour(bin_count);
    for(int i = 0; i < bin_count; i++){
    cerr << "Enter colour: ";
        cin >> bin_colour[i];
        while (!proverka(bin_colour[i])){
            cin >> bin_colour[i];
        }
    }
    return bin_colour;
}

int main()
{
    //���� ������
    size_t number_count;
    cerr << "Enter number count:";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;               //���-�� ��������
    cerr << "Enter bin count:" ;
    cin >> bin_count;

    vector<string> bin_colour = input(bin_count);


    //������� �����������
    const auto bins = make_histogram(numbers, bin_count);

    //����� �����������

    show_histogram_svg(bins, bin_colour);

    return 0;
}
