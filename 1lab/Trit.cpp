#include "Trit.h"

Trit operator~(Trit t) {
    if (t == True) {
        return False;
    }
    if (t == Unknown) {
        return Unknown;
    }
    if (t == False) {
        return True;
    }
}

Trit operator&(Trit t1, Trit t2) {
    if (t1 == True) {
        return t2;
    }
    if (t1 == False || t2 == False) {
        return False;
    }
    if (t1 == Unknown) {
        return Unknown;
    }
}

Trit operator|(Trit t1, Trit t2) {
    if (t1 == True || t2 == True) {
        return True;
    }
    if (t1 == False) {
        return t2;
    }
    if (t1 == Unknown) {
        return Unknown;
    }
}
