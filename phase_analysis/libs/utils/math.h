#pragma once


namespace MySpace::PhAn::Utility {

    // Показательная функция, которая не боится знаков:
    // для x < 0 возвращаемое значение -(-x)^y
    double sign_save_pow(double x, double y);

} // namespace MySpace::PhAn::Utility;