#include <iostream>
#include <vector>

using namespace std;

// -------------------- MEMENTO --------------------
// The Memento class stores the internal state of the GameCharacter.
// It captures a snapshot (health, level, codeName) so that the state
// can be restored later without exposing internal details.
class CharacterMemento {
private:
    int health_;
    int level_;
    string codeName_;

public:
    CharacterMemento(int health, int level, string codeName)
        : health_(health), level_(level), codeName_(codeName) {
    }

    int getHealth() const { return health_; }
    int getLevel() const { return level_; }
    string getCodeName() const { return codeName_; }
};

// -------------------- ORIGINATOR --------------------
// The Originator is the GameCharacter. It creates a Memento containing
// its current state and can restore its state from a Memento.
class GameCharacter {
    int health_;
    int level_;
    string codeName_;

public:
    GameCharacter(int health, int level, string codeName)
        : health_(health), level_(level), codeName_(codeName) {
    }

    // Display current state of the character
    void showStatus() {
        cout << endl << "The states for Character--" << endl;
        cout << "Character: " << codeName_ << endl;
        cout << "Health: " << health_ << endl;
        cout << "Level: " << level_ << endl;
    }

    // Save current state into a Memento
    CharacterMemento saveState() {
        return CharacterMemento(health_, level_, codeName_);
    }

    // Restore state from a Memento
    void restorState(const CharacterMemento& memento) {
        health_ = memento.getHealth();
        level_ = memento.getLevel();
        codeName_ = memento.getCodeName();
    }

    // Simulate damage taken
    void takeDamage(int damage) {
        health_ -= damage;
    }

    // Simulate leveling up
    void levelUp() {
        level_++;
    }
};

// -------------------- CARETAKER --------------------
// The Caretaker manages the history of Mementos.
// It never modifies the Mementos, only stores and retrieves them.
class Caretaker {
private:
    vector<CharacterMemento> history_;

public:
    void save(const CharacterMemento& memento) {
        history_.push_back(memento);
    }

    CharacterMemento get(int index) {
        return history_.at(index);
    }
};

// -------------------- DEMO --------------------
int main() {
    // Create a game character (Originator)
    GameCharacter hero(100, 1, "Shadow Night");

    // Create caretaker to manage saves
    Caretaker caretaker;

    // Show initial state and save it
    hero.showStatus();
    caretaker.save(hero.saveState());

    // Character takes damage and levels up
    hero.takeDamage(30);
    hero.levelUp();
    hero.showStatus();

    // Save new state
    caretaker.save(hero.saveState());

    // Restore to initial state using caretaker
    hero.restorState(caretaker.get(0));
    hero.showStatus();
}
