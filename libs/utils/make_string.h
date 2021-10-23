#pragma once

#include <string>
#include <sstream>


namespace MySpace::Utility {
    
    class MakeString {
    public:
        template<class T>
        MakeString& operator<< (const T& arg) {
            stream_ << arg;
            return *this;
        }
        
        std::string asString() const {
            return stream_.str();
        }
        
        operator std::string() const {
            return asString();
        }
        
    protected:
        std::stringstream stream_;
    };

} // namespace MySpace::Utility;