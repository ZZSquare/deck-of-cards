# deck-of-cards
Games that require a deck of cards

## Usage
```cpp
#include "deck.hpp"
Deck deck;                 // shuffled 52 cards (Deck(4) for a shoe)
auto hand = deck.deal(2);
```
Play Blackjack: `make && ./blackjack`  
Run tests: `make test`
