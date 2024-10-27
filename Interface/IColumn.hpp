#pragma once
#include <string>

template <class ColumnClass>
class IColumn {
public:
    ColumnClass add_value(float);
    ColumnClass add_value(int);
    ColumnClass add_value(std::string);

    int getIntValue(int idx);
    float getFloatValue(int idx);
    std::string getStringValue(int idx);
    
    int getSize();
    std::string getName();
    int getType();
    void print_values();

    ColumnClass loadFromBytes(char* byteArray);
};