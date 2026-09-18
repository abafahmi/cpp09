#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

class RPN
{
private:
    std::stack<int> _stack;

    bool isOperator(const std::string& token);
    void calculate(const std::string& token);

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    void parsing(const std::string& expression);
};

#endif
