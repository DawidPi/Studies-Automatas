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

    struct Value{
        State state;
        TapeElement writeElement;
        HeadTransition headTransition;
    };

public:
    using Action = Value;

    void addTransition(State startingState, TapeElement readElement,
                       State nextState, TapeElement writeElement, HeadTransition transition){
        auto key = std::make_pair(std::move(startingState), std::move(readElement));
        auto value = Value{.state = std::move(nextState), .writeElement=std::move(writeElement), .headTransition=std::move(transition)};

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
