Guess the Word is a console-based word guessing game written in C++17, inspired by the classic Hangman format. The player is presented with a hidden word and must reveal it by guessing one letter at a time before running out of lives.
Gameplay revolves around a pool of 20 curated words spanning five categories — Tech, Science, Nature, General, and Math/History. Each round, a word is randomly drawn and displayed as blank underscores. The player has 6 lives per round, and each wrong letter guess costs one life. An ASCII gallows illustration updates progressively with each mistake, giving the game a visual sense of urgency.
Key features include:

-> A hint system that reveals the word's description at the cost of one life, adding a strategic trade-off to each round.
-> A scoring system that awards 50 base points for a correct guess plus a 10-point bonus for each remaining life, rewarding efficient play.
-> Shuffled word pools that cycle through the full word list before repeating, ensuring variety across sessions.
-> A clean round-by-round structure, letting players continue to a next round or quit after each word.
-> Input flexibility — players can type a letter directly or go through the menu, and all input is normalized to uppercase for consistency.
