
/**
 * @file Expression.cpp
 * @brief Expression
 *
 * @copyright 2022, GPL-3.0
 */
#include "ExpressionElement.cpp"
#include "ExpressionOperator.cpp"
/**
 * @brief Expression
 *
 */
class Expression
{
public:
    ExpressionElement a;
    ExpressionOperator operon;
    ExpressionElement b;
};
