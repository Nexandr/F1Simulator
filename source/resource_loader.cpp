#include "../headers/resource_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>


static std::string clean(const std::string& s) {
    std::string result = s;
    if (!result.empty() && result.back() == '\r') result.pop_back();
    return result;
}

static std::vector<std::string> split_csv(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ','))
        fields.push_back(clean(cell));
    return fields;
}