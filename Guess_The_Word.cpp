#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

// -- Data ----------------------------------------------------

struct WordEntry {
    string word;
    string hint;
    string category;
};

const vector<WordEntry> WORD_LIST = {
    {"PYTHON",    "A popular programming language named after a snake",          "Tech"},
    {"ECLIPSE",   "When one celestial body moves into the shadow of another",    "Science"},
    {"LIBRARY",   "A place to borrow books, or a collection of reusable code",   "General"},
    {"OCEAN",     "A vast body of salt water covering most of the Earth",        "Nature"},
    {"KEYBOARD",  "You use this device to type on a computer",                   "Tech"},
    {"QUANTUM",   "Relating to the smallest discrete unit of energy",            "Science"},
    {"JUNGLE",    "Dense tropical forest teeming with wildlife",                 "Nature"},
    {"ALGORITHM", "A step-by-step procedure for solving a problem",              "Tech"},
    {"VOLCANO",   "A mountain that can erupt with lava and ash",                 "Nature"},
    {"BINARY",    "A number system using only 0s and 1s",                        "Tech"},
    {"AURORA",    "Colorful lights visible near the polar regions",              "Science"},
    {"COMPASS",   "A navigation tool whose needle always points north",          "General"},
    {"SPHINX",    "A mythical creature with a human head and a lion's body",     "History"},
    {"GLACIER",   "A large, slow-moving mass of ice",                            "Nature"},
    {"SYNTAX",    "The rules that define the structure of a programming language","Tech"},
    {"METEOR",    "A space rock that burns up entering Earth's atmosphere",      "Science"},
    {"FOREST",    "A large area covered chiefly with trees and undergrowth",     "Nature"},
    {"CIPHER",    "A secret or disguised way of writing; a code",                "General"},
    {"MATRIX",    "A rectangular array of numbers arranged in rows and columns", "Math"},
    {"FOSSIL",    "Preserved remains of a prehistoric organism",                 "Science"},
};

const int MAX_LIVES = 6;

// -- Helpers -------------------------------------------------

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printTitle() {
    cout << "\n";
    cout << "  +====================================+\n";
    cout << "  |    G U E S S  T H E  W O R D      |\n";
    cout << "  +====================================+\n\n";
}

void drawGallows(int livesLeft) {
    // ASCII gallows -- 6 stages
    const vector<string> stages[7] = {
        // 6 lives (empty gallows)
        {"  +---+  ",
         "  |   |  ",
         "      |  ",
         "      |  ",
         "      |  ",
         "      |  ",
         " ========="},
         // 5 lives (head)
         {"  +---+  ",
          "  |   |  ",
          "  O   |  ",
          "      |  ",
          "      |  ",
          "      |  ",
          " ========="},
          // 4 lives (body)
          {"  +---+  ",
           "  |   |  ",
           "  O   |  ",
           "  |   |  ",
           "      |  ",
           "      |  ",
           " ========="},
           // 3 lives (one arm)
           {"  +---+  ",
            "  |   |  ",
            "  O   |  ",
            " /|   |  ",
            "      |  ",
            "      |  ",
            " ========="},
            // 2 lives (two arms)
            {"  +---+  ",
             "  |   |  ",
             "  O   |  ",
             " /|\\  |  ",
             "      |  ",
             "      |  ",
             " ========="},
             // 1 life (one leg)
             {"  +---+  ",
              "  |   |  ",
              "  O   |  ",
              " /|\\  |  ",
              " /    |  ",
              "      |  ",
              " ========="},
              // 0 lives (full figure)
              {"  +---+  ",
               "  |   |  ",
               "  O   |  ",
               " /|\\  |  ",
               " / \\  |  ",
               "      |  ",
               " ========="},
    };

    int stage = MAX_LIVES - livesLeft;
    if (stage < 0) stage = 0;
    if (stage > 6) stage = 6;

    for (const auto& line : stages[stage]) {
        cout << "    " << line << "\n";
    }
    cout << "\n";
}

void printLives(int lives) {
    cout << "  Lives: ";
    for (int i = 0; i < MAX_LIVES; i++) {
        cout << (i < lives ? "[*] " : "[ ] ");
    }
    cout << "(" << lives << "/" << MAX_LIVES << ")\n\n";
}

void printWordDisplay(const string& word, const set<char>& guessed) {
    cout << "  Word: ";
    for (char c : word) {
        if (guessed.count(c))
            cout << c << " ";
        else
            cout << "_ ";
    }
    cout << "\n\n";
}

void printWrongGuesses(const string& word, const set<char>& guessed) {
    cout << "  Wrong guesses: ";
    bool any = false;
    for (char c : guessed) {
        if (word.find(c) == string::npos) {
            cout << c << " ";
            any = true;
        }
    }
    if (!any) cout << "-";
    cout << "\n\n";
}

bool isWordGuessed(const string& word, const set<char>& guessed) {
    for (char c : word)
        if (!guessed.count(c)) return false;
    return true;
}

