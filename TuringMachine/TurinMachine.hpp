//
// Created by dawid on 10/26/17.
//

#ifndef PROJECT_TURINMACHINE_HPP
#define PROJECT_TURINMACHINE_HPP

template <typename Tape, typename TransitionTable>
class TuringMachine{
public:
    TuringMachine(Tape, TransitionTable);
    void makeStep();
    void restart();

    TransitionTable::State getCurrentState();
    const Tape& getCurrentTape();

};

#endif //PROJECT_TURINMACHINE_HPP
