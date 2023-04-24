#include "Cards.h"

namespace CardCounter {
    using enum HAND_TYPE;
    const int TOTAL_RANKS = 13;
    const int TOTAL_SUITS = 4;

    std::string handTypeToStr(HAND_TYPE hand) {
        switch (hand) {
            case HIGH_CARD:
                return "highest-card";
            case PAIR:
                return "one-pair";
            case TWO_PAIR:
                return "two-pair";
            case THREE_OF_A_KIND:
                return "three-of-a-kind";
            case STRAIGHT:
                return "straight";
            case FLUSH:
                return "flush";
            case FULL_HOUSE:
                return "full-house";
            case FOUR_OF_A_KIND:
                return "four-of-a-kind";
            case STRAIGHT_FLUSH:
                return "straight-flush";
            default:
                return "failure";
        }
    }

/*
 * Draw elements from deck into hand by order, one by one, and invoke the evalMethods method on hand each time
 * as the hand eventually grows to a total union of hand and deck. Record calculated hand types and return the
 * highest scoring among them.
 */
    std::string evalHandType(const std::vector<CardComparer> &evalMethods, const Hand& hand, const Deck &deck) {
        HAND_TYPE highest = HIGH_CARD, temp;
        int numDraws = 0, discardPos;
        Hand tempHand = hand;
        Deck tempDeck = deck;
        for (CardComparer eval : evalMethods) {
            for (int i = 0; i < hand.size(); i++) { // perform draws by discarding elements in left-to-right order,
                // before replacing them, doing so for all 5 draws in all 5 starting
                // discard positions. Does not account for drawing in other orderings.
                discardPos = i;
                do {
                    for (int j = numDraws;
                         j > 0 && !tempDeck.empty(); j--) { // discard cards and replace them with drawn cards
                        tempHand[discardPos] = tempDeck.front();
                        discardPos = discardPos + 1 < hand.size() ? discardPos + 1 : 0; // wrap discardPos around hand
                        tempDeck.pop_front();
                    }
                    temp = eval(tempHand); // use provided method to evaluate hand_types
                    if (highest < temp) highest = temp;
                    numDraws++;
                    tempHand = hand;
                    tempDeck = deck;
                    discardPos = i;
                } while (numDraws < deck.size()); // continue until all cards are drawn
            }
        }
        return handTypeToStr(highest);
    }

/*
 * Return a hand of the longest sequence in the passed parameter.
 */
    Hand sequence(const Hand &hand) {
        Hand sequence;
        Hand sortedSelf = hand;
        Card lastCard = sortedSelf.at(0);
        int seqLen = 1, MAX_SEQ_LEN = 5;
        auto seqStart = sortedSelf.begin() + 1;
        auto cardsInSequence = [](const Card &last, const Card &curr) {
            int rankDiff = curr.rankAsInt() - last.rankAsInt();
            return rankDiff == (int)Rank::ACE - (int)Rank::FIVE || rankDiff == 1; // The ACE - FIVE figure comes from
                                                                                  // the state of a sequence with low ACE.
                                                                                  // The sorted hand will be ordered:
                                                                                  // TWO, THREE, FOUR, FIVE, ACE when read
                                                                                  // by loop below, so the rankDiff is
                                                                                  // ACE - FIVE when the sequence is valid.
        };

        std::sort(sortedSelf.begin(), sortedSelf.end());

        if (cardsInSequence(lastCard, *seqStart)) {
            sequence.emplace_back(lastCard); // add a new set of sequence
            lastCard = *seqStart;
            seqStart++;
            seqLen++;
            while (cardsInSequence(lastCard, *seqStart)) { // Count up sequence until end
                if (seqLen >= MAX_SEQ_LEN) // Sequences capped at length of 5
                    break;
                sequence.push_back(lastCard); // append cards to continuing sequence
                lastCard = *seqStart;
                if (seqStart + 1 != sortedSelf.end()) seqStart++;
                else sequence.push_back(*seqStart);
                seqLen++;
            }
        }

        return sequence;
    }

    HAND_TYPE straightsOrFlush(const Hand &hand) {
        int STRAIGHT_LEN = 5;
        Hand h = sequence(hand);
        if (h.size() == STRAIGHT_LEN) {
            for (auto it = h.begin() + 1; it != h.end(); it++) {
                if (!(it - 1)->sharesSuit(*it))
                    return STRAIGHT;
            }
            return STRAIGHT_FLUSH;
        }
        else {
            for (auto it = hand.begin() + 1; it != hand.end(); it++) {
                if (!(it - 1)->sharesSuit(*it))
                    return HIGH_CARD;
            }
            return FLUSH;
        }
    }

    HAND_TYPE rankMatches(const Hand &hand) {
        int numRanks[TOTAL_RANKS] = { 0 };
        int mostMatches = 0;
        for (int i = 0; i < TOTAL_RANKS; i++) {
            for (const Card &c: hand)
                numRanks[i] += c.hasRank((Rank) i);
            if (mostMatches < numRanks[i]) mostMatches = numRanks[i];
        }
        switch (mostMatches) {
            case 4:
                return FOUR_OF_A_KIND;
            case 3:
                for (int i : numRanks) // Currently doesn't confirm the pair is "not the same as each other"
                    if (i == 2) return FULL_HOUSE;
            case 2:
                int numPairs = 0;
                for (int i : numRanks)
                    if (i == 2) numPairs++;
                return numPairs > 1 ? TWO_PAIR : PAIR;
        }
        return HIGH_CARD;
    }
}