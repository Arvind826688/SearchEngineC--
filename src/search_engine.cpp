#include "search_engine.h"
#include "indexer.h"
#include <algorithm>
#include <iostream>

// Constructor
SearchEngine::SearchEngine() {}

// Destructor
SearchEngine::~SearchEngine() {}

// Index the documents
void SearchEngine::indexDocuments(const std::vector<std::string>& docs) {
    buildInvertedIndex(docs);
}

// Build the inverted index
void SearchEngine::buildInvertedIndex(const std::vector<std::string>& docs) {
    Indexer indexer;
    invertedIndex = indexer.createInvertedIndex(docs);
}

// Search for documents that contain the query terms
std::vector<std::string> SearchEngine::search(const std::string& query) {
    Indexer indexer;
    std::vector<std::string> queryTerms = indexer.tokenize(query);
    std::vector<int> results;

    for (const auto& term : queryTerms) {
        if (invertedIndex.find(term) != invertedIndex.end()) {
            std::vector<int>& docIds = invertedIndex[term];
            results.insert(results.end(), docIds.begin(), docIds.end());
        }
    }

    // Remove duplicate results
    std::sort(results.begin(), results.end());
    results.erase(std::unique(results.begin(), results.end()), results.end());

    // Convert document IDs to file names (or return a placeholder for simplicity)
    std::vector<std::string> docNames;
    for (const auto& docId : results) {
        docNames.push_back("doc" + std::to_string(docId) + ".txt");
    }

    return docNames;
}
