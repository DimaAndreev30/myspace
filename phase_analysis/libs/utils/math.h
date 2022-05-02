#pragma once


namespace NMySpace::NPhan::NUtils {

    // Показательная функция, которая не боится знаков:
    // для x < 0 возвращаемое значение -(-x)^y
    double SignSavePow(double x, double y);

}
