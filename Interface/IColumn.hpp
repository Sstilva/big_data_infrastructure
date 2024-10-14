#pragma once
#include <string>

class IColumn {
public:
    void add_value(float);
    void add_value(int);
    void add_value(std::string);
    
    int getSize();
    std::string getName();
    int getType();
    void print_values();
};