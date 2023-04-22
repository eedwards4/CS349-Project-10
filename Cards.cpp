//
// Created by student on 4/21/23.
//

#include "Cards.h"
static const int TOTAL_SUITS = 4;
static const int TOTAL_RANKS = 13;


std::string CardCounter::strHandType(CardCounter::WIN_HANDS hand) {
    switch (hand) {
        case HIGH_CARD:
            return "highest-card";
        case PAIR:
            return "pair";
        case TWO_PAIR:
            return "two-pair";
        case THREE_OF_A_KIND:
            return "three-of-a-kind";
        case STRAIGHT:
            return "straight";
        case FLUSH:
            return "flush";
        case FOUR_OF_A_KIND:
            return "four-of-a-kind";
        case STRAIGHT_FLUSH:
            return "straight-flush";
        default:
            return "failure";
    }
}

CardCounter::WIN_HANDS CardCounter::compare(const Hand &hand, const Deck &deck) {
    int suitCounts[TOTAL_SUITS] = { 0 };
    int rankCounts[TOTAL_RANKS] = { 0 };
    Hand sharedCards = commonCards(hand, deck);
    /*int matchCounts[]; Maybe an array of the number of matches for each card could be useful? */

    for (Hand h : sharedCards.sequences()) {
        if (h.size() == 5)
            return STRAIGHT_FLUSH;
    }

    for (int s : suitCounts)
        suitCounts[s] = numSuit(hand, deck, (Card::Suit)s);

    for (int r : rankCounts)
        rankCounts[r] = numRank(hand, deck, (Card::Rank)r);

    // Now that we have the number of occurrences for each rank and suit,
    // we can determine more about the value of hand with draws from deck
    return HIGH_CARD;
}

int CardCounter::numRank(const Hand &hand, const Deck &deck, Card::Rank rank) {
    int counter = 0;
    for (const Card &c : hand)
        if (c.hasRank(rank))
            counter++;
    for (const Card &c : deck)
        if (c.hasRank(rank))
            counter++;
    return counter;
}

int CardCounter::numSuit(const Hand &hand, const Deck &deck, Card::Suit suit) {
    int counter = 0;
    for (const Card &c : hand)
        if (c.hasSuit(suit))
            counter++;
    for (const Card &c : deck)
        if (c.hasSuit(suit))
            counter++;
    return counter;
}

/*
 * Returns a Hand containing the matching cards from the passed hand and deck
 */
Hand CardCounter::commonCards(const Hand &hand, const Deck &deck) {
    Hand matchedCards;
    for (const Card &hc : hand) {
        for (const Card &dc : deck) {
            if (hc == dc) {
                matchedCards.push_back(hc);
                matchedCards.push_back(dc);
            }
        }
    }
    return matchedCards;
}

/*
 * Return a vector of all possible sequences in the calling object.
 */
std::vector<Hand> Hand::sequences() const {
    std::vector<Hand> sequences;
    Hand sortedSelf = *this;
    Card lastCard = sortedSelf.at(0);
    int seqLen = 1, numSeq = 0;
    auto seqStart = sortedSelf.begin();

    std::sort(sortedSelf.begin(), sortedSelf.end());

    for (auto it =sortedSelf.begin() + 1; it != sortedSelf.end(); it++) {
        if (seqStart->rankAsInt() - lastCard.rankAsInt() == 1) {
            sequences.emplace_back(lastCard); // add a new set of sequences
            lastCard = *seqStart;
            seqStart++;
            seqLen++;
            while (seqStart->rankAsInt() - lastCard.rankAsInt() == 1 && seqStart != sortedSelf.end()) {
                if (seqLen > 5)
                    break;
                sequences.at(numSeq).push_back(lastCard); // append cards to continuing sequence
                lastCard = *seqStart;
                seqStart++;
                seqLen++;
            }
            seqLen = 1;
            numSeq++;
        }
        seqStart = it;
        lastCard = *it;
    }
    return sequences;
}

