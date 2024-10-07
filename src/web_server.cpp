#include "crow_all.h"
#include "search_engine.h"
#include "utils.h"
#include <iostream>

int main() {
    SearchEngine engine;

    // Load documents from the data folder
    std::vector<std::string> docs;
    std::vector<std::string> filePaths = Utils::getFilesInDirectory("./data/");
    for (const auto& filePath : filePaths) {
        docs.push_back(Utils::readFile(filePath));
    }

    engine.indexDocuments(docs);

    crow::SimpleApp app;

    // Define a route for search queries
    CROW_ROUTE(app, "/search")
        .methods(crow::HTTPMethod::GET)
        ([&engine](const crow::request& req) {
            auto query_param = req.url_params.get("q");
            if (!query_param) {
                return crow::response(400, "Query parameter 'q' is required");
            }

            std::string query(query_param);
            auto results = engine.search(query);

            // Generate the HTML response
            std::ostringstream html;
            html << "<html><body><h1>Search Results for \"" << query << "\"</h1><ul>";
            for (const auto& [doc, score] : results) {
                html << "<li>" << doc << " (Score: " << score << ")</li>";
            }
            html << "</ul></body></html>";

            return crow::response(html.str());
        });

    // Launch the web server
    app.port(8080).multithreaded().run();

    return 0;
}
