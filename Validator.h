#pragma once

#include "TStack.h"
#include "TTable.h"
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <iterator>
#include <algorithm>
class TToken {
private:
	std::string Value;
	size_t Pos;
public:
	TToken(std::string& value, size_t pos)	:Value(value), Pos(pos) {}
	TToken() :  Pos(0) {}
	const std::string& GetValue()const			{ return Value; }
	size_t GetPosition()const					{ return Pos; }
	bool operator= (const TToken& tmp) const;
	bool operator!= (const TToken& tmp) const;
	TToken& operator=(const TToken& tmp);
};

using Token = TToken;

class Validator
{
private:
	TStack<Token> Stack;
	std::vector<Token> Tokens;

	size_t ERRORS = 0;
	std::vector<int> Open, Close;
public:
	explicit Validator(std::vector<Token>  tokens) : Tokens(std::move(tokens)) {}
	size_t GetError();
	void Validate();
	void PrintTable();

};

