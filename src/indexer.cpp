#include "indexer.h"
#include <sstream>
#include <cctype>

// Create an inverted index from a list of documents
std::unordered_map<std::string, std::vector<int>> Indexer::createInvertedIndex(const std::vector<std::string>& docs) {
    std::unordered_map<std::string, std::vector<int>> invertedIndex;

    for (int docId = 0; docId < docs.size(); ++docId) {
        std::vector<std::string> tokens = tokenize(docs[docId]);

        for (const auto& token : tokens) {
            invertedIndex[token].push_back(docId);
        }
    }

    return invertedIndex;
}

// Tokenize a document into words
std::vector<std::string> Indexer::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;
    
    while (ss >> word) {
        // Remove punctuation and make lowercase
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return !std::isalnum(c); }), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        tokens.push_back(word);
    }

    return tokens;
}
