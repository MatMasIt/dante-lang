typedef struct Stree {
    Stree *parent;
    ArrayList * children; //Stree **children;
    Token token;
} Stree;

STree sTreeInit(Token token, Stree *parent){
    Stree a;
    a.token = token;
    a.parent = parent;
    a.children = arraylist_new();
}

void sTreeAddChildren(Stree *this, Stree children){
   arraylist_append(this.children, children);
}
