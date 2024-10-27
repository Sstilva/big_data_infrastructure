/*
Здесь хранится структура классов БД
*/
#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <map>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include "../table/table.hpp"

class Database : public IDatabase<Table> {
    public:
        Database();
        //from interface
        void loadDatabase();
        void saveDatabase();
        Table createTable(std::string tableName);
        Table createTable(std::string tableName, std::vector<std::string> columnNames, std::vector<int> columnTypes);
        Table getTable(std::string tableName);
        std::map<std::string, Table> getTables();
        
        // Диск
        int writeToDisk(std::string savePath);
        void loadFromDisk(std::string loadPath);

        void printTables();
        void saveTables();
        void writeTableToDisk(std::string tableName);
        void loadTable(std::filesystem::path path);
        void flush();

        // void readTable();
        // void loadTable();
        

        void deleteTable(std::string tableName);
    private:
        std::map<std::string, Table> tables;
        std::string databasePath = "MyDatabase";
};

#endif