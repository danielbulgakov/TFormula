#pragma once
#include "TStack.h"
#include "Validator.h"
#include <utility>
#include <vector>
#include <map>
class Translator
{
private:
	TStack<Token> Stack;
	std::vector<Token> Answer, Input;
public:
	explicit Translator(std::vector<Token>  input) : Input(std::move(input)) {}
	std::vector<Token> Translate();
};

