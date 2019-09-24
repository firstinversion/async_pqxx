#include <catch2/catch.hpp>

#include <boost/asio/spawn.hpp>

#include "test_database.hpp"

TEST_CASE("manager: insert point", "[manager]") {
    auto database = async_pqxx::test::database();
    auto manager  = async_pqxx::test::get_test_manager();

    auto res = manager.exec0("INSERT INTO integration.points(x, y, z) VALUES(1, 2, 3);");
    REQUIRE(res.affected_rows() == 1);
}

TEST_CASE("manager: async insert point", "[manager]") {
    auto database = async_pqxx::test::database();
    auto manager  = async_pqxx::test::get_test_manager();

    async_pqxx::test::run([&](boost::asio::yield_context yield) {
        auto res = manager.async_exec0("INSERT INTO integration.points(x, y, z) VALUES(1, 2, 3);", yield);
        REQUIRE(res.affected_rows() == 1);
    });
}
