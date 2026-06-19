#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
vector<string> words = {"программа", "компьютер", "алгоритм", "переменная", "функция", "цикл", "массив"};
string chooseWord() {
    int index = rand() % words.size();
    return words[index];
void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); i++) {
        if (guessed[i]) {
            cout « word[i] « " ";
        } else {
            cout « "_ ";
        }
    }
    cout « endl;
}
void displayHangman(int errors) {
    cout « "Ошибок: " « errors « "/6" « endl;
    if (errors >= 1) cout « "  O" « endl;
    if (errors >= 2) cout « "  |" « endl;
    if (errors >= 3) cout « " /|" « endl;
    if (errors >= 4) cout « " /|\\" « endl;
    if (errors >= 5) cout « " / " « endl;
    if (errors >= 6) cout « " / \\" « endl;
}
bool isWordGuessed(const vector<bool>& guessed) {
    for (bool b : guessed) {
        if (!b) return false;
    }
    return true;
}
void playRound() {
    string word = chooseWord();
    vector<bool> guessed(word.length(), false);
    vector<char> wrongLetters;
    int errors = 0;
    const int MAX_ERRORS = 6;
    cout « "\n Игра 'Виселица' " « endl;
    cout « "Слово загадано. Угадай буквы!" « endl;
    while (errors < MAX_ERRORS && !isWordGuessed(guessed)) {
        cout « "\nТекущее слово: ";
        displayWord(word, guessed);
        cout « "Неверные буквы: ";
        for (char c : wrongLetters) cout « c « " ";
        cout « endl;
        displayHangman(errors);
        cout « "Введите букву: ";
        char guess;
        cin » guess;
        guess = tolower(guess);
        if (!isalpha(guess)) {
            cout « "Введите букву!" « endl;
            continue;
        }
        bool alreadyGuessed = false;
        for (size_t i = 0; i < word.length(); i++) {
            if (guessed[i] && word[i] == guess) {
                alreadyGuessed = true;
                break;
            }
        }
        for (char c : wrongLetters) {
            if (c == guess) alreadyGuessed = true;
        }
        if (alreadyGuessed) {
            cout « "Ты уже называл(а) эту букву!" « endl;
            continue;
        }
        bool found = false;
        for (size_t i = 0; i < word.length(); i++) {
            if (word[i] == guess) {
                guessed[i] = true;
                found = true;
            }
        }
        if (!found) {
            wrongLetters.push_back(guess);
            errors++;
            cout « "Такой буквы нет!" « endl;
        } else {
            cout « "Верно!" « endl;
        }
    }
    cout « "\n Результат " « endl;
    if (isWordGuessed(guessed)) {
        cout « "Поздравляю! Ты отгадал(а) слово: " « word « endl;
    } else {
        displayHangman(MAX_ERRORS);
        cout « "Ты проиграл(а)! Загаданное слово: " « word « endl;
    }
}
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    cout « " Игра 'Виселица' " « endl;
    char again;
    do {
        playRound();
        cout « "\nПродолжить игру? (y/n): ";
        cin » again;
    } while (again == 'y' || again == 'Y');
    cout « "Спасибо за игру!" « endl;
    return 0;
}
