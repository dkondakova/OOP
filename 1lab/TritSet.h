#pragma once

#include "Trit.h"
#include <iostream>

using namespace std;

typedef unsigned int uint;
const int trits_in_uint = sizeof(uint) * 4;

const int unknown_uint = 1431655765;

class TritSet {
friend class prx;
public:
    TritSet(size_t cap);
    TritSet(const TritSet &set);
    ~TritSet();
    const int capacity() const;

    class prx {
    friend class TritSet;
    public:
        prx(TritSet& s, int ind);
        prx& operator=(Trit t);
    private:
        TritSet& set;
        int index;
    };

    prx operator[](const int index);
    Trit operator[](const int index) const;
    TritSet& operator=(const TritSet &other);
    bool operator==(const TritSet &other);
    size_t lenght();
    void shrink();
    void trim(size_t lastIndex);
    size_t cardinality(Trit value);

private:
    size_t cap;
    uint *arr;
    void extend(const int index);
};

TritSet operator~(TritSet const &a);
TritSet operator&(TritSet const &a, TritSet const &b);
TritSet operator|(TritSet const &a, TritSet const &b);
