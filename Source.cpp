#include "Validator.h"
#include "Translator.h"
#include "TFormula.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <regex>

using namespace std;



int main() {

    setlocale(LC_ALL, "Russian");





    string Math = "(a / b ) + (1/3) ; a = 2 ; b = 3;";
    TFormula Formula;
    Formula.FromTXT("Examples.txt");
    //std::cout << "Right Answer 1 2 * 3 / 54 42 + * 8 / 5 32 1 + - *" << std::endl;

    //std::cout << std::endl <<"Answer: "<< Formula.Evaluate() << std::endl;

    // EXP (((1*2)/3)*(54+42))/(8)*(5-(32+1))
    return 0;
}

//(5 + 6) * 2
//(18 / 6) + (3 * 4)
//((2 + 3) * 2) / 5
//(a + b + c); a = 1; b = 2; c = 3
//(a * b) - c; a = 7; b = 2; c = 20