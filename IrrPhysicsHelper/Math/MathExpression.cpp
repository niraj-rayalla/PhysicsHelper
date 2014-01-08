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

#include "MathExpression.h"

std::string MathExpression::timeOnlyMathExpr[1] = {"t"};
std::string MathExpression::cartesianMathExpr[3] = {"x", "y", "z" };
std::string MathExpression::polar2DMathExpr[2] = {"theta", "r"};
std::string MathExpression::spherical3DMathExpr[3] = {"theta", "phi", "r"};
void MathExpression::Setup(std::string* _validVariables, int _validVariablesSize)
{
	RemoveWhiteSpace();

	validVariables = _validVariables;
	validVariablesSize = _validVariablesSize;

	tokenList = GetListOfTokens(str);
	wholeMathTerm = GetMathTerm(tokenList->begin(), tokenList->end());
}

MathExpression::MathExpression(const char *str_in, std::string* _validVariables, int _validVariablesSize)
{
	str = str_in;
	Setup(_validVariables, _validVariablesSize);
}

MathExpression::MathExpression(std::string str_in, std::string* _validVariables, int _validVariablesSize)
{
	str = str_in;
	Setup(_validVariables, _validVariablesSize);
}

MathExpression::~MathExpression()
{
	if (tokenList)
	{
		for (std::list<MathExpressionToken*>::iterator it = tokenList->begin() ; it != tokenList->end(); it++ )
		{
			delete (*it);
		}
		delete tokenList;
	}
	delete wholeMathTerm;
}


void MathExpression::RemoveWhiteSpace()
{
	unsigned int i;
	for (i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			str.erase(i, 1);
			i--;
		}
	}
}

bool MathExpression::IsLetter(char x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return true;

	return false;
}

bool MathExpression::IsNumber(char x)
{
	if ((x >= '0' && x <= '9') || x == '.' || x == '-')
		return true;

	return false;
}

bool MathExpression::IsOperator(char x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^' )
		return true;

	return false;
}

//Check if a given std::string is a variable that is allowed.
bool MathExpression::IsValidVariable(std::string x)
{
	if (validVariables)
	{
		for (int i = 0; i < validVariablesSize; i++)
		{
			if (x == validVariables[i])
			{
				return true;
			}
		}
	}

	return false;
}

//Check if a given std::string is a special operation.
bool MathExpression::IsSpecialOperation(std::string x)
{
	if ( x == "cos" || x == "sin" || x == "tan" || x == "acos" || x == "asin" || x == "atan" || 
			x == "cosh" || x == "sinh" || x == "tanh" || x == "abs" || x == "sqrt" || x == "log")
			return true;

	return false;
}

//Get a std::std::list of MathExpressionTokens.
std::list<MathExpressionToken*>* MathExpression::GetListOfTokens(std::string inStr)
{
	std::list<MathExpressionToken*>* tokenList = new std::list<MathExpressionToken*>();
	std::string currentTokenLexeme = "";
	MathToken currentToken = MathToken_None;
	bool changed = false;

	unsigned int i;
	for (i = 0; i < inStr.length(); i++)
	{
		MathToken newToken;

		if (IsLetter(str[i]))
		{
			newToken = Word;
		}
		else if (IsNumber(str[i]))
		{
			//For negative sign make sure it is part of a number. If not then it's an operator.
			if ((currentToken == Number || currentToken == Word || currentToken == RightParen) && str[i] == '-')
			{
				newToken = Operator;
			}
			else
			{
				newToken = Number;
			}
		}
		else if (IsOperator(str[i]))
		{
			newToken = Operator;
		}
		else if (str[i] == '(')
		{
			newToken = LeftParen;
		}
		else if (str[i] == ')')
		{
			newToken = RightParen;
		}
		else
		{
			delete tokenList;
			return NULL;
		}

		//If this letter is not the first and the newToken does not equal to the old token then add the previous cause
		//a new token has started.
		if (currentTokenLexeme != "" && currentToken != newToken)
		{
			//If the token to be added is a word then check if it valid variable or a special operation.
			if (currentToken == Word)
			{
				bool isSpecialOp = IsSpecialOperation(currentTokenLexeme);
				bool isValidVar = IsValidVariable(currentTokenLexeme);
				if (!isValidVar && !isSpecialOp)
				{
					delete tokenList;
					return NULL;
				}

				if (isSpecialOp)
					currentToken = SpecialOperation;
			}

			tokenList->push_back(new MathExpressionToken(currentTokenLexeme, currentToken));
			currentTokenLexeme = "";
		}

		currentTokenLexeme += str[i];
		currentToken = newToken;
	}

	if (currentTokenLexeme != "")
	{
		tokenList->push_back(new MathExpressionToken(currentTokenLexeme, currentToken));
	}

	return tokenList;
}

OperatorType MathExpression::GetOperatorType(std::string x)
{
	if (x == "+")
	{
		return Addition;
	}
	else if (x == "-")
	{
		return Subtraction;
	}
	else if (x == "*")
	{
		return Multiplication;
	}
	else if (x == "/")
	{
		return Division;
	}
	else if (x == "^")
	{
		return Exponent;
	}

	return NoOperator;
}

