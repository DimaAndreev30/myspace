#include "compos.h"

#include <cmath>
#include <algorithm>

#include <iostream>


double pow2(double x) {
    return x*x;
}

namespace NMySpace::NPhan::NPheq {
    
    TCompos::TCompos(size_t N)
    {
        x.reserve(N);
        y.reserve(N);
    }
    
    bool TCompos::SetFromKValues(const std::vector<double>& kValues, 
                                 const std::vector<double>& z) {
        size_t N = kValues.size();
        
        x.resize(N);
        y.resize(N);
                
        switch (N) {
            case 1: {// Уравнение нерешаемо (вообще говоря, надо кидать исключение)
                x[0] = y[0] = 1;
                V = L = 0.5;
                
                break;
            }
            case 2: {// Две компоненты, линейное уравнение      
                x[0] = (kValues[1] - 1)/(kValues[1] - kValues[0]);
                y[0] = kValues[0]*x[0];
                
                x[1] = 1 - x[0];
                y[1] = 1 - y[0];
                
                V = (z[0] - x[0])/(y[0] - x[0]);
                L = 1 - V;
                
                break;
            }
            case 3: {// Три компоненты, квадратное уравнение
                double D2 = pow2((1 - z[0])/(kValues[0] - 1)) + 
                            pow2((1 - z[1])/(kValues[1] - 1)) + 
                            pow2((1 - z[2])/(kValues[2] - 1)) - 2*(
                            (z[0] - z[1]*z[2])/((kValues[1] - 1)*(kValues[2] - 1)) + 
                            (z[1] - z[2]*z[0])/((kValues[2] - 1)*(kValues[0] - 1)) + 
                            (z[2] - z[0]*z[1])/((kValues[0] - 1)*(kValues[1] - 1)));
                
                if (D2 < 0.0) {
                    return false;
                }
                
                double b = ((1 - z[0])/(kValues[0] - 1) + 
                            (1 - z[1])/(kValues[1] - 1) + 
                            (1 - z[2])/(kValues[2] - 1));
                double D = std::sqrt(D2);
                
                double left = -1/(*std::max_element(kValues.cbegin(), kValues.cend()) - 1);
                double right = -1/(*std::min_element(kValues.cbegin(), kValues.cend()) - 1);
                
                double V1 = (-b - D)/2;
                double V2 = (-b + D)/2;
                
                if (left < V1 && V1 < right) {
                    V = V1;
                } else if (left < V2 && V2 < right) {
                    V = V2;
                } else {
                    return false;
                }
                
                L = 1 - V;
                
                for (int i = 0; i < 3; i++) {
                    x[i] = z[i]/(1 + (kValues[i] - 1)*V);
                    y[i] = kValues[i]*x[i];
                }
                
                break;
            }
            default: {// Общий случай, решение итерационным методом
                break;
            }
        }
          
        return true;
    }
    
}
