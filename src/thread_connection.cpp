#include <async_pqxx/thread_connection.hpp>

namespace async_pqxx::this_thread {

    thread_local std::unique_ptr<pqxx::connection> _connection;

    pqxx::connection& connection() { return *_connection; }

    void connect(const std::string& connection_string) {
        _connection = std::make_unique<pqxx::connection>(connection_string);
    }

    void disconnect() { _connection.reset(); }

}  // namespace async_pqxx::this_thread
