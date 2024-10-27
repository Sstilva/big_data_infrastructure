/*
Этот файл предназначен для хранения интерфейсов, описывающих БД
*/
#ifndef DATABASE_INTERFACES_HPP
#define DATABASE_INTERFACES_HPP

#include <vector>
#include <string>
#include "./ITable.hpp"

class IDatabase {
    /*
    Должен возвращать только интерфейсы таблиц, потому что он манипулирует только таблицами
    */
    public:
        void loadDatabase();
        void saveDatabase();
        ITable createTable(std::string& tableName);
        ITable getTable(std::string& tableName);
        // std::vector<ITable> getTables();
        void deleteTable(std::string tableName);
};

#endif