#include "Cards.h"

namespace CardCounter {
    using enum HAND_TYPE;

    std::string handTypeToStr(HAND_TYPE hand) {
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
    std::string evalHandType(CardComparer evaluate, const Hand& hand, const Deck &deck) {
        HAND_TYPE highest = HIGH_CARD, temp;
        int numDraws = 0, numDiscards = 0, discardPos;
        Hand tempHand = hand;
        for (int i = 0; i < hand.size(); i++) { // perform draws by discarding elements in left-to-right order,
                                                // before replacing them, doing so for all 5 draws in all 5 starting
                                                // discard positions. Does not account for drawing in other orderings.
            discardPos = i;
            do {
                for (int j = numDiscards; j >= 0; j--){ // discard cards and replace them with drawn cards
                    tempHand[discardPos] = deck[numDraws];
                    discardPos = discardPos + 1 < hand.size() ? discardPos + 1 : 0; // wrap discardPos around hand
                }
                temp = evaluate(tempHand); // use passed method to evaluate hand_types
                if (highest < temp) highest = temp;
                numDraws++;
                numDiscards++;
            } while (numDraws < deck.size()); // continue until all cards are drawn
        }
        return handTypeToStr(highest);
    }

/*
 * Returns a Hand containing the matching cards from the passed hand and deck
 */
    Hand commonCards(const Hand &hand, const Deck &deck) {
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
    std::vector<Hand> handSequences(const Hand &hand) {
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

    HAND_TYPE straightFlush(const Hand& hand) {
        for (const Hand &h : handSequences(hand)) {
            if (h.size() == 5)
                return STRAIGHT_FLUSH;
        }
        return HIGH_CARD;
    }

    HAND_TYPE fourOfAKind(const Hand &hand) {
        int numSuits[4] = { 0 };
        for (int i = 0; i < 4; i++) {
            for (const Card &c: hand)
                numSuits[i] += c.hasSuit((Suit) i);
            if (numSuits[i] == 4)
                return FOUR_OF_A_KIND;
        }
        return HIGH_CARD;
    }
}