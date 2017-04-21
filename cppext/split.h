#include <string>
#include <algorithm>
#include <vector>

namespace cppext
{
    template <typename Iter, typename StringT>
        auto findFirstNotOf(Iter&& begin, Iter&& end, StringT&& delim)
			-> decltype(auto)
        {
            return std::find_first_of(
                begin,
                end,
                delim.cbegin(),
                delim.cend(),
                [](auto a, auto b) { return a != b; }
            );
        }

        template <typename Iter, typename StringT>
        auto findFirstOf(Iter&& begin, Iter&& end, StringT&& delim)
			-> decltype(auto)
        {
            return std::find_first_of(
                begin,
                end,
                delim.cbegin(),
                delim.cend()
            );
        }

        template <typename Iter, typename StringT, class Container>
        auto recursiveSplit(Iter&& begin, Iter&& end, StringT&& delim, Container&& store)
			-> void
        {
            auto beginCopy = findFirstNotOf(begin, end, delim);
            if(beginCopy != end)
            {
                auto endCopy = findFirstOf(beginCopy, end, delim);
                store.emplace_back(StringT{ beginCopy, endCopy });
                recursiveSplit(endCopy, end, delim, store);
            }
        }

		template<typename StringT, template<typename = StringT, typename = std::allocator<StringT>> class Container = std::vector>
        auto split(StringT&& toSplit, StringT&& delim)
        {
            Container<StringT> store;
            recursiveSplit(toSplit.cbegin(), toSplit.cend(), delim, store);
            return store;
        }
}
