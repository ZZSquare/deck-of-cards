// Play Blackjack against the computer.
#include <iostream>
#include <string>
#include "blackjack.hpp"
#include "deck.hpp"

using Hand = std::vector<Card>;

constexpr int NUM_DECKS = 8;
constexpr int RESHUFFLE_AT_DECKS_LEFT = 6;  // reshuffle once only this many decks remain
constexpr size_t RESHUFFLE_CARDS = RESHUFFLE_AT_DECKS_LEFT * 52;
enum class Result { Win, Loss, Push };

static std::string show(const Hand& h, bool hideSecond = false) {
    if (hideSecond) return h[0].str() + " ??";
    std::string s;
    for (const Card& c : h) s += c.str() + " ";
    return s + " (" + std::to_string(handValue(h)) + ")";
}

static Result playRound(Deck& deck) {
    if (deck.size() <= RESHUFFLE_CARDS) {
        std::cout << "\n--- Reshuffling the shoe ---\n";
        deck.reset();
    }
    Hand player = deck.deal(2), dealer = deck.deal(2);
    std::cout << "\nDealer: " << show(dealer, true) << "\nYou:    " << show(player) << "\n";

    if (handValue(player) == 21) {
        std::cout << "Blackjack!\n";
        return handValue(dealer) == 21 ? Result::Push : Result::Win;
    }

    while (handValue(player) < 21) {
        std::cout << "(h)it or (s)tand? ";
        std::string in;
        if (!std::getline(std::cin, in)) exit(0);
        if (in.empty()) continue;
        if (in[0] == 'h' || in[0] == 'H') {
            player.push_back(deck.draw());
            std::cout << "You:    " << show(player) << "\n";
        } else if (in[0] == 's' || in[0] == 'S') break;
    }
    if (handValue(player) > 21) { std::cout << "Bust! You lose.\n"; return Result::Loss; }

    std::cout << "Dealer: " << show(dealer) << "\n";
    while (handValue(dealer) < 17) {  // dealer stands on all 17s
        dealer.push_back(deck.draw());
        std::cout << "Dealer: " << show(dealer) << "\n";
    }

    int p = handValue(player), d = handValue(dealer);
    if (d > 21 || p > d) { std::cout << "You win!\n"; return Result::Win; }
    if (p == d) { std::cout << "Push.\n"; return Result::Push; }
    std::cout << "Dealer wins.\n";
    return Result::Loss;
}

int main() {
    Deck deck(NUM_DECKS);
    int w = 0, l = 0, p = 0;
    while (true) {
        switch (playRound(deck)) {
            case Result::Win: ++w; break;
            case Result::Loss: ++l; break;
            case Result::Push: ++p; break;
        }
        std::cout << "Record: " << w << "W " << l << "L " << p << "P\nPlay again? (y/n) ";
        std::string in;
        if (!std::getline(std::cin, in) || in.empty() || (in[0] != 'y' && in[0] != 'Y')) break;
    }
}
