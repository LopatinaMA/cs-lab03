#include <vector>
#include <iostream>
#include <math.h>
#include <winsock2.h>
#include <windows.h>

using namespace std;


const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH -3-1;

string get_system_info()
{
    string result;
    const size_t MAX_LEN = 256;
    char str_info[MAX_LEN];

    DWORD info = GetVersion();
    DWORD mask =0x0000ffff;
    DWORD version = info & mask;
    DWORD version_major = version & 0x00ff;
    DWORD version_minor = version & 0xff00;
    sprintf(str_info, "Windows v%u.%u", version_major, version_minor);
    result = str_info;
    if((info & 0x8000'0000) == 0)
    {
        DWORD build = info >> 16;
        sprintf(str_info, " (build %u)\n", build);
        result += str_info;
    }

    return result;
}

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

void show_histogram_svg(const vector<size_t>& bins, vector<string> bin_colour)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto SYS_INFO_LEFT = 20;

    size_t TXT = (IMAGE_WIDTH - TEXT_WIDTH) / BLOCK_WIDTH;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    size_t max_bin = bins[0];       //������������ ������ �������
    for (size_t bin: bins)
    {
        if(max_bin < bin)
        {
            max_bin = bin;
        }
    }

    double top = 0;
    for (int i = 0; i < bins.size(); i++)
    {
        size_t height = bins[i];
        //���������, ����� �� �������������� ������, ���� �����, ����������� height
        if (max_bin > TXT)
        {
            height = TXT*(static_cast<double> (bins[i]) / max_bin);
        }
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, bin_colour[i], "red");
        top += BIN_HEIGHT;
    }

    string system_info = get_system_info();
    svg_text(SYS_INFO_LEFT, BIN_HEIGHT * bins.size() + TEXT_BASELINE, system_info);
    svg_end();

}
