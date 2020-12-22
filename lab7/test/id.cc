#include "gtest/gtest.h"
#include "id.h"

TEST(ID, Unique){
    UniqueID a;
    UniqueID b;
    EXPECT_NE(a.value, b.value);
}