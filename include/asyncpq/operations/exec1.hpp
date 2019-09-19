#pragma once

#include <boost/asio/post.hpp>
#include <pqxx/transaction>
#include <string>

namespace asyncpq::internal {

    struct exec1_impl {
        boost::asio::io_context& _execute_ioc;
        std::string              _query;

        template <typename Token>
        decltype(auto) operator()(Token&& token) const {
            auto work_guard = boost::asio::make_work_guard(boost::asio::get_associated_executor(token));
            boost::asio::post(_execute_ioc,
                              [query = std::move(_query),  // TODO: clang-tidy claims this is impotent. How do we ensure
                                                           // that the _query is in fact moved and not copied.
                               token      = std::forward<Token>(token),
                               work_guard = std::move(work_guard)]() mutable {
                                  pqxx::work w(asyncpq::this_thread::connection());
                                  auto       row = w.exec1(query);
                                  w.commit();

                                  boost::asio::post(
                                      boost::asio::get_associated_executor(token),
                                      [token = std::forward<Token>(token), row = row]() mutable { token({}, row); });
                              });
        }
    };

}  // namespace asyncpq::internal
