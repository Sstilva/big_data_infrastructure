#pragma once
#include <vector>

class ITable {
public:
    void add_row(std::vector<void*> values);
    std::vector<void*> read_row(int row_index);
    void delete_row(int row_index);
};