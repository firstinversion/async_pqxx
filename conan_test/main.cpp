#include <boost/asio/io_context.hpp>
#include <boost/asio/spawn.hpp>

#include <async_pqxx/manager.hpp>

int main() {
    async_pqxx::manager     manager(4, "host=localhost port=5432");
    boost::asio::io_context ioc;
    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto result = manager.exec1("SELECT 1;", yield);
        assert(result[0].as<int>() == 1);
    });
    ioc.run();

    return 0;
}
