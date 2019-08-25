// Copyright Takatoshi Kondo 2015
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(MQTT_EXCEPTION_HPP)
#define MQTT_EXCEPTION_HPP

#include <exception>
#include <sstream>

#include <boost/system/error_code.hpp>

#include <mqtt/namespace.hpp>
#include <mqtt/utf8encoded_strings.hpp>

namespace MQTT_NS {

struct protocol_error : std::exception {
    virtual char const* what() const noexcept {
        return "protocol error";
    }
};

struct remaining_length_error : std::exception {
    virtual char const* what() const noexcept {
        return "remaining length error";
    }
};

struct variable_length_error : std::exception {
    virtual char const* what() const noexcept {
        return "variable length error";
    }
};

struct utf8string_length_error : std::exception {
    virtual char const* what() const noexcept {
        return "utf8string length error";
    }
};

struct utf8string_contents_error : std::exception {
    utf8string_contents_error(utf8string::validation r):r(r) {}
    virtual char const* what() const noexcept {
        if (r == utf8string::validation::ill_formed) {
            return "utf8string ill_formed";
        }
        else {
            BOOST_ASSERT(r == utf8string::validation::well_formed_with_non_charactor);
            return "utf8string well_formed_with_non_charactor";
        }
    }
    utf8string::validation r;
};

struct will_message_length_error : std::exception {
    virtual char const* what() const noexcept {
        return "will message length error";
    }
};

struct password_length_error : std::exception {
    virtual char const* what() const noexcept {
        return "password length error";
    }
};

struct bytes_transferred_error : std::exception {
    bytes_transferred_error(std::size_t expected, std::size_t actual) {
        std::stringstream ss;
        ss << "bytes transferred error. expected: " << expected << " actual: " << actual;
        msg = ss.str();
    }
    virtual char const* what() const noexcept {
        return msg.data();
    }
    std::string msg;
};

struct read_bytes_transferred_error : bytes_transferred_error {
    read_bytes_transferred_error(std::size_t expected, std::size_t actual)
        :bytes_transferred_error(expected, actual) {
        msg = "[read] " + msg;
    }
};

struct write_bytes_transferred_error : bytes_transferred_error {
    write_bytes_transferred_error(std::size_t expected, std::size_t actual)
        :bytes_transferred_error(expected, actual) {
        msg = "[write] " + msg;
    }
};

struct packet_id_exhausted_error : std::exception {
    virtual char const* what() const noexcept {
        return "packet_id exhausted error";
    }
};

struct property_parse_error : std::exception {
    virtual char const* what() const noexcept {
        return "property parse error";
    }
};

struct property_length_error : std::exception {
    virtual char const* what() const noexcept {
        return "property length error";
    }
};

} // namespace MQTT_NS

#endif // MQTT_EXCEPTION_HPP
