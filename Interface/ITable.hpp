#pragma once
#include <vector>
#include "../column/column.hpp"

class ITable {
public:
    /*
        Получение данных
    */
    Column getColumn(std::string colname);
    Column getColumn(char* colname);

    ITable* add_row(std::vector<void*> values);
    std::vector<void*> read_row(int row_index);
    void delete_row(int row_index);
};