#include <vector>
#include <stdexcept> // out_of_range exception
#include "Token.cpp"
#include "Element.cpp"
class SyntaxTreeNode
{
public:
    std::vector<SyntaxTreeNode *> children;
    SyntaxTreeNode *parent;
    SyntaxToken token;
    Element element; // make this an abstract parent class
    SyntaxTreeNode()
    {
        children = std::vector<SyntaxTreeNode *>();
        parent = nullptr;
        token = 0;
    }
    SyntaxTreeNode *getChild(int i)
    {
        return children.at(i);
    }
    void setChild(SyntaxTreeNode *syntaxTreeNode, int pos)
    {
        children.at(pos) = syntaxTreeNode;
    }
    SyntaxTreeNode *addChild(Token t)
    {
        SyntaxTreeNode *stn = new SyntaxTreeNode();
        stn->parent = this;
        children.push_back(stn);
        return stn;
    }
};
