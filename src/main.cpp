#include "search_engine.h"
#include "utils.h"
#include <iostream>

int main() {
    std::vector<std::string> docs;
    std::vector<std::string> filePaths = Utils::getFilesInDirectory("./data/");
    
    for (const auto& filePath : filePaths) {
        docs.push_back(Utils::readFile(filePath));
    }

    SearchEngine engine;
    engine.indexDocuments(docs);

    std::string query;
    std::cout << "Enter search query: ";
    std::getline(std::cin, query);

    std::vector<std::pair<std::string, double>> results = engine.search(query);

    if (results.empty()) {
        std::cout << "No results found.\n";
    } else {
        for (const auto& [doc, score] : results) {
            std::cout << "Document: " << doc << " | Score: " << score << std::endl;
        }
    }

    return 0;
}
