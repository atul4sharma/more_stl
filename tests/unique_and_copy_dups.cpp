

#include <catch/catch.hpp>
#include <include/unique_and_copy_dups.hpp>

#include <iterator>
#include <functional>

TEST_CASE("source with 0 elements", "[unique_and_copy_dups]")
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

TEST_CASE("source with 1 element", "[unique_and_copy_dups]")
{
    auto source = std::vector<int>{1};
    auto dups   = std::vector<int>{};

    auto result = mstl::unique_and_copy_dups(std::begin(source)
                                            ,std::end(source)
                                            ,std::back_inserter(dups)
                                            ,std::equal_to<int>{});

    REQUIRE( ( std::vector<int>{begin(source), result.first} == std::vector<int>{1}
               &&
               dups.size() == 0 ) );
}

TEST_CASE("source without dups", "[unique_and_copy_dups]")
{
    auto source = std::vector<int>{1, 2, 3};
    auto dups   = std::vector<int>{};

    auto result = mstl::unique_and_copy_dups(std::begin(source)
                                            ,std::end(source)
                                            ,std::back_inserter(dups)
                                            ,std::equal_to<int>{});

    REQUIRE( ( result.first == std::end(source)
               &&
               dups.size() == 0 ) );
}

TEST_CASE("source with dups", "[unique_and_copy_dups]")
{
    auto source = std::vector<int>{1, 1, 1, 2, 2, 3};
    auto dups   = std::vector<int>{};

    auto result = mstl::unique_and_copy_dups(std::begin(source)
                                            ,std::end(source)
                                            ,std::back_inserter(dups)
                                            ,std::equal_to<int>{});

    REQUIRE( ( std::vector<int>{begin(source), result.first} == std::vector<int>{1, 2, 3}
               &&
               dups == std::vector<int>{1, 1, 2} ) );
}

TEST_CASE("source of pairs with dups", "[unique_and_copy_dups]")
{
    auto source = std::vector<std::pair<std::string, int>> {
         {"one", 1}
        ,{"one", 2}
        ,{"two", 2}
        ,{"three", 3}
        ,{"three", 4}
    };
    auto dups   = std::vector<std::pair<std::string, int>>{};

    auto const is_equal = [](std::pair<std::string, int> const & left
                            ,std::pair<std::string, int> const & right)
    {
        return left.first == right.first;
    };

    auto result = mstl::unique_and_copy_dups(std::begin(source)
                                            ,std::end(source)
                                            ,std::back_inserter(dups)
                                            ,is_equal);

    REQUIRE( ( std::vector<std::pair<std::string, int>>{begin(source), result.first}
               ==
               std::vector<std::pair<std::string, int>> {
                    {"one", 1}
                   ,{"two", 2}
                   ,{"three", 3}
               }
               &&
               dups == std::vector<std::pair<std::string, int>> {
                    {"one", 2}
                   ,{"three", 4}
               } ) );
}
