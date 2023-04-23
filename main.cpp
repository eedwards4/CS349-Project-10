#include <iostream>
#include "CommonLib.h"
#include "Cards.h"

using HAND_TYPE = CardCounter::HAND_TYPE;
const auto evalHandType = CardCounter::evalHandType;
const auto commonCards = CardCounter::commonCards;
const auto handSequences = CardCounter::handSequences;

HAND_TYPE straightFlush(const Hand&);
HAND_TYPE fourOfAKind(const Hand&);
// implement more methods which return hand_type and receive hand param. We can use these with evalMethods vec.

int main(int argc, char* argv[]) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "cardCounter");

    std::vector<CardCounter::CardComparer> evalMethods = { straightFlush, fourOfAKind };
    Hand hand;
    Deck deck;

    for (int i = 9; i <= 13; i++) {
        hand.emplace_back((Card::Rank) i, Card::Suit::DIAMONDS);
        deck.emplace_front((Card::Rank)(i - 5), Card::Suit::CLUBS);
    }

    // do stuff

    for (auto method : evalMethods)
        cout << evalHandType(method, hand, deck) << endl;

    return 0;
}


HAND_TYPE straightFlush(const Hand& hand) {
    for (const Hand &h : handSequences(hand)) {
        if (h.size() == 5)
            return CardCounter::STRAIGHT_FLUSH;
    }
    return CardCounter::HIGH_CARD;
}

HAND_TYPE fourOfAKind(const Hand &hand) {
    int numSuits[4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (const Card &c: hand)
            numSuits[i] += c.hasSuit((Card::Suit) i);
        if (numSuits[i] == 4)
            return CardCounter::FOUR_OF_A_KIND;
    }
    return CardCounter::HIGH_CARD;
}