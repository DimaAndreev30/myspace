#include "src/FD_by_P.h"
#include "src/FD_along_c.h"

#include <phase_analysis/libs/cubic_eos/constants.h>
#include <phase_analysis/libs/cubic_eos/RK.h>
#include <phase_analysis/libs/cubic_eos/SRK.h>
#include <phase_analysis/libs/cubic_eos/PR.h>

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace MySpace::PhAn;

        
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
        .m = 72.149,
        .Pc = 32.156, 
        .Vc = 0.3110, 
        .Tc = 469.700, 
        .w = 0.2510, 
        .name = "C5"
    });
    components.push_back(PureSubstanceProps{
        .m = 30.069,
        .Pc = 48.718, 
        .Vc = 0.1456, 
        .Tc = 305.330, 
        .w = 0.0993, 
        .name = "C2"
    });
    
    auto k = std::make_shared<std::vector<std::vector<double>>>(
        components.size(), 
        std::vector<double>(components.size()));
    (*k)[0][1] = (*k)[1][0] = 0.0212;
    (*k)[0][2] = (*k)[2][0] = 0.0026;
    (*k)[1][2] = (*k)[2][1] = 0.0090;
    
    auto eos = std::make_shared<EoS::RKInterface>();
    
    std::ofstream file("output.txt");
    createFDAlongC(file, components, eos, k, EoS::T_ZERO + 37.8, 133,
                   {0.7, 0.3, 0.0}, {0.4, 0.0, 0.6}, 5000);


    return 0;
}
