/**
 * @file SyntaxTreeNode.cpp
 * @brief Syntax Tree, base of Abstract Syntax Tree
 *
 * @copyright 2022, GPL-3.0
 */
#include <vector>
#include <stdexcept> // out_of_range exception
#include "Token.cpp"
#include "Element.cpp"
/**
 * @brief Syntax tree node element, containing token, element, parent and children
 *
 */
class SyntaxTreeNode
{
public:
    std::vector<SyntaxTreeNode *> children;
    SyntaxTreeNode *parent;
    SyntaxToken token;
    Element element; // make this an abstract parent class
    /**
     * @brief Construct a new Syntax Tree Node object
     *
     */
    SyntaxTreeNode()
    {
        children = std::vector<SyntaxTreeNode *>();
        parent = nullptr;
        token = 0;
    }
    /**
     * @brief Add Children and return its pointer
     *
     * @param t SyntaxToken
     * @return SyntaxTreeNode* pointer to children
     */
    SyntaxTreeNode *addChild(SyntaxToken t)
    {
        SyntaxTreeNode *stn = new SyntaxTreeNode();
        stn->parent = this;
        stn->token = t;
        children.push_back(stn);
        return stn;
    }

    /**
     * @brief Print Syntax Tree
     */
    void printTree()
    {
    }
};

// TODO introduce bytecode
