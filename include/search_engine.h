#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <unordered_map>

class SearchEngine {
public:
    SearchEngine();
    ~SearchEngine();

    void indexDocuments(const std::vector<std::string>& docs);
    std::vector<std::pair<std::string, double>> search(const std::string& query); // Modified to return ranked results

private:
    std::unordered_map<std::string, std::vector<int>> invertedIndex;
    std::vector<std::string> documents;
    std::unordered_map<std::string, double> idfScores;  // Store IDF values for terms

    void buildInvertedIndex(const std::vector<std::string>& docs);
    double calculateTF(const std::string& term, const std::string& document);
    double calculateIDF(const std::string& term);
};

#endif // SEARCH_ENGINE_H
