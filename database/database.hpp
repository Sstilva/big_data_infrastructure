/*
Здесь хранится структура классов БД
*/
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../Interface/IDatabase.hpp"

class Database : DatabaseInterface {
    public:
        void hello();
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