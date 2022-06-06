#pragma once
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <iostream>

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH -3-1;

string get_system_info();

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void show_histogram_svg(const vector<size_t>& bins, vector<string> bin_colour);
