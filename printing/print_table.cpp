#ifndef PRINT_TABLE
#define PRINT_TABLE

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#include "../table/table.hpp"
#include "../column/column.hpp"


void printStrTable(const std::vector<std::vector<std::string>> &table) {
    if (table.empty()) {
        std::cout << "Empty Table" << std::endl;
        return;
    }

    // Определяем макс. ширину строки в каждой колонке
    // Нужно для красивого отображения таблицы
    std::vector<size_t> maxWidths(table[0].size(), 0);
    for (const auto &row : table) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (maxWidths[i] < row[i].length()) {
                maxWidths[i] = row[i].length();
            }
        }
    }

    // Выводим таблицу в красивой форме. Ширина колонок = макс. ширине
    // значения в них
    std::cout << "\n";
    for (const auto &row : table) {
        bool firstCol = true;
        for (size_t i = 0; i < row.size(); ++i) {
            if (!firstCol) std::cout << " | "; // Добавляем сепаратор между колонками
            std::cout << std::setw(maxWidths[i]) << row[i];
            firstCol = false;
        }
        std::cout << "\n";
    }
}


// Эта функция выводит сначала превращает таблицу в 
// строковое представление, затем выводит через другую printTable
void printTable(Table table){
    if(table.columns.size() == 0){ 
        std::cout << "Пустая таблица!" << std::endl;
        return;
    }

    std::vector<std::vector<std::string>> string_representation = std::vector<std::vector<std::string>>();
    // Сначала добавим имена колонок
    string_representation.push_back(table.columnNames);
    // Теперь добавим столько строк, сколько есть в первой колонке
    for(int i = 0; i < table.columns[0].getSize(); ++i){
        string_representation.push_back(std::vector<std::string>(0));
    }

    for(int i = 0; i < table.columns.size(); ++i){
        std::vector<std::string> column_representation = table.columns[i].getStringRepresentation();
        for(int b = 0; b < column_representation.size(); ++b){
            string_representation[b + 1].push_back(column_representation[b]);
        }
    }
    // Теперь уже отправляем таблицу в виде матрицы строк на вывод
    printStrTable(string_representation);

}

#endif