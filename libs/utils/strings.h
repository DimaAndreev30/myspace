#pragma once

#include "utils.h"

#include <ostream>
#include <sstream>
#include <string>


// TODO: reserve

namespace NMySpace::NUtils {
    class TStringBuilder;
}

namespace NMySpace::NUtils::NPrivate {
    
    template <typename U>
    TStringBuilder&& Append(TStringBuilder&& output, U&& u) {
        static_assert(!std::is_same_v<U, char>, "i8 serialized as char, not number");
        static_assert(!std::is_same_v<U, unsigned char>, "ui8 serialized as char, not number");
        return std::move(output) << std::forward<U>(u);
    }

    template <class U, class... V>
    TStringBuilder&& Append(TStringBuilder&& output, U&& u, V&&... v) {
        return Append(Append(std::move(output), std::forward<U>(u)), std::forward<V>(v)...);
    }
    
}

namespace NMySpace::NUtils {
    
    class TStringBuilder: public TMoveOnly {
    public:
        template<class T>
        TStringBuilder&& operator<< (T&& arg) {
            Stream_ << std::forward<T>(arg);
            return std::move(*this);
        }
        
        std::string AsString() && {
            std::string result = std::move(Stream_).str();
            Stream_ = std::stringstream();
            return result;
        }
        
        operator std::string() && {
            return std::move(*this).AsString();
        }
        
    protected:
        std::stringstream Stream_;
    };
    
    template <class... V>
    std::string CreateString(V&&... v) {
        return NPrivate::Append(TStringBuilder(), std::forward<V>(v)...);
    }

}

std::ostream& operator<< (std::ostream& out, NMySpace::NUtils::TStringBuilder&& builder);
