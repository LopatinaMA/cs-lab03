#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
    vector<string> bin_colour(size_t bin_count);
};
vector<size_t> make_histogram(Input data);
void find_minmax(vector<double> numbers, double& min, double& max);
void show_histogram_text(const vector<size_t>& bins);
bool proverka(string bin_colour);
