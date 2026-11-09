#include <cassert>
#include <iostream>
#include <set>
#include "blackjack.hpp"
#include "deck.hpp"

int main() {
    Deck d(1, 1);
    std::set<std::string> uniq;
    for (auto& c : d.cards()) uniq.insert(c.str());
    assert(d.size() == 52 && uniq.size() == 52);

    assert(d.deal(5).size() == 5 && d.size() == 47);

    bool threw = false;
    try { d.deal(48); } catch (const std::out_of_range&) { threw = true; }
    assert(threw);

    assert(Deck(1, 7).cards() == Deck(1, 7).cards());  // same seed, same order

    assert(handValue({{Rank::Ace, Suit::Spades}, {Rank::King, Suit::Hearts}}) == 21);
    assert(handValue({{Rank::Ace, Suit::Spades}, {Rank::King, Suit::Hearts}, {Rank::Five, Suit::Clubs}}) == 16);
    std::cout << "all tests passed\n";
}
