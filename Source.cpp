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