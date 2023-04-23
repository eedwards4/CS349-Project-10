//
// Created by student on 4/21/23.
//

#include "Cards.h"

std::string CardCounter::handTypeToStr(CardCounter::HAND_TYPE hand) {
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

/*
 * Draw elements from deck into hand by order, one by one, and invoke the evaluate method on hand each time
 * as the hand eventually grows to a total union of hand and deck. Record calculated hand types and return the
 * highest scoring among them.
 */
std::string CardCounter::evalHandType(CardCounter::CardComparer evaluate, const Hand& hand, const Deck &deck) {
    HAND_TYPE highest = HIGH_CARD, temp;
    int numDraws = 0;
    Hand tempHand = hand;
    do {
        tempHand.push_back(deck.at(numDraws));
        temp = evaluate(tempHand);
        if (highest < temp) highest = temp;
        numDraws++;
    } while (numDraws < deck.size());
    return handTypeToStr(highest);
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
 * Return a vector of all possible handSequences in the calling object.
 */
std::vector<Hand> CardCounter::handSequences(const Hand &hand) {
    std::vector<Hand> sequences;
    Hand sortedSelf = hand;
    Card lastCard = sortedSelf.at(0);
    int seqLen = 1, numSeq = 0;
    auto seqStart = sortedSelf.begin();

    std::sort(sortedSelf.begin(), sortedSelf.end());

    for (auto it = sortedSelf.begin() + 1; it != sortedSelf.end(); it++) {
        if (seqStart->rankAsInt() - lastCard.rankAsInt() == 1) {
            sequences.emplace_back(lastCard); // add a new set of handSequences
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

