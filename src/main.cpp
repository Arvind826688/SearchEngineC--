#include "search_engine.h"
#include "utils.h"
#include <iostream>

int main() {
    // Load documents from data folder
    std::vector<std::string> docs;
    std::vector<std::string> filePaths = Utils::getFilesInDirectory("./data/");
    
    for (const auto& filePath : filePaths) {
        docs.push_back(Utils::readFile(filePath));
    }

    // Initialize Search Engine
    SearchEngine engine;
    engine.indexDocuments(docs);

    // Perform a search
    std::string query;
    std::cout << "Enter search query: ";
    std::getline(std::cin, query);

    std::vector<std::string> results = engine.search(query);
    
    // Display results
    if (results.empty()) {
        std::cout << "No results found.\n";
    } else {
        for (const auto& result : results) {
            std::cout << result << std::endl;
        }
    }

    return 0;
}
