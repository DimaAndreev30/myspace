#pragma once

#include "strings.h"

#include <exception>
#include <string>


namespace NMySpace::NUtils {
    
    class TException: public std::exception {
    public:
        template <class... T>
        TException(T&&... what)
            : What_(CreateString(std::forward<T>(what)...))
        {
        }
        
        virtual const std::string& What() const noexcept {
            return What_;
        }
        
        const char* what() const noexcept override final {
            return What().c_str();
        }
        
    private:
        std::string What_;
    };
    
    #define EXCEPTION_WITH_PREFIX(TYPE) \
    class T##TYPE##Exception: public TException { \
    public: \
        template <class... T> \
        T##TYPE##Exception(T&&... what) \
            : TException(#TYPE ": ", std::forward<T>(what)...) {} \
    };
    
    EXCEPTION_WITH_PREFIX(EnsureFailed)
    EXCEPTION_WITH_PREFIX(OutOfRange)
    EXCEPTION_WITH_PREFIX(BadValue)
    EXCEPTION_WITH_PREFIX(BadTest)
    
    #undef EXCEPTION_WITH_PREFIX
    
}
