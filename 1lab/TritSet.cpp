#include "TritSet.h"
#include <math.h>
#include <algorithm>
//#include <iterator>

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

TritSet::TritSet(size_t cap) :
    cap((cap + trits_in_uint - 1) / trits_in_uint * trits_in_uint),
    arr(new uint[(cap + trits_in_uint - 1) / trits_in_uint]())
{
    for (int i = 0; i < (cap + trits_in_uint - 1) / trits_in_uint; i++) {
        arr[i] = unknown_uint;
    }
}

TritSet::TritSet(const TritSet &set) :
    cap(set.cap),
    arr(new uint[set.cap / trits_in_uint])
{
    for (int i = 0; i < set.cap / trits_in_uint; i++) {
        arr[i] = set.arr[i];
    }
}

TritSet::~TritSet() {
    delete [] arr;
}

const int TritSet::capacity() const {
    return cap;
}

TritSet::prx::prx(TritSet& s, int ind) :
    set(s),
    index(ind)
{}
TritSet::prx& TritSet::prx::operator=(Trit t) {
    if (index > set.capacity() - 1) {
        if (t == Unknown) {
            return *this;
        }
        set.extend(index);
    }
    int uint_ind = index / trits_in_uint;
    uint& r = set.arr[uint_ind];
    int shift = (trits_in_uint - 1 - index % trits_in_uint) * 2;
    uint mask = 0x3 << shift;
    r &= ~mask;
    r |= t << shift;

    return *this;
}

TritSet::prx TritSet::operator[](const int index) {
    return TritSet::prx(*this, index);
}

Trit TritSet::operator[](const int index) const {
    if (index > cap - 1) {
        return Unknown;
    }
    int uint_ind = index / trits_in_uint;
    int shift = (trits_in_uint - 1 - index % trits_in_uint) * 2;
    uint r = arr[uint_ind] >> shift;
    Trit t = (Trit)(r & 0x3);
    return t;
}

TritSet& TritSet::operator=(const TritSet &other) {
    if (this != &other) {
        cap = other.cap;

        if (arr != NULL) {
            delete [] arr;
        }
        arr = new uint[other.cap / trits_in_uint];
        for (size_t i = 0; i < other.cap; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

bool TritSet::operator==(const TritSet &other) {
    if (cap == other.cap) {
        for (int i = 0; i < cap / trits_in_uint; i++) {
            if (arr[i] != other.arr[i]) {
                return false;
            }
        }
        return true;
    }
    return false;;
}

size_t TritSet::lenght() {
    for (size_t i = cap / trits_in_uint - 1; i >= 0; i--) {
        for (int p = 0; p < trits_in_uint; p++) {
            if ((arr[i] >> 2 * p & 0x3) != Unknown) {
                return i * trits_in_uint + trits_in_uint - p;
            }
        }
    }
    return 0;   //all trits = Unknown
}

void TritSet::shrink() {
    int i = (this->lenght() - 1) / trits_in_uint;
    uint *new_arr = new uint[i + 1];
    for (size_t j = 0; j <= i; j++) {
        new_arr[j] = arr[j];
    }
    delete [] arr;
    arr = new_arr;

    cap = (i + 1) * trits_in_uint;
}

void TritSet::trim(size_t lastIndex) {
    int i = lastIndex / trits_in_uint;
    int temp = (trits_in_uint - lastIndex % trits_in_uint) - 1;
    for (int j = 0; j < temp; j++) {
        arr[i] &= ~(0x3 << j * 2);
        arr[i] |= (Unknown << j * 2);
    }
    for (i = lastIndex / trits_in_uint + 1; i < cap / trits_in_uint; i++) {
        arr[i] = unknown_uint;
    }
}

size_t TritSet::cardinality(Trit value) {
    size_t last = this->lenght() - 1;  //last known trit's index
    int i = last / trits_in_uint;
    int k = 0;
    for (int j = trits_in_uint - last % trits_in_uint - 1; j < trits_in_uint; j++) {
        if ((arr[i] >> 2 * j & 0x3) == value) {
            k++;
        }
    }
    for (i = last / trits_in_uint - 1; i >= 0; i--) {
        for (int j = 0; j < trits_in_uint; j++) {
            if (((arr[i] >> 2 * j) & 0x3) == value) {
                k++;
            }
        }
    }
    return k;
}

void TritSet::extend(const int index) {
    uint *new_arr = new uint[(index + trits_in_uint) / trits_in_uint]();
    for (size_t i = 0; i < (index + trits_in_uint) / trits_in_uint; i++) {
        if (i < cap / trits_in_uint) {
            new_arr[i] = arr[i];
        } else {
            new_arr[i] = unknown_uint;
        }
    }
    delete [] arr;
    arr = new_arr;

    cap = (index + trits_in_uint) / trits_in_uint * trits_in_uint;
}

TritSet operator~(TritSet const &a) {
    TritSet c(a.capacity());
    for (int i = 0; i < a.capacity(); i++) {
        c[i] = ~a[i];
    }
    return c;
}

TritSet operator&(TritSet const &a, TritSet const &b) {
    int min_c = min(a.capacity(), b.capacity());
    int max_c = max(a.capacity(), b.capacity());
    TritSet c(max_c);
    for (int i = 0; i < min_c; i++) {
        c[i] = a[i] & b[i];
    }
    if (min_c != max_c) {
        Trit t = Unknown;
        for (int i = min_c; i < max_c; i++) {
            if (a.capacity() > b.capacity()) {
                c[i] = t & a[i];
            } else {
                 c[i] = t & b[i];
            }
        }
    }
    return c;
}

TritSet operator|(TritSet const &a, TritSet const &b) {
    int min_c = min(a.capacity(), b.capacity());
    int max_c = max(a.capacity(), b.capacity());
    TritSet c(max_c);
    for (int i = 0; i < min_c; i++) {
        c[i] = a[i] | b[i];
    }
    if (min_c != max_c) {
        Trit t = Unknown;
        for (int i = min_c; i < max_c; i++) {
            if (a.capacity() > b.capacity()) {
                c[i] = t | a[i];
            } else {
                 c[i] = t | b[i];
            }
        }
    }
    return c;
}
