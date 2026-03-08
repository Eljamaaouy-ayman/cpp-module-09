#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>

bool parse_line(std::string &line, double &val);
void print_the_result(std::map<std::string, float> &data, std::string &date, double &value);