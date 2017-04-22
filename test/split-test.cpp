#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cppext/split.h"

#include <type_traits>

#include <vector>
#include <list>

using namespace cppext;
using namespace std;
using namespace testing;

template<typename T>
struct is_vector : false_type
{
};

template <typename T, typename Alloc>
struct is_vector<std::vector<T, Alloc>> : true_type
{
};

TEST(Split, DefaultReturnTypeIsVector)
{
	auto returnType = split(string{"a,b,c"}, string{ "," });

	EXPECT_TRUE(is_vector<decltype(returnType)>());
}

//TEST(Split, DoesNotAllowContainersWithDifferentValueType)
//{
//	split<string, vector<const char*>>(string{ "a,b,c" }, string{ "," });
//}

TEST(Split, SplittingRValueStringWithRValueCharIsSupported)
{
	auto splitted = split(string{ "a,b,c,d,e" }, ',');

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingLValueStringWithRValueCharIsSupported)
{
	auto toSplit = string{ "a,b,c,d,e" };

	auto splitted = split(toSplit, ',');

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingRValueStringWithLValueCharIsSupported)
{
	char delim = ',';

	auto splitted = split(string{ "a,b,c,d,e" }, delim);

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingLValueStringWithLValueCharIsSupported)
{
	auto toSplit = string{ "a,b,c,d,e" };
	char delim = ',';

	auto splitted = split(toSplit, delim);

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingRValueStringWithRValueStringIsSupported)
{
	auto splitted = split(string{ "a,b,c,d,e" }, string{ "," });

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingRValueStringWithLValueStringIsSupported)
{
	auto delim = string{","};

	auto splitted = split(string{ "a,b,c,d,e" }, delim);

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingLValueStringWithRValueStringIsSupported)
{
	auto toSplit = string{ "a,b,c,d,e" };

	auto splitted = split(toSplit, string{ "," });

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingLValueStringWithLValueStringIsSupported)
{
	auto toSplit = string{ "a,b,c,d,e" };
	auto delim = string{ "," };

	auto splitted = split(toSplit, delim);

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingConstCharWithConstCharIsSupported)
{
	auto splitted = split("a,b,c,d,e", ",");

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingRValueStringWithConstCharIsSupported)
{
	auto splitted = split(string{ "a,b,c,d,e" }, ",");

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingLValueStringWithConstCharIsSupported)
{
	auto toSplit = string{ "a,b,c,d,e" };
	auto splitted = split(toSplit, ",");

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingConstCharWithRValueStringIsSupported)
{
	auto splitted = split("a,b,c,d,e", string{ "," });

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingConstCharWithLValueStringIsSupported)
{
	auto delim = string{ "," };
	auto splitted = split("a,b,c,d,e", delim);

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingConstCharWithRValueCharIsSupported)
{
	auto splitted = split("a,b,c,d,e", ',');

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, SplittingConstCharWithLValueCharIsSupported)
{
	auto delim = ',';
	auto splitted = split("a,b,c,d,e", delim);

	EXPECT_THAT(splitted.size(), Eq(5));
}

TEST(Split, ListCanBeUsedAsReturnedContainerType)
{
	auto splitted = split<list<string>>("a, b, c, d, e", ",");

	EXPECT_THAT(splitted.size(), Eq(5));
}
