#include "Cards.h"

namespace CardCounter {
    // Set of all possible orders to discard a hand when drawing up to 5 cards
    const std::vector<std::vector<uint8_t>> DISCARD_PERMUTATIONS = {
            { 0,1,2,3,4 },
            { 1,0,2,3,4 },
            { 2,0,1,3,4 },
            { 0,2,1,3,4 },
            { 1,2,0,3,4 },
            { 2,1,0,3,4 },
            { 2,1,3,0,4 },
            { 1,2,3,0,4 },
            { 3,2,1,0,4 },
            { 2,3,1,0,4 },
            { 1,3,2,0,4 },
            { 3,1,2,0,4 },
            { 3,0,2,1,4 },
            { 0,3,2,1,4 },
            { 2,3,0,1,4 },
            { 3,2,0,1,4 },
            { 0,2,3,1,4 },
            { 2,0,3,1,4 },
            { 1,0,3,2,4 },
            { 0,1,3,2,4 },
            { 3,1,0,2,4 },
            { 1,3,0,2,4 },
            { 0,3,1,2,4 },
            { 3,0,1,2,4 },
            { 4,0,1,2,3 },
            { 0,4,1,2,3 },
            { 1,4,0,2,3 },
            { 4,1,0,2,3 },
            { 0,1,4,2,3 },
            { 1,0,4,2,3 },
            { 1,0,2,4,3 },
            { 0,1,2,4,3 },
            { 2,1,0,4,3 },
            { 1,2,0,4,3 },
            { 0,2,1,4,3 },
            { 2,0,1,4,3 },
            { 2,4,1,0,3 },
            { 4,2,1,0,3 },
            { 1,2,4,0,3 },
            { 2,1,4,0,3 },
            { 4,1,2,0,3 },
            { 1,4,2,0,3 },
            { 0,4,2,1,3 },
            { 4,0,2,1,3 },
            { 2,0,4,1,3 },
            { 0,2,4,1,3 },
            { 4,2,0,1,3 },
            { 2,4,0,1,3 },
            { 3,4,0,1,2 },
            { 4,3,0,1,2 },
            { 0,3,4,1,2 },
            { 3,0,4,1,2 },
            { 4,0,3,1,2 },
            { 0,4,3,1,2 },
            { 0,4,1,3,2 },
            { 4,0,1,3,2 },
            { 1,0,4,3,2 },
            { 0,1,4,3,2 },
            { 4,1,0,3,2 },
            { 1,4,0,3,2 },
            { 1,3,0,4,2 },
            { 3,1,0,4,2 },
            { 0,1,3,4,2 },
            { 1,0,3,4,2 },
            { 3,0,1,4,2 },
            { 0,3,1,4,2 },
            { 4,3,1,0,2 },
            { 3,4,1,0,2 },
            { 1,4,3,0,2 },
            { 4,1,3,0,2 },
            { 3,1,4,0,2 },
            { 1,3,4,0,2 },
            { 2,3,4,0,1 },
            { 3,2,4,0,1 },
            { 4,2,3,0,1 },
            { 2,4,3,0,1 },
            { 3,4,2,0,1 },
            { 4,3,2,0,1 },
            { 4,3,0,2,1 },
            { 3,4,0,2,1 },
            { 0,4,3,2,1 },
            { 4,0,3,2,1 },
            { 3,0,4,2,1 },
            { 0,3,4,2,1 },
            { 0,2,4,3,1 },
            { 2,0,4,3,1 },
            { 4,0,2,3,1 },
            { 0,4,2,3,1 },
            { 2,4,0,3,1 },
            { 4,2,0,3,1 },
            { 3,2,0,4,1 },
            { 2,3,0,4,1 },
            { 0,3,2,4,1 },
            { 3,0,2,4,1 },
            { 2,0,3,4,1 },
            { 0,2,3,4,1 },
            { 1,2,3,4,0 },
            { 2,1,3,4,0 },
            { 3,1,2,4,0 },
            { 1,3,2,4,0 },
            { 2,3,1,4,0 },
            { 3,2,1,4,0 },
            { 3,2,4,1,0 },
            { 2,3,4,1,0 },
            { 4,3,2,1,0 },
            { 3,4,2,1,0 },
            { 2,4,3,1,0 },
            { 4,2,3,1,0 },
            { 4,1,3,2,0 },
            { 1,4,3,2,0 },
            { 3,4,1,2,0 },
            { 4,3,1,2,0 },
            { 1,3,4,2,0 },
            { 3,1,4,2,0 },
            { 2,1,4,3,0 },
            { 1,2,4,3,0 },
            { 4,2,1,3,0 },
            { 2,4,1,3,0 },
            { 1,4,2,3,0 },
            { 4,1,2,3,0 },
    };


