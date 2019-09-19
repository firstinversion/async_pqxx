#pragma once

#include <pqxx/connection>

namespace async_pqxx::this_thread {

    pqxx::connection& connection();

    void connect(const std::string& connection_string);
    void disconnect();

}  // namespace async_pqxx::this_thread
