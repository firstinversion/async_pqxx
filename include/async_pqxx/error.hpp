#pragma once

#include <boost/system/error_code.hpp>

namespace async_pqxx {

    boost::system::error_category& async_pqxx_category();

    boost::system::error_code make_async_pqxx_error(const std::string&);

}  // namespace async_pqxx
