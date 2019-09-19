#pragma once

#include <pqxx/connection>

namespace asyncpq::this_thread {

    pqxx::connection& connection();

    void connect(const std::string& connection_string);
    void disconnect();

}  // namespace asyncpq::this_thread
