#pragma once

enum Trit{False, Unknown, True};

Trit operator~(Trit t);
Trit operator&(Trit t1, Trit t2);
Trit operator|(Trit t1, Trit t2);
