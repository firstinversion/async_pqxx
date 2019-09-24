#include "test_database.hpp"

#include <pqxx/transaction>
#include <spdlog/spdlog.h>

namespace async_pqxx::test {

    test_database::test_database(pqxx::connection& connection)
        : _connection(connection)
        , _schema(connection) {}

    test_schema::test_schema(pqxx::connection& connection)
        : _connection(connection) {
        pqxx::work work(connection);
        auto       res = work.exec0("CREATE SCHEMA integration;");
        work.commit();

        _points = std::make_unique<test_table_points>(_connection);
        _person = std::make_unique<test_table_person>(_connection);
    }

    test_schema::~test_schema() {
        pqxx::work work(_connection);
        auto       res = work.exec0("DROP SCHEMA integration;");
        work.commit();
    }

    test_table_points::test_table_points(pqxx::connection& connection)
        : _connection(connection) {
        pqxx::work work(_connection);
        auto       res = work.exec0(
            "CREATE TABLE integration.points("
            "    id    bigserial primary key,"
            "    x     double not null,"
            "    y     double not null,"
            "    z     double not null"
            ");");
        work.commit();
    }

    test_table_points::~test_table_points() {
        pqxx::work work(_connection);
        auto       res = work.exec0("DROP TABLE integration.points;");
        work.commit();
    }

    test_table_person::test_table_person(pqxx::connection& connection)
        : _connection(connection) {
        pqxx::work work(_connection);
        auto       res = work.exec0(
            "CREATE TABLE integration.person("
            "    id            bigserial not null,"
            "    first_name    text    not null,"
            "    last_name     text    not null,"
            "    email         text,"
            "    phone         text,"
            ""
            "    PRIMARY KEY (id),"
            "    UNIQUE(email),"
            "    UNIQUE(phone)"
            ");");
        work.commit();
    }

    test_table_person::~test_table_person() {
        pqxx::work work(_connection);
        auto       res = work.exec0("DROP TABLE integration.person;");
        work.commit();
    }

}  // namespace async_pqxx::test
