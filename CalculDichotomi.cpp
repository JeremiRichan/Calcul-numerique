#include "CalculDichotomi.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cctype>
#include <iomanip>

CalculNumerique::CalculNumerique() {}

void CalculNumerique::definirFonction(const std::string& expr) 
{
        expression = expr;
}

void CalculNumerique::ignorerEspaces(const std::string& s, size_t& pos) 
{
        while (pos < s.length() && std::isspace(s[pos])) pos++;
}

double CalculNumerique::evaluer(const std::string& s, double x, size_t& pos) 
{
        double resultat = analyserTerme(s, x, pos);
        ignorerEspaces(s, pos);
        while (pos < s.length() && (s[pos] == '+' || s[pos] == '-')) 
        {
                char op = s[pos++];
                double terme = analyserTerme(s, x, pos);
                if (op == '+') 
                {
                        resultat += terme;
                }
                else 
                {
                        resultat -= terme;
                }
                ignorerEspaces(s, pos);
        }
        return resultat;
}

double CalculNumerique::analyserTerme(const std::string& s, double x, size_t& pos) 
{
        double resultat = analyserFacteur(s, x, pos);
        ignorerEspaces(s, pos);
        while (pos < s.length() && (s[pos] == '*' || s[pos] == '/')) 
        {
                char op = s[pos++];
                double facteur = analyserFacteur(s, x, pos);
                if (op == '*') 
                {
                        resultat *= facteur;
                }
                else 
                {
                        resultat /= facteur;
                }
                ignorerEspaces(s, pos);
        }
        return resultat;
}

double CalculNumerique::analyserFacteur(const std::string& s, double x, size_t& pos) 
{
        ignorerEspaces(s, pos);
        if (pos >= s.length()) 
        {
                return 0;
        }

        if (s[pos] == '-') 
        { 
                pos++; 
                return -analyserFacteur(s, x, pos); 
        }
        if (s[pos] == '+') 
        { 
                pos++; 
                return analyserFacteur(s, x, pos); 
        }

        if (std::isdigit(s[pos]) || s[pos] == '.') {
                size_t debut = pos;
                while (pos < s.length() && (std::isdigit(s[pos]) || s[pos] == '.')) 
                {
                        pos++;
                }
                return std::stod(s.substr(debut, pos - debut));
        }

        if (s[pos] == 'x') 
        { 
                pos++; 
                return x; 
        }

        if (s[pos] == '(') {
                pos++;
                double res = evaluer(s, x, pos);
                ignorerEspaces(s, pos);
                if (pos < s.length() && s[pos] == ')') 
                {
                        pos++;
                }
                return res;
        }

        // Fonctions usuelles
        if (s.substr(pos, 3) == "sin") 
        {
                pos += 3; ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]=='(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos); 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]==')') 
                {
                        pos++;
                }
                return std::sin(val);
        }
        if (s.substr(pos, 3) == "cos") 
        {
                pos += 3; 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]=='(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos); 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]==')') 
                {
                        pos++;
                }
                return std::cos(val);
        }
        if (s.substr(pos, 3) == "exp") 
        {
                pos += 3; 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]=='(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos); 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]==')') 
                {
                        pos++;
                }
                return std::exp(val);
        }
        if (s.substr(pos, 4) == "sqrt") 
        {
                pos += 4; 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]=='(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos); 
                ignorerEspaces(s, pos); 
                if(pos<s.length()&&s[pos]==')') 
                {
                        pos++;
                }
                return std::sqrt(val);
        }

        std::cerr << "Erreur syntaxe position : " << pos << std::endl;
        return 0;
}

double CalculNumerique::methodeDichotomie(double a, double b, double precision) 
{
        size_t pos = 0;
        double fa = evaluer(expression, a, pos);
        pos = 0;
        double fb = evaluer(expression, b, pos);

        if (fa * fb >= 0) 
        {
                std::cerr << "Erreur : f(a) et f(b) doivent avoir des signes opposés." << std::endl;
                std::cerr << "f(a) = " << fa << ", f(b) = " << fb << std::endl;
                return 0;
        }

        double milieu = 0.0;
        int iter = 0;

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Iter | a        | b        | milieu   | f(milieu)" << std::endl;
        std::cout << "-----|----------|----------|----------|-----------" << std::endl;

        while ((b - a) > precision) 
        {
                milieu = (a + b) / 2.0;
                pos = 0;
                double fMilieu = evaluer(expression, milieu, pos);

                std::cout << std::setw(4) << iter 
                        << " | " << std::setw(8) << a 
                        << " | " << std::setw(8) << b 
                        << " | " << std::setw(8) << milieu 
                        << " | " << std::setw(9) << fMilieu << std::endl;

                if (std::abs(fMilieu) < 1e-15) 
                {
                        break;
                }

                pos = 0;
                double faActuel = evaluer(expression, a, pos);
                
                if (faActuel * fMilieu < 0) 
                {
                        b = milieu;
                } else 
                {
                        a = milieu;
                }
                iter++;

                if (iter > 1000) 
                {
                        std::cerr << "Trop d'iterations." << std::endl;
                        break;
                }
        }

        std::cout << "Solution approchee : " << milieu << std::endl;
        return milieu;
}

void CalculNumerique::genererDonneesPlot(const std::string& nomFichier, double borneInf, double borneSup) 
{
        std::ofstream fichierSortie(nomFichier);
        if (!fichierSortie.is_open()) 
        {
                return;
        }

        double marge = (borneSup - borneInf) * 0.5;
        double debut = borneInf - marge;
        double fin = borneSup + marge;
        double pas = (fin - debut) / 100.0;

        for (double x = debut; x <= fin; x += pas) 
        {
                size_t pos = 0;
                fichierSortie << x << " " << evaluer(expression, x, pos) << std::endl;
        }
        fichierSortie.close();
}