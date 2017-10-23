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

    // standard input is a file: http://www.linfo.org/standard_input.html
    std::string fileData(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
    std::cout << "filesize: " << fileData.size() << std::endl;
    std::cout << fileData << std::endl;

    auto currentChar = fileData.begin();
    std::cout << "new input" << std::endl;
    while(currentChar != fileData.end()){
        if(*currentChar == '#'){
            automata = Automaton(transitionTable, states[0]);
            automata.setAcceptingStates({states[1], states[3], states[5], states[6], states[8], states[9], states[10], states[11]});
            std::cout << std::endl << "new input" << std::endl;
        } else if(alphabet.find(*currentChar) == alphabet.end()){
            std::cerr << "letter not in alphabet" << std::endl;
        } else{
            std::cout << "letter: " << *currentChar << std::endl;
            automata.update(*currentChar);
            std::cout << "current states:" << std::endl;
            for(const auto& state : automata.currentStates()){
                std::cout << state << std::endl;
            }
            std::cout << "accepted [" << (automata.isAccepted() ? "A" : "N") << "]" << std::endl;
        }

        currentChar++;
    }

    return 0;
}