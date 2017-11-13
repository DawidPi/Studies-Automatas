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
            return const_cast<T&>(fetchFrom(mPositiveIdxValues, idx));
        } else {
            return const_cast<T&>(fetchFrom(mNegativeIdxValues, std::abs(idx) -1));
        }
    }

    const T& operator[](size_t idx) const {
        if(idx >= 0){
            return fetchFrom(const_cast<Container&>(mPositiveIdxValues), idx);
        } else {
            return fetchFrom(const_cast<Container&>(mNegativeIdxValues), std::abs(idx) -1);
        }
    }

    void clear(){
        mPositiveIdxValues.clear();
        mNegativeIdxValues.clear();
    }

    //poor man's iterators
    class iterator{
    public:
        iterator(){}
        iterator(Tape* tape, size_type index) : mTape(tape), mIndex(index){}

        iterator& operator++(){
            mIndex++;
            return *this;
        }

        iterator operator++(int){
            auto iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator==(const iterator& rhs){
            return mIndex == rhs.mIndex;
        }

        bool operator!=(const iterator& rhs){
            return !(mIndex == rhs.mIndex);
        }

        T& operator*() const {
            return (*mTape)[mIndex];
        };

    private:
        Tape* mTape = nullptr;
        size_type mIndex = 0;
    };

    class const_iterator{
    public:
        const_iterator(){}
        const_iterator(const Tape* tape, size_type index) : mTape(tape), mIndex(index){}

        const_iterator& operator++(){
            mIndex++;
            return *this;
        }

        const_iterator operator++(int){
            auto iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator==(const const_iterator& rhs){
            return mIndex == rhs.mIndex;
        }

        bool operator!=(const const_iterator& rhs){
            return !(mIndex == rhs.mIndex);
        }

        const T& operator*() const {
            return (*mTape)[mIndex];
        };

    private:
        const Tape* mTape = nullptr;
        size_type mIndex = 0;
    };

    iterator begin(){
        return {this, -static_cast<size_type>(mNegativeIdxValues.size())};
    }

    iterator end(){
        return {this, mPositiveIdxValues.size()};
    }

    const_iterator begin() const{
        return {this, -static_cast<size_type>(mNegativeIdxValues.size())};
    }
    const_iterator end() const{
        return {this, mPositiveIdxValues.size()};
    }

private:

    const T& fetchFrom(Container& container, size_t idx) const{
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
