CXXFLAGS = -Wall -std=c++17 -O2
SRC_FILES := src/main.cpp src/utils.cpp

dev: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -Werror -Wextra -Wpedantic -g $(SRC_FILES) -o a.out

macos: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o a.out

windows: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o a.exe
