# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGET = strassen  # Change this to match your desired output file

# Source files
SRCS = strassen.cpp  # Change to match your actual C++ source file

# Rule to compile the program
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule to remove compiled files
clean:
	rm -f $(TARGET)

