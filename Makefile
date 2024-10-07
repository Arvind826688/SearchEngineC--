CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -lpthread  # Required for Crow web framework (if using it for web interface)

# Target executable names
TARGET = search_engine web_server

# Source files
SRC = src/main.cpp src/search_engine.cpp src/indexer.cpp src/utils.cpp
WEB_SRC = src/web_server.cpp src/search_engine.cpp src/indexer.cpp src/utils.cpp

# Object files
OBJ = $(SRC:.cpp=.o)
WEB_OBJ = $(WEB_SRC:.cpp=.o)

# Include paths (modify if Crow is installed in a specific directory)
INCLUDE = -I./include -I/path/to/crow/include  # Update this to point to Crow's include directory

# Default rule to build both search_engine and web_server
all: $(TARGET)

# Rule to build the search engine executable
search_engine: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^

# Rule to build the web server executable (only if using a web interface)
web_server: $(WEB_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LIBS) -o $@ $^

# Rule to compile individual .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean rule to remove object files and executables
clean:
	rm -f $(OBJ) $(WEB_OBJ) $(TARGET)

# Phony target to ensure `clean` is always executed
.PHONY: all clean
