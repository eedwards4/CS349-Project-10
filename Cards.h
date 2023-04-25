//
// Created by student on 4/21/23.
//

#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iostream>

#ifndef CS349_PROJECT_10_CARDS_H
#define CS349_PROJECT_10_CARDS_H


namespace CardCounter {
    // ENUMS
    enum class Rank {
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13,
        ACE = 14
    };
    enum class Suit { CLUBS, SPADES, HEARTS, DIAMONDS };
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
                char c = str[0];
                if (std::isdigit(c))
                    rank = (Rank)(c - '0');
                if (std::isalpha(c)) {
                    switch (c) {
                        case 'T':
                            rank = TEN;
                            break;
                        case 'J':
                            rank = JACK;
                            break;
                        case 'Q':
                            rank = QUEEN;
                            break;
                        case 'K':
                            rank = KING;
                            break;
                        case 'A':
                            rank = ACE;
                    }
                }
                switch (str[1]) {
                    case 'C':
                        suit = CLUBS;
                        break;
                    case 'S':
                        suit = SPADES;
                        break;
                    case 'H':
                        suit = HEARTS;
                        break;
                    case 'D':
                        suit = DIAMONDS;
                }
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

        friend std::ostream& operator<<(std::ostream& os, const Card &card) {
            std::string cardStr;
            switch (card.rank) {
                case TWO:
                    cardStr.append("2");
                    break;
                case THREE:
                    cardStr.append("3");
                    break;
                case FOUR:
                    cardStr.append("4");
                    break;
                case FIVE:
                    cardStr.append("5");
                    break;
                case SIX:
                    cardStr.append("6");
                    break;
                case SEVEN:
                    cardStr.append("7");
                    break;
                case EIGHT:
                    cardStr.append("8");
                    break;
                case NINE:
                    cardStr.append("9");
                    break;
                case TEN:
                    cardStr.append("T");
                    break;
                case JACK:
                    cardStr.append("J");
                    break;
                case QUEEN:
                    cardStr.append("Q");
                    break;
                case KING:
                    cardStr.append("K");
                    break;
                case ACE:
                    cardStr.append("A");
            }
            switch (card.suit) {
                case CLUBS:
                    cardStr.append("C");
                    break;
                case SPADES:
                    cardStr.append("S");
                    break;
                case HEARTS:
                    cardStr.append("H");
                    break;
                case DIAMONDS:
                    cardStr.append("D");
            }
            return os << cardStr;
        }

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

        friend std::ostream& operator<<(std::ostream& os, const Hand& hand) {
            for (auto it = hand.begin(); it != hand.end() - 1; it++) {
                os << *it << " ";
            }
            return os << hand.back();
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

        friend std::ostream& operator<<(std::ostream& os, const Deck& deck) {
            for (auto it = deck.begin(); it != deck.end() - 1; it++) {
                os << *it << " ";
            }
            return os << deck.back();
        }
    };

    //METHODS
    typedef HAND_TYPE (*CardComparer)(const Hand&); // Type which holds functions with signature "HAND_TYPE funcName(const Hand&)"
    std::string handTypeToStr(HAND_TYPE);
    std::string evalHandType(const std::vector<CardComparer>&, const Hand&, const Deck&);
    Hand sequence(const Hand&);

    HAND_TYPE straightsOrFlush(const Hand&);
    HAND_TYPE rankMatches(const Hand&);
}


#endif //CS349_PROJECT_10_CARDS_H
