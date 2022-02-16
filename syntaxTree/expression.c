typedef struct FunctionCall FunctionCall;
typedef struct Expression Expression;

typedef enum ExpressionElementType
{
    expression,
    functionCall,
    variable,
    literal
} ExpressionElementType;

typedef union ExpressionElementValue
{
    FunctionCall *functionCall;
    Expression *expression;
    Variable *variable;
    Literal *literal;
} ExpressionElementValue;

typedef enum ExpressionOperator
{
    assign, // =
    is,     // è
    isNot,  // non è
    not,    // non
    or
    ,          // o
    and,       // e
    xor,       // aut
    morethan,  // >
    lessthan,  // <
    moreequal, // >=
    lessequal, // <=
    plus,      // +
    minus,     // -
    times,     // *
    division,  // /
    modulo     // modulo
} ExpressionOperator;

typedef struct ExpressionElement
{
    ExpressionElementType type;
    ExpressionElementValue value;
} ExpressionElement;

typedef struct Expression
{
    ExpressionElement a;
    ExpressionOperator expressionOperator;
    ExpressionElement b;
} Expression;
