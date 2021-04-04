#include <iostream>
using namespace std;



struct node
{
   
    node* left, * right;
    string country;
    string capital;
};


node* newNode(string country,string capital)
{
    node* Node = new node();
    Node->country = country;
    Node->capital = capital;
    Node->left = Node->right = NULL;
    return (Node);
}


node* rightRotate(node* x)
{
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}


node* leftRotate(node* x)
{
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
 
node* splay(node* root, string country)
{
    
    if (root == NULL || root->country == country)
        return root;

    if (root->country > country)
    {
        if (root->left == NULL) return root;

        if (root->left->country > country)
        {
            
            root->left->left = splay(root->left->left, country);

          
            root = rightRotate(root);
        }
        else if (root->left->country < country) 
        {
          
            root->left->right = splay(root->left->right, country);

            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    }
    else
    {
        
        if (root->right == NULL) return root;

        if (root->right->country > country)
        {
            root->right->left = splay(root->right->left, country);

            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->country < country)
        {
            
            root->right->right = splay(root->right->right, country);
            root = leftRotate(root);
        }

        
        return (root->right == NULL) ? root : leftRotate(root);
    }
}


node* search(node* root, string country)
{
    return splay(root, country);
}


void preOrder(node* root)
{
    if (root != NULL)
    {
        cout << root->country << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

node* insert(node* root, string country,string capital)
{
    
    if (root == NULL) return newNode(country, capital);

    root = splay(root, country);

    if (root->country == country) return root;

    node* newnode = newNode(country,capital);

    
    if (root->country > country)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }

    
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode; 
}


struct node* delete_count(struct node* root, string country)
{
    struct node* temp;
    if (!root)
        return NULL;

    root = splay(root, country);

    
    if (country != root->country)
        return root;

    
    if (!root->left)
    {
        temp = root;
        root = root->right;
    }
    else if (!root->right)
    {
        temp = root;
        root = root->left;
    }
    else
    {
        temp = root;

        
        root = splay(root->left, country);

        
        root->right = temp->right;
    }

    
    free(temp);

    return root;

}
void showtree(node* temp) {
    if (!temp) { return; }
    if (temp->left) {
        cout << temp->country<< " -> " << temp->left->country << endl;
    }
    if (temp->right) {
        cout << temp->country << " -> " << temp->right->country << endl;
    }
    showtree(temp->left);
    showtree(temp->right);
}
int main()
{
    node* root = newNode("Ukraine","kyiv");
    root=insert(root, "Germany","Berlin" );
    root=insert(root, "Spain","Madrid" );
    root = insert(root, "Russia", "Moscow");
    root = insert(root, "Italy", "Roma");
    root = insert(root, "Polland", "Warsaw");
    cout << "digraph g{\n";
    showtree(root);
    cout << "}\n";


    root=search(root, "Russia");
    cout << "digraph g{\n";
    showtree(root);
    cout << "}\n";


    root=delete_count(root, "Russia");
    cout << "digraph g{\n";
    showtree(root);
    cout << "}\n";
    
    return 0;
}
