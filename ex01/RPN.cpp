#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& other) : _stack(other._stack)
{
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(const std::string& token)
{
    return token == "+" || token == "-" ||
           token == "*" || token == "/";
}

void RPN::calculate(const std::string& token)
{
    if (_stack.size() < 2)
        throw std::runtime_error("Error");
    int right = _stack.top();
    _stack.pop();
    int left = _stack.top();
    _stack.pop();
    int result;
    if (token == "+")
        result = left + right;
    else if (token == "-")
        result = left - right;
    else if (token == "*")
        result = left * right;
    else
    {
        if (right == 0)
            throw std::runtime_error("Error");
        result = left / right;
    }

    _stack.push(result);
}

void RPN::parsing(const std::string& expression)
{
    if (expression.empty())
        throw std::runtime_error("Error");

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && std::isdigit(token[0])){
            _stack.push(token[0] - '0');
        }
        else if (isOperator(token)){
            calculate(token);
        }
        else{
            throw std::runtime_error("Error");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    std::cout << _stack.top() << std::endl;
}
