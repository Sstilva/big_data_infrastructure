#pragma once
#include <string>

class IColumn {
public:
    /*
        Добавление значений
    */
    void add_value(float);
    void add_value(int);
    void add_value(std::string);

    /*
        Получение значений
    */

    void* getValue(int idx);

    int getIntValue(int idx);
    float getFloatValue(int idx);
    std::string getStringValue(int idx);
    
    /*
        Инфо о колонках
    */
    int getSize();
    std::string getName();
    int getType();
    void print_values();

    /*
        Статистические функции
    */
    double mean();
    double median();
    double percentile(double q);
};