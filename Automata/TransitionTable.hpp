//
// Created by pilar on 30.09.2017.
//

#ifndef CLIONPROJECTSAUTOMATA_TRANSITIONTABLE_HPP
#define CLIONPROJECTSAUTOMATA_TRANSITIONTABLE_HPP

#include <set>
#include <map>

template <typename StateType, typename TransitionType>
class TransitionTable {
public:
    using State = StateType;
    using States = std::set<State>;
    using Transition = TransitionType;
    using Key = std::pair<State, Transition>;

    void pushTransition(const Key& key, const States& states) {
        mTransitionMap.insert({key, states});
    }

    const States& fetchNextStates(const Key& stateTransitionPair){
        static const TransitionTable::States noStates;
        auto foundIter = mTransitionMap.find(stateTransitionPair);
        bool newStatesFound = foundIter != mTransitionMap.end();
        if(newStatesFound)
            return foundIter->second;
        else
            return noStates;
    }
    
private:
    std::map<Key, States> mTransitionMap;
};


#endif //CLIONPROJECTSAUTOMATA_TRANSITIONTABLE_HPP
