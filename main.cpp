#include <iostream>
#include "CommonLib.h"
#include "Cards.h"

using namespace CardCounter;
using enum HAND_TYPE;
using enum Rank;
using enum Suit;


int main(int argc, char* argv[]) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "cardCounter");

    std::vector<CardComparer> evalMethods = { straightFlush, fourOfAKind };
    Hand hand;
    Deck deck;

    for (int i = 8; i < 13; i++) {
        hand.emplace_back((Rank) i, DIAMONDS);
        deck.emplace_front((Rank)(i - 5), CLUBS);
    }

    // do stuff

    for (auto method : evalMethods)
        cout << evalHandType(method, hand, deck) << endl;

    return 0;
}

