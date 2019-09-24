#pragma once

#include <async_pqxx/manager.hpp>
#include <pqxx/connection>
#include <pqxx/transaction>

namespace async_pqxx::test {

    class table_points {
    public:
        explicit table_points(pqxx::connection& connection, pqxx::work& create);
        ~table_points();

    private:
        pqxx::connection& _connection;
    };

    class table_person {
    public:
        explicit table_person(pqxx::connection& connection, pqxx::work& create);
        ~table_person();

    private:
        pqxx::connection& _connection;
    };

    class schema {
    public:
        explicit schema(pqxx::connection& connection);
        ~schema();

    private:
        pqxx::connection&                  _connection;
        std::unique_ptr<table_points> _points;
        std::unique_ptr<table_person> _person;
    };

    class database {
    public:
        database();
        explicit database(const char* connection_string);
        ~database();

    private:
        pqxx::connection             _connection;
        std::unique_ptr<schema> _schema;
    };

    async_pqxx::manager get_test_manager();

}  // namespace async_pqxx::test
