#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <Automata/TransitionTable.hpp>
#include <Automata/Automata.hpp>

using TransTable = TransitionTable<std::string, char>;
using Automaton = Automata<TransTable>;

using namespace std::literals::string_literals;

std::vector<Automaton::State> states{
        "starting point"s,
        "integer ready"s,
        "integer finished"s,
        "accepted"s,
        "waiting for number"s,
        "1"s,
        "10"s,
        "fraction"s,
        "first"s,
        "second"s,
        "third"s,
        "zero waiting"s
};

char fetchNextLetter();


void addTransitionPack(TransTable& transitionTable, Automaton::State fromState, std::set<Automaton::Transition> signals, Automaton::States toStates){
    for(const auto& signal : signals){
        transitionTable.pushTransition({fromState, signal}, toStates);
    }
}

int main() {
    std::set<char> alphabet{'-', '+', ','};
    std::set<char> subAlphabetAllNumbers;
    for(unsigned int alphabetNumber = 0; alphabetNumber < 10; alphabetNumber++){
        auto numberLetter = std::to_string(alphabetNumber)[0];
        alphabet.insert(numberLetter);
        subAlphabetAllNumbers.insert(numberLetter);
    }
    std::set<char> subAlphabetAllNumbersNoZero = subAlphabetAllNumbers;
    subAlphabetAllNumbersNoZero.erase('0');


    std::shared_ptr<TransTable> transitionTable(new TransTable);

    addTransitionPack(*transitionTable, states[0], {'-', '+'}, {states[4]});
    transitionTable->pushTransition({states[0], '0'}, {states[11]});
    addTransitionPack(*transitionTable, states[0], subAlphabetAllNumbersNoZero, {states[1]});
    transitionTable->pushTransition({states[0], '1'}, {states[5]});
    transitionTable->pushTransition({states[0], ','}, {states[2]});

    transitionTable->pushTransition({states[1], ','}, {states[2]});
    addTransitionPack(*transitionTable, states[2], subAlphabetAllNumbers, {states[3]});
    addTransitionPack(*transitionTable, states[3], subAlphabetAllNumbers, {states[3]});

    addTransitionPack(*transitionTable, states[4], subAlphabetAllNumbersNoZero, {states[1]});
    transitionTable->pushTransition({states[4], '0'}, {states[11]});
    transitionTable->pushTransition({states[4], ','}, {states[2]});

    addTransitionPack(*transitionTable, states[11], subAlphabetAllNumbersNoZero, {states[1]});
    transitionTable->pushTransition({states[11], '0'}, {states[11]});
    transitionTable->pushTransition({states[11], ','}, {states[2]});

    transitionTable->pushTransition({states[5], '0'}, {states[6]});
    transitionTable->pushTransition({states[6], ','}, {states[7]});
    transitionTable->pushTransition({states[7], '0'}, {states[8]});
    transitionTable->pushTransition({states[8], '0'}, {states[9]});
    transitionTable->pushTransition({states[9], '0'}, {states[10]});
    addTransitionPack(*transitionTable, states[10], {'0', '1', '2', '3', '4'}, {states[3]});


    Automaton automata(transitionTable, states[0]);
    automata.setAcceptingStates({states[1], states[3], states[5], states[6], states[8], states[9], states[10], states[11]});

    char exitCharacter{'c'};
    assert(alphabet.find(exitCharacter) == alphabet.end());

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
            for(const auto& state : automata.currentStates())
                std::cout << "states: " << state << std::endl;
            std::cout << "[" << (automata.isAccepted()?'A':'N') << "]" << std::endl;
        }

    }

    return 0;
}

char fetchNextLetter() {
    char fetchedLetter;
    while(isspace(fetchedLetter = std::cin.get()));
    return fetchedLetter;
}