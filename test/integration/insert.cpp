#include <catch2/catch.hpp>

#include <boost/asio/spawn.hpp>

#include "test_database.hpp"

TEST_CASE("manager: insert point", "[manager]") {
    auto database = async_pqxx::test::database();
    auto manager  = async_pqxx::test::get_test_manager();

    auto result = manager.exec0("INSERT INTO integration.points(x, y, z) VALUES(1, 2, 3);");
    REQUIRE(result.affected_rows() == 1);
}

TEST_CASE("manager: async insert point", "[manager]") {
    auto database = async_pqxx::test::database();
    auto manager  = async_pqxx::test::get_test_manager();

    async_pqxx::test::run([&](boost::asio::yield_context yield) {
        auto result = manager.async_exec0("INSERT INTO integration.points(x, y, z) VALUES(1, 2, 3);", yield);
        REQUIRE(result.affected_rows() == 1);
    });
}

TEST_CASE("manager: insert point returning id", "[manager]") {
    auto database = async_pqxx::test::database();
    auto manager  = async_pqxx::test::get_test_manager();

    auto result_1 = manager.exec1("INSERT INTO integration.points(x, y, z) VALUES (1, 2, 3) RETURNING id;");
    REQUIRE(result_1[0].as<int64_t>() == 1);

    auto result_2 = manager.exec1("INSERT INTO integration.points(x, y, z) VALUES (1, 2, 3) RETURNING id;");
    REQUIRE(result_2[0].as<int64_t>() == 2);
}

//TEST_CASE("manager: insert param") {
//    auto database = async_pqxx::test::database();
//    auto manager  = async_pqxx::test::get_test_manager();
//
//    auto result_insert =
//        manager.exec1("INSERT INTO integration.points(x, y, z) VALUES ({}, {}, {}) RETURNING id;", 1, 2, 3);
//    auto result_select =
//        manager.exec1("SELECT x, y, z FROM integration.points WHERE id = {};", result_insert[0].as<int64_t>());
//    REQUIRE(result_select[0].as<double>() == 1);
//    REQUIRE(result_select[1].as<double>() == 2);
//    REQUIRE(result_select[2].as<double>() == 3);
//}
