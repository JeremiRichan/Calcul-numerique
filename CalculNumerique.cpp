#include "CalculNumerique.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <cctype>

CalculNumerique::CalculNumerique() {}

void CalculNumerique::definirExpression(const std::string& expr)
{
        expression = expr;
}

double CalculNumerique::evaluer(const std::string& s, double x, size_t& pos)
{
        double resultat = analyserTerme(s, x, pos);
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
        }
        return resultat;
}

double CalculNumerique::analyserTerme(const std::string& s, double x, size_t& pos)
{
        double resultat = analyserFacteur(s, x, pos);
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
        }
        return resultat;
}

double CalculNumerique::analyserFacteur(const std::string& s, double x, size_t& pos) 
{
        while (pos < s.length() && s[pos] == ' ') 
        {
                pos++;
        }
        if (pos >= s.length()) return 0;

        if (s[pos] == '-') {
                pos++;
                return -analyserFacteur(s, x, pos);
        }
        if (s[pos] == '+') {
                pos++;
                return analyserFacteur(s, x, pos);
        }

        if (std::isdigit(s[pos]) || s[pos] == '.') {
                size_t start = pos;
                while (pos < s.length() && (std::isdigit(s[pos]) || s[pos] == '.')) 
                {
                        pos++;
                }
                std::string nombreStr = s.substr(start, pos - start);
                return std::stod(nombreStr);
        }

        if (s[pos] == 'x') {
                pos++;
                return x;
        }

        if (s[pos] == '(') {
        pos++;
        double resultat = evaluer(s, x, pos);
        if (pos < s.length() && s[pos] == ')') 
        {
                pos++;
        }
        return resultat;
        }

        if (s.substr(pos, 3) == "sin") {
                pos += 3;
                if (pos < s.length() && s[pos] == '(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos);
                if (pos < s.length() && s[pos] == ')') 
                {
                        pos++;
                }
                return std::sin(val);
        }
        
        if (s.substr(pos, 3) == "cos") {
                pos += 3;
                if (pos < s.length() && s[pos] == '(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos);
                if (pos < s.length() && s[pos] == ')') 
                {
                        pos++;
                }
                return std::cos(val);
        }

        if (s.substr(pos, 3) == "exp") {
                pos += 3;
                if (pos < s.length() && s[pos] == '(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos);
                if (pos < s.length() && s[pos] == ')') 
                {
                        pos++;
                }
                return std::exp(val);
        }

        if (s.substr(pos, 4) == "sqrt") {
                pos += 4;
                if (pos < s.length() && s[pos] == '(') 
                {
                        pos++;
                }
                double val = evaluer(s, x, pos);
                if (pos < s.length() && s[pos] == ')') 
                {
                        pos++;
                }
                return std::sqrt(val);
        }

        std::cerr << "Erreur de syntaxe a la position : " << pos << " (caractere: " << s[pos] << ")" << std::endl;
        return 0;
}

double CalculNumerique::calculerDerivee(double x)
{
        double h = 1e-7;
        size_t pos = 0;
        double f_x_plus_h = evaluer(expression, x + h, pos);
        pos = 0;
        double f_x_moins_h = evaluer(expression, x - h, pos);
        return (f_x_plus_h - f_x_moins_h) / (2.0 * h);
}

double CalculNumerique::methodeNewtonRaphson(double x0, double precision)
{
        double x = x0;
        int iter = 0;

        while (true)
        {
                iter++;
                size_t pos = 0;
                double f_x = evaluer(expression, x, pos);
                double f_prime_x = calculerDerivee(x);

                if (std::abs(f_prime_x) < 1e-15) 
                {
                        std::cerr << "Erreur: Derivee nulle. Arret." << std::endl;
                        return x;
                }

                double x_next = x - (f_x / f_prime_x);

                if (std::abs(x_next - x) < precision)
                {
                        std::cout << "Convergence atteinte apres " << iter << " iterations." << std::endl;
                        return x_next;
                }

                if (iter > 1000) {
                        std::cerr << "Divergence detectee." << std::endl;
                        return x_next;
                }

                x = x_next;
        }
}