//
// Created by student on 4/21/23.
//

#include <vector>
#include <queue>
#include <string>

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

    Card(const std::string& str) {

    }

    Card& operator=(const Card& card) {
        rank = card.rank;
        suit = card.suit;
    }

    bool operator==(const Card& card) { return rank == card.rank && suit == card.suit; }
    bool operator<(const Card& card) { return rank < card.rank; }

    bool hasRank(Rank r) { return rank == r; };
    bool hasSuit(Suit s) { return suit == s; };
private:
    Rank rank;
    Suit suit;
};

class Hand : public std::vector<Card> {
public:
    Hand();
};

class Deck : public std::queue<Card> {
public:
    Deck();
    // Make iteration method?
};


class CardCounter {
public:
    static void compare(const Hand&, const Deck&);
    static int numSuit(const Hand&, const Deck&, Card::Suit);
    static int numRank(const Hand&, const Deck&, Card::Rank);

private:
    enum { HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FOUR_OF_A_KIND, STRAIGHT_FLUSH } ;
};


#endif //CS349_PROJECT_10_CARDS_H
