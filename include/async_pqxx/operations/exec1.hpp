#pragma once

#include <boost/asio/post.hpp>
#include <pqxx/transaction>
#include <string>

#include <async_pqxx/thread_connection.hpp>

namespace async_pqxx::internal {

    template <typename WorkGuard>
    struct exec1_impl {
        boost::asio::io_context& _execute_ioc;
        WorkGuard                _work_guard;
        std::string              _query;

        template <typename Token>
        decltype(auto) operator()(Token&& token) const {
            boost::asio::post(_execute_ioc, [&, token = std::forward<Token>(token)]() mutable {
                pqxx::work w(async_pqxx::this_thread::connection());
                auto       row = w.exec1(_query);
                w.commit();

                boost::asio::post(
                    boost::asio::get_associated_executor(token),
                    [token = std::forward<Token>(token), row = std::move(row)]() mutable { token({}, row); });
            });
        }
    };

}  // namespace async_pqxx::internal