    using enum HAND_TYPE;
    const int TOTAL_RANKS = 13;
    const int TOTAL_SUITS = 4;

    std::string handTypeToStr(HAND_TYPE hand) {
        switch (hand) {
            case HIGH_CARD:
                return "highest_card";
            case PAIR:
                return "one_pair";
            case TWO_PAIR:
                return "two_pairs";
            case THREE_OF_A_KIND:
                return "three_of_a_kind";
            case STRAIGHT:
                return "straight";
            case FLUSH:
                return "flush";
            case FULL_HOUSE:
                return "full_house";
            case FOUR_OF_A_KIND:
                return "four_of_a_kind";
            case STRAIGHT_FLUSH:
                return "straight_flush";
            default:
                return "failure";
        }
    }

/*
 * Draw elements from deck into hand by order, one by one, and invoke the evalMethods method on hand each time
 * as the every hand order configuration has been checked. Record calculated hand types and return the
 * highest scoring among them.
 */
    std::string evalHandType(const std::vector<CardComparer> &evalMethods, const Hand& hand, const Deck &deck) {
        HAND_TYPE highest = HIGH_CARD, temp;
        int numDraws = 0;
        Hand tempHand = hand;
        Deck tempDeck = deck;
        for (CardComparer eval : evalMethods) {
            for (auto discardOrder : DISCARD_PERMUTATIONS) { // use lookup table of permutations of all possible draw orders
                auto discardPos = discardOrder.begin(); // set discardPos to iterator for discard order permutations
                do {
                    for (int j = numDraws; j > 0; j--) { // discard cards and replace them with drawn cards
                        tempHand[*discardPos] = tempDeck.front();
                        tempDeck.pop_front();
                        discardPos++;
                    }
                    temp = eval(tempHand); // use provided method to evaluate hand_types
                    if (highest < temp) highest = temp;
                    numDraws++;
                    tempHand = hand;
                    tempDeck = deck;
                    discardPos = discardOrder.begin();
                } while (numDraws <= deck.size()); // continue until all cards are drawn
                numDraws = 0; // reset numDraws
            }
        }
        return handTypeToStr(highest);
    }

/*
 * Return a hand of the longest sequence in the passed parameter.
 */
    Hand sequence(const Hand &hand) {
        Hand sequence, temp, sortedSelf = hand; // a sequence to return, a temp to eval sequences, and a sorted copy
        Card lastCard; // the previously added card of the sequence for evaluation
        int MAX_SEQ_LEN = 5;

        std::sort(sortedSelf.begin(), sortedSelf.end());
        sequence = temp = Hand(sortedSelf.front());
        lastCard = sortedSelf.front();

        for (auto seqStart = sortedSelf.begin() + 1; seqStart != sortedSelf.end(); seqStart++) {
            while (seqStart->rankAsInt() - lastCard.rankAsInt() == 1 ||
                   seqStart->hasRank(Rank::ACE) && lastCard.hasRank(Rank::FIVE)) { // Count up sequence until end
                if (temp.size() >= MAX_SEQ_LEN) // Sequences capped at length of 5
                    break;
                temp.push_back(*seqStart); // append cards to continuing sequence
                lastCard = *seqStart;
                if (seqStart + 1 != sortedSelf.end()) seqStart++;
            }
            if (temp.size() > sequence.size())
                sequence = temp;
            temp = Hand(*seqStart); // Set first card of next sequence temp will hold
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
            for (const Card &c : hand)
                numRanks[i] += c.hasRank((Rank) (i + 2)); // Add two to match assignment of elements of Rank enum
            if (mostMatches < numRanks[i]) mostMatches = numRanks[i];
        }
        switch (mostMatches) {
            case 4:
                return FOUR_OF_A_KIND;
            case 3:
                for (int i : numRanks) // Currently doesn't confirm the pair is "not the same as each other"
                    if (i == 2) return FULL_HOUSE;
                return THREE_OF_A_KIND;
            case 2:
                int numPairs = 0;
                for (int i : numRanks)
                    if (i == 2) numPairs++;
                return numPairs > 1 ? TWO_PAIR : PAIR;
        }
        return HIGH_CARD;
    }
}
