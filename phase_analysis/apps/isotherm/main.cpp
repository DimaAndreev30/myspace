#include "src/plot_by_V.h"
#include "src/plot_by_P.h"

#include <phase_analysis/libs/cubic_eos/constants.h>

#include <phase_analysis/libs/cubic_eos/RK.h>
#include <phase_analysis/libs/cubic_eos/SRK.h>
#include <phase_analysis/libs/cubic_eos/PR.h>

#include <string>
#include <iostream>
#include <fstream>


using namespace MySpace::PhAn;


const PureSubstanceProps C1_METHANE{
    .m = 16.043, 
    .Pc = 45.992, 
    .Vc = 0.0986, 
    .Tc = 190.564, 
    .w = 0.0114, 
    .name = "C1"
};
       
const PureSubstanceProps C10_nDECANE{
    .m = 142.282, 
    .Pc = 21.030, 
    .Vc = 0.6098, 
    .Tc = 617.700, 
    .w = 0.4880, 
    .name = "C10"
};
        
int main(int argc, char* argv[]) {
    std::ofstream file1("output1.txt");
    createPVCurveByV(file1, C10_nDECANE, EoS::RKInterface{}, EoS::T_ZERO + 200, 1000);
    
    std::ofstream file2("output2.txt");
    createPVCurveByP(file2, C10_nDECANE, EoS::PRInterface{}, EoS::T_ZERO + 200, 1000, 0.0, 100.0);
    
    return 0;
}
