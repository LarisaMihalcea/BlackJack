The game will operate according to the following rules:

Cards from 2 to 10 have their face value, while face cards (J,Q,K) have a value of 10, and the ace (A) can have a value of 1 or 11.
Players play against a person known as the Dealer, and to win, they must have a higher card total than the dealer's. If the card total exceeds 21, the player loses. If the dealer exceeds 21, then everyone at the table wins, except those who have exceeded 21 before the dealer.
Each player receives 2 cards at the beginning, and the dealer also receives 2 cards, but one is face down (NOTE! In real Blackjack, cards are dealt one at a time to each player and only after the second to each player, but to simplify the issue, we will consider that players receive the 2 cards upfront, and the dealer is the last person to receive the 2 cards).
After the cards have been dealt, each player has the option to draw a card (HIT) or to stand at their current total (STAND). Players can draw as many cards as they want, but if they exceed 21, they lose (NOTE! For simplicity, we will consider the following scenario: If the dealer's or players' card total is less than 16, they are required to draw a card. If the card total is 17-21, they must stand from drawing cards. If the total is greater than 21, they lose).

Functional requirements:

If the command is "check_cards", check if a deck of cards is tampered with, if it's a normal deck, or if it's a deck prepared for blackjack. A deck of cards is considered tampered with if there are cards with numbers or suits that do not exist in reality (allowed numbers are from 2 to 14, where 11 represents an ace, and allowed suits are red, black, diamond, or club), and display "Tampered Deck". A deck of cards is considered OK if it's not tampered with, if all cards in it are different, and if there are a total of 52 cards, in which case display "OK Deck". A deck is considered good for Blackjack if it's not tampered with, and in this case display "Prepared for Blackjack". Leave a newline (\n) after these prints.

If the command is "shuffle_cards", shuffle the cards using the Linear Congruential Generator (LCG) algorithm. The generator is defined by the recurrence relation Xn+1 = (a * Xn + c) mod m. If 2 pairs of numbers a, c, and X0 are given from the keyboard, then generate a pair of indices, and the cards at those positions will be swapped, and the current index will become the previous index for the generator (See example!). The constant m will represent the number of cards in the deck. This algorithm will be applied to the deck 50 times. Display the shuffled cards in the format <card_number>,<card_suit>, separated by newline (\n).

If the command is "play_game", play Blackjack games until EOF with n players at a table. The game will follow the rules stated at the beginning of the problem. It is assumed that there are NO ACES in the deck! (Meaning the deck will consist of 48 cards, not 52!) The deck of cards will be shuffled before each round of Blackjack using the LCG algorithm described above (applied also 50 times). Initially, the deck of cards is arranged in the following order: there will be 48 cards in a deck (since we don't have aces) in the order 2 red, 3 red, ..., 14 red, 2 black, ..., 14 black, 2 diamond, ..., 14 diamond, 2 club, ..., 14 club (Note that there is no 11!). At each round, the deck of cards will be shuffled using the LCG algorithm with the current values read from the keyboard. The stake is 10 euros per player, so the round's winnings bring the player 10 euros, and if they lose, they will have 10 euros minus. If a player runs out of money (has less than 10 euros), they will leave the table. Finally, display the remaining persons at the table in the format person_name: money_sum, separated by newline (\n).

Input:
The first line contains a word "command", representing the sub-point you want to perform. For sub-point 1), read from the keyboard until EOF, lines of the format <card_number>,<card_suit>, where card_number is an 8-bit integer without a sign, and card_suit is a string of characters with a maximum of 30 characters. For sub-point 2), read 6 integers from the keyboard, 3 per line, representing the constants a, c, and X0. Then, read cards until EOF in the format specified in sub-point 1). For sub-point 3), read an integer n representing the number of players present at the Blackjack table. On the next n lines, you will find the n players in the format <name> <money_sum>, where name is a string of characters representing the player's name, consisting of a single word, and money_sum represents the amount of money the player enters the table with, an unsigned 32-bit integer. On the following lines until EOF, read 6 values per line, representing the inputs of the LCG generator for shuffling the cards in the current game.

Output:
Values will be displayed at the output according to the specification in the requirement, without displaying any additional text in the console! Only display the requested result!

Restrictions and Clarifications:
1 <= n <= 20;
name and card_suit have a maximum of 30 characters.
money_sum is a 16-bit integer.
Hardcoded solutions are not accepted!
In case of a tie, the player neither loses nor wins money.
The dealer receives the cards last.
First, all players receive 2 cards (+ dealer), then it moves to the hit/stand stage.
The deck is dealt from position 0, then 1, then 2.
Between rounds, the deck is reshuffled starting from the configuration of the previous round.
