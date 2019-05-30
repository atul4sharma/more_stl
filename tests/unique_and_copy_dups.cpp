

#include <catch/catch.hpp>
#include <include/unique_and_copy_dups.hpp>

#include <iterator>
#include <functional>

TEST_CASE("empty source", "[unique_and_copy_dups]")
{
    auto source = std::vector<int>{};
    auto dups   = std::vector<int>{};

    auto result = mstl::unique_and_copy_dups(std::begin(source)
                                            ,std::end(source)
                                            ,std::back_inserter(dups)
                                            ,std::equal_to<int>{});

    REQUIRE( ( result.first == std::end(source)
               &&
               dups.size() == 0 ) );
}
