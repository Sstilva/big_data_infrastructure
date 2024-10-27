#pragma once
#include <vector>
#include "IColumn.hpp"
#include "IDatabase.hpp"

template <class TableClass, class ColumnClass>
class ITable {
public:
    // Добавить колонку
    ColumnClass addColumn(std::string colname, int columnType);
    // Удалить колонку
    TableClass removeColumn(std::string colname);
    // Добавить строку
    TableClass add_row(std::vector<void*> values);
    std::vector<void*> read_row(int row_index);
    void delete_row(int row_index);

private:
    std::vector<ColumnClass> columns;
    std::vector<int> columnTypes;
};