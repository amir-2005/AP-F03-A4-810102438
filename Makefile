CXX = g++ -g -std=c++20

FILES = build/main.o build/Leitner.o build/Box.o build/Card.o
EXE = LeitnerBox

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@

build/main.o: src/main.cpp src/Leitner.hpp src/constants.hpp
	$(CXX) -c $< -o $@

build/Leitner.o: src/Leitner.cpp src/Leitner.hpp src/Box.hpp
	$(CXX) -c $< -o $@

build/Box.o: src/Box.cpp src/Box.hpp src/Card.hpp
	$(CXX) -c $< -o $@

build/Card.o: src/Card.cpp src/Card.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)
