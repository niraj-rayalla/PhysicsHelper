/*	
Copyright (C) 2013  Niraj Rayalla

This file is part of 3-DPhysicsSim.    

3-DPhysicsSim is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

3-DPhysicsSim is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MATH_EXPRESSION
#define _MATH_EXPRESSION

#include <string>
#include <list>
#include <math.h>    
#include <stdio.h>
#include <stdlib.h>
using namespace std;

enum MathToken
{
	MathToken_None,
	LeftParen, RightParen,
	Operator,
	SpecialOperation,
	Word,
	Number
};

class MathExpressionToken
{
public:
	std::string lexeme;
	MathToken token;

	MathExpressionToken(std::string _lexeme, MathToken _token)
	{
		lexeme = _lexeme;
		token = _token;
	}

	~MathExpressionToken()
	{
		lexeme.clear();
	}
};

enum OperatorType
{
    NoOperator,
    Exponent,
    Multiplication,
    Division,
    Addition,
    Subtraction
};

enum SpecialOperations
{
    NoSpecialOperation,
    SpecialOp_Cos,
    SpecialOp_Sin,
    SpecialOp_Tan,
    SpecialOp_ACos,
    SpecialOp_ASin,
    SpecialOp_ATan,
    SpecialOp_CosH,
    SpecialOp_SinH,
    SpecialOp_TanH,
    SpecialOp_Abs,
    SpecialOp_Sqrt,
    SpecialOp_Log
};

class MathTerm
{
protected:
	OperatorType nextOperator;
	SpecialOperations specialOperation;
	std::list<MathTerm*>* subTermList;

public:
	MathTerm() 
	{ 
		nextOperator = NoOperator;
		specialOperation = NoSpecialOperation; 
		subTermList = NULL;
	}

	~MathTerm()
	{
		if (subTermList)
		{
			for (std::list<MathTerm*>::iterator it = subTermList->begin() ; it != subTermList->end(); it++ )
			{
				delete (*it);
			}

			delete subTermList;
		}
	}

	OperatorType GetNextOperator() { return nextOperator; }

	void SetNextOperator(OperatorType _nextOperator) { nextOperator = _nextOperator; }
	void SetSubTermList(std::list<MathTerm*>* _subTermList) { subTermList = _subTermList; }
	void SetSpeicalOperation(SpecialOperations _specialOperation) { specialOperation = _specialOperation; }

	void AddTerm(MathTerm* newMathTerm)
	{
		if (!subTermList)
			subTermList = new std::list<MathTerm*>();

		subTermList->push_back(newMathTerm);
	}

	virtual double GetValue(double* validVariables)
	{
		double value = 0.0;

		OperatorType currentOperator;

		std::list<MathTerm*>::iterator it = subTermList->begin();
		value = (*it)->GetValue(validVariables);
		currentOperator = (*it)->nextOperator;

		it++;

		for ( it ; it != subTermList->end(); it++ )
		{
			double newValue = (*it)->GetValue(validVariables);
			switch(currentOperator)
			{
			case Exponent:
				value = pow(value, newValue);
				break;
			case Addition:
				value += newValue;
				break;
			case Subtraction:
				value -= newValue;
				break;
			case Multiplication:
				value *= newValue;
				break;
			case Division:
				value /= newValue;
				break;
			}

			currentOperator = (*it)->nextOperator;
		}

		switch(specialOperation)
		{
		case SpecialOp_Cos:
			value = cos(value);
			break;
		case SpecialOp_Sin:
			value = sin(value);
			break;
		case SpecialOp_Tan:
			value = tan(value);
			break;
		case SpecialOp_ACos:
			value = acos(value);
			break;
		case SpecialOp_ASin:
			value = asin(value);
			break;
		case SpecialOp_ATan:
			value = atan(value);
			break;
		case SpecialOp_CosH:
			value = cosh(value);
			break;
		case SpecialOp_SinH:
			value = sinh(value);
			break;
		case SpecialOp_TanH:
			value = tanh(value);
			break;
		case SpecialOp_Abs:
			value = abs(value);
			break;
		case SpecialOp_Sqrt:
			value = sqrt(value);
			break;
		case SpecialOp_Log:
			value = log(value);
			break;
		}

		return value;
	}
};

class ConstantMathItem : public MathTerm
{
private:
	double number;

public:
	ConstantMathItem(double _number): MathTerm() { number = _number; }

	double GetValue(double* validVariables) { return number; }
};

class VariableMathItem : public MathTerm
{
private:
	std::string var;
	int index;

public:
	VariableMathItem(std::string _var, int _index): MathTerm() { var = _var; index = _index; }

	double GetValue(double* validVariables)
	{
		double value = 0.0;

		value = validVariables[index];

		return value;
	}
};

class MathExpression
{
private:
	std::list<MathExpressionToken*>* tokenList;
	MathTerm* wholeMathTerm;
	std::string* validVariables;
	int validVariablesSize;

	void Setup(std::string* _validVariables, int _validVariablesSize);

	bool IsLetter(char x);
	bool IsNumber(char x);
	bool IsOperator(char x);
	bool IsValidVariable(std::string x);
	bool IsSpecialOperation(std::string x);
	OperatorType GetOperatorType(std::string x);
	SpecialOperations GetSpecialOperationType(std::string x);
	MathTerm* GetMathTerm(std::list<MathExpressionToken*>::iterator itBegin, std::list<MathExpressionToken*>::iterator itEnd);
	std::list<MathExpressionToken*>::iterator GetParenEnd(std::list<MathExpressionToken*>::iterator itBegin, std::list<MathExpressionToken*>::iterator itFinalEnd);
	int GetValidVariableIndex(std::string lexeme);
public:
	std::string str;
	static std::string timeOnlyMathExpr[1];
	static std::string cartesianMathExpr[3];
	static std::string polar2DMathExpr[2];
	static std::string spherical3DMathExpr[3];

	MathExpression(const char* str_in, std::string* _validVariables, int _validVariablesSize);
	MathExpression(std::string str_in, std::string* _validVariables, int _validVariablesSize);
	~MathExpression();

	void RemoveWhiteSpace();
	std::list<MathExpressionToken*>* GetListOfTokens(std::string inStr);

	double GetValue(double* validVariableValues)
	{
		return wholeMathTerm->GetValue(validVariableValues);
	}
};

//std::string timeOnlyMathExpr[1];// = { "t" };

#endif
