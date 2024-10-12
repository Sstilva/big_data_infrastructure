#pragma once
#include <string>
#include <vector>

class IDatabase {
public:

    virtual std::string get(const std::string& tableName, const std::string& key) = 0;

    virtual void put(const std::string& tableName, const std::string& key, const std::string& value) = 0;

    virtual std::vector<std::string> getMultiple(const std::string& tableName, const std::vector<std::string>& keys) = 0;

    virtual void createTable(const std::string& tableName) = 0;

    virtual void deleteTable(const std::string& tableName) = 0;

    virtual ~IDatabase() = default;
};
