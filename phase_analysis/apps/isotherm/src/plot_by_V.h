#pragma once

#include <phase_analysis/libs/properties/pure_substance.h>
#include <phase_analysis/libs/cubic_eos/interface.h>

#include <ostream>


namespace MySpace::PhAn {
    
    // Построение изотермы P(V) по кубическому уравнению состояния типа Ван-дер-Ваальса.
    // Вывод в формате "V P dP Z po" - объем, давление, первая производная, Z-factor, плотность.
    // Если была найдена двухфазная область, то в выводе будет две кривых - первая жидкая, вторая газовая.
    
    // Параметры на вход предполагаются в обычной (размерной) форме.
    
    // Флаг isAuto задает способ определения области графика:
    // если isAuto = false, то график строится в пределах [V1, V2], заданных через аргументы функции,
    // иначе значения V1, V2 расчитываются автоматически, стараясь поймать характерную область изотермы.
    
    void createPVCurveByV(std::ostream& out,
                          const EoS::Params& params,
                          const EoS::Interface& eos,
                          double T,
                          int N, bool isAuto = true, double V1 = 0.0, double V2 = 0.0);
                          
    void createPVCurveByV(std::ostream& out,
                          const PureSubstanceProps& props,
                          const EoS::Interface& eos,
                          double T,
                          int N, bool isAuto = true, double V1 = 0.0, double V2 = 0.0);
    
} // namespace MySpace::PhAn;