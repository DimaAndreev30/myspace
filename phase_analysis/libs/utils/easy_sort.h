#pragma once


// Библиотека с функциями, выполняющими сортировку трехэлементного массива.

namespace NMySpace::NPhan::NUtils {

    // Сортировка от меньшего к большему.
    void Sort3(double array[3]);
    // Сортировка от большего к меньшему.
    void Sort3Desc(double array[3]);

    // Сортировка от меньшего к большему по модулю.
    void SortAbs3(double array[3]);
    // Сортировка от большего к меньшему по модулю.
    void SortAbs3Desc(double array[3]);
    
}
