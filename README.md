# Codewars-Problem-Response
Diff function to find the derivative of a string expression with respect to x.

[Problem Link](https://www.codewars.com/kata/584daf7215ac503d5a0001ae/cpp)

Works on funcs with format (op a b) and (func a)

Works with operands '+, -, *, /, ^'

Works with functions 'sin, cos, tan, exp, ln'

Exponent only works when raised to constants, since implementing f(x)^g(x) derivative is complex.

Simple DFS implementation.
Uses basic derivative rules.
No error checking.
