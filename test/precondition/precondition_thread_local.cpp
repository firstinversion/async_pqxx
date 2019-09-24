#include <catch2/catch.hpp>

#include <cstdint>
#include <thread>

thread_local int32_t number = 1;

TEST_CASE("precondition_thread_local: basic usage", "[precondition_thread_local]") {
    std::vector<std::thread> threads;
    threads.reserve(10);
    for (auto i = 0; i < 10; ++i) {
        threads.emplace_back([]() {
            REQUIRE(number == 1);
            ++number;
            REQUIRE(number == 2);
            ++number;
            REQUIRE(number == 3);
            --number;
            REQUIRE(number == 2);
        });
    }

    std::for_each(threads.begin(), threads.end(), [](auto& t) { t.join(); });
}
