#pragma once

#include <string>
#include <vector>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

void find_minmax(vector<double> numbers, double& min, double& max);
bool proverka(string bin_colour);
