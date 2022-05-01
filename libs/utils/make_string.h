#pragma once

#include <sstream>
#include <string>


namespace NMySpace::NUtils {
    
    class TMakeString {
    public:
        template<class T>
        TMakeString&& operator<< (T&& arg) && {
            Stream_ << std::forward<T>(arg);
            return std::move(*this);
        }
        
        std::string asString() && {
            return Stream_.str();
        }
        
        operator std::string() && {
            return std::move(*this).asString();
        }
        
    protected:
        std::stringstream Stream_;
    };

}
