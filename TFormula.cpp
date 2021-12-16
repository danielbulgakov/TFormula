#include "TFormula.h"

std::vector<Token> TFormula::ToTokens(std::string& MathExprs) {
    std::string MathExpr = MathExprs;
    auto NoSpaceEnd = std::remove(MathExpr.begin(), MathExpr.end(), ' ');
    MathExpr.erase(NoSpaceEnd, MathExpr.end());
    bool isdefinevalues = false;
    std::vector <TToken> res;
    std::string gg;
    size_t pos = 0;

    for (size_t i = 0; i < MathExpr.size(); i++, pos++) {
        if (MathExpr[i] == '.') MathExpr[i] = ',';
        if (MathExpr[i] == ' ') continue;
        if (MathExpr[i] == ';') isdefinevalues = true;

        if (isdigit(MathExpr[i]) || MathExpr[i] == ',' ||
            (isdefinevalues && MathExpr[i] == '-')
            ) {
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

void TFormula::DefineValues(std::vector<Token> &fml)
{
    std::map<std::string, std::string> ValuesTable;
    size_t EndExpressionPos = 0;
    std::string Name, Value;

    for (const auto& x : fml) { // create map values
        
        if (x.GetValue() == ";" && EndExpressionPos == 0)
            EndExpressionPos = x.GetPosition();
        if (EndExpressionPos != 0) {
            if (isletter(x.GetValue()[0]))
                Name = x.GetValue();
            if (isdigit(x.GetValue()[0]) || x.GetValue()[0] == '-')
                Value = x.GetValue();
            if (Name.size() != 0 && Value.size() != 0) {
                ValuesTable.insert((std::pair<std::string, std::string>(Name, Value)));
                Value.clear();
                Name.clear();
            }
        }
    }

    if (EndExpressionPos == 0) return;

    std::map<std::string, std::string>::iterator it;
    
    for (auto& x : fml) {
        it = ValuesTable.find(x.GetValue());
        if (it != ValuesTable.end()) {
            x.SetValue(it->second);
        }
    }
    size_t tmp = fml.size();
    for (size_t i = 0; i < tmp - EndExpressionPos; i++) {
        fml.pop_back();
    }










}


bool TFormula::isletter(char ch) {
     return (ch >= 'a' && ch <= 'z'); 
}



/*
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
*/
void TFormula::PrintTranslator() {
    std::cout << endl << "Транслятор : ";
    for (auto x : Expt) {
        std::cout << x.GetValue() << " ";
    }
    std::cout << endl;
    return;
}

void TFormula::VectorToStack() {
    for (const auto& x : Expt) {
        stack.Push(x);

    }
}


TFormula::TFormula(std :: string exp): Exp(std::move(std::move(exp))) {
	std::vector<Token> aaa = ToTokens(Exp);
    DefineValues(aaa);
    if (isIncorrect == true) return;
	Validator vld(aaa);
	vld.Validate();
    if (vld.GetError() != 0) {
        isIncorrect = true;
        vld.PrintTable();
        return;
    }

	Translator trs(aaa);
	Expt = trs.Translate();

	VectorToStack();
}

TFormula::TFormula(){}


double TFormula::Evaluate()
{
    if (isIncorrect) {
        throw std::invalid_argument("Неверно введено выражение");
        return NAN;
    }
    if (stack.IsEmpty()) {
        throw std::invalid_argument("Неопределенная операция");
        return NAN;
    }
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
            if (y == 0) {
                throw std::overflow_error("Деление на ноль в " + std::to_string(tk.GetPosition()) + " позиции");
                return NAN;
            }
            x /= y;
        }
    }
    else {
         x = stod(tk.GetValue());  
    }
    return x;
}

void TFormula::FromTXT(std::string Path)
{
    
    ifstream inFile;
    std::string buff;
    inFile.open(Path);
    while (inFile.peek() != EOF) {
        std::cout << "======================================";

        std::getline(inFile, buff);
        std::cout << std::endl;
        std::cout << buff << std::endl;
        if (buff.size() == 0) continue;
        try {
            TFormula Formula(buff);
            double Answer = 0;
            Answer = Formula.Evaluate();
            std::cout << "Ответ: " << Answer << std::endl;


            std::ostringstream oss;
            oss << std::setprecision(6) << std::noshowpoint << Answer;
            ToTXT("Results.txt", oss.str());
        }
        catch (std::invalid_argument& e) {
            std::cout << "Ответ: " << e.what() << std::endl;
            ToTXT("Results.txt", e.what());
        }
        catch (std::overflow_error& e) {
            std::cout << "Ответ: " << e.what() << std::endl;
            ToTXT("Results.txt", e.what());
        }
        /*
        TFormula Formula(buff);
        double Answer = 0;
        try {
            Answer = Formula.Evaluate();
            std::cout << "Ответ: " << Answer << std::endl;


            std::ostringstream oss;
            oss << std::setprecision(6) << std::noshowpoint << Answer;         

            ToTXT("Results.txt", oss.str() );
        }
        catch (std::invalid_argument& e) {
            std::cout << "Ответ: " << e.what() << std::endl;
            ToTXT("Results.txt", e.what() );
        }
        catch (std::overflow_error& e) {
            std::cout << "Ответ: " << e.what() << std::endl;
            ToTXT("Results.txt", e.what() );
        }
        */

        
    }

    inFile.close();
    return;
}

void TFormula::ToTXT(std::string Path, std::string Answer) {

    ofstream ofFile;
    ofFile.open(Path, std::ios_base::app | std::ios_base::in );
    if (ofFile.is_open())
        ofFile << Answer << endl;
    ofFile.close();
    return;
}
