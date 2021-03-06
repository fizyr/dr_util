#include <string>
#include <sstream>
#include <array>

#include <gtest/gtest.h>

#include "functional.hpp"
#include "tuple.hpp"

using namespace dr;

int main(int argc, char * * argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(FunctionalTest, callHardcoded) {
	EXPECT_EQ(true,  call([] () { return true;  }, std::make_tuple()));
	EXPECT_EQ(false, call([] () { return false; }, std::make_tuple()));
}

TEST(FunctionalTest, callInput) {
	EXPECT_EQ(true,  call([] (bool input) { return input; }, std::make_tuple(true)));
	EXPECT_EQ(false, call([] (bool input) { return input; }, std::make_tuple(false)));
}

TEST(FunctionalTest, callSum) {
	EXPECT_EQ( 3, call([] (int a, int b) { return a + b; }, std::make_tuple(1, 2)));
	EXPECT_EQ(17, call([] (int a, int b) { return a + b; }, std::make_tuple(7, 10)));
}
