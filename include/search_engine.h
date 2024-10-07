#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <unordered_map>

class SearchEngine {
public:
    // Constructor and Destructor
    SearchEngine();
    ~SearchEngine();

    // Methods
    void indexDocuments(const std::vector<std::string>& docs);
    std::vector<std::string> search(const std::string& query);

private:
    std::unordered_map<std::string, std::vector<int>> invertedIndex; // Inverted index
    void buildInvertedIndex(const std::vector<std::string>& docs);
};

#endif // SEARCH_ENGINE_H
