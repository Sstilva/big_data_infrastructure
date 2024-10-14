
#include "column.hpp"
#include "column_type_enum.hpp"
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

Column::Column(int col_type){
    // Создаем колонку только с указанием типа
    this->column_type = col_type;
    this->string_values = std::vector<std::string>();
    this->int_values = std::vector<int>();
    this->float_values = std::vector<float>();
}

Column::Column(int col_type, std::string col_name){
    this->column_type = col_type;
    this->name = col_name;
    this->string_values = std::vector<std::string>();
    this->int_values = std::vector<int>();
    this->float_values = std::vector<float>();

}

Column::Column(int col_type, std::string, std::vector<std::string> str_values){
    // Создаем колонку типа str и заполняем ее значения
    if(col_type != TableColumnType::STRING){
        throw std::invalid_argument("Тип колонки и тип значений не совпадают!");
    }

    // Копируем переданные значения
    this->column_type = col_type;
    this->string_values = std::vector<std::string>(str_values.size());
    this->string_values.insert(std::end(this->string_values), std::begin(str_values), std::end(str_values));
}

void Column::add_value(int val){
    if(this->column_type != TableColumnType::INTEGER){
        std::cout << "Не могу добавить int в колонку типа не int!" << std::endl;
        throw std::invalid_argument("Тип колонки и тип значений не совпадают!");
    }
    this->int_values.push_back(val);
}

void Column::add_value(float val){
    if(this->column_type != TableColumnType::FLOAT){
        std::cout << "Не могу добавить float в колонку типа не float!" << std::endl;
        throw std::invalid_argument("Тип колонки и тип значений не совпадают!");
    }
    this->float_values.push_back(val);

}

void Column::add_value(std::string val){
    if(this->column_type != TableColumnType::STRING){
        std::cout << "Не могу добавить строку в колонку типа не строка!" << std::endl;
        throw std::invalid_argument("Тип колонки и тип значений не совпадают!");
    }
    std::cout << "Размер до: "<< this->string_values.size() << std::endl;
    this->string_values.push_back(val);
    std::cout << "Размер после: " << this->string_values.size() << std::endl;
}

template <typename T>
void print_col_values(T values_vector){
    for(int i = 0; i < values_vector.size(); ++i){
        std::cout << "| " << values_vector[i] << std::endl;
    }
}

void Column::print_values(){
    std::cout << "-----" << std::endl;
    std::cout << this->name << std::endl;
    std::cout << "-----" << std::endl;

    if(this->column_type == TableColumnType::STRING){
        print_col_values(this->string_values);
    }
    else if(this->column_type == TableColumnType::INTEGER){
        print_col_values(this->int_values);
    }
    else if(this->column_type == TableColumnType::FLOAT){
        print_col_values(this->float_values);
    }
    
    std::cout << "-----" << std::endl;

}


std::vector<std::string> Column::getStringRepresentation(){
    std::vector<std::string> values = std::vector<std::string>();
    if(this->column_type == TableColumnType::INTEGER){
        for(int i = 0; i < this->int_values.size(); ++i){
            std::stringstream ss;
            ss << this->int_values[i];
            values.push_back(ss.str());
        }
    }
    else if(this->column_type == TableColumnType::FLOAT){
        for(int i = 0; i < this->float_values.size(); ++i){
            std::stringstream ss;
            ss << this->float_values[i];
            values.push_back(ss.str());
        }
    }
    else if(this->column_type == TableColumnType::STRING){
        for(int i = 0; i < this->string_values.size(); ++i){
            values.push_back(this->string_values[i]);
        }
    }
    return values;
}

int Column::getSize(){
    switch(this->column_type){
        case TableColumnType::INTEGER:
            return this->int_values.size();
        case TableColumnType::FLOAT:
            return this->float_values.size();
        case TableColumnType::STRING:
            return this->string_values.size();
        default:
            throw;
    }
}