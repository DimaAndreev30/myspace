#include "src/mixture_factory.h"

#include <phase_analysis/libs/cubic_eos/constants.h>

#include <phase_analysis/libs/cubic_eos/RK.h>
#include <phase_analysis/libs/cubic_eos/SRK.h>
#include <phase_analysis/libs/cubic_eos/PR.h>

#include <phase_analysis/libs/phase_equilibrium/solver.h>
#include <phase_analysis/libs/phase_equilibrium/wilson.h>

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace NMySpace::NPhan;


void CreateFD(
    std::ofstream& out,
    const std::shared_ptr<NCubicEoS::TCubicEoS>& eos,
    const std::vector<TPureSubstanceProps>& comps,
    double T, 
    const std::vector<std::vector<double>>& k,
    const std::vector<double>& z,
    double dP=1e-1, double P1=0.0, double P2=1e3)
{
    size_t N = comps.size();
    NPheq::TFlash::TSettings setts;
    
    TCubicEoSMixtureFactory factory(eos, comps, T, k);
    
    std::vector<double> kValues(N);
    double P = 0.0;
    for (int i = 0; i < N; i++) {
        kValues[i] = NPheq::ComputePsWilson(comps[i], T);
        if (P < kValues[i]) {
            P = kValues[i];
        }
    }
    P *= 1 + 1e-1;
    if (P < P1) {
        P = P1;
    }
    for (int i = 0; i < N; i++) {
        kValues[i] /= P;
    }
    
    out << "# P N V L ZL VL ZV VV [x_i y_i K_i]\n";
    
    for (; P < P2; P += dP) {
        factory.SetPressure(P);
        NPheq::TFlash::TResult res = NPheq::TFlash::Compute(setts, factory, z, kValues);
        
        if (res.Status == NPheq::TFlash::TResult::EStatus::NotConverge) {
            break;
        }
        
        out << P << ' ' << res.IterationsNumber 
            << ' ' << res.Compos.V << ' ' << res.Compos.L << ' '
            << factory.ZL << ' '<< NCubicEoS::FromZFactor(factory.ZL, P, T) << ' '
            << factory.ZV << ' '<< NCubicEoS::FromZFactor(factory.ZV, P, T) << ' ';
        for (int i = 0; i < N; i++) {
            out << res.Compos.x[i] << ' ' << res.Compos.y[i] << ' '
                << res.Compos.y[i]/res.Compos.x[i] << ' ';
        }
        out << std::endl;
    }
}

void CreateFDAlongC(
    std::ofstream& out,
    const std::shared_ptr<NCubicEoS::TCubicEoS>& eos,
    const std::vector<TPureSubstanceProps>& comps,
    double T, double P,
    const std::vector<std::vector<double>>& k,
    const std::vector<double>& from,
    const std::vector<double>& to,
    size_t number)
{
    size_t N = comps.size();
    NPheq::TFlash::TSettings setts;
    
    TCubicEoSMixtureFactory factory(eos, comps, T, k, P);
    
    std::vector<double> kValues(N);
    for (int i = 0; i < N; i++) {
        kValues[i] = NPheq::ComputePsWilson(comps[i], T)/P;
    }
    
    out << "# P N V L ZL VL ZV VV [x_i y_i K_i]\n";
    
    for (size_t i = 1; i < number; ++i) {
        std::vector<double> z(N);
        for (size_t j = 0; j < N; ++j) {
            z[j] = ((number - i)*from[j] + i*to[j])/number;
        }
        
        NPheq::TFlash::TResult res = NPheq::TFlash::Compute(setts, factory, z, kValues);
        
        if (res.Status == NPheq::TFlash::TResult::EStatus::NotConverge) {
            break;
        }
        
        out << P << ' ' << res.IterationsNumber 
            << ' ' << res.Compos.V << ' ' << res.Compos.L << ' '
            << factory.ZL << ' '<< NCubicEoS::FromZFactor(factory.ZL, P, T) << ' '
            << factory.ZV << ' '<< NCubicEoS::FromZFactor(factory.ZV, P, T) << ' ';
        for (int i = 0; i < N; i++) {
            out << res.Compos.x[i] << ' ' << res.Compos.y[i] << ' '
                << res.Compos.y[i]/res.Compos.x[i] << ' ';
        }
        out << std::endl;
    }
}
        
int main(int argc, char* argv[]) {
    /*
    std::vector<PureSubstanceProps> components;
    components.push_back(PureSubstanceProps{
        .m = 16.043, 
        .Pc = 45.992, 
        .Vc = 0.0986, 
        .Tc = 190.564, 
        .w = 0.0114, 
        .name = "C1"
    });
    components.push_back(PureSubstanceProps{
        .m = 142.282, 
        .Pc = 21.030, 
        .Vc = 0.6098, 
        .Tc = 617.700, 
        .w = 0.4880, 
        .name = "C10"
    });
    
    auto k = std::make_shared<std::vector<std::vector<double>>>(
        components.size(), 
        std::vector<double>(components.size()));
    (*k)[0][1] = (*k)[1][0] = 0.0459;
    
    auto eos = std::make_shared<EoS::PRInterface>();
    
    std::ofstream file("output.txt");
    createFDByP(file, components, eos, k, EoS::T_ZERO);
    */
    
    /*
    std::vector<PureSubstanceProps> components;
    components.push_back(PureSubstanceProps{
        .m = 16.043, 
        .Pc = 45.992, 
        .Vc = 0.0986, 
        .Tc = 190.564, 
        .w = 0.0114, 
        .name = "C1"
    });
    components.push_back(PureSubstanceProps{
        .m = 142.282, 
        .Pc = 21.030, 
        .Vc = 0.6098, 
        .Tc = 617.700, 
        .w = 0.4880, 
        .name = "C10"
    });
    components.push_back(PureSubstanceProps{
        .m = 58.122, 
        .Pc = 37.960, 
        .Vc = 0.2549, 
        .Tc = 425.125, 
        .w = 0.2010, 
        .name = "C4"
    });
    
    auto k = std::make_shared<std::vector<std::vector<double>>>(
        components.size(), 
        std::vector<double>(components.size()));
    (*k)[0][1] = (*k)[1][0] = 0.0459;
    (*k)[0][2] = (*k)[2][0] = 0.0146;
    (*k)[1][2] = (*k)[2][1] = 0.0092;
    
    auto eos = std::make_shared<EoS::RKInterface>();
    
    std::ofstream file("output.txt");
    createFDAlongC(file, components, eos, k, EoS::T_ZERO + 137.8, 67,
                   {0.85, 0.15, 0.0}, {0.1, 0.0, 0.9}, 5000);
    */
    
    
    std::vector<TPureSubstanceProps> comps;
    comps.push_back(TPureSubstanceProps{
        .m = 16.043, 
        .Pc = 45.992, 
        .Vc = 0.0986, 
        .Tc = 190.564, 
        .w = 0.0114, 
        .Name = "C1"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 72.149,
        .Pc = 32.156, 
        .Vc = 0.3110, 
        .Tc = 469.700, 
        .w = 0.2510, 
        .Name = "C5"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 30.069,
        .Pc = 48.718, 
        .Vc = 0.1456, 
        .Tc = 305.330, 
        .w = 0.0993, 
        .Name = "C2"
    });
    
    auto k = std::vector<std::vector<double>>(
        comps.size(), 
        std::vector<double>(comps.size()));
    k[0][1] = k[1][0] = 0.0212;
    k[0][2] = k[2][0] = 0.0026;
    k[1][2] = k[2][1] = 0.0090;
    
    auto eos = std::make_shared<NCubicEoS::TRK>();
    
    std::ofstream file("output.txt");
    CreateFDAlongC(file, eos, comps, NCubicEoS::T_ZERO + 37.8, 33, k,
                   {0.5, 0.5, 0.0}, {0.0, 0.2, 0.8}, 5000);

    return 0;
}
