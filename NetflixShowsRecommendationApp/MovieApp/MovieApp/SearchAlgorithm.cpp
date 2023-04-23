
#include "SearchAlgorithm.h"

bool operator<(const ShowNBool& other1, const ShowNBool& other2)
{
    int size1 = 0;
    int size2 = 0;
    for (const auto& it : other1.boolArray) {
        if (it == true) {
            size1++;
        }
    }
    for (const auto& it : other2.boolArray) {
        if (it == true) {
            size2++;
        }
    }
    return (size1 < size2);
}

bool operator<(const std::pair<DbShow, int>& other1, const std::pair<DbShow, int>& other2)
{
    return other1.second < other2.second;
}


bool PredictiveSearch(const std::string& text, const std::string& pattern) {
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

std::unordered_set<std::string> SplitStringByWords(std::string& text) {
    std::unordered_set<std::string> wordArray;
    std::string word;
    std::istringstream stream(text);
    while (stream >> word) {
        wordArray.insert(word);
    }
    return wordArray;
}

std::vector<bool> CreateFoundArray(std::unordered_set<std::string>& wordArray, std::string& text) {
    std::vector<bool> foundArray;
    for (auto& it : wordArray) {
        foundArray.push_back(PredictiveSearch(text, it));
    }
    return foundArray;
}

//std::string CreateMegaString(Database& storage, int index) {
//    std::string megaString;
//    
//    std::vector<std::string> actors = storage.getMatchingAuthors(index);
//    std::vector<std::string> directors = storage.getMatchingDirectors(index);
//    std::vector<std::string> countries = storage.getMatchingCountries(index);
//
//    auto show = storage.m_StoragePtr->get<Show>(index);
//    megaString += (show.GetTitle() + " ");
//    //megaString += (show.GetDescription() + " ");
//
//    for (auto& it : actors) {
//        megaString += (it + " ");
//    }
//    for (auto& it : countries) {
//        megaString += (it + " ");
//    }
//    for (auto& it : directors) {
//        megaString += (it + " ");
//    }
//    return megaString;
//}

std::string CreateMegaString2(const FullShow& fullshow) {
    std::string megaString;

    megaString += (fullshow.title + " ");
    //megaString += (show.GetDescription() + " ");

    for (auto& it : fullshow.actors) {
        megaString += (it + " ");
    }
    for (auto& it : fullshow.countries) {
        megaString += (it + " ");
    }
    for (auto& it : fullshow.directors) {
        megaString += (it + " ");
    }
    return megaString;
}

//std::vector<FullShow> createFullShowVector(Database& storage) {
//    std::vector<FullShow> showVector;
//    auto showCount = storage.m_StoragePtr->count<Show>();
//    for (int i = 1; i <= showCount; i++) {
//        FullShow fs;
//        fs.index = i;
//        auto show = storage.m_StoragePtr->get<Show>(i);
//        fs.title = show.GetTitle();
//        fs.actors = storage.getMatchingAuthors(i);
//        fs.directors = storage.getMatchingDirectors(i);
//        fs.countries = storage.getMatchingCountries(i);
//        showVector.push_back(fs);
//    }
//    return showVector;
//}

//std::vector<ShowNBool> CreateSortedShowAndBoolArrayVector(std::string text, Database& storage) {
//
//    std::unordered_set<std::string> wordSet = SplitStringByWords(text);
//    std::vector<bool> foundArray;
//
//    
//    std::vector<ShowNBool> pairArray;
//    auto showCount = storage.m_StoragePtr->count<Show>();
//    for (int i = 1; i <= showCount; i++) {
//        std::string megaString = CreateMegaString(storage, i);
//        foundArray = CreateFoundArray(wordSet, megaString);
//        ShowNBool show;
//        bool atLeastOneFoundWord = false;
//        for (const auto& it : foundArray) {
//            if (it == true) {
//                atLeastOneFoundWord = true;
//            }
//        }
//        if (atLeastOneFoundWord == true) {
//            show.s = storage.m_StoragePtr->get<Show>(i);
//            show.boolArray = foundArray;
//            pairArray.push_back(show);
//        }
//       
//    }
//
//    std::sort(pairArray.begin(), pairArray.end());
//
//    return pairArray;
//}

//std::priority_queue<FullShowNBool> CreateSortedFullShowAndBoolArrayVector(std::string text, const std::vector<FullShow>& showVector) {
//    std::unordered_set<std::string> wordSet = SplitStringByWords(text);
//    std::vector<bool> foundArray;
//    std::priority_queue<FullShowNBool> prqueue;
//
//    std::vector<FullShowNBool> pairArray;
//    for (auto& it : showVector) {
//        std::string megaString = CreateMegaString2(it);
//        foundArray = CreateFoundArray(wordSet, megaString);
//        FullShowNBool show;
//        bool atLeastOneFoundWord = false;
//        for (const auto& it : foundArray) {
//            if (it == true) {
//                atLeastOneFoundWord = true;
//            }
//        }
//        if (atLeastOneFoundWord == true) {
//            show.s = it;
//            show.boolArray = foundArray;
//            //pairArray.push_back(show);
//            prqueue.push(show);
//        }
//    }
//    return prqueue;
//}

std::priority_queue<std::pair<DbShow, int>> Search(std::string text, Database& storage) {
    auto showCount = storage.m_StoragePtr->count<DbShow>();
    std::unordered_set<std::string> wordSet = SplitStringByWords(text);
    std::priority_queue<std::pair<DbShow, int>> prqueue;

    for (int i = 1; i <= showCount; i++) {
        auto show = storage.m_StoragePtr->get<DbShowTokens>(i);
        int count = 0;
        for (auto& it : wordSet) {
            if (PredictiveSearch(show.GetTokens(), it)) {
                count++;
            }
        }
        if (count > 0) {
            prqueue.emplace(std::make_pair (storage.m_StoragePtr->get<DbShow>(i), count));
        }
    }
    return prqueue;
}
