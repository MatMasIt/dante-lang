#include <vector>
#include <stdexcept> // out_of_range exception
class SyntaxTreeNode{
    public:
        std::vector<SyntaxTreeNode> children();
        SyntaxTreeNode *parent;
        Token token;
        int vecPos;
        SyntaxTreeNode getChild(int i){
            return children.at(i);
        }
        void setChild(SyntaxTreeNode syntaxTreeNode){
            children.at(syntaxTreeNode.vecPos) = syntaxTreeNode;
        }
        SyntaxTreeNode addChild(Token t){
            SyntaxTreeNode stn;
            stn.vecPos = children.size()-1;
            *(stn.parent) = this;
            vector.push_back(stn);
            return stn;
        }
};
