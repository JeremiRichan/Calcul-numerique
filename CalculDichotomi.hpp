#ifndef CALCUL_DICHOTOMIE_HPP
#define CALCUL_DICHOTOMIE_HPP

#include <string>

class CalculNumerique {
        public:
        CalculNumerique();
        void definirFonction(const std::string& expr);
        
        double methodeDichotomie(double a, double b, double precision);

        void genererDonneesPlot(const std::string& nomFichier, double borneInf, double borneSup);

        private:
        std::string expression;
        
        void ignorerEspaces(const std::string& s, size_t& pos);
        
        double evaluer(const std::string& s, double x, size_t& pos);
        
        double analyserTerme(const std::string& s, double x, size_t& pos);
        
        double analyserFacteur(const std::string& s, double x, size_t& pos);
};

#endif