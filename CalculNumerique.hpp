#ifndef CALCUL_NUMERIQUE_HPP
#define CALCUL_NUMERIQUE_HPP

#include <string>

class CalculNumerique {
    public:
        CalculNumerique();
        
        void definirExpression(const std::string& expr);
        
        double methodeNewtonRaphson(double x0, double precision);

    private:
        std::string expression;
        
        double evaluer(const std::string& s, double x, size_t& pos);

        double analyserTerme(const std::string& s, double x, size_t& pos);

        double analyserFacteur(const std::string& s, double x, size_t& pos);

        double calculerDerivee(double x);
};

#endif