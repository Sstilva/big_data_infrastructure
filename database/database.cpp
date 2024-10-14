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

void Database::hello() {
    printf("Hello!");
}

void Database::loadDatabase(){
    printf("Hello!");
}

void Database::saveDatabase(){

}

void Database::readTable(){

}

void Database::loadTable(){

}

std::vector<Table> Database::getTables(){
    return std::vector<Table>(5);
}



Table Database::makeTable(std::string table_name, std::vector<std::string> column_names, std::vector<int> column_types){
    /*
    Функция создает таблицу в базе данных
    */
    std::cout << "Создаю новую таблицу в базе!" << std::endl;

    Table new_table = Table(table_name, column_names, column_types);
    this->tables.push_back(new_table);

    // Вернем айди таблицы
    // Проблема: если удалить какую-либо таблицу, размер изменится на меньший
    // тогда будет коллизия айдишников...
    std::cout << "Таблица создана!" << std::endl;
    return new_table;
}