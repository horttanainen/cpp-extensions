#include <string>
#include <algorithm>
#include <vector>

namespace cppext
{
    template <typename Iter, typename StringT>
        decltype(auto) findFirstNotOf(Iter&& begin, Iter&& end, StringT&& delim)
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
        decltype(auto) findFirstOf(Iter&& begin, Iter&& end, StringT&& delim)
        {
            return std::find_first_of(
                begin,
                end,
                delim.cbegin(),
                delim.cend()
            );
        }

        template <typename Iter, typename StringT, class Container>
        void recursiveSplit(Iter&& begin, Iter&& end, StringT&& delim,
            Container&& store)
        {
            auto beginCopy = findFirstNotOf(begin, end, delim);
            if(beginCopy != end)
            {
                auto endCopy = findFirstOf(beginCopy, end, delim);
                store.emplace_back(StringT{ beginCopy, endCopy });
                recursiveSplit(endCopy, end, delim, store);
            }
        }

        template <typename StringT>
        std::vector<StringT> split(const StringT& toSplit, const StringT& delim)
        {
            std::vector<StringT> store;
            recursiveSplit(toSplit.cbegin(), toSplit.cend(), delim, store);
            return store;
        }
}
