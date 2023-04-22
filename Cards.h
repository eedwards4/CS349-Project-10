//
// Created by student on 4/21/23.
//

#include <vector>
#include <deque>
#include <string>
#include <algorithm>

#ifndef CS349_PROJECT_10_CARDS_H
#define CS349_PROJECT_10_CARDS_H


class Card {
public:
    typedef enum { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE } Rank;
    typedef enum { CLUBS, SPADES, HEARTS, DIAMONDS } Suit;

    Card() {
        rank = ACE;
        suit = CLUBS;
    }

    Card(const Card& card) {
        rank = card.rank;
        suit = card.suit;
    }

    explicit Card(const std::string& str) {
        if (str.length() == 2) {
            int numRankVal = str[0] - '0';
            int alphRankVal = std::toupper(str[0]) - 'A';
            int suitVal = std::toupper(str[1]) - 'A';
            int NUM_NUMBERS = 9, NUM_ALPHAS = 26;

            // Convert rank based on string index 0
            if (numRankVal >= 0 && numRankVal <= NUM_NUMBERS)
                rank = (Rank)numRankVal;
            if (alphRankVal >= 0 && alphRankVal <= NUM_ALPHAS)
                rank = (Rank)alphRankVal;

            // Convert suit based on string index 1
            if (suitVal >= 0 && suitVal <= NUM_ALPHAS)
                suit = (Suit)suitVal;
        }
    }

    Card& operator=(const Card& card) = default;

    bool operator==(const Card& card) const { return rank == card.rank && suit == card.suit; }
    bool operator!=(const Card& card) const { return rank != card.rank && suit != card.suit; }
    bool operator<(const Card& card) const { return rank < card.rank; }

    int rankAsInt() { return rank; }
    int suitAsInt() { return suit; }

    bool hasRank(Rank r) const { return rank == r; };
    bool hasSuit(Suit s) const { return suit == s; };
private:
    Rank rank;
    Suit suit;
};

class Hand : public std::vector<Card> {
public:
    Hand();
    explicit Hand(const Card &c) { push_back(c); }
    explicit Hand(const std::vector<Card> &vc) {
        this->clear();
        for (const Card &c : vc)
            push_back(c);
    }
    std::vector<Hand> sequences() const;
};

class Deck : public std::deque<Card> {
public:
    Deck();
};


class CardCounter {
public:
    typedef enum { HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FOUR_OF_A_KIND, STRAIGHT_FLUSH } WIN_HANDS;
    static WIN_HANDS compare(const Hand&, const Deck&);
    static int numSuit(const Hand&, const Deck&, Card::Suit);
    static int numRank(const Hand&, const Deck&, Card::Rank);
    static Hand commonCards(const Hand&, const Deck&);
    static std::string strHandType(WIN_HANDS);
};


#endif //CS349_PROJECT_10_CARDS_H