SpecialOperations MathExpression::GetSpecialOperationType(std::string x)
{
	if (x == "cos")
	{
		return SpecialOp_Cos;
	}
	else if (x == "sin")
	{
		return SpecialOp_Sin;
	}
	else if (x == "tan")
	{
		return SpecialOp_Tan;
	}
	else if (x == "acos")
	{
		return SpecialOp_ACos;
	}
	else if (x == "asin")
	{
		return SpecialOp_ASin;
	}
	else if (x == "atan")
	{
		return SpecialOp_ATan;
	}
	else if (x == "cosh")
	{
		return SpecialOp_CosH;
	}
	else if (x == "sinh")
	{
		return SpecialOp_SinH;
	}
	else if (x == "tanh")
	{
		return SpecialOp_TanH;
	}
	else if (x == "abs")
	{
		return SpecialOp_Abs;
	}
	else if (x == "sqrt")
	{
		return SpecialOp_Sqrt;
	}
	else if (x == "log")
	{
		return SpecialOp_Log;
	}

	return NoSpecialOperation;
}

std::list<MathExpressionToken*>::iterator MathExpression::GetParenEnd(std::list<MathExpressionToken*>::iterator itBegin, std::list<MathExpressionToken*>::iterator itFinalEnd)
{
	int parenValue = 1;

	std::list<MathExpressionToken*>::iterator it = itBegin;
	for(it; it != itFinalEnd; it++)
	{
		if ((*it)->token == LeftParen)
		{
			parenValue++;
		}
		else if ((*it)->token == RightParen)
		{
			parenValue--;
		}

		if (parenValue == 0)
			break;
	}

	return it;
}

int MathExpression::GetValidVariableIndex(std::string lexeme)
{
	for (int i = 0; i < validVariablesSize; i++)
	{
		if (lexeme == validVariables[i])
		{
			return i;
		}
	}

	return -1;
}

MathTerm* MathExpression::GetMathTerm(std::list<MathExpressionToken*>::iterator itBegin, std::list<MathExpressionToken*>::iterator itEnd)
{
	std::list<MathTerm*>* mathTerm = new std::list<MathTerm*>();

	std::list<MathTerm*>* subMathTerm = new std::list<MathTerm*>();
	MathTerm* lastAddedMathTerm = NULL;
	SpecialOperations specialOp = NoSpecialOperation;
	MathTerm* exponentTerm = NULL;

	std::list<MathExpressionToken*>::iterator itParenBegin;
	std::list<MathExpressionToken*>::iterator itParenEnd;

	std::list<MathExpressionToken*>::iterator it = itBegin;
	for(it; it != itEnd; it++)
	{
		/*if (parenLevel == 0)
		{*/
			//Get the math term for all token till a plus or minus sign on the begining level.
			if (lastAddedMathTerm)
			{
				if ((*it)->token == Operator)
				{
					OperatorType operatorType = GetOperatorType((*it)->lexeme);

					if (operatorType == Addition || operatorType == Subtraction)
					{
						MathTerm* additionTerm = new MathTerm();
						additionTerm->SetNextOperator(operatorType);
						additionTerm->SetSubTermList(subMathTerm);
						mathTerm->push_back(additionTerm);

						subMathTerm = new std::list<MathTerm*>();
					}
					else
					{
						//If an ^ operator is found then a new math term should be made for the number
						//being powered. So remove the lastAddedMathTerm from the std::std::list and add the new term
						//that will be made for the exponent term. If no exponent operator then just set the
						//last math term's operator to the one found.
						if (operatorType == Exponent)
						{
							subMathTerm->pop_back();
							exponentTerm = new MathTerm();
							exponentTerm->AddTerm(lastAddedMathTerm);
							subMathTerm->push_back(exponentTerm);
						}
						
						lastAddedMathTerm->SetNextOperator(operatorType);
					}
					
					lastAddedMathTerm = NULL;
					//No need to check for adding cause cant add operator as a math term.
					continue;
				}
				else
				{
					if (!exponentTerm)
						lastAddedMathTerm->SetNextOperator(Multiplication);
				}
			}
			else
			{
				if ((*it)->token == Operator)
				{
					//An operator occured at the start.
					delete mathTerm;
					return NULL;
				}
			}

			//Now add the current token's math term or recursivley add it if left paren found
			if ((*it)->token == Number)
			{
				lastAddedMathTerm = new ConstantMathItem(atof((*it)->lexeme.c_str()));
			}
			else if ((*it)->token == Word)
			{
				std::string lexeme = (*it)->lexeme;
				lastAddedMathTerm = new VariableMathItem(lexeme, GetValidVariableIndex(lexeme));
			}
			else if ((*it)->token == LeftParen)
			{
				std::list<MathExpressionToken*>::iterator newEnd = GetParenEnd(++it, itEnd);
				lastAddedMathTerm = GetMathTerm(it, newEnd);
				it = newEnd;
				if (it == itEnd)
					break;
			}
			else if ((*it)->token == RightParen)
			{
				//An extra right paren, so error.
				delete mathTerm;
				return NULL;
			}
			else if ((*it)->token == SpecialOperation)
			{
				specialOp = GetSpecialOperationType((*it)->lexeme);
				continue;
			}

			if (exponentTerm)
			{
				exponentTerm->AddTerm(lastAddedMathTerm);

				lastAddedMathTerm = exponentTerm;
				exponentTerm = NULL;
			}
			else
			{
				subMathTerm->push_back(lastAddedMathTerm);				
			}

			if (specialOp != NoSpecialOperation)
			{
				lastAddedMathTerm->SetSpeicalOperation(specialOp);
				specialOp = NoSpecialOperation;
			}
	}

	MathTerm* additionTerm = new MathTerm();
	additionTerm->SetNextOperator(NoOperator);
	additionTerm->SetSubTermList(subMathTerm);
	mathTerm->push_back(additionTerm);

	MathTerm* finalTerm  = new MathTerm();
	finalTerm->SetNextOperator(NoOperator);
	finalTerm->SetSubTermList(mathTerm);

	return finalTerm;
}