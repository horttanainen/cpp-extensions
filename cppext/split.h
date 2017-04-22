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
				std::forward<Iter>(begin),
				std::forward<Iter>(end),
				std::cbegin(delim),
				std::cend(delim),
                [](auto a, auto b) { return a != b; }
            );
        }

        template <typename Iter, typename StringT>
        auto findFirstOf(Iter&& begin, Iter&& end, StringT&& delim)
			-> decltype(auto)
        {
            return std::find_first_of(
                std::forward<Iter>(begin),
				std::forward<Iter>(end),
				std::cbegin(delim),
				std::cend(delim)
            );
        }

        template <typename Iter1, typename Iter2, typename StringT, class Container>
        auto recursiveSplit(Iter1&& begin, Iter2&& end, StringT&& delim, Container& store)
			-> void
        {
            auto beginCopy = findFirstNotOf(begin, end, delim);
            if(beginCopy != end)
            {
                auto endCopy = findFirstOf(beginCopy, end, delim);
                store.emplace_back( beginCopy, endCopy );
                recursiveSplit(endCopy, std::forward<Iter2>(end), std::forward<StringT>(delim), store);
            }
        }

		template<typename Container = std::vector<std::string>>
		auto split(const char* toSplit, const char* delim)
		{
			return split<std::string&&, std::string&&, Container>(std::string{ toSplit }, std::string{ delim });
		}

		template<typename StringT,typename Container = std::vector<std::string>>
		auto split(StringT&& toSplit, const char* delim)
		{
			return split<StringT, std::string&&, Container>(std::forward<StringT>(toSplit), std::string{ delim });
		}

		template<typename StringT, typename Container = std::vector<std::string>>
		auto split(const char* toSplit, StringT&& delim)
		{
			return split<std::string&&, StringT, Container>(std::string{ toSplit }, std::forward<StringT>(delim));
		}

		template<typename StringT1, typename StringT2, typename Container = std::vector<std::remove_reference_t<StringT1>>>
		auto split(StringT1&& toSplit, StringT2&& delim)
			->std::enable_if_t< std::is_same_v<std::remove_reference_t<StringT2>, char>, Container>
        {
			return split<StringT1, std::add_rvalue_reference_t<std::remove_reference_t<StringT1>>, Container>(std::forward<StringT1>(toSplit), std::remove_reference_t<StringT1>{delim});
        }

		template<typename StringT1, typename StringT2, typename Container = std::vector<std::remove_reference_t<StringT1>>>
		auto split(StringT1&& toSplit, StringT2&& delim)
			->std::enable_if_t< ! std::is_same_v<std::remove_reference_t<StringT2>, char>, Container>
		{
			static_assert(std::is_same_v<std::remove_reference_t<StringT1>, typename Container::value_type>, "Container value type should be same as first of the split arguments.");

			auto store = Container{};
			recursiveSplit(std::cbegin(toSplit), std::cend(toSplit), std::forward<StringT2>(delim), store);
			return store;
		}
}
