#pragma once

#include <phase_analysis/libs/properties/pure_substance.h>
#include <phase_analysis/libs/cubic_eos/interface.h>

#include <ostream>


namespace MySpace::PhAn {
    
    // Функция для отладки решения кубического уравнения типа Ван-дер-Ваальса:
    // на заданном диапазоне решает его относительно объема для заданного вещества.
    // Вывод в формате "P Z V status" - давление, Z-factor, вычисленный объем, статус найденного решения.
    // Если была найдена двухфазная область, то в выводе будет две кривых - первая жидкая, вторая газовая.
    
    // Параметры на вход полагаются рассчитанными по Interface::computeParamsTFactor
    
    void createPVCurveByP(std::ostream& out,
                          const EoS::Params& TFactor,
                          const EoS::Interface& eos,
                          double T,
                          int N, double P1, double P2);
                          
    void createPVCurveByP(std::ostream& out,
                          const PureSubstanceProps& props,
                          const EoS::Interface& eos,
                          double T,
                          int N, double P1, double P2);
    
} // namespace MySpace::PhAn;