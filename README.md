# 21Point
---
## A game that inspired by RE7 21 mode, all codes are written by myself.
### Currently only support two human players using the same ui (Multiplayer). The mode competing with AI (Single Player) will be developed if I have time
---
### How to play
Build the code with C compiler, just follow the message on the debug window to play the game.

Two-player game drawing cards alternatingly. Two players shares the same deck which has cards valued 1 to 11. The one whose deck is closest to 21 but not beyond wins.

First two players will be given a face-down card, which is known only by themselves. The following cards are visible for both players. Player hit "Y" key to draw a card, one can decide whether to draw a card this turn. If both player decide not to draw a card, all the deck is empty, then it's time for checking results.

Player should have their deck close to 21, but should not go beyond 21, otherwise the one whose deck is less than 21 wins. If both player's deck go beyond 21, then the one with less total card value wins.

If you wish to continue after one round, the total score for both player will be recorded.


