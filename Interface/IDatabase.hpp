/*
Этот файл предназначен для хранения интерфейсов, описывающих БД
*/
#ifndef DATABASE_INTERFACES_HPP
#define DATABASE_INTERFACES_HPP

#include <vector>
#include <string>
#include "./ITable.hpp"

template <class TableClass>
class IDatabase {
    /*
    Должен возвращать только интерфейсы таблиц, потому что он манипулирует только таблицами
    */
    public:
        // Запись на диск
        virtual int writeToDisk(std::string filePath) = 0;
        // Загрузка с диска
        virtual void loadFromDisk(std::string filePath) = 0;
        // ...
        virtual void loadDatabase() = 0;
        virtual void saveDatabase() = 0;
        virtual TableClass createTable(std::string tableName) = 0;
        virtual TableClass getTable(std::string tableName) = 0;
        // std::vector<ITable> getTables();
        virtual void deleteTable(std::string tableName) = 0;
};

#endif