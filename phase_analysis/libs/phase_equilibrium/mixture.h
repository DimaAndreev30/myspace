#pragma once

#include <memory>
#include <vector>
#include <utility>


namespace NMySpace::NPhan::NPheq {
    
    class IMixture {
    public:
        explicit IMixture(size_t N): N_(N) {}
        virtual ~IMixture() = default;
        
    public:
        size_t N() const {
            return N_;
        }
        
        // Летучесть i-ой компоненты:
        virtual double Phi(size_t i) const = 0;
        
    private:
        const size_t N_ = 0;
    };
    
    // TODO: С таким подходом, в итерационном методе на каждой итерации 
    // создается / уничтожается массив phi. Имеет смысл оптимизировать
    
    class TSimpleMixtureHolder: public IMixture {
    public:
        explicit TSimpleMixtureHolder(std::vector<double>&& phi)
            : IMixture(phi.size())
            , Phi_(std::move(phi))
        {
        }
        
        double Phi(size_t i) const override {
            return Phi_[i];
        }
    
    private:
        const std::vector<double> Phi_;
    };
    
    class IMixtureFactory {
    public:
        enum ETrait {
            AsLiquid,
            AsVapor
        };
        
        enum EStatus {
            Ok,
            InvalidCompos
        };
        
    public:
        explicit IMixtureFactory(size_t N): N_(N) {}
        virtual ~IMixtureFactory() = default;
        
    public:
        size_t N() const {
            return N_;
        }
        
        virtual std::unique_ptr<IMixture> Build(
            const std::vector<double>& c, 
            ETrait trait) const = 0;
        
    private:
        const size_t N_ = 0;
    };
    
}
