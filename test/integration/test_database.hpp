#pragma once

#include <pqxx/connection>

namespace async_pqxx::test {

    class test_table_points {
    public:
        explicit test_table_points(pqxx::connection& connection);
        ~test_table_points();

    private:
        pqxx::connection& _connection;
    };

    class test_table_person {
    public:
        explicit test_table_person(pqxx::connection& connection);
        ~test_table_person();

    private:
        pqxx::connection& _connection;
    };

    class test_schema {
    public:
        explicit test_schema(pqxx::connection& connection);
        ~test_schema();

    private:
        pqxx::connection&                  _connection;
        std::unique_ptr<test_table_points> _points;
        std::unique_ptr<test_table_person> _person;
    };

    class test_database {
    public:
        explicit test_database(pqxx::connection& connection);
        ~test_database() = default;

    private:
        pqxx::connection& _connection;
        test_schema       _schema;
    };

}  // namespace async_pqxx::test
