#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>

class Indexer {
public:
    Indexer() {}
    std::unordered_map<std::string, std::vector<int>> createInvertedIndex(const std::vector<std::string>& docs);
    std::vector<std::string> tokenize(const std::string& text);
};

#endif // INDEXER_H
