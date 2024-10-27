
#ifndef TABLE_TABLE_HPP
#define TABLE_TABLE_HPP

#include "../Interface/ITable.hpp"
#include <vector>
#include <string>
#include "../column/column.hpp"


class Table: public ITable<Table, Column> {
    public:
        Table();
        Table(std::string tableName);
        Table(std::string table_name, std::vector<std::string> column_names, std::vector<int> column_types);
        
        std::string name;
        std::vector<std::string> columnNames;
        std::vector<int> columnTypes;
        std::vector<Column> columns;

        Column addColumn(std::string colname, int columnType);
        // Функции добавления строк
        Table add_row(std::vector<void*> values);
        std::vector<void*> read_row(int row_index);
        void delete_row(int row_index);

};

#endif