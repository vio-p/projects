#include "pch.h"
#include "Utility.h"

#include <utility>
#include <string>

UTILITYLIB_API std::vector<std::string> SplitCsvLine(const std::string& line)
{
	std::vector<std::string> result;
	std::string column;
	bool quotationMarks = false;
	for (size_t index = 0; index < line.size(); index++)
	{
		if (line[index] == '\"' && !quotationMarks)
		{
			quotationMarks = true;
		}
		else if (line[index] == '\"' && quotationMarks)
		{
			quotationMarks = false;
		}
		else if (line[index] == ',' && !quotationMarks)
		{
			result.push_back(column);
			column.clear();
		}
		else
		{
			column += line[index];
		}
	}
	result.push_back(column);
	return result;
}

UTILITYLIB_API std::vector<std::string> SplitString(const std::string& str, const std::string& delim)
{
	std::vector<std::string> result;
	size_t startIndex = 0;

	for (size_t found = str.find(delim); found != std::string::npos; found = str.find(delim, startIndex))
	{
		result.emplace_back(str.begin() + startIndex, str.begin() + found);
		startIndex = found + delim.size();
	}
	if (startIndex != str.size())
		result.emplace_back(str.begin() + startIndex, str.end());
	return result;
}

UTILITYLIB_API std::vector<std::string> SplitIntoWords(const std::string& str)
{
	std::vector<std::string> words;
	std::string word;
	std::istringstream stream(str);
	while (stream >> word) {
		words.push_back(word);
	}
	return words;
}

UTILITYLIB_API std::string ToLowerCase(const std::string& str)
{
	std::string newStr = str;
	std::transform(str.begin(), str.end(), newStr.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return newStr;
}

UTILITYLIB_API bool PredictiveSearch(const std::string& text, const std::string& pattern) {
	int indexText = 0;
	while (indexText < text.size() - 1) {
		if (indexText + pattern.size() - 1 > text.size() - 1) {//se verifica daca s-a trecut de size-ul textului
			return false;
		}
		if (pattern[0] != text[indexText]) {//leftmost mismatch
			if (text[indexText] == ' ') {//alphabet-blank
				indexText += 1;
			}
			else {
				indexText += 2;
			}
		}
		else {//leftmost match
			if (pattern[pattern.size() - 1] == text[pattern.size() - 1 + indexText]) {//rightmost match
				bool mismatch = false;
				for (int i = pattern.size() - 1 + indexText - 1, j = pattern.size() - 2; i > indexText; i--, j--) {
					if (text[i] != pattern[j]) {//mismatch in the center
						indexText += pattern.size() - 1;
						mismatch = true;
						break;
					}
				}
				if (!mismatch) {
					return true;//return index of first character from found sequence
				}
			}
			else {//rightmost mismatch
				if (text[pattern.size() - 1 + indexText] == ' ') {//alphabet blank
					indexText += pattern.size() - 1 + 1;
				}
				else {//alphabet alphabet
					if (text[pattern.size() - 1 + indexText + 1] == ' ') {//blank
						indexText += pattern.size() - 1 + 1;
					}
					else {
						indexText += 2;
					}
				}
			}
		}

	}
	return false;
}

UTILITYLIB_API std::vector<int> StringToVectorOfIntValues(const std::string& str)
{
	std::vector<std::string> stringValues = SplitString(str, " ");
	std::vector<int> values;
	for (const auto& stringValue : stringValues)
	{
		values.push_back(std::stoi(stringValue));
	}
	return values;
}

UTILITYLIB_API std::vector<double> StringToVectorOfDoubleValues(const std::string& str)
{
	std::vector<std::string> stringValues = SplitString(str, " ");
	std::vector<double> values;
	for (const auto& stringValue : stringValues)
	{
		values.push_back(std::stod(stringValue));
	}
	return values;
}
