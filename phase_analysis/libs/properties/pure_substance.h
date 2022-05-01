#pragma once

#include <string>


namespace NMySpace::NPhAn {
    
    // Структура для хранения справочной информации о чистом веществе.
    struct TPureSubstanceProps {
        double m = 0.0; // Молярная масса
        double Pc = 0.0; // Критическое давление
        double Vc = 0.0; // Критический объем
        double Tc = 0.0; // Критическая температура
        double w = 0.0; // Ацентрический фактор
        
        std::string name = "unknown";
    };
    
}
