#pragma once


namespace NMySpace::NPhan::NCubicEoS {
    
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
    double GetSRK_M(double w);
    double GetPR_M(double w);
    
    double ToZFactor(double V, double P, double T);
    double FromZFactor(double Z, double P, double T);
    
}
