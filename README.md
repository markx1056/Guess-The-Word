Guess the Word:

A console-based word guessing game built in C++ where players reveal hidden words letter by letter before running out of lives, featuring an ASCII hangman display, a hint system, and a round-based scoring system.

Features:

-> Guess hidden words by entering one letter at a time
-> ASCII gallows that updates visually with each wrong guess
-> Reveal a hint for any word at the cost of one life
-> Automatically calculates and tracks score across rounds
-> Shuffled word pool ensures no repeats until all words are played

Technologies Used:

-> C++17
-> STL Containers (vector, set)
-> Structs & Modular Functions
-> Random Shuffling (rand, srand)

How to Play:

Guess a Letter — Enter any letter to check if it appears in the hidden word
Reveal Hint — Costs 1 life but displays the word's description
Quit — Exit the game at any time and view your final score
