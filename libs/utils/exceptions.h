#pragma once

#include <exception>
#include <string>


namespace NMySpace::NUtils {
    
    class TException : public std::exception {
    public:
        template <class T>
        TException(T&& what)
            : What_(std::forward<T>(what))
        {
        }
        
        const char* what() const noexcept {
            return What_.c_str();
        }
        
    private:
        std::string What_;
    };
    
}
