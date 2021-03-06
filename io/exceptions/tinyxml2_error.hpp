#ifndef IO__TINYXML2_ERROR_HPP
#define IO__TINYXML2_ERROR_HPP

#include <stdexcept>
#include <string>

#include "../../lib/tinyxml2/tinyxml2.hpp"

namespace tinyxml2
{
    class TinyXML2Error : public std::exception
    {
        private:    // Attributes
            std::string _message;

        public:     // Public methods
            TinyXML2Error(const char* message);
            TinyXML2Error(std::string message);
            TinyXML2Error(XMLError err);
            TinyXML2Error(XMLError err, const char* message);
            TinyXML2Error(XMLError err, std::string message);
            const char* what() const noexcept;
    };

    std::string xmlErrorToString(XMLError err);
}

#endif//IO__TINYXML2_ERROR_HPP