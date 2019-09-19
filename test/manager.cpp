#include <catch2/catch.hpp>

#include <asyncpq/manager.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/spawn.hpp>

TEST_CASE("manager: select 1 from database", "[manager]") {
    asyncpq::manager        manager(4, "host=localhost port=5432");
    boost::asio::io_context ioc;
    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto result = manager.exec1("SELECT 1;", yield);
        REQUIRE(result[0].as<int>() == 1);
    });
    ioc.run();
}
