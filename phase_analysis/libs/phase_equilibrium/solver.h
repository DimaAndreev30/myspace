#pragma once

#include "two_phase_compos.h"

#include <phase_analysis/libs/mixture/interface.h>

#include <vector>


namespace MySpace::PhAn {
    
    // TODO: Добавить провероки на соответствие размерности.
    // TODO: Определиться с моделью обработки исключительных ситуаций
    // и способах доставки описания ошибки.
    // Самое простое - просто прекращать работу со статусом "ошибка",
    // а описание писать в какой-нибудь лог.
    // Некоторые ситуации, которые в релизной сборке встречаться впринципе не должны,
    // имеет смысл все же обрабатывать ассертами. (например, несоотв. размерностей)
    // TODO: Определиться, наконец, как возвращать результат:
    // через возвращаемое значение или через параметр. 
    // (эти вопросы не только здесь возникают)
    
    struct PhEqSettings {
        int maxIterationsNumber = 1000;
        double eps = 1e-4;
    };
    
    struct PhEqResult {
        enum Status {
            OK,
            NOT_CONVERGE
        } status = OK;
        
        int iterationsNumber = 0;
        
        TwoPhaseCompos compos{};
    };
    
    // Основной алгоритм, вычисляющий K-values и концентрации компонент в фазах
    // итерационным (flash) методом.
    PhEqResult computePhEq(const PhEqSettings& setts, 
                           MixtureInterface& mixture,
                           const std::vector<double>& z, 
                           std::vector<double>& kValues);
     
} // namespace MySpace::PhAn;
