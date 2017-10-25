//
// Created by dawid on 10/26/17.
//

#ifndef PROJECT_TURINGMACHINEOPERATIONS_HPP
#define PROJECT_TURINGMACHINEOPERATIONS_HPP

#include <utility>
#include <map>

template <typename TapeElement, typename State>
class TuringMachineTransitionTable{
public:
    enum class HeadTransition{LEFT, RIGHT, NONE};

private:
    using Key = std::pair<State, TapeElement>;
    using Value = std::tuple<State, TapeElement, HeadTransition>;

public:
    using Action = Value;
    using State = Key;

    void addTransition(State startingState, TapeElement readElement,
                       State nextState, TapeElement writeElement, HeadTransition transition){
        auto key = std::make_pair(std::move(startingState), std::move(readElement));
        auto value = std::make_tuple(std::move(nextState), std::move(writeElement), std::move(transition));

        mTransitionMap.insert({std::move(key), std::move(value)});
    }

    Action getAction(State state, TapeElement readElement){
        auto foundAction = mTransitionMap.find(std::make_pair(std::move(state), std::move(readElement)));

        if(foundAction == mTransitionMap.end())
            throw std::logic_error("Key not found");

        return foundAction->second;
    }

    void clearTransitions(){
        mTransitionMap.clear();
    }

private:
    using Map = std::map<Key, Value>;

    Map mTransitionMap;
};

#endif //PROJECT_TURINGMACHINEOPERATIONS_HPP
