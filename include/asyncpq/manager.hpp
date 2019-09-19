#pragma once

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <cstdint>
#include <pqxx/connection>
#include <pqxx/row>
#include <thread>
#include <vector>

#include "thread_connection.hpp"
#include <asyncpq/operations/exec1.hpp>

namespace asyncpq {

    class manager {
    public:
        manager(std::size_t connection_count, const std::string& connection_string)
            : _connection_count(connection_count) {
            for (std::size_t i = 0; i < _connection_count; ++i) {
                _execution_threads.emplace_back([& ioc = _io_context, connection_string = connection_string]() mutable {
                    this_thread::connect(connection_string);
                    ioc.run();
                });
            }
        }

        ~manager() {
            std::for_each(_execution_threads.begin(), _execution_threads.end(), [](auto& t) { t.join(); });
        }

        manager(manager&)  = delete;
        manager(manager&&) = delete;
        manager& operator=(manager&) = delete;
        manager& operator=(manager&&) = delete;

        template <typename Token>
        decltype(auto) exec1(std::string query, Token&& token) {
            return boost::asio::async_initiate<Token, void(boost::system::error_code, pqxx::row)>(
                internal::exec1_impl{_io_context, std::move(query)}, token);
        }

    private:
        std::size_t              _connection_count;
        boost::asio::io_context  _io_context;
        std::vector<std::thread> _execution_threads;
    };

}  // namespace asyncpq
