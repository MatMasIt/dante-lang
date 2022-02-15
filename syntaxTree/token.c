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
    IfE * ifE;
} TokenValue;

typedef struct Token{
    TokeType tokenType;
    TokenValue tokenValue;
} Token;