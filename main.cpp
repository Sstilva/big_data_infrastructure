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
void fill_table(Table *t){
    std::vector<std::string> c1 = {"Hello, world!", "DBs are cool!", "Super cool", "?", "!", ";"};
    std::vector<int> c2 = {10, 20, 30, 30, 40, 50};
    std::vector<float> c3 = {0.0, 0.1, 0.5, 0.8, 0.9, 0.99};
    for(int i = 0; i < c1.size(); ++i){
        (*t).add_row({(void*)&c1[i], (void*)&c2[i], (void*)&c3[i]});
    }
}

int main(void) {
    // Создали БД
    Database a = Database();
    // Создали таблицу в БД
    std::vector<int> column_types = { TableColumnType::STRING, TableColumnType::INTEGER, TableColumnType::FLOAT };
    std::vector<std::string> column_names = { "TestStringColumn", "TestIntColumn", "TestFloatColumn" };
    Table table = a.makeTable("Hello_World", column_names, column_types);

    fill_table(&table);

    std::cout << "Вывожу таблицу: " << std::endl;
    printTable(table);

    std::cout << "Статистика: " << std::endl;
    std::cout << "Среднее TestIntColumn: " << table.getColumn("TestIntColumn").mean() << std::endl;
    std::cout << "Медиана TestIntColumn: " << table.getColumn("TestIntColumn").median() << std::endl;
    std::cout << "0.1 квантиль TestIntColumn: " << table.getColumn("TestIntColumn").percentile(0.1) << std::endl;
    std::cout << "0.9 квантиль TestIntColumn: " << table.getColumn("TestIntColumn").percentile(0.9) << std::endl;
    return 0;
}