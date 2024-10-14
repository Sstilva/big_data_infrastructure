
#ifndef TABLE_TABLE_HPP
#define TABLE_TABLE_HPP

#include <vector>
#include <string>
#include "../column/column.hpp"

class Table {
    public:
        Table();
        Table(std::string table_name, std::vector<std::string> column_names, std::vector<int> column_types);
        
        std::string name;
        std::vector<std::string> columnNames;
        std::vector<int> columnTypes;
        std::vector<Column> columns;

        // Функции добавления строк
        Table add_row(std::vector<void*> values);
};

#endif