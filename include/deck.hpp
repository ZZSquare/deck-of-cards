#pragma once
#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>
#include "card.hpp"

// A deck of playing cards. Use numDecks > 1 for a shoe.
class Deck {
public:
    explicit Deck(int numDecks = 1, unsigned seed = std::random_device{}())
        : numDecks_(numDecks), rng_(seed) { reset(); }

    // Restore all cards and shuffle.
    void reset() {
        cards_.clear();
        for (int d = 0; d < numDecks_; ++d)
            for (Suit s : ALL_SUITS)
                for (Rank r : ALL_RANKS) cards_.push_back({r, s});
        shuffle();
    }

    void shuffle() { std::shuffle(cards_.begin(), cards_.end(), rng_); }

    Card draw() {
        if (cards_.empty()) throw std::out_of_range("deck is empty");
        Card c = cards_.back();
        cards_.pop_back();
        return c;
    }

    std::vector<Card> deal(size_t n) {
        if (n > cards_.size()) throw std::out_of_range("not enough cards");
        std::vector<Card> hand;
        for (size_t i = 0; i < n; ++i) hand.push_back(draw());
        return hand;
    }

    size_t size() const { return cards_.size(); }
    const std::vector<Card>& cards() const { return cards_; }

private:
    int numDecks_;
    std::mt19937 rng_;
    std::vector<Card> cards_;
};
