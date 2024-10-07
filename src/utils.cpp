#include "utils.h"
#include <fstream>
#include <filesystem>

// Read a file's content into a string
std::string Utils::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

// Get list of files in a directory
std::vector<std::string> Utils::getFilesInDirectory(const std::string& dirPath) {
    std::vector<std::string> filePaths;
    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        filePaths.push_back(entry.path().string());
    }
    return filePaths;
}
