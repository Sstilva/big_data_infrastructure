/*
Файл содержит реализацию класса БД
*/

#include <iostream>
#include "database.hpp"
#include "../column/column_type_enum.hpp"
#include "../table/table.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <filesystem>
#include <stdio.h>

void Database::loadDatabase(){
    if (!std::filesystem::exists(databasePath)){
        std::cout << "Could not find Database on Disk" << std::endl;
        return;
    }
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(databasePath)){
        std::filesystem::path path(dirEntry);
    }
}

void Database::loadTable(std::filesystem::path path){
    std::string tableName = path.stem().string();
    std::string tableData = "";
    createTable(tableName);
}

void Database::saveDatabase(){
    if (!std::filesystem::exists(databasePath)){
        std::cout << "Attempting first load on Disk";
        auto res = std::filesystem::create_directory(databasePath);
        if (res == -1){
            std::cout << "Failed to save database";
            return;
        }
    }
    saveTables();
}
void Database::saveTables(){
    for ( const auto &tableKV : tables ) {
        auto tableName = tableKV.first;
        try
        {
            writeTableToDisk(tableName);
        }
        catch (const char* error)
        {
            std::cout << "Colud not write table `"<< tableName <<"` to disk" << std::endl;
        }
        
    }
}

void flush(std::string tableName){}

void Database::writeTableToDisk(std::string tableName){
    auto table = tables[tableName];
    //TODO fix ITable.serialize()
    // auto tableData = table.serializeTable();
    std::string tablePath = databasePath + "/" + tableName + ".txt";
    std::string tableData = "columnName; columnType; ColumnData\n";    
    std::ofstream out( tablePath );
    out << tableData;
}

std::map<std::string, ITable> Database::getTables(){
    std::map<std::string, ITable> tablesInterfaces;
    for ( const auto &table : tables ) {
        tablesInterfaces.insert({table.first, static_cast<ITable>(table.second)});
    } 

    return tablesInterfaces;
}

ITable Database::getTable(std::string tableName){
    if (tables.find(tableName) == tables.end()){
        std::cout << "Unknown table\n";
    }
    auto table = tables[tableName];
    return static_cast<ITable>(table);
}

void Database::printTables(){
    for ( const auto &table : tables ) {
        std::cout << table.first << "\n";
    }

}

ITable Database::createTable(std::string tableName){
    if(tables.find(tableName) != tables.end()){
        std::cout << "Table `"<< tableName << "` already exitst" << std::endl;
        return tables[tableName];
    }
    
    std::cout << "Creating new table `"<< tableName <<"`" << std::endl;

    Table new_table = Table(tableName);
    tables.insert({tableName, new_table});
    return static_cast<ITable>(new_table);
}


ITable Database::createTable(std::string tableName, std::vector<std::string> columnNames, std::vector<int> columnTypes){
    /*
    Функция создает таблицу в базе данных
    */
    if(tables.find(tableName) != tables.end()){

        std::cout << "Table `"<< tableName << "` already exitsts" << std::endl;
        return tables[tableName];
    }
    
    std::cout << "Creating new table `"<< tableName <<"`" << std::endl;

    Table new_table = Table(tableName, columnNames, columnTypes);
    tables.insert({tableName, new_table});
    return static_cast<ITable>(new_table);
}

void Database::deleteTable(std::string tableName){
    if(tables.find(tableName) == tables.end()){

        std::cout << "Table `"<< tableName << "` does not exitst" << std::endl;
        return;
    }
    auto table = tables[tableName];
    //TODO сделать метод для правильного удаления таблицы
    // table.erase();
    tables.erase(tableName);
    std::cout<< "Deleted table `" << tableName<< "`\n";
}