#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <queue>
#include "Database.h"

struct FullShow {
    int index;
    std::string title;
    std::vector<std::string> countries;
    std::vector<std::string> directors;
    std::vector<std::string> actors;

};
struct FullShowNBool {
    FullShow s;
    std::vector<bool> boolArray;
};

struct ShowNBool {
    DbShow s;
    std::vector<bool> boolArray;
public:
    bool operator < (ShowNBool const& other) {
        int size1 = 0;
        int size2 = 0;
        for (const auto& it : other.boolArray) {
            if (it == true) {
                size1++;
            }
        }
        for (const auto& it : this->boolArray) {
            if (it == true) {
                size2++;
            }
        }
        return (size1 < size2);
    }
};

bool operator<(const ShowNBool& other1, const ShowNBool& other2);
bool operator<(const std::pair<DbShow, int>& other1, const std::pair<DbShow, int>& other2);
std::priority_queue<std::pair<DbShow, int>> CreateOrderedArray(std::string text, Database& storage);


bool PredictiveSearch(const std::string& text, const std::string& pattern);

std::unordered_set<std::string> SplitStringByWords(std::string& text);
std::vector<bool> CreateFoundArray(std::unordered_set<std::string>& wordArray, std::string& text);
std::string CreateMegaString(Database& storage, int index);
std::vector<ShowNBool> CreateSortedShowAndBoolArrayVector(std::string text, Database& storage);

std::string CreateMegaString2(const FullShow& fullshow);
std::vector<FullShow> createFullShowVector(Database& storage);
std::priority_queue<FullShowNBool> CreateSortedFullShowAndBoolArrayVector(std::string text, const std::vector<FullShow>& showVector);
