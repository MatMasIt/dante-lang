typedef struct Variable
{
} Variable;
typedef enum ExpressionElementType
{
    expression,
    functionCall,
    variable,
    literal
} ExpressionElementType;
typedef enum ExpressionOperator
{
    assign,
    is,
    isNot,
    not,
    or,
    and,
    xor,
    morethan,
    lessthan,
    moreequal,
    lessequal,
    plus,
    minus,
   times,
   division,
   mmodulo
};
//                              {=, è, non è, non, o, e, aut, >, <, >=, <= , +, -, *, /, modulo}
typedef struct Expression
{
    ExpressionElement a;
    ExpressionOperator expressionOperator;
    ExpressionElement b;
} Expression;
typedef struct IfE
{
    Expression expression;
} IfE;
typedef enum TokenType{
     mainT,
     iftT,
     elseifT,
     elseT,
     elseifT,
     elseT,
     returnT,
     callT,
     argtT,
     importT,
     fromT,
     funcT,
     retutnsT,
     predefinedT
} TokenType;
typedef union TokenValue{
    Function * function;
    Expression * expression;
    IfE *ifE;
} TokenValue;
typedef struct Token{
    TokeType tokenType;
    TokenValue tokenValue;
} Token;
typedef struct Stree
{
    Stree *parent;
    Stree **children;
    Token token;
} Stree;
