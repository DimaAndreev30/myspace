#pragma once


// Библиотека с функциями, выполняющими сортировку трехэлементного массива.

namespace MySpace::PhAn::Utility {

    // Сортировка от меньшего к большему.
    void sort3(double array[3]);
    // Сортировка от большего к меньшему.
    void sort3Desc(double array[3]);

    // Сортировка от меньшего к большему по модулю.
    void sortAbs3(double array[3]);
    // Сортировка от большего к меньшему по модулю.
    void sortAbs3Desc(double array[3]);
    
} // namespace MySpace::PhAn::Utility;