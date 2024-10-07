#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    static std::string readFile(const std::string& filePath);
    static std::vector<std::string> getFilesInDirectory(const std::string& dirPath);
};

#endif // UTILS_H
