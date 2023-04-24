//
// Created by student on 4/21/23.
//

#include <vector>
#include <deque>
#include <string>
#include <algorithm>

#ifndef CS349_PROJECT_10_CARDS_H
#define CS349_PROJECT_10_CARDS_H


namespace CardCounter {
    // ENUMS
    enum class Rank: int { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
    enum class Suit: int { CLUBS, SPADES, HEARTS, DIAMONDS };
    enum class HAND_TYPE { HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH };

    // CLASSES
    class Card {
    public:
        using enum Rank;
        using enum Suit;

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

        Card(Rank r, Suit s) {
            rank = r;
            suit = s;
        }

        Card& operator=(const Card& card) = default;

        bool operator==(const Card& card) const { return rank == card.rank && suit == card.suit; }
        bool operator!=(const Card& card) const { return rank != card.rank && suit != card.suit; }
        bool operator<(const Card& card) const { return rank < card.rank; }

        int rankAsInt() const { return (int)rank; }
        int suitAsInt() const { return (int)suit; }

        bool hasRank(Rank r) const { return rank == r; };
        bool hasSuit(Suit s) const { return suit == s; };
        bool sharesRank(const Card &card) const { return rank == card.rank; };
        bool sharesSuit(const Card &card) const { return suit == card.suit; };
    private:
        Rank rank;
        Suit suit;
    };

    class Hand : public std::vector<Card> {
    public:
        Hand() = default;
        explicit Hand(const Card &c) { push_back(c); }
        explicit Hand(const std::vector<Card> &vc) {
            this->clear();
            for (const Card &c : vc)
                push_back(c);
        }
    };

    class Deck : public std::deque<Card> {
    public:
        Deck() = default;
        explicit Deck(const Card &c) { push_front(c); }
        explicit Deck(const std::deque<Card> &dd) {
            this->clear();
            for (const Card &c : dd)
                push_front(c);
        }
    };

    //METHODS
    typedef HAND_TYPE (*CardComparer)(const Hand&); // Type which holds functions with signature "HAND_TYPE funcName(const Hand&)"
    std::string handTypeToStr(HAND_TYPE);
    std::string evalHandType(CardComparer, const Hand&, const Deck&);
    Hand commonCards(const Hand&, const Deck&);
    Hand sequence(const Hand&);

    HAND_TYPE straights(const Hand&);
    HAND_TYPE flush(const Hand&);
    HAND_TYPE rankMatches(const Hand&);
}


#endif //CS349_PROJECT_10_CARDS_H
