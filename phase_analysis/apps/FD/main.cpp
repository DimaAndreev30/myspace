#include <phase_analysis/libs/cubic_eos/mixture/interface.h>

#include <phase_analysis/libs/cubic_eos/RK.h>
#include <phase_analysis/libs/cubic_eos/SRK.h>
#include <phase_analysis/libs/cubic_eos/PR.h>

#include <phase_analysis/libs/phase_equilibrium/wilson.h>
#include <phase_analysis/libs/phase_equilibrium/solver.h>

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace MySpace::PhAn;


void createFD(
    std::ofstream& out,
    const std::vector<PureSubstanceProps>& components,
    const std::shared_ptr<std::vector<std::vector<double>>>& k,
    const std::vector<double>& z,
    const std::shared_ptr<EoS::Interface>& eos,
    double T, 
    double dP=1e-1, double P1=0.0, double P2=1e3)
{
    int N = components.size();
    PhEqSettings setts;
    
    EoS::CubicEoSMixture mixture(T, eos);
    for (const auto& comp : components) {
        mixture.addComponent(comp);
    }
    mixture.setK(k);
    
    std::vector<double> kValues(N);
    // Задать начальное приближение (пока расчитываю, что последний элемент самый тяжелый)
    double P = computePsWilson(components.back(), T)*(1 + 1e-1);
    for (int i = 0; i < N; i++) {
        kValues[i] = computePsWilson(components[i], T)/P;
    }
    
    if (P < P1) {
        P = P1;
    }
    
    out << "# P N V L ZL VL ZV VV [x_i y_i K_i]\n";
    
    for (; P < P2; P += dP) {
        mixture.setPressure(P);
        PhEqResult res = computePhEq(setts, mixture, z, kValues);
        
        if (res.status == PhEqResult::NOT_CONVERGE) {
            break;
        }
        
        out << P << ' ' << res.iterationsNumber 
            << ' ' << res.compos.V << ' ' << res.compos.L << ' '
            << mixture.ZL << ' '<< eos->computeFromZFactor(mixture.ZL, T, P) << ' '
            << mixture.ZV << ' '<< eos->computeFromZFactor(mixture.ZV, T, P) << ' ';
        for (int i = 0; i < N; i++) {
            out << res.compos.x[i] << ' ' << res.compos.y[i] << ' '
                << res.compos.y[i]/res.compos.x[i] << ' ';
        }
        out << std::endl;
    }
}
        
int main(int argc, char* argv[]) {
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
    
    std::vector<double> z({0.1, 0.9});
    
    auto eos = std::make_shared<EoS::PRInterface>();
    
    std::ofstream file("output.txt");
    createFD(file, components, k, z, eos, EoS::T_ZERO);
    
    return 0;
}