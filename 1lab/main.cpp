#include "gtest/gtest.h"
#include "TritSet.h"
#include <iostream>

using namespace std;

typedef unsigned int uint;

TEST (TritSetTest, allTest) {
    TritSet set(1000);
    size_t allocLength = set.capacity();
    EXPECT_GE(allocLength, 1000 * 2 / 8 / sizeof(uint));

    set[1000000000] = Unknown;
    EXPECT_EQ(allocLength, set.capacity());

    set[1000000000] = True;
    EXPECT_LT(allocLength, set.capacity());

    allocLength = set.capacity();
    set[1000000000] = Unknown;
    set[1000000] = False;
    EXPECT_EQ(allocLength, set.capacity());

    set.shrink();
    EXPECT_GT(allocLength, set.capacity());
    EXPECT_EQ(set.capacity(), (1000000 / trits_in_uint + 1) * trits_in_uint);

    EXPECT_EQ(set.cardinality(Unknown), 1000000);
    EXPECT_EQ(set.cardinality(False), 1);
    EXPECT_EQ(set.cardinality(True), 0);

    TritSet set_not = ~set;
    EXPECT_EQ(set_not.cardinality(False), set.cardinality(~False));
    EXPECT_EQ(set_not.cardinality(True), set.cardinality(~True));

    int known_trits = set.cardinality(True) + set.cardinality(False);
    TritSet set_or = set | set_not;
    EXPECT_EQ(set_or.cardinality(True), known_trits);
    TritSet set_and = set & set_not;
    EXPECT_EQ(set_and.cardinality(False), known_trits);

    EXPECT_EQ(set.lenght(), 1000001);
    set[5000000] = True;
    EXPECT_EQ(set.lenght(), 5000001);
    EXPECT_EQ(set.cardinality(True), 1);

    set.trim(2000000);
    EXPECT_EQ(set.cardinality(False), 1);
    EXPECT_EQ(set.cardinality(True), 0);

    TritSet setA(1000);
    TritSet setB(2000);
    TritSet setC = setA & setB;
    EXPECT_EQ(setC.capacity(), setB.capacity());

    setA = setA;
    setB = setB;
    TritSet setC2 = setA & setB;
    ASSERT_TRUE((setC2 == setC));
    /*TritSet setE1(10);
    TritSet setE2(20);
    ASSERT_TRUE(setE1 == setE2);
    */
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
