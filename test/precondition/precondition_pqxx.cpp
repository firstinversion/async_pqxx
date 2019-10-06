#include <catch2/catch.hpp>

#include <pqxx/pqxx>
#include <spdlog/spdlog.h>

// CREATE TABLE points(
//    id bigserial not null,
//    x float not null,
//    y float not null,
//    z float not null,
//
//    PRIMARY KEY (id)
//);

const char* default_connection_string() {
    static const char* default_str = "host=localhost port=5432";
    char*              provided_str;
    provided_str = getenv("ASYNC_PQXX_TEST_DATABASE");

    spdlog::info("DATABASE CONNECTION STRING: {}", provided_str ? provided_str : default_str);
    if (provided_str)
        return provided_str;
    else
        return default_str;
}

TEST_CASE("precondition_pqxx: select 1 from database", "[precondition_pqxx]") {
    pqxx::connection connection(default_connection_string());
    pqxx::work       work(connection);

    auto r = work.exec1("SELECT 1;");
    work.commit();

    REQUIRE(r[0].as<int>() == 1);
}
