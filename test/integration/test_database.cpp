#include "test_database.hpp"

#include <stdlib.h>
#include <pqxx/transaction>
#include <spdlog/spdlog.h>

namespace async_pqxx::test {

    const char* default_connection_string() {
        char* provided;
        provided = getenv("ASYNC_PQXX_TEST_DATABASE");
        if (provided) return provided;
        else return "host=localhost port=5432";
    }

    database::database()
        : _connection(default_connection_string())
        , _schema(std::make_unique<schema>(_connection)) {}

    database::database(const char* connection_string)
        : _connection(connection_string)
        , _schema(std::make_unique<schema>(_connection)) {}

    database::~database() { _schema.reset(); }

    schema::schema(pqxx::connection& connection)
        : _connection(connection) {
        pqxx::work work(connection);
        auto       res = work.exec0("CREATE SCHEMA integration;");

        _points = std::make_unique<table_points>(_connection, work);
        _person = std::make_unique<table_person>(_connection, work);
        work.commit();
    }

    schema::~schema() {
        _points.reset();
        _person.reset();

        pqxx::work work(_connection);
        auto       res = work.exec0("DROP SCHEMA integration;");
        work.commit();
    }

    table_points::table_points(pqxx::connection& connection, pqxx::work& create)
        : _connection(connection) {
        auto res = create.exec0(
            "CREATE TABLE integration.points("
            "    id    bigserial    primary key,"
            "    x     integer      not null,"
            "    y     integer      not null,"
            "    z     integer      not null"
            ");");
    }

    table_points::~table_points() {
        pqxx::work work(_connection);
        auto       res = work.exec0("DROP TABLE integration.points;");
        work.commit();
    }

    table_person::table_person(pqxx::connection& connection, pqxx::work& create)
        : _connection(connection) {
        auto res = create.exec0(
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
    }

    table_person::~table_person() {
        pqxx::work work(_connection);
        auto       res = work.exec0("DROP TABLE integration.person;");
        work.commit();
    }

    async_pqxx::manager get_test_manager() { return async_pqxx::manager(4, default_connection_string()); }

}  // namespace async_pqxx::test
