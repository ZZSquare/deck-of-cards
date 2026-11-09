#pragma once
#include <array>
#include <string>

enum class Suit { Spades, Hearts, Diamonds, Clubs };
enum class Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

inline constexpr std::array<Suit, 4> ALL_SUITS = {Suit::Spades, Suit::Hearts, Suit::Diamonds, Suit::Clubs};
inline constexpr std::array<Rank, 13> ALL_RANKS = {
    Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six, Rank::Seven, Rank::Eight,
    Rank::Nine, Rank::Ten, Rank::Jack, Rank::Queen, Rank::King, Rank::Ace};

struct Card {
    Rank rank;
    Suit suit;

    // Rank order for comparisons (2..14, Ace high).
    int value() const { return static_cast<int>(rank); }

    std::string str() const {
        static const char* names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        static const char* suits[] = {"♠", "♥", "♦", "♣"};
        return std::string(names[value() - 2]) + suits[static_cast<int>(suit)];
    }

    bool operator==(const Card& o) const { return rank == o.rank && suit == o.suit; }
};
