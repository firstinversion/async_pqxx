#include <catch2/catch.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/spawn.hpp>

#include <async_pqxx/manager.hpp>

TEST_CASE("manager: select 1 from database", "[manager]") {
    async_pqxx::manager     manager(4, "host=localhost port=5432");
    boost::asio::io_context ioc;
    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto result = manager.exec1("SELECT 1;", yield);
        REQUIRE(result[0].as<int>() == 1);
    });
    ioc.run();
}

TEST_CASE("manager: select from database", "[manager]") {
    async_pqxx::manager     manager(4, "host=localhost port=5432");
    boost::asio::io_context ioc;
    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto result = manager.exec("SELECT * FROM generate_series(1, 6) num;", yield);
        REQUIRE(result.size() == 6);
        REQUIRE(result[0][0].as<int>() == 1);
        REQUIRE(result[2][0].as<int>() == 3);
    });
    ioc.run();
}

TEST_CASE("manager: select using function", "[manager]") {
    async_pqxx::manager     manager(4, "host=localhost port=5432");
    boost::asio::io_context ioc;
    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto result = manager.exec_functor<pqxx::row>(
            [](pqxx::connection& connection) -> pqxx::row {
                pqxx::work w(connection);
                pqxx::row  res = w.exec1("SELECT 1;");
                w.commit();

                return res;
            },
            yield);

        REQUIRE(result[0].as<int32_t>() == 1);
    });
    ioc.run();
}
