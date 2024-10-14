/*
Этот файл предназначен для хранения интерфейсов, описывающих БД
*/
#ifndef DATABASE_INTERFACES_HPP
#define DATABASE_INTERFACES_HPP

#include <vector>
#include <string>
#include "../table/table.hpp"

class DatabaseInterface {
    public:
        void loadDatabase();
        void saveDatabase();
        void readTable();
        Table makeTable(std::string table_name, std::vector<std::string> column_names, std::vector<int> column_types);
        void loadTable();
        std::vector<Table> getTables();
    private:
        std::vector<Table> tables;
};

#endif