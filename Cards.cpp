//
// Created by student on 4/21/23.
//

#include "Cards.h"
static const int TOTAL_SUITS = 4;
static const int TOTAL_RANKS = 13;

void CardCounter::compare(const Hand &hand, const Deck &deck) {
    int suitCounts[TOTAL_SUITS] = { 0 };
    int rankCounts[TOTAL_RANKS] = { 0 };

    for (int s : suitCounts)
        suitCounts[s] = numSuit(hand, deck, (Card::Suit)s);

    for (int r : rankCounts)
        rankCounts[r] = numRank(hand, deck, (Card::Rank)r);

    // Now that we have the number of occurrences for each rank and suit,
    // we can determine more about the value of hand with draws from deck
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

