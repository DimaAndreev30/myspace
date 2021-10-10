#pragma once

#include <string>


namespace MySpace::PhAn {
    
    // Структура для хранения справочной информации о чистом веществе.
    struct PureSubstanceProps {
        double m; // Молярная масса
        double Pc, Vc, Tc; // Критические параметры
        double w; // Ацентрический фактор
        
        std::string name = "unknown";
    };
    
} // namespace MySpace::PhAn;