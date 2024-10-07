#include "search_engine.h"
#include "indexer.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// Constructor
SearchEngine::SearchEngine() {}

// Destructor
SearchEngine::~SearchEngine() {}

// Index the documents and build the inverted index and IDF scores
void SearchEngine::indexDocuments(const std::vector<std::string>& docs) {
    documents = docs;
    buildInvertedIndex(docs);

    // Calculate IDF scores for all terms
    for (const auto& entry : invertedIndex) {
        idfScores[entry.first] = calculateIDF(entry.first);
    }
}

// Build the inverted index from the documents
void SearchEngine::buildInvertedIndex(const std::vector<std::string>& docs) {
    Indexer indexer;
    invertedIndex = indexer.createInvertedIndex(docs);
}

// Calculate TF (Term Frequency) for a term in a specific document
double SearchEngine::calculateTF(const std::string& term, const std::string& document) {
    Indexer indexer;
    std::vector<std::string> tokens = indexer.tokenize(document);

    int termCount = std::count(tokens.begin(), tokens.end(), term);
    return static_cast<double>(termCount) / tokens.size();  // Normalize by document length
}

// Calculate IDF (Inverse Document Frequency) for a term across all documents
double SearchEngine::calculateIDF(const std::string& term) {
    int docCount = documents.size();
    int docsWithTerm = invertedIndex[term].size();
    return log(static_cast<double>(docCount) / (1 + docsWithTerm));  // IDF formula
}

// Perform a search and return ranked documents using TF-IDF or phrase search
std::vector<std::pair<std::string, double>> SearchEngine::search(const std::string& query) {
    // Check if the query is a phrase (enclosed in double quotes)
    if (query.find("\"") != std::string::npos) {  
        std::string phrase = query.substr(1, query.length() - 2);  // Extract the phrase (strip quotes)
        std::vector<std::pair<std::string, double>> results;
        
        // Search for the phrase in each document
        for (int docId = 0; docId < documents.size(); ++docId) {
            if (documents[docId].find(phrase) != std::string::npos) {  // Exact phrase match
                results.push_back({"doc" + std::to_string(docId) + ".txt", 1.0});  // Placeholder score for phrase match
            }
        }

        return results;
    } else {
        // Perform word-based search using TF-IDF
        Indexer indexer;
        std::vector<std::string> queryTerms = indexer.tokenize(query);
        std::unordered_map<int, double> docScores;

        // Calculate the TF-IDF score for each query term in the documents
        for (const auto& term : queryTerms) {
            if (invertedIndex.find(term) != invertedIndex.end()) {
                for (int docId : invertedIndex[term]) {
                    double tf = calculateTF(term, documents[docId]);
                    double idf = idfScores[term];
                    docScores[docId] += tf * idf;  // Compute TF-IDF score
                }
            }
        }

        // Sort the documents by their TF-IDF score
        std::vector<std::pair<std::string, double>> rankedResults;
        for (const auto& [docId, score] : docScores) {
            rankedResults.push_back({"doc" + std::to_string(docId) + ".txt", score});
        }

        std::sort(rankedResults.begin(), rankedResults.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;  // Sort in descending order of score
        });

        return rankedResults;
    }
}
