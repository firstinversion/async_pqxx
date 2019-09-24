#pragma once

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/use_future.hpp>
#include <cstdint>
#include <pqxx/connection>
#include <pqxx/row>
#include <pqxx/transaction>
#include <spdlog/spdlog.h>
#include <thread>
#include <type_traits>
#include <vector>

#include <async_pqxx/operations/exec_functor.hpp>
#include <async_pqxx/thread_connection.hpp>

namespace async_pqxx {

    class manager {
    public:
        manager(std::size_t connection_count, const std::string& connection_string)
            : _connection_count(connection_count)
            , _hold_open(boost::asio::make_work_guard(_io_context)) {
            for (std::size_t i = 0; i < _connection_count; ++i) {
                _execution_threads.emplace_back([& ioc = _io_context, connection_string = connection_string]() mutable {
                    try {
                        this_thread::connect(connection_string);
                    } catch (const std::exception& e) {
                        spdlog::error("async_pqxx: {}", e.what());
                    }
                    ioc.run();
                });
            }
        }

        ~manager() {
            _hold_open.reset();
            std::for_each(_execution_threads.begin(), _execution_threads.end(), [](auto& t) { t.join(); });
        }

        manager(manager&)  = delete;
        manager(manager&&) = delete;
        manager& operator=(manager&) = delete;
        manager& operator=(manager&&) = delete;

        template <typename FuncRet, typename Token>
        decltype(auto) exec_functor(std::function<FuncRet(pqxx::connection&)>&& functor, Token&& token) {
            auto work_guard = boost::asio::make_work_guard(boost::asio::get_associated_executor(token));
            return boost::asio::async_initiate<Token, void(boost::system::error_code, FuncRet)>(
                internal::exec_functor_impl<decltype(work_guard), FuncRet>{
                    _io_context,
                    std::move(work_guard),
                    std::forward<std::function<FuncRet(pqxx::connection&)>>(functor)},
                std::forward<Token>(token));
        }

        template <typename Token>
        decltype(auto) async_exec1(std::string query, Token&& token) {  // NOLINT(performance-unnecessary-value-param)
            return exec_functor<pqxx::row>(
                [query = std::move(query)](pqxx::connection& connection) mutable {
                    pqxx::work w(connection);
                    auto       res = w.exec1(query);
                    w.commit();
                    return res;
                },
                token);
        }

        decltype(auto) exec1(std::string query) {  // NOLINT(performance-unnecessary-value-param)
            return async_exec1(std::move(query), boost::asio::use_future).get();
        }

        template <typename Token>
        decltype(auto) async_exec(std::string query, Token&& token) {  // NOLINT(performance-unnecessary-value-param)
            return exec_functor<pqxx::result>(
                [query = std::move(query)](pqxx::connection& connection) mutable {
                    pqxx::work w(connection);
                    auto       res = w.exec(query);
                    w.commit();
                    return res;
                },
                std::forward<Token>(token));
        }

        decltype(auto) exec(std::string query) {  // NOLINT(performance-unnecessary-value-param)
            return async_exec(std::move(query), boost::asio::use_future).get();
        }

        template <typename Token>
        decltype(auto) async_exec0(std::string query, Token&& token) {  // NOLINT(performance-unnecessary-value-param)
            return exec_functor<pqxx::result>(
                [query = std::move(query)](pqxx::connection& connection) mutable {
                    pqxx::work w(connection);
                    auto       res = w.exec0(query);
                    w.commit();
                    return res;
                },
                std::forward<Token>(token));
        }

        decltype(auto) exec0(std::string query) {  // NOLINT(performance-unnecessary-value-param)
            return async_exec0(std::move(query), boost::asio::use_future).get();
        }

    private:
        std::size_t                                                              _connection_count;
        boost::asio::io_context                                                  _io_context;
        boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _hold_open;
        std::vector<std::thread>                                                 _execution_threads;
    };

}  // namespace async_pqxx
