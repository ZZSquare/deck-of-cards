#pragma once
#include <vector>
#include "card.hpp"

// Best blackjack total: aces count 11 unless that would bust, then 1.
inline int handValue(const std::vector<Card>& hand) {
    int total = 0, aces = 0;
    for (const Card& c : hand) {
        if (c.rank == Rank::Ace) { total += 11; ++aces; }
        else if (c.value() >= 10) total += 10;
        else total += c.value();
    }
    while (total > 21 && aces-- > 0) total -= 10;
    return total;
}
