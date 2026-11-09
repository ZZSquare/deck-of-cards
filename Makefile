CXX ?= c++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

all: blackjack

blackjack: src/blackjack.cpp include/*.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

test_deck: tests/test_deck.cpp include/*.hpp
	$(CXX) $(CXXFLAGS) -UNDEBUG $< -o $@

test: test_deck
	./test_deck

clean:
	rm -f blackjack test_deck
