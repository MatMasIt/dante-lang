typedef enum VariableType{
    integer,
    decimal,
    string,
    object
}  VariableType;

typedef union VariableValue{
    int integer;
    float decimal;
    char * string;
    void * object;
} VariableValue;

typedef struct Variable
{
    VariableType type;
    VariableValue value;
} Variable;
