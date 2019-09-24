#pragma once

#include <boost/asio/post.hpp>

#include <async_pqxx/thread_connection.hpp>

namespace async_pqxx::internal {

    template <typename WorkGuard, typename FuncRet>
    struct exec_functor_impl {
        boost::asio::io_context&                  _execute_ioc;
        WorkGuard                                 _work_guard;
        std::function<FuncRet(pqxx::connection&)> _functor;

        template <typename Token>
        decltype(auto) operator()(Token&& token) {
            boost::asio::post(_execute_ioc,
                              [token      = std::forward<Token>(token),
                               work_guard = std::forward<WorkGuard>(_work_guard),
                               functor = std::forward<std::function<FuncRet(pqxx::connection&)>>(_functor)]() mutable {
                                  auto result = functor(async_pqxx::this_thread::connection());
                                  boost::asio::post(boost::asio::get_associated_executor(token),
                                                    [token  = std::forward<Token>(token),
                                                     result = std::move(result)]() mutable { token({}, result); });
                              });
        }
    };

}  // namespace async_pqxx::internal
