typedef struct FunctionCall
{
    ArrayList *parameters; // Expression *expression;
} FunctionCall;

void sTreeAddFunctionCallParameter(FunctionCall *this, Expression *children)
{
    arraylist_append(this->parameters, children);
}
