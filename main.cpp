#include <iostream>
#include "CommonLib.h"
#include "Cards.h"

using namespace CardCounter;
using enum HAND_TYPE;
using enum Rank;
using enum Suit;

const int MAX_HAND_SIZE = 5;
const int MAX_DECK_SIZE = 5;

int main(int argc, char* argv[]) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "cardCounter");

    std::vector<CardComparer> evalMethods = { straightsOrFlush, rankMatches };
    std::string text;
    Hand hand;
    Deck deck;

    infile >> text;
    while (infile.good()) {
        while (hand.size() < MAX_HAND_SIZE) {
            hand.emplace_back(text);
            infile >> text;
        }
        while (deck.size() < MAX_DECK_SIZE) {
            deck.emplace_back(text);
            infile >> text;
        }
        outfile << "Hand: " << hand << " Deck: " << deck << " Best hand: " << evalHandType(evalMethods, hand, deck) << endl;
        hand.clear();
        deck.clear();
    }

    return 0;
}

