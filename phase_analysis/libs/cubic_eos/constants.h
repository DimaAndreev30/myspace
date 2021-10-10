#pragma once


namespace MySpace::PhAn::EoS {
    
    // Универсальная газовая постоянная.
    // Размерности [P] = Bar, [V] = m3/Kmol, [T] = K
    extern const double R_CONST;

    // Ноль цельсия в Кельвинах.
    extern const double T_ZERO;

    // Коэффициенты для параметров кубических УРС Ван-дер-Ваальсовского типа.
    extern const double OmegaA0_RK,  OmegaB0_RK;
    extern const double OmegaA0_SRK, OmegaB0_SRK;
    extern const double OmegaA0_PR,  OmegaB0_PR;

    // Корень из двух, просто потому что он очень часто нужен.
    extern const double SQRT_TWO;

    // Коэффициенты на основе ацентрического фактора.
    double getSRK_M (double w);
    double getPR_M  (double w);
    
} // namespace MySpace::PhAn::EoS;