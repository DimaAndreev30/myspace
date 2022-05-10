#pragma once

#include <libs/utils/assert.h>

#include <array>
#include <map>


// TODO: настроить себе нормальный компилятор для std=c++17 и доделать этот класс

namespace NMySpace::NPhan::NUtils::NPrivate {
    
    class TSparseBuilder;
    
}

namespace NMySpace::NPhan::NUtils {
    
    template<class T, class TIndex, class TBuilder = NPrivate::TSparseBuilder>
    class TSparse {
    public:
        using TData = std::map<TIndex, T>;
        
    public:
        template <class... U>
        TSparse(U&&... args)
            : Size_(TBuilder::BuildSize(args...))
            , Data_(TBuilder::BuildData({}, std::forward<U>(args)...))
        {
        }
        
        explicit TSparse(TIndex size, T&& zero = {})
            : Size_(size)
            , Zero_(std::forward(zero))
        {
        }
        
        TSparse(const TSparse& value) = default;
        TSparse(TSparse&& value) = default;
        
        TSparse& operator=(const TSparse& value) {
            if (&value == this) {
                return *this;
            }
            
            EnsureSize(value.Size());
            EnsureZero(value.Zero());
            
            Data_ = value.Data_;
            
            return *this;
        }
        
        TSparse& operator=(TSparse&& value) {
            if (&value == this) {
                return *this;
            }
            
            EnsureSize(value.Size());
            EnsureZero(value.Zero());
            
            Data_ = std::move(value.Data_);
            
            return *this;
        }
        
        template<class U>
        TSparse& operator=(U&& value) {
            EnsureSize(TBuilder::BuildSize(value));
            
            Data_ = TBuilder::BuildData(Zero_, std::forward<U>(value));
            
            return *this;
        }
        
    public:
        TIndex Size() const {
            return Size_;
        }
        
        const T& Zero() const {
            return Zero_;
        }
    
        T& operator[](TIndex i) {
            EnsureIndex(i);
            
            return Data_.emplace(i, Zero_).first->second;
        }
        
        const T& operator[](TIndex i) const {
            EnsureIndex(i);
            
            auto it = Data_.find(i);
            return it == Data_.cend() ? Zero_ : it->second;
        }
        
    public:
        typename TData::iterator begin() {
            return Data_.begin();
        }
        typename TData::const_iterator begin() const {
            return Data_.cbegin();
        }
        typename TData::const_iterator cbegin() const {
            return Data_.cbegin();
        }
        
        typename TData::iterator end() {
            return Data_.end();
        }
        typename TData::const_iterator end() const {
            return Data_.cend();
        }
        typename TData::const_iterator cend() const {
            return Data_.cend();
        }
        
        typename TData::iterator rbegin() {
            return Data_.rbegin();
        }
        typename TData::const_iterator rbegin() const {
            return Data_.crbegin();
        }
        typename TData::const_iterator crbegin() const {
            return Data_.crbegin();
        }
        
        typename TData::iterator rend() {
            return Data_.rend();
        }
        typename TData::const_iterator rend() const {
            return Data_.crend();
        }
        typename TData::const_iterator crend() const {
            return Data_.crend();
        }
        
    private:
        void EnsureIndex(TIndex i) const {
            MS_ENSURE_EX(
                i < Size_, 
                NMySpace::NUtils::TOutOfRangeException, 
                "got index " << i << " >= " << Size_);
        }
        
        void EnsureSize(TIndex size) const {
            MS_ENSURE_EX(
                size == Size_, 
                NMySpace::NUtils::TBadValueException, 
                "got size " << size << " != " << Size_);
        }
        
        void EnsureZero(const T& zero) const {
            MS_ENSURE_EX(
                zero == Zero_, 
                NMySpace::NUtils::TBadValueException, 
                "");
        }
        
    private:
        const T Zero_ = {};
        const TIndex Size_ = {};
        TData Data_;
    };
    
    template<class T>
    using TSparseRow = TSparse<T, size_t>;
    
}

namespace NMySpace::NPhan::NUtils::NPrivate {
    
    class TSparseBuilder {
    public:
        template<class T>
        static size_t BuildSize(const std::vector<T>& row) {
            return row.size();
        }
        
        template<class T>
        static std::map<size_t, T> BuildData(
            const T& zero, 
            const std::vector<T>& row
        ) {
            std::map<size_t, T> data{};
            
            for (size_t i = 0; i < row.size(); ++i) {
                if (row[i] == zero) {
                    continue;
                }
                data[i] = row[i];
            }
            return data;
        }
        
        template<class T>
        static std::map<size_t, T> BuildData(
            const T& zero, 
            std::vector<T>&& row
        ) {
            std::map<size_t, T> data{};
            
            for (size_t i = 0; i < row.size(); ++i) {
                if (row[i] == zero) {
                    continue;
                }
                data[i] = std::move(row[i]);
            }
            return data;
        }
    };
    
}
