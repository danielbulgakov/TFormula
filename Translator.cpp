#include "Translator.h"

std::vector<Token> Translator::Translate()
{
    std::map<char, int > keyMap = { { '(' , 0},
                                   {  ')' , 1},
                                   {  '+' , 2}, { '-' , 2},
                                   {  '*' , 3}, { '/' , 3} };

    for (const auto& tok : Input) {



        if ((tok.GetValue()[0] >= 'a' && tok.GetValue()[0] <= 'z' ||
            tok.GetValue()[0] >= '0' && tok.GetValue()[0] <= '9')) 
        {
            Answer.push_back(tok);
        }
        else if (Stack.IsEmpty())
        {
            Stack.Push(tok);
        }
        else if (keyMap.find(tok.GetValue()[0])->second == 0) {
            Stack.Push(tok);
        }
        


        else if (keyMap.find(tok.GetValue()[0])->second == 1) {
            while (!Stack.IsEmpty() &&
                keyMap.find(Stack.Top().GetValue()[0])->second != 0
               ) {
                 Answer.push_back(Stack.Pop()); 
            }
            if (!Stack.IsEmpty()) {
                Stack.Pop();
            }
        }

        else if (!Stack.IsEmpty() && keyMap.find(tok.GetValue()[0])->second > keyMap.find(Stack.Top().GetValue()[0])->second)
        {
            Stack.Push(tok);
        }

        else{
            while (!Stack.IsEmpty() && (keyMap.find(Stack.Top().GetValue()[0])->second >= keyMap.find(tok.GetValue()[0])->second)) {
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
