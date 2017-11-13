//
// Created by dawid on 10/23/17.
//

#include <string>
#include <iostream>
#include "TuringMachineTransitionTable.hpp"
#include "Tape.hpp"
#include "TuringMachine.hpp"

using namespace std;
using namespace std::literals;
using TransitionTable = TuringMachineTransitionTable<char, std::string>;
using TuringTape = Tape<char>;
using HeadTransition = TransitionTable::HeadTransition;
using Turing = TuringMachine<char, std::string>;

int main(){
    std::cout << "Hello Turing Machine" << std::endl;

    TransitionTable transitionTable;
    transitionTable.clearTransitions();
    transitionTable.addTransition("q0"s, '0', "q1"s, '1', HeadTransition::LEFT);

    TuringTape tape;
    for(TuringTape::size_t idx=-2; idx < 5; ++idx){
        tape[idx] = static_cast<int>(idx + 2);
    }

    for(TuringTape::size_t idx=-2; idx < 5; ++idx){
        std::cout << static_cast<int>(tape[idx]) << std::endl;
    }

    Turing machine(tape, transitionTable, "q0"s);

};