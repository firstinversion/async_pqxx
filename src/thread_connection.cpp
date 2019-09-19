#include <asyncpq/thread_connection.hpp>

namespace asyncpq::this_thread {

    thread_local std::unique_ptr<pqxx::connection> _connection;

    pqxx::connection& connection() { return *_connection; }

    void connect(const std::string& connection_string) {
        _connection = std::make_unique<pqxx::connection>(connection_string);
    }

    void disconnect() { _connection.reset(); }

}  // namespace asyncpq::this_thread
