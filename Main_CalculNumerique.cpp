#include "CalculNumerique.hpp"
#include <iostream>
#include <ctime>

int main()
{
        CalculNumerique resolution;
        std::string expression;
        
        std::cout << "Entrez l'expression a resoudre  : " << std::endl;
        std::getline(std::cin, expression);

        resolution.definirExpression(expression);

        double x0 = 1.0;
        double precision = 1e-7;

        std::cout << "Calcul en cours..." << std::endl;

        clock_t start = clock();
        
        double solution = resolution.methodeNewtonRaphson(x0, precision);
        
        clock_t end = clock();

        std::cout << "Solution trouvee : " << solution << std::endl;
        std::cout << "Temps d'execution : " << double(end - start) / CLOCKS_PER_SEC << " secondes" << std::endl;

        return 0;
}