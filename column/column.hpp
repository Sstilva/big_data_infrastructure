
#ifndef COLUMN_COLUMN_HPP
#define COLUMN_COLUMN_HPP

#include <string>
#include <vector>
#include "../Interface/IColumn.hpp"

class Column: public IColumn {
    public:
        Column(int col_type);
        Column(int col_type, std::string col_name);
        Column(int col_type, std::string col_name, std::vector<std::string> str_values);

        /*
            Добавление значений в колонку
        */
       void add_value(float);
       void add_value(int);
       void add_value(std::string);

       /*
            Ввод-вывод
       */
        std::vector<std::string> getStringRepresentation();

        /*
            Информация о структуре
        */
        int getSize();

        std::string getName();
        int getType() {return column_type;};
        void print_values();

        int getIntValue(int idx);
        float getFloatValue(int idx);
        std::string getStringValue(int idx);
    private:
        std::string name;
        int column_type;
        std::vector<int> int_values;
        std::vector<float> float_values;
        std::vector<std::string> string_values;
};

#endif