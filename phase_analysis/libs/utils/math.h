#pragma once


namespace NMySpace::NPhan::NUtils {

    // Показательная функция, которая не боится знаков:
    // для x < 0 возвращаемое значение -(-x)^y
    double signSavePow(double x, double y);

}
