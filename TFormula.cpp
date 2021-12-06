#include "TFormula.h"

std::vector<Token> TFormula::ToTokens(std::string& MathExprs) {
    std::string MathExpr = MathExprs;
    auto NoSpaceEnd = std::remove(MathExpr.begin(), MathExpr.end(), ' ');
    MathExpr.erase(NoSpaceEnd, MathExpr.end());
    //MathExpr = CheckValues(MathExpr);
    std::vector <TToken> res;
    std::string gg;
    size_t pos = 0;

    for (size_t i = 0; i < MathExpr.size(); i++, pos++) {
        if (MathExpr[i] == '.') MathExpr[i] = ',';
        if (MathExpr[i] == ' ') continue;

        if (isdigit(MathExpr[i]) || MathExpr[i] == ',') {
            gg += MathExpr[i];
            if (gg.size() > 1) pos--;
        }
        else if (isletter(MathExpr[i]) || MathExpr[i] == ',') {
            gg += MathExpr[i];
            if (gg.size() > 1) pos--;
        }
        else {
            if (!gg.empty()) {
                TToken tmp(gg, pos);
                res.push_back(tmp);
                gg = "";
            }

            gg = MathExpr[i];
            TToken tmp(gg, pos);
            res.push_back(tmp);
            gg = "";

        }
        if (i == MathExpr.size() - 1 && !gg.empty()) {
            TToken tmp(gg, pos);
            res.push_back(tmp);
            gg = "";

        }
    }

    return res;
}

bool TFormula::isletter(char ch) {
     return (ch >= 'a' && ch <= 'z'); 
}




std::string TFormula::ReplaceAll(const std::string& inputStr, const std::string& src, const std::string& dst)
{
    std::string result(inputStr);

    size_t pos = result.find(src);
    while (pos != std::string::npos) {
        result.replace(pos, src.size(), dst);
        pos = result.find(src, pos);
    }

    return result;
}

std::string TFormula::CheckValues(std::string& MathExpr)
{
    if (MathExpr[MathExpr.size() - 1] != ';') MathExpr += ';';
    std::string result = MathExpr;
    std::string values;

    if (std::string(MathExpr).find(';') != std::string::npos) {
        result = MathExpr.substr(0, std::string(MathExpr).find_first_of(';'));
        values = MathExpr.substr(std::string(MathExpr).find_first_of(';') + 1,
            std::string(MathExpr).size() - std::string(MathExpr).find_first_of(';'));

        std::string buff;
        std::string value;
        for (auto x : values) {
            if (x == '=') {
                continue;
            }
            if (isletter(x)) buff += x;
            else if (isdigit(x) || x == '.' || x == ',' || x == '-')  value += x;
            else if (x == ';') {
                if (buff.size() == 0 || value.size() == 0) {
                    isIncorrect = true;
                    return "NaN";
                }
                
                result = ReplaceAll(result, buff,'0' + value );
                buff.clear();
                value.clear();
            }
        }
    }
    return result;
}

void TFormula::VectorToStack() {
    for (const auto& x : Expt) {
        stack.Push(x);
    }
}


TFormula::TFormula(std :: string exp): Exp(std::move(std::move(exp))) {
	std::vector<Token> aaa = ToTokens(Exp);
    if (isIncorrect == true) return;
	Validator vld(aaa);
	vld.Validate();
    if (vld.GetError() != 0) {
        isIncorrect = true;
        return;
    }
	vld.PrintTable();
	Translator trs(aaa);
	Expt = trs.Translate();
	VectorToStack();
}

TFormula::TFormula()
{
}

double TFormula::Evaluate()
{
    if (isIncorrect) {
        IncorrectExprMess();
        return NAN;
    }
    assert(!stack.IsEmpty());
    double x, y;
    Token tk(stack.Top()); stack.Pop();
    size_t n = tk.GetValue().size();
    if (n == 1 && std::string("+-*/").find(tk.GetValue()) != std::string::npos) {
        y = Evaluate();
        x = Evaluate();
        if (tk.GetValue()[0] == '+') x += y;
        else if (tk.GetValue()[0] == '-') x -= y;
        else if (tk.GetValue()[0] == '*') x *= y;
        else if (tk.GetValue()[0] == '/') {
            assert(y != 0);
            x /= y;
        }
    }
    else {
        unsigned i;  x = stod(tk.GetValue(), reinterpret_cast<size_t*>(&i));  assert(i == n);
    }
    return x;
}

void TFormula::FromTXT(std::string Path)
{
    
    ifstream inFile;
    std::string buff;
    inFile.open(Path);
    while (inFile.peek() != EOF) {
        std::cout << "=========================================";
        std::getline(inFile, buff);
        std::cout << std::endl;
        std::cout << buff << std::endl;
        TFormula Formula(buff);
        
        
        std::cout << "�����: " << Formula.Evaluate() << std::endl;
    }
    std::cout << "=========================================";
    inFile.close();
    return;
}

void TFormula::IncorrectExprMess()
{
    std::cout << "\n��������� ��������� ������� �������!\n";
}