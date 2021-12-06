#include "Validator.h"

bool TToken::operator=(const TToken& tmp) const
{
    return (Value == tmp.GetValue() && Pos == tmp.GetPosition());
}

bool TToken::operator!=(const TToken& tmp) const
{
    return (Value != tmp.GetValue() || Pos != tmp.GetPosition());
}

TToken& TToken::operator=(const TToken& tmp)
= default;

size_t Validator::GetError()
{
    return ERRORS;
}

void Validator::Validate()
{


    for (const auto& tok : Tokens) {

        if ((tok.GetValue()[0] >= 'a' && tok.GetValue()[0] <= 'z')) {
            ERRORS++;
        }
        
            if (!(tok.GetValue()[0] >= 'a' && tok.GetValue()[0] <= 'z'))
                if (!(tok.GetValue()[0] >= '0' && tok.GetValue()[0] <= '9'))
                    if (!(tok.GetValue()[0] == '(' || tok.GetValue()[0] == ')'))
                        if (!(tok.GetValue()[0] == '*' || tok.GetValue()[0] == '/'))
                            if (!(tok.GetValue()[0] == '-' || tok.GetValue()[0] == '+' || tok.GetValue()[0] == ' ')) {
                                 ERRORS++;
                                std::cout << (std::string("Wrong symbol = \"") + tok.GetValue()[0])+"\"" + " POS = " << tok.GetPosition() << std::endl;
                            }
    
        
        if (tok.GetValue()[0] == '(') {
            Stack.Push(tok);
        }
        if (tok.GetValue()[0] == ')') {
            if (Stack.IsEmpty()) {
                ERRORS++;
                Close.push_back(tok.GetPosition());
                Open.push_back(-1);
            }
            else {
                Open.push_back(Stack.Pop().GetPosition());
                Close.push_back(tok.GetPosition());
            }
        }

    }
    if (!Stack.IsEmpty())
    {
        while (!Stack.IsEmpty()) {
            Open.push_back(Stack.Pop().GetPosition());
            Close.push_back(-1);
            ERRORS++;
        }
    }



}

void Validator::PrintTable()
{
    if (Open.size() == 0 && Close.size() == 0) return;
    std::cout << std::endl;
    enum CollBR{
        OpenBr = 0,
        CloseBr = 1
    };
    std::reverse(std::begin(Open), std::end(Open));
    std::reverse(std::begin(Close), std::end(Close));
    TTable<std::string> Result("Скобки", std::max(Open.size(), Close.size()), 2);
    Result.SetNameColl("Открывающаяся", OpenBr);
    Result.SetNameColl("Закрывающаяся", CloseBr);

    for (size_t i = 0; i < Result.GetRow(); i++) {
        Result.SetValue(i, OpenBr, (Open[i] == -1 ? "-" : (std::to_string(Open[i]))));
        Result.SetValue(i, CloseBr, (Close[i] == -1 ? "-" : (std::to_string(Close[i]))));
    }

    Result.Print();
    std::cout << std::endl << "Количество ошибок в расстановке скобок = " <<  ERRORS << std::endl;


}
