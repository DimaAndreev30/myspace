#pragma once


namespace MySpace::Utility
{


// Показательная функция, которая не боится знаков:
// для x < 0 возвращаемое значение -(-x)^y
double sign_save_pow(double x, double y);

    
} // namespace MySpace::Utility;