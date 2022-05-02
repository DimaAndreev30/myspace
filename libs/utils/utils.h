#pragma once


namespace NMySpace::NUtils {
    
    class TMoveOnly {
    protected:
        TMoveOnly() = default;
        TMoveOnly(TMoveOnly&&) = default;
        TMoveOnly& operator= (TMoveOnly&&) = default;
        TMoveOnly(const TMoveOnly&) = delete;
        TMoveOnly& operator= (const TMoveOnly&) = delete;
    };
    
}
