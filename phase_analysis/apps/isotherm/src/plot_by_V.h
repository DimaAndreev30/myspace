#pragma once

#include <phase_analysis/libs/cubic_eos/eos.h>
#include <phase_analysis/libs/properties/pure_substance.h>

#include <ostream>


namespace NMySpace::NPhan {
    
    // Построение изотермы P(V) по кубическому уравнению состояния типа Ван-дер-Ваальса.
    // Вывод в формате "V P dP Z po" - объем, давление, первая производная, Z-factor, плотность.
    
    // Флаг isAuto задает способ определения области графика:
    // если isAuto = false, то график строится в пределах [V1, V2], заданных через аргументы функции,
    // иначе значения V1, V2 расчитываются автоматически, стараясь поймать характерную область изотермы.
    
    void createPVCurveByV(std::ostream& out,
                          const NEoS::TParams& p,
                          const NEoS::TCubicEoS& eos,
                          double T,
                          int N, bool isAuto = true, double V1 = 0.0, double V2 = 0.0);
                          
    void createPVCurveByV(std::ostream& out,
                          const TPureSubstanceProps& props,
                          const NEoS::TCubicEoS& eos,
                          double T,
                          int N, bool isAuto = true, double V1 = 0.0, double V2 = 0.0);
    
}
