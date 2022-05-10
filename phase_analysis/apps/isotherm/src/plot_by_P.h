#pragma once

#include <phase_analysis/libs/cubic_eos/eos.h>
#include <phase_analysis/libs/properties/pure_substance.h>

#include <ostream>


namespace NMySpace::NPhan {
    
    // Функция для отладки решения кубического уравнения типа Ван-дер-Ваальса:
    // на заданном диапазоне решает его относительно объема для заданного вещества.
    // Вывод в формате "P Z V status" - давление, Z-factor, вычисленный объем, статус найденного решения.
    // Если была найдена двухфазная область, то в выводе будет две кривых - первая жидкая, вторая газовая.
    
    void CreatePVCurveByP(std::ostream& out,
                          const NCubicEoS::TDimlessParamsWOPressure& p,
                          const NCubicEoS::TCubicEoS& eos,
                          double T,
                          int N, double P1, double P2);
                          
    void CreatePVCurveByP(std::ostream& out,
                          const TPureSubstanceProps& props,
                          const NCubicEoS::TCubicEoS& eos,
                          double T,
                          int N, double P1, double P2);
    
}
