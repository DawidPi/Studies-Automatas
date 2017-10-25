//
// Created by dawid on 10/23/17.
//

#include <string>
#include <iostream>
#include "TuringMachineTransitionTable.hpp"

using namespace std;
using namespace std::literals;
using TransitionTable = TuringMachineTransitionTable<char, std::string>;
using HeadTransition = TransitionTable::HeadTransition;

int main(){
    std::cout << "Hello Turing Machine" << std::endl;

    TransitionTable transitionTable;
    transitionTable.clearTransitions();
    transitionTable.addTransition("q0"s, '0', "q1"s, '1', HeadTransition::LEFT);
    transitionTable.getAction("q0"s, '0');

};