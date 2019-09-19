#include <catch2/catch.hpp>

#include <pqxx/pqxx>

// CREATE TABLE points(
//    id bigserial not null,
//    x float not null,
//    y float not null,
//    z float not null,
//
//    PRIMARY KEY (id)
//);

TEST_CASE("precondition_pqxx: select 1 from database", "[precondition_pqxx]") {
    pqxx::connection connection("host=localhost port=5432");
    pqxx::work       work(connection);

    auto r = work.exec1("SELECT 1;");
    work.commit();

    REQUIRE(r[0].as<int>() == 1);
}
