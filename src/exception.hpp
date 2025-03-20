#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP


#include <string>
#include <cstring>
#include <exception>


using std::string;
using std::exception;

namespace MyExceptions
{
    class ErrorAnswerUser : public exception
    {
        public:
            ErrorAnswerUser() noexcept = default;

            ErrorAnswerUser(const char *e) noexcept : msg(e)
            { }

            ErrorAnswerUser(const ErrorAnswerUser &other) noexcept : msg(other.msg)
            { }

            const char *what(void) const noexcept override
            {
                return msg.c_str();                
            }

            virtual ~ErrorAnswerUser() noexcept
            { }
        
        protected:
            std::string msg;
    };

    class ErrorAnswerAdmin : public ErrorAnswerUser
    {
        public:
            ErrorAnswerAdmin(const char *e) noexcept : ErrorAnswerUser(e)
            { }

            ErrorAnswerAdmin(const ErrorAnswerAdmin & other) noexcept : ErrorAnswerUser(other)
            { }

            virtual ~ErrorAnswerAdmin() noexcept 
            { }

    };
};


#endif
