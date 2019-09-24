#include <catch2/catch.hpp>

#include <boost/asio/spawn.hpp>

#include "test_database.hpp"

TEST_CASE("manager: insert point", "[manager]") {
    auto database = async_pqxx::test::database();
    auto manager  = async_pqxx::test::get_test_manager();
    auto ioc      = boost::asio::io_context();

    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto res = manager.exec0("INSERT INTO integration.points(x, y, z) VALUES(1, 2, 3);", yield);
        REQUIRE(res.affected_rows() == 1);
    });
}
