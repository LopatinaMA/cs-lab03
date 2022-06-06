#include "SVG.h"
#include "histogram.h"
#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>

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


    size_t bin_count;               //ךמכ-גמ סעמכבצמג
    if (promt = true)
        cerr << "Enter bin count:" ;
    in >> bin_count;
    data.bin_count = bin_count;

    return data;
}


size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size=item_size*item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}


Input download(const string& address)
{
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
    {
        double connect;
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res)
        {
            cerr << curl_easy_strerror(res) << endl;
            exit(1);
        }
        if (CURLE_OK == res){
            res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect);
        }
        if (CURLE_OK == res){
            printf("Time: %.1f", connect);
        }
    }
    curl_easy_cleanup(curl);
    return read_input(buffer, false);

}






vector<string> inp (size_t bin_count)
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

        Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
        for (size_t i=0; i < argc; i++)
        {
            if (string(argv[i]) == "-bins && (argv[6] > 0) && (argv[6] < 10) ")
            {
                const auto bins=argv[6];
            }
            else
            {
                cerr << "Please enter the number of -bins...";
                return 0;
            }
        }
    }
    else
    {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input);
    vector<string> bin_colour = inp(input.bin_count);
    show_histogram_svg(bins, bin_colour);
}
