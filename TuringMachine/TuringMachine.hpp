//
// Created by dawid on 10/26/17.
//

#ifndef PROJECT_TURINMACHINE_HPP
#define PROJECT_TURINMACHINE_HPP

#include "Tape.hpp"
#include "TuringMachineTransitionTable.hpp"

template<typename TapeElement, typename State>
class TuringMachine {
public:
    using TransitionTable = TuringMachineTransitionTable<TapeElement, State>;
    using TuringTape = Tape<TapeElement>;

    TuringMachine(const TuringTape &tape, const TransitionTable &transitionTable, const State &initialState)
            : mTape(tape),
              mTransitionTable(transitionTable),
              mCurrentState(initialState) {}

    TuringMachine(const TuringMachine& rhs) = delete;

    void makeStep() {

        auto action = mTransitionTable.getAction(mCurrentState, mTape[mCurrentTapeIndex]);
        mCurrentState = action.state;
        mTape[mCurrentTapeIndex] = action.writeElement;

        if(action.headTransition == TransitionTable::HeadTransition::LEFT)
            --mCurrentTapeIndex;
        else if(action.headTransition == TransitionTable::HeadTransition::RIGHT)
            ++mCurrentTapeIndex;
    }

    const State& getCurrentState(){
        return mCurrentState;
    }

    const TuringTape &getCurrentTape(){
        return mTape;
    }

private:
    using IndexType = typename TuringTape::size_type;
    TuringTape mTape;
    IndexType mCurrentTapeIndex = IndexType();
    TransitionTable mTransitionTable;
    State mCurrentState;
};

#endif //PROJECT_TURINMACHINE_HPP
