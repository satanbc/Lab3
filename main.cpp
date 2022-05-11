#include <iostream>

using namespace std;

struct node
{
    int key;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; height = 1; }
};

void print(node *tree)
{
    if (tree != NULL)
    {
        print(tree->left);
        cout<<tree->key;
        print(tree->right);
    }
}

unsigned char height(node* tree)
{
    return tree?tree->height:0;
}

int bfactor(node* tree)
{
    return height(tree->right)-height(tree->left);
}

void fixheight(node* tree)
{
    unsigned char hl = height(tree->left);
    unsigned char hr = height(tree->right);
    tree->height = (hl>hr?hl:hr)+1;
}

node* Rright(node* p)
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* Rleft(node* q)
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* tree)
{
    fixheight(tree);
    if( bfactor(tree)==2 )
    {
        if( bfactor(tree->left) < 0 )
            tree->left = Rright(tree->left);
        return Rright(tree);
    }
    if( bfactor(tree)==-2 )
    {
        if( bfactor(tree->right) > 0  )
            tree->right = Rright(tree->right);
        return Rleft(tree);
    }
    return tree;
}

node* add(node *tree, int k)
{
    if( !tree ) return new node(k);
    if( k<tree->key )
        tree->left = add(tree->left,k);
    else
        tree->right = add(tree->right,k);
    return balance(tree);
}

void menu(){
    cout << "-----------------" << endl;
    cout << "1-Add an element" << endl;
    cout << "2-Print the tree" << endl;
    cout << "0-Exit" << endl;
    cout << "-----------------" << endl;
    cout << endl;
    cout << "You choose: ";
}

void selectAction() {
    node *t = NULL;
    int e;
        int button;
        cin >> button;
        switch (button) {
            case 1: {
                cout << endl;
                cout << endl;

                cout << "Insert an element: ";
                cin >> e;
                add(t, e);

                cout << endl;
                cout << endl;
                break;
            }
            case 2: {
                cout << endl;
                cout << endl;

                print(t);

                cout << endl;
                cout << endl;
                break;
            }
            case 0: {
                exit(1);
            }
        }
}

int main() {
    while(true){
        menu();
        selectAction();
    }
}
