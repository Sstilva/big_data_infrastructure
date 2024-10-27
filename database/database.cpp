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
#include <fstream>
#include <filesystem>
#include <cstring>

Database::Database(){
    std::cout << "Создана новая пустая БД!" << std::endl;
}

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

std::map<std::string, Table> Database::getTables(){
    std::map<std::string, Table> tablesInterfaces;
    for ( const auto &table : tables ) {
        tablesInterfaces.insert({table.first, static_cast<Table>(table.second)});
    } 

    return tablesInterfaces;
}

Table Database::getTable(std::string tableName){
    if (tables.find(tableName) == tables.end()){
        std::cout << "Unknown table\n";
    }
    auto table = tables[tableName];
    return static_cast<Table>(table);
}

void Database::printTables(){
    for ( const auto &table : tables ) {
        std::cout << table.first << "\n";
    }

}

Table Database::createTable(std::string tableName){
    if(tables.find(tableName) != tables.end()){
        std::cout << "Table `"<< tableName << "` already exitst" << std::endl;
        return tables[tableName];
    }
    
    std::cout << "Creating new table `"<< tableName <<"`" << std::endl;

    Table new_table = Table(tableName);
    tables.insert({tableName, new_table});
    return static_cast<Table>(new_table);
}


Table Database::createTable(std::string tableName, std::vector<std::string> columnNames, std::vector<int> columnTypes){
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
    return this->tables[tableName];
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

int Database::writeToDisk(std::string savePath){
    std::cout << "Начинаю запись БД в файл" << std::endl;
    // Откроем файл для записи
    std::ofstream file;
    file.open(savePath, std::ios_base::binary);
    
    if(!file.is_open()){
        std::cout << "Ошибка: не могу открыть файл " << savePath << " для записи!";
        throw "Can't open path to save Database!";
    }

    // Определим, сколько у нас таблиц
    int tableCount = this->tables.size();
    // Запишем кол-во таблиц в файл
    std::cout << "Записываю кол-во таблиц: " << tableCount << std::endl;
    file.write((char*)&tableCount, sizeof(tableCount));

    std::cout << "Начинаю проход по таблицам" << std::endl;
    for(auto const& [key, val] : this->tables){
        // Запишем имя таблицы
        const char* tableName = key.c_str();
        int tableNameSize = key.size();
        std::cout << "\tИмя таблицы и размер имени в байтах: " << tableName << "; " << tableNameSize << std::endl;
        // (сначала пишем сколько байт занимает имя)
        file.write((char*)&tableNameSize, sizeof(tableNameSize));
        // затем само имя
        file.write(tableName, tableNameSize);
        // Запишем кол-во колонок
        int columnCount = val.columns.size();
        file.write((char*)&columnCount, sizeof(columnCount));
        std::cout << "\tКол-во колонок: " << columnCount << std::endl;

        // теперь идем по колонкам
        for(int b = 0; b < val.columns.size(); ++b){
            // Запишем имя колонки: сначала кол-во байт, потом сами
            // байты
            const char* colName = val.columnNames[b].c_str();
            int colNameSize = val.columnNames[b].size();
            file.write((char*)&colNameSize, sizeof(colNameSize));
            file.write(colName, colNameSize);
            std::cout << "\t\tИмя колонки и размер имени в байтах: " << colName << " " << colNameSize << std::endl;

            // Запишем тип колонки
            file.write((char*)&val.columnTypes[b], sizeof(val.columnTypes[b]));
            std::cout << "\t\tТип колонки: " << val.columnTypes[b] << std::endl;
            // Запишем значения колонки
            int bytesToWrite = 0;
            const char* columnValuesBytes = this->tables[key].columns[b].getBytesOfValues(bytesToWrite);
            std::cout << "\t\tРазмер значений колонки в байтах: " << bytesToWrite << std::endl;
            file.write(columnValuesBytes, bytesToWrite);
            free((void*)columnValuesBytes); // Чистим память выделенную под байты
        }
    }
    
    file.close();
    return 1;
}

void Database::loadFromDisk(std::string loadPath){
    // Почистить память перед чтением?

    std::cout << "Начинаю загрузку БД из файла" << std::endl;
    std::filesystem::path inputFilePath{loadPath};
    uint length = std::filesystem::file_size(inputFilePath);
    char* content = (char*)malloc(length);
    // Откроем файл для записи
    std::ifstream file;
    file.open(loadPath, std::ios_base::binary);
    if(!file.is_open()){
        std::cout << "Ошибка: не могу открыть файл " << loadPath << " для чтения!";
        throw "Can't open file to load Database!";
    }
    file.read(content, length);
    file.close();

    // Зеркалим процедуру записи
    int currentOffset = 0;
    // Читаем кол-во таблиц
    int tableCount = *(int*)(content + currentOffset);
    std::cout << "Определил кол-во загружаемых таблиц: " << tableCount;
    currentOffset += sizeof(int);

    this->tables = std::map<std::string, Table>();
    for(int i = 0; i < tableCount; ++i){
        // Прочитаем имя таблицы
        int tableNameLength = *(int*)(content + currentOffset);
        currentOffset += sizeof(int);
        std::cout << "Число байт в имени таблицы: " << tableNameLength << std::endl;
        std::string tableName = std::string(content + currentOffset, 0, tableNameLength);
        std::cout << "Имя таблицы: " << tableName << std::endl;
        currentOffset += tableNameLength;
        Table table = this->createTable(tableName);
        // Получим число колонок в таблице
        int columnCount = *(int*)(content + currentOffset);
        currentOffset += sizeof(int);
        std::cout << "В таблице " << tableName << " " << columnCount << " колонок" << std::endl;
        // Идем по колонкам
        for(int b = 0; b < columnCount; ++b){
            // Получаем имя колонки
            int columnNameLength = *(int*)(content + currentOffset);
            currentOffset += sizeof(int);
            std::cout << "Число байт в имени колонки: " << columnNameLength << std::endl;
            std::string columnName = std::string(content + currentOffset, 0, columnNameLength);
            std::cout << "Имя колонки: " << columnName << std::endl;
            currentOffset += columnNameLength;
            // Теперь получим тип колонки
            int columnType = *(int*)(content + currentOffset);
            currentOffset += sizeof(int);
            // Создадим колонку
            Column col = table.addColumn(columnName, columnType);
            // И загрузим в нее значения
            col.loadFromBytes(content + currentOffset);
        }
        return;
    }
    // if(!file.is_open()){
    //     std::cout << "Ошибка: не могу открыть файл " << savePath << " для записи!";
    //     throw "Can't open path to save Database!";
    // }

    // // Определим, сколько у нас таблиц
    // int tableCount = this->tables.size();
    // // Запишем кол-во таблиц в файл
    // std::cout << "Записываю кол-во таблиц: " << tableCount << std::endl;
    // file.write((char*)&tableCount, sizeof(tableCount));

    // std::cout << "Начинаю проход по таблицам" << std::endl;
    // for(auto const& [key, val] : this->tables){
    //     // Запишем имя таблицы
    //     const char* tableName = key.c_str();
    //     int tableNameSize = key.size();
    //     std::cout << "Имя таблицы и размер имени в байтах: " << tableName << "; " << tableNameSize << std::endl;
    //     // (сначала пишем сколько байт занимает имя)
    //     file.write((char*)&tableNameSize, sizeof(tableNameSize));
    //     // затем само имя
    //     file.write(tableName, tableNameSize);
    //     // Запишем кол-во колонок
    //     int columnCount = val.columns.size();
    //     file.write((char*)&columnCount, sizeof(columnCount));
    //     std::cout << "Кол-во колонок: " << columnCount << std::endl;

    //     // теперь идем по колонкам
    //     for(int b = 0; b < val.columns.size(); ++b){
    //         // Запишем имя колонки: сначала кол-во байт, потом сами
    //         // байты
    //         const char* colName = val.columnNames[b].c_str();
    //         int colNameSize = val.columnNames[b].size();
    //         file.write((char*)&colNameSize, sizeof(colNameSize));
    //         file.write(colName, colNameSize);
    //         std::cout << "Имя колонки и размер имени в байтах: " << colName << " " << colNameSize << std::endl;

    //         // Запишем тип колонки
    //         file.write((char*)&val.columnTypes[b], sizeof(val.columnTypes[b]));
    //         std::cout << "Тип колонки: " << val.columnTypes[b] << std::endl;
    //         // Запишем значения колонки
    //         int bytesToWrite = 0;
    //         const char* columnValuesBytes = this->tables[key].columns[b].getBytesOfValues(bytesToWrite);
    //         std::cout << "Размер значений колонки в байтах: " << bytesToWrite << std::endl;
    //         file.write(columnValuesBytes, bytesToWrite);
    //         free((void*)columnValuesBytes); // Чистим память выделенную под байты
    //     }
    // }
    
    // file.close();
    free((void*)content);
}