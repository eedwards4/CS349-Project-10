//
// Created by student on 4/21/23.
//

#include "Cards.h"

void CardCounter::compare(const Hand &hand, const Deck &deck) {
    int suitCounts[4] = { 0, 0, 0, 0 }
    for (int i = CLUBS; i < DIAMONDS; i++) {
        suitCounts[i] = numSuit(i); // i should be interepreted by compiler as Suit { 0, 1, 2, 3 }
    }

}

int CardCounter::numRank(const Hand &hand, const Deck &deck, Card::Rank rank) {
    int counter = 0;
    for (Card c : hand)
        if (c.hasRank(rank))
            counter++;
    for (Card c : deck)
        if (c.hasRank(rank))
            counter++;
    return counter;
}

int CardCounter::numSuit(const Hand &hand, const Deck &deck, Card::Suit suit) {
    int counter = 0;
    for (Card c : hand)
        if (c.hasSuit(suit))
            counter++;
    for (Card c : deck)
        if (c.hasSuit(suit))
            counter++;
    return counter;
}

