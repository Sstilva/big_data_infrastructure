
#include <iostream>
#include "table.hpp"
#include "../column/column.hpp"
#include "../column/column_type_enum.hpp"
#include <vector>
#include <algorithm>
#include <sstream>

Table::Table(std::string table_name, std::vector<std::string> column_names, std::vector<int> column_types){
    std::cout << "Создаю таблицу!" << std::endl;
    // Создаем таблицу. Сначала запишем в целом какие колонки у нас есть
    // а также сохраним имя таблицы
    this->columnNames = column_names;
    this->columnTypes = column_types;
    this->name = table_name;

    for(int i = 0; i < column_names.size(); ++i){
        Column clm = Column(column_types[i], column_names[i]);
        this->columns.push_back(clm);
    }
}

Table::Table(){
    std::cout << "Empty table constructed!" << std::endl;
}

// =================================
// Получение колонки
// =================================
Column Table::getColumn(std::string colName){
    for(int i = 0; i < this->columnNames.size(); ++i){
        if(this->columnNames[i] == colName){
            return this->columns[i];
        }
    }
    std::stringstream msg;
    msg << "Колонка " << colName << " не найдена в таблице!";
    throw msg.str();
}

Column Table::getColumn(char* colName){
    return this->getColumn(std::string(colName));
}


// =================================
// Добавление строки 
// =================================
void Table::add_row(std::vector<void*> values){
    std::cout << "Получен запрос на добавление строки в таблицу!" << std::endl;
    int column_count = this->columns.size();
    std::cout << "Число колонок: " << column_count << std::endl;

    for(int i = 0; i < this->columns.size(); ++i){
        int column_type = this->columnTypes[i];

        if(column_type == TableColumnType::STRING){
            std::string str_pointed_to = *(std::string*)values[i];
            std::cout << "Получена строка: " << str_pointed_to << std::endl;
            this->columns[i].add_value(str_pointed_to);
        }
        
        if(column_type == TableColumnType::INTEGER){
            int int_pointed_to = *(int*)values[i];
            std::cout << "Получен int: " << int_pointed_to << std::endl;
            this->columns[i].add_value(int_pointed_to);
        }

        if(column_type == TableColumnType::FLOAT){
            float float_pointed_to = *(float*)values[i];
            std::cout << "Получен float: " << float_pointed_to << std::endl;
            this->columns[i].add_value(float_pointed_to);
        }
    }

}

std::vector<void*> read_row(int row_index){

}

void delete_row(int row_index){

}