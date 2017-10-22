#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "TransitionTable.hpp"
#include "Automata.hpp"

using TransTable = TransitionTable<std::string, char>;
using Automaton = Automata<TransTable>;

using namespace std::literals::string_literals;

std::vector<Automaton::State> states{
        "q0"s, "q1"s, "q2"s, "q3"s, "q4"s
};

char fetchNextLetter();

int main() {
    std::set<char> alphabet{'a', 'b'};
    char exitCharacter{'c'};
    assert(alphabet.find(exitCharacter) == alphabet.end());

    std::shared_ptr<TransTable> transitionTable(new TransTable);
    transitionTable->pushTransition({states[0], 'a'}, {states[1]});
    transitionTable->pushTransition({states[0], 'b'}, {states[4]});
    transitionTable->pushTransition({states[1], 'a'}, {states[4]});
    transitionTable->pushTransition({states[1], 'b'}, {states[2]});
    transitionTable->pushTransition({states[2], 'a'}, {states[3]});
    transitionTable->pushTransition({states[2], 'b'}, {states[3]});
    transitionTable->pushTransition({states[3], 'a'}, {states[2]});
    transitionTable->pushTransition({states[3], 'b'}, {states[2]});
    transitionTable->pushTransition({states[4], 'a'}, {states[4]});
    transitionTable->pushTransition({states[4], 'b'}, {states[4]});

    Automaton automata(transitionTable, states[0]);
    automata.setAcceptingStates({states[2]});

    while(true){
        std::cout<< "Podaj literę [" << exitCharacter << " to close]: " << std::flush;
        char fetchedLetter = fetchNextLetter();
        bool letterNotFoundInAlphabet = alphabet.find(fetchedLetter) == alphabet.end();
        if(letterNotFoundInAlphabet){
            if(fetchedLetter == exitCharacter){
                std::cout << "exiting..." << std::endl;
                return 0;
            } else {
                std::cout << "letter not in alphabet" << std::endl;
            }
            if(!std::cin){
                std::cin.clear();
            }
        }else{
            std::cout << "letter: " << fetchedLetter << std::endl;
            automata.update(fetchedLetter);
            std::cout << "state: " << automata.currentState() << "[" << (automata.isAccepted()?'A':'N') << "]" << std::endl;
        }

    }

    return 0;
}

char fetchNextLetter() {
    char fetchedLetter;
    while(isspace(fetchedLetter = std::cin.get()));
    return fetchedLetter;
}