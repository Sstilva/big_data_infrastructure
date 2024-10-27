#include <stdio.h>
#include "database/database.hpp"
#include "column/column_type_enum.hpp"
#include <iostream>
#include "printing/print_table.cpp"

/*
    Тестируем наши БД здесь
*/

/*
    Порядок теста:
        1. Создать БД
        2. Создать таблицу в БД
        3. Добавить в таблицу строки
        4. Удалить строки из таблицы
        ...
*/
int main(void) {
    // Создали БД
    Database a = Database();
    a.loadDatabase();
    // Создали таблицу в БД
    std::vector<int> column_types = { TableColumnType::STRING, TableColumnType::INTEGER, TableColumnType::FLOAT };
    std::vector<std::string> column_names = { "TestStringColumn", "TestIntColumn", "TestFloatColumn" };
    auto table = a.createTable("Hello_World", column_names, column_types);
    auto table_ = a.createTable("Hello_World_", column_names, column_types);
    auto table__ = a.createTable("Hello_World_", column_names, column_types);

    std::string str_to_append = std::string("Hello, world!");
    int int_to_append = 10;
    float float_to_append = 20.15;

    std::cout << "Добавляю строку в таблицу!" << std::endl;
    std::vector<void*> row_pointers = {
        (void*)&str_to_append,
        (void*)&int_to_append,
        (void*)&float_to_append
    };

    table.add_row(row_pointers);

    std::string st2 = std::string("Hey!");
    int int2 = 40;
    float float2 = 70.75;

    std::vector<void*> row_pointers2 = {
        (void*)&st2,
        (void*)&int2,
        (void*)&float2
    };

    table.add_row(row_pointers2);

    std::cout << "Вывожу таблицу: " << std::endl;
    printTable(table);
    a.writeToDisk("db_dump.bin");

    Database b = Database();
    b.loadFromDisk("db_dump.bin");
    return 0;
}