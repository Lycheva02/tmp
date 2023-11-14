#include "exc.h"
#include "gtest/gtest.h"

class TMyTest: public testing::Test {};

TEST(TMyTest, exception)
{
    TMyException exc;
    exc << "123";
    exc.what();
    EXPECT_THROW(throw exc, TMyException);
    First one;
    one << "45" << "678";
    one.what();
    EXPECT_THROW(throw one, First);
    Second two;
    two << "90123456";
    two.what();
    EXPECT_THROW(throw two, Second);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}