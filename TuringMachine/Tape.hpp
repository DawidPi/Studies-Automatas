//
// Created by dawid on 10/25/17.
//

#ifndef PROJECT_TAPE_HPP
#define PROJECT_TAPE_HPP

#include <vector>
#include <cstdlib>

template <typename T>
class Tape {
    using Container = std::vector<T>;
public:
    using size_t = long long int;
    using size_type = size_t;

    Tape(T defaultValue = T()) : mDefaultValue(defaultValue) {}

    T& operator[](size_t idx){
        if(idx >= 0){
            return fetchFrom(mPositiveIdxValues, idx);
        } else {
            return fetchFrom(mNegativeIdxValues, std::abs(idx) -1);
        }
    }

    void clear(){
        mPositiveIdxValues.clear();
        mNegativeIdxValues.clear();
    }

private:

    T& fetchFrom(Container& container, size_t idx){
        if(idx >= container.size()){
            container.resize(idx+1, mDefaultValue);
        }

        return container[idx];
    }

    const T mDefaultValue;
    Container mPositiveIdxValues;
    Container mNegativeIdxValues;
};

#endif //PROJECT_TAPE_HPP
