#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#ifdef UTILITYLIB_EXPORTS
#define UTILITYLIB_API __declspec(dllexport)
#else
#define UTILITYLIB_API __declspec(dllimport)
#endif


UTILITYLIB_API std::vector<std::string> SplitCsvLine(const std::string& line);

UTILITYLIB_API std::vector<std::string> SplitString(const std::string& str, const std::string& delim);

UTILITYLIB_API std::vector<std::string> SplitIntoWords(const std::string& str);

UTILITYLIB_API std::string ToLowerCase(const std::string& str);

UTILITYLIB_API bool PredictiveSearch(const std::string& text, const std::string& pattern);

UTILITYLIB_API std::vector<int> StringToVectorOfIntValues(const std::string& str);

UTILITYLIB_API std::vector<double> StringToVectorOfDoubleValues(const std::string& str);

//template<class T>
//UTILITYLIB_API std::vector<T> StringToVectorOfValues(const std::string& str);

//template<class T>
//inline UTILITYLIB_API std::vector<T> StringToVectorOfValues(const std::string& str)
//{
//	std::vector<std::string> stringValues = SplitString(str, " ");
//	std::vector<T> values;
//	for (const auto& stringValue : stringValues)
//	{
//		if (std::is_same<double, T>::value)
//		{
//			values.push_back(std::stod(stringValue));
//		}
//		else if (std::is_same<int, T>::value)
//		{
//			values.push_back(std::stoi(stringValue));
//		}
//		else
//		{
//			throw std::exception{ "undefined type" };
//		}
//	}
//	return values;
//}