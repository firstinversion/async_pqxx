#include <boost/asio/io_context.hpp>
#include <boost/asio/spawn.hpp>

#include <async_pqxx/manager.hpp>

const char* default_connection_string() {
    static const char* default_str = "host=localhost port=5432";
    char*              provided_str;
    provided_str = getenv("ASYNC_PQXX_TEST_DATABASE");

    spdlog::info("DATABASE CONNECTION STRING: {}", provided_str ? provided_str : default_str);
    if (provided_str)
        return provided_str;
    else
        return default_str;
}

int main() {
    async_pqxx::manager     manager(4, default_connection_string());
    boost::asio::io_context ioc;
    boost::asio::spawn(ioc, [&](boost::asio::yield_context yield) {
        auto result = manager.async_exec1("SELECT 1;", yield);
        assert(result[0].as<int>() == 1);
    });
    ioc.run();

    return 0;
}
