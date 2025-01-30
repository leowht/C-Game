/*
** EPITECH PROJECT, 2024
** JSONStorage
** File description:
** JSONStorage
*/

#ifndef JSONSTORAGE
#define JSONSTORAGE

#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <string>

class IJSONArray {
public:
    virtual ~IJSONArray() = default;
    virtual void insertData(int fileID, const std::string& file) = 0;
    virtual void removeData(int fileID) = 0;
    virtual const std::string& getData(int fileID) const = 0;
};

class JSONArray : public IJSONArray {
public:
    void insertData(int fileID, const std::string& file) override {
        if (files.find(fileID) != files.end()) {
            std::cout << "File already added" << std::endl;
            return;
        }
        files[fileID] = file;
    }

    void removeData(int fileID) override {
        if (files.find(fileID) == files.end()) {
            throw std::runtime_error("Removing non-existent file.");
        }
        files.erase(fileID);
    }

    const std::string& getData(int fileID) const override {
        auto it = files.find(fileID);
        if (it == files.end()) {
            throw std::runtime_error("Retrieving non-existent file.");
        }
        return it->second;
    }

private:
    std::unordered_map<int, std::string> files{};
};

class JSONStorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<IJSONArray>> JSONArrays{};

    std::shared_ptr<IJSONArray> getJSONArray(const std::string& category) const {
        auto it = JSONArrays.find(category);
        if (it == JSONArrays.end()) {
            throw std::runtime_error("JSON category not registered: " + category);
        }
        return it->second;
    }

public:
    void registerCategory(const std::string& category) {
        if (JSONArrays.find(category) != JSONArrays.end()) {
            throw std::runtime_error("Category already registered: " + category);
        }
        JSONArrays[category] = std::make_shared<JSONArray>();
    }

    void addJSON(const std::string& category, int fileID, const std::string& file) {
        getJSONArray(category)->insertData(fileID, file);
    }

    void removeJSON(const std::string& category, int fileID) {
        getJSONArray(category)->removeData(fileID);
    }

    const std::string& getJSON(const std::string& category, int fileID) const {
        return getJSONArray(category)->getData(fileID);
    }
};

#endif /* !JSONSTORAGE */
