#include "Translator.h"

std::vector<Token> Translator::Translate()
{
    std::map<char, int > keyMap = { { '(' , 0},
                                   {  ')' , 1},
                                   {  '+' , 2}, { '-' , 2},
                                   {  '*' , 3}, { '/' , 3} };

    for (const auto& tok : Input) {

        int ind = tok.GetValue().size() - 1;

        if ((tok.GetValue()[ind] >= 'a' && tok.GetValue()[ind] <= 'z' ||
            tok.GetValue()[ind] >= '0' && tok.GetValue()[ind] <= '9'))
        {
            Answer.push_back(tok);
        }
        else if (Stack.IsEmpty())
        {
            Stack.Push(tok);
        }
        else if (keyMap.find(tok.GetValue()[ind])->second == 0) {
            Stack.Push(tok);
        }
        


        else if (keyMap.find(tok.GetValue()[ind])->second == 1) {
            while (!Stack.IsEmpty() &&
                keyMap.find(Stack.Top().GetValue()[ind])->second != 0
               ) {
                 Answer.push_back(Stack.Pop()); 
            }
            if (!Stack.IsEmpty()) {
                Stack.Pop();
            }
        }

        else if (!Stack.IsEmpty() && keyMap.find(tok.GetValue()[ind])->second > keyMap.find(Stack.Top().GetValue()[ind])->second)
        {
            Stack.Push(tok);
        }

        else{
            while (!Stack.IsEmpty() && (keyMap.find(Stack.Top().GetValue()[ind])->second >= keyMap.find(tok.GetValue()[ind])->second)) {
                Token tk = Stack.Pop();
                if (tk.GetValue() != ")" && tk.GetValue() != "(")
                    Answer.push_back(tk);
            }
            Stack.Push(tok);
        
        }
        
        
        

        




    }
    if (!Stack.IsEmpty())
    {
        while (!Stack.IsEmpty()) {
            

            
                Answer.push_back(Stack.Pop());
        }
    }



    return Answer;
}
