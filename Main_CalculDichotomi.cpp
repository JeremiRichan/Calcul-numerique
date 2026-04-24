#include "CalculDichotomi.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main() {
        std::string expr;
        double a, b, precision;

        std::cout << "Expression (ex: x*x-2): ";
        std::getline(std::cin, expr);

        std::cout << "Borne inferieure (a): ";
        std::cin >> a;
        std::cout << "Borne superieure (b): ";
        std::cin >> b;
        precision = 1e-6;

        CalculNumerique calcul;
        calcul.definirFonction(expr);

        double racine = calcul.methodeDichotomie(a, b, precision);

        // Génération Gnuplot
        std::string fichierData = "dichotomie_data.dat";
        std::string fichierScript = "dichotomie_plot.gnuplot";

        calcul.genererDonneesPlot(fichierData, a, b);

        std::ofstream scriptGp(fichierScript);
        if (scriptGp.is_open()) {
                scriptGp << "set title 'Dichotomie: " << expr << "'" << std::endl;
                scriptGp << "set grid" << std::endl;
                scriptGp << "plot '" << fichierData << "' using 1:2 with lines title 'f(x)', \\" << std::endl;
                scriptGp << "     " << racine << " title 'Racine' with points pt 7 ps 1.5 lc rgb 'red'" << std::endl;
                scriptGp.close();

                std::system(("gnuplot -persist " + fichierScript).c_str());
        }

        return 0;
}