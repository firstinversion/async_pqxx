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

struct item {
    int32_t                            local_num  = 0;
    inline static thread_local int32_t thread_num = 0;
};

TEST_CASE("precondition_thread_local: 'static' class member", "[precondition_thread_local]") {
    std::vector<std::thread> threads;
    threads.reserve(10);
    for (auto i = 0; i < 10; ++i) {
        threads.emplace_back([]() {
            item i;
            i.thread_num = i.local_num;
            REQUIRE(i.thread_num == 0);
            ++i.thread_num;
            REQUIRE(i.thread_num == 1);
            ++i.thread_num;
            REQUIRE(i.thread_num == 2);
            --i.thread_num;
            REQUIRE(i.thread_num == 1);
        });
    }

    std::for_each(threads.begin(), threads.end(), [](auto& t) { t.join(); });
}