// -- Game Loop -----------------------------------------------

void playRound(const WordEntry& entry, int& score, int round) {
    set<char> guessed;
    int lives = MAX_LIVES;
    bool hintUsed = false;
    string displayHint = string(entry.hint.size(), '*');

    while (true) {
        clearScreen();
        printTitle();

        cout << "  Round " << round
            << "   |   Score: " << score
            << "   |   Category: [" << entry.category << "]\n\n";

        drawGallows(lives);
        printLives(lives);
        printWordDisplay(entry.word, guessed);
        printWrongGuesses(entry.word, guessed);

        // Hint
        cout << "  Hint: " << (hintUsed ? entry.hint : displayHint) << "\n\n";

        // Check win / lose
        if (isWordGuessed(entry.word, guessed)) {
            int bonus = lives * 10;
            cout << "  *** CORRECT! The word was: " << entry.word << "\n";
            cout << "  +50 base pts  +" << bonus << " life bonus  =  +" << (50 + bonus) << " pts\n\n";
            score += 50 + bonus;
            cout << "  Press ENTER to continue...";
            cin.ignore(); cin.get();
            return;
        }

        if (lives <= 0) {
            cout << "  X  GAME OVER for this round.\n";
            cout << "  The word was: " << entry.word << "\n\n";
            cout << "  Press ENTER to continue...";
            cin.ignore(); cin.get();
            return;
        }

        // Menu
        cout << "  -------------------------------------\n";
        cout << "  [G] Guess a letter\n";
        if (!hintUsed && lives > 1)
            cout << "  [H] Reveal hint  (-1 life)\n";
        cout << "  [Q] Quit game\n";
        cout << "  -------------------------------------\n";
        cout << "  Choice: ";

        string input;
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        if (input == "Q") {
            cout << "\n  Thanks for playing! Final score: " << score << "\n\n";
            exit(0);
        }
        else if (input == "H") {
            if (hintUsed) {
                cout << "\n  Hint already revealed!\n";
            }
            else if (lives <= 1) {
                cout << "\n  Not enough lives!\n";
            }
            else {
                hintUsed = true;
                lives--;
                cout << "\n  Hint revealed! (-1 life)\n";
            }
        }
        else if (input == "G" || (input.size() == 1 && isalpha(input[0]))) {
            char letter;
            if (input == "G") {
                cout << "  Enter letter: ";
                string l; cin >> l;
                transform(l.begin(), l.end(), l.begin(), ::toupper);
                letter = l.empty() ? ' ' : l[0];
            }
            else {
                letter = input[0];
            }

            if (!isalpha(letter)) {
                cout << "\n  Please enter a valid letter.\n";
                continue;
            }

            if (guessed.count(letter)) {
                cout << "\n  You already guessed '" << letter << "'!\n";
                cin.ignore();
                continue;
            }

            guessed.insert(letter);

            if (entry.word.find(letter) == string::npos) {
                lives--;
                cout << "\n  '" << letter << "' is NOT in the word.\n";
            }
            else {
                cout << "\n  '" << letter << "' is in the word!\n";
            }
        }
        else {
            cout << "\n  Invalid input.\n";
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    clearScreen();
    printTitle();

    cout << "  Welcome to Guess the Word!\n";
    cout << "  You have " << MAX_LIVES << " lives per round.\n";
    cout << "  Guess letters to reveal the hidden word.\n\n";
    cout << "  Scoring:\n";
    cout << "    +50  pts  for guessing the word\n";
    cout << "    +10  pts  per remaining life\n";
    cout << "    -1   life for using a hint\n\n";
    cout << "  Press ENTER to start...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    int score = 0;
    int round = 1;

    // Shuffle word list
    vector<WordEntry> pool = WORD_LIST;
    for (int i = (int)pool.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(pool[i], pool[j]);
    }

    while (true) {
        if (pool.empty()) {
            pool = WORD_LIST;
            for (int i = (int)pool.size() - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                swap(pool[i], pool[j]);
            }
        }

        WordEntry entry = pool.back();
        pool.pop_back();

        playRound(entry, score, round);
        round++;

        clearScreen();
        printTitle();
        cout << "  Round " << (round - 1) << " complete!\n";
        cout << "  Current score: " << score << "\n\n";
        cout << "  [P] Play next round\n";
        cout << "  [Q] Quit\n";
        cout << "  Choice: ";

        string ch;
        cin >> ch;
        transform(ch.begin(), ch.end(), ch.begin(), ::toupper);

        if (ch == "Q") break;
    }

    clearScreen();
    printTitle();
    cout << "  +==============================+\n";
    cout << "  |  FINAL SCORE: " << setw(5) << score << "  pts     |\n";
    cout << "  |  Rounds played: " << setw(4) << (round - 1) << "           |\n";
    cout << "  +==============================+\n\n";
    cout << "  Thanks for playing!\n\n";

    return 0;
}
