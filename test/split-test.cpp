#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cppext/split.h"

#include <type_traits>
#include <list>

using namespace cppext;
using namespace std;

template<typename T>
struct is_container : false_type
{
};

template <typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>> : true_type
{
};

TEST(Split, DefaultReturnTypeIsVector)
{
	auto returnType = split(string{"a,b,c"}, string{ "," });

	EXPECT_TRUE(is_container<decltype(returnType)>());
}

//TEST(Split, DoesNotAllowContainersWithDifferentValueType)
//{
//	split<string, vector<const char*>>(string{ "a,b,c" }, string{ "," });
//}

//// check that container value type is same as stringT