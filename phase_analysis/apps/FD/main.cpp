#include "src/mixture_factory.h"

#include <phase_analysis/libs/cubic_eos/constants.h>

#include <phase_analysis/libs/cubic_eos/RK.h>
#include <phase_analysis/libs/cubic_eos/SRK.h>
#include <phase_analysis/libs/cubic_eos/PR.h>

#include <phase_analysis/libs/phase_equilibrium/solver.h>
#include <phase_analysis/libs/phase_equilibrium/wilson.h>

#include <phase_analysis/libs/utils/math.h>

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
   
int main(int argc, char* argv[]) {
    std::vector<TPureSubstanceProps> comps;
    comps.push_back(TPureSubstanceProps{
        .m = 28.0135, 
        .Pc = 33.9439, 
        .Tc = 126.2, 
        .w = 0.04, 
        .Name = "N2"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 44.0098, 
        .Pc = 73.7646, 
        .Tc = 304.19, 
        .w = 0.225, 
        .Name = "C02"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 16.0429, 
        .Pc = 46.0015, 
        .Tc = 190.6, 
        .w = 0.008, 
        .Name = "C1"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 30.0698, 
        .Pc = 48.8387, 
        .Tc = 305.4, 
        .w = 0.098, 
        .Name = "C2"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 51.374, 
        .Pc = 39.8483, 
        .Tc = 394.521, 
        .w = 0.15845, 
        .Name = "C3-C4"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 75.7158, 
        .Pc = 33.1578, 
        .Tc = 483.845, 
        .w = 0.24871, 
        .Name = "C5-C6"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 98.134, 
        .Pc = 30.0487, 
        .Tc = 570.697, 
        .w = 0.32946, 
        .Name = "C7-C9"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 117.97, 
        .Pc = 29.7148, 
        .Tc = 611.278, 
        .w = 0.330049, 
        .Name = "C10-C14"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 158.431, 
        .Pc = 24.258, 
        .Tc = 684.722, 
        .w = 0.411079, 
        .Name = "C15-C19"
    });
    comps.push_back(TPureSubstanceProps{
        .m = 331.231, 
        .Pc = 16.5846, 
        .Tc = 754.265, 
        .w = 0.72855, 
        .Name = "C20-C45"
    });
    
    std::vector<double> z(comps.size());
    z[0] = 0.001988;
    z[1] = 0.022246;
    z[2] = 0.010392;
    z[3] = 0.061417;
    z[4] = 0.063418;
    z[5] = 0.081342;
    z[6] = 0.108514;
    z[7] = 0.187289;
    z[8] = 0.266403;
    z[9] = 0.196991;
    
    auto k = std::vector<std::vector<double>>(
        comps.size(), 
        std::vector<double>(comps.size()));
    for (size_t i = 0; i < comps.size(); ++i) {
        for (size_t j = 0; j < comps.size(); ++j) {
            k[i][j] = k[j][i] = 1 - NUtils::SignSavePow(
                2*std::sqrt(comps[i].Tc*comps[j].Tc)/(comps[i].Tc + comps[j].Tc),
                (z[i] + z[j])/2);
        }
    }
    
    auto eos = std::make_shared<NCubicEoS::TPR>();
    
    std::ofstream file("output.txt");
    CreateFD(file, eos, comps, NCubicEoS::T_ZERO + 100.0, k, z, 1e-1, 10, 30);

    return 0;
}
