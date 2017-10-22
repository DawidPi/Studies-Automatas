//
// Created by pilar on 30.09.2017.
//

#ifndef CLIONPROJECTSAUTOMATA_AUTOMATA_HPP
#define CLIONPROJECTSAUTOMATA_AUTOMATA_HPP

#include <memory>
#include <algorithm>

template <typename TransitionTable>
class Automata{
public:
    using State = typename TransitionTable::State;
    using States = typename TransitionTable::States;
    using Transition = typename TransitionTable::Transition;

    Automata(std::shared_ptr<TransitionTable> transitionTable, const State& initialState):
            mTransitionTable(transitionTable),
            mCurrentStates({initialState})
            {}

    const State& currentState(){
        return *mCurrentStates.begin();
    }

    void setAcceptingStates(const States& states){
        mAcceptingStates = states;
    }

    bool isAccepted(){
        auto acceptanceCriteria = [this](const State& state){return mAcceptingStates.find(state) != mAcceptingStates.end();};
        return std::any_of(mCurrentStates.begin(), mCurrentStates.end(), acceptanceCriteria);
    }

    void update(const Transition& transition){
        States newStates;
        for(auto& state : mCurrentStates){
            auto& statesFromState = mTransitionTable->fetchNextStates({state, transition});
            newStates.insert(statesFromState.begin(), statesFromState.end());
        }

        mCurrentStates = newStates;
    }

private:
    std::shared_ptr<TransitionTable> mTransitionTable;
    States mCurrentStates;
    States mAcceptingStates;
};

#endif //CLIONPROJECTSAUTOMATA_AUTOMATA_HPP
