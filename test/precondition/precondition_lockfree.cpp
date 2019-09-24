#include <catch2/catch.hpp>

#include <boost/lockfree/queue.hpp>
#include <thread>

TEST_CASE("precondition_lockfree: basic usage of queue", "[precondition_lockfree]") {
    boost::lockfree::queue<int32_t> queue(100);
    bool                            terminate = false;

    std::thread exe_thread([&]() {
        while (true) {
            int32_t result;
            bool not_empty = queue.pop(result);  // Probably kills us, pop would need to block until a new message came
                                                 // for this to be useful in our case.
            REQUIRE(result == 245);
            if (terminate && !not_empty) break;
        }
    });

    queue.push(245);
    queue.push(245);
    terminate = true;
    exe_thread.join();
}
