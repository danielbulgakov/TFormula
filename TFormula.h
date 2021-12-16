#pragma once
#include <string>
#include <utility>
#include <utility>
#include <vector>
#include <fstream>
#include "Translator.h"
#include "Validator.h"
#include "TStack.h"
#include <sstream>
#include <iomanip>
using namespace  std;
class TFormula
{
private:
    bool isIncorrect = false;

    
    std::string Exp; // String of Expression
	std::vector<Token> Expt; // Token Vector of Expression
	TStack<Token> stack;
    

    std::vector<Token> ToTokens(std::string& MathExprs);
    void DefineValues(std::vector<Token> & fml);

    // TO delete
    //std::string ReplaceAll(const std::string& inputStr, const std::string& src, const std::string& dst);
    //std::string CheckValues(std::string& MathExpr);    
    // --

    bool isletter(char ch);
    void PrintTranslator();
    void VectorToStack();
    void IncorrectExprMess();
    void TryEval(TFormula& fm);
public:
    TFormula(std::string exp);
    double Evaluate();
    TFormula();
    void FromTXT(std::string Path);
    void ToTXT(std::string Path, std::string Answer);
    
};


