# Created by Ethan Edwards on 4/27/2023
# ethanedwards.me
# Test-case generator for highest-hand problem

# Imports
import random

# Variable defs
cards = {1: "A", 2: "2", 3: "3", 4: "4", 5: "5", 6: "6", 7: "7", 8: "8", 9: "9", 10: "T", 11: "J", 12: "Q", 13: "K"}
suits = {1: "C", 2: "D", 3: "H", 4: "S"}


# Main
def main():
    tempInput = input("Enter name of file to write to [this will overwrite any existing file]: ")
    wFile = open(tempInput, "w")
    numCases = int(input("Enter number of test cases to generate: "))

    for i in range(numCases):
        # Generate random hand
        hand = []
        for j in range(10):
            card = cards[random.randint(1, 13)]
            suit = suits[random.randint(1, 4)]
            hand.append(card + suit)

        # Print hand
        print(" ".join(hand))
        wFile.write(" ".join(hand) + "\n")


main()
