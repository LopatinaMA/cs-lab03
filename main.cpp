#include <iostream>
#include <vector>
using namespace std;

// SVG
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}


void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";

}

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "red");
        top += BIN_HEIGHT;
    }
    svg_end();

}

vector<double> input_numbers (size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(vector<double> numbers, double& min, double& max)
{
    min = numbers[0];
    for(double number: numbers)
    {
        if(min > number)
        {
            min = number;
        }
        if (max < number)
        {
            max = number;
        }
    }
    // (здесь код поиска минимума и максимума)
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    double min, max;

    find_minmax(numbers, min, max) ;
    vector<size_t> bins(bin_count,0); //переменная показывающая количество чисел в заданном диапазоне
    double bin_size = (max - min)/ bin_count; //разме корзины
    for(size_t i=0; i < numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count-1) && !found; j++)
        {
            auto lo = min + j * bin_size;       //Нижняя граница корзины
            auto hi = min + (j + 1) * bin_size;     //Верхняя граница корзины
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)     //Для максимального числа
        {
            bins [bin_count-1]++;

        }
    }
    return bins;
}

show_histogram_text(const vector<size_t>& bins)
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

int main()
{
    //Ввод данных
    size_t number_count;
    cerr << "Enter number count:";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count:" ;
    cin >> bin_count;


    //Рассчет гистограммы
    const auto bins = make_histogram(numbers, bin_count);

    //Вывод гистограммы

    show_histogram_svg(bins);

    return 0;
}
