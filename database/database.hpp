/*
Здесь хранится структура классов БД
*/
#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <map>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include "../Interface/IDatabase.hpp"

class Database : IDatabase {
    public:

        //from interface
        void loadDatabase();
        void saveDatabase();
        ITable createTable(std::string tableName);
        ITable createTable(std::string tableName, std::vector<std::string> columnNames, std::vector<int> columnTypes);
        ITable getTable(std::string tableName);
        std::map<std::string, ITable> getTables();
        
        // Custom
        void printTables();
        void saveTables();
        void writeTableToDisk(std::string tableName);
        void loadTable(std::filesystem::path path);
        void flush();

        // void readTable();
        // void loadTable();
        

        void deleteTable(std::string tableName);
    private:
        std::map<std::string, ITable> tables;
        std::string databasePath = "MyDatabase";
};

#endif