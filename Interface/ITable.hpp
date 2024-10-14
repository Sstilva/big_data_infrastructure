#pragma once
#include <vector>

class ITable {
public:
    void add_row(std::vector<void*> values);
};