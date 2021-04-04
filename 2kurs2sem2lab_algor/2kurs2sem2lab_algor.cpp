#include <iostream>
#include <string>

using namespace std;
struct country {
    string name;
    string capital;
};
struct node {
    country data;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    bool color;
    int childs = 0;
};

class RB_TREE {

    node* root;

public:
    RB_TREE() : root(nullptr) {}

    node* GetRoot() { return root; }

    void insert(country input) {
        if (root == nullptr) {
            root = new node();
            root->data = input;
            root->parent = nullptr;
            root->color = 0;
            cout << "Added\n";
        }
        else {
            auto linker = GetRoot();
            node* newnode = new node();
            newnode->data = input;

            while (linker != nullptr) {
                linker->childs++;
                if (linker->data.capital > input.capital) {
                    if (linker->left == nullptr) {
                        linker->left = newnode;
                        newnode->color = 1;
                        newnode->parent = linker;
                        cout << "Added\n"; break;
                    }
                    else { linker = linker->left; }
                }
                else {
                    if (linker->right == nullptr) {
                        linker->right = newnode;
                        newnode->color = 1;
                        newnode->parent = linker;
                        cout << "Added\n"; break;
                    }
                    else { linker = linker->right; }
                }
            }
            insertclr(newnode);
        }
    }

    void insertclr(node* z) {
        while (z->parent->color == 1) {
            auto grandparent = z->parent->parent;
            auto uncle = GetRoot();
            if (z->parent == grandparent->left) {
                if (grandparent->right) { uncle = grandparent->right; }
                if (uncle->color == 1) {
                    z->parent->color = 0;
                    uncle->color = 0;
                    grandparent->color = 1;
                    if (grandparent->data.capital != root->data.capital) { z = grandparent; }
                    else { break; }
                }
                else if (z == grandparent->left->right) {
                    L_rotate(z->parent);
                }
                else {
                    z->parent->color = 0;
                    grandparent->color = 1;
                    R_rotate(grandparent);
                    if (grandparent->data.capital != root->data.capital) { z = grandparent; }
                    else { break; }
                }
            }
            else {
                if (grandparent->left) { uncle = grandparent->left; }
                if (uncle->color == 1) {
                    z->parent->color = 0;
                    uncle->color = 0;
                    grandparent->color = 1;
                    if (grandparent->data.capital != root->data.capital) { z = grandparent; }
                    else { break; }
                }
                else if (z == grandparent->right->left) {
                    R_rotate(z->parent);
                }
                else {
                    z->parent->color = 0;
                    grandparent->color = 1;
                    L_rotate(grandparent);
                    if (grandparent->data.capital != root->data.capital) { z = grandparent; }
                    else { break; }
                }
            }
        }
        root->color = 0;
    }

    void RemoveNode(node* parent, node* curr, country input) {
        if (curr == nullptr) { return; }
        if (curr->data.capital == input.capital) {
            //CASE -- 1
            if (curr->left == nullptr && curr->right == nullptr) {
                node* decreas = curr->parent;
                if (parent->data.capital == curr->data.capital) { root = nullptr; }
                else if (parent->right == curr) {
                    deletefix(curr);
                    parent->right = nullptr;
                }
                else {
                    deletefix(curr);
                    parent->left = nullptr;
                }
                while (decreas != nullptr) {
                    decreas->childs--;
                    decreas = decreas->parent;
                }
            }
            //CASE -- 2
            else if (curr->left != nullptr && curr->right == nullptr) {
                country swap = curr->data;
                //               int swap_c=curr->childs;
                curr->data = curr->left->data;
                //               curr->childs=curr->left->childs;
                curr->left->data = swap;
                //               curr->left->childs=swap_c;
                RemoveNode(curr, curr->left, input);
            }
            else if (curr->left == nullptr && curr->right != nullptr) {
                country swap = curr->data;
                //             int swap_c=curr->childs;
                curr->data = curr->right->data;
                //              curr->childs=curr->right->childs;
                curr->right->data = swap;
                //             curr->right->childs=swap_c;
                RemoveNode(curr, curr->right, input);
            }
            //CASE -- 3
            else {
                bool flag = false;
                node* temp = curr->right;
                while (temp->left) { flag = true; parent = temp; temp = temp->left; }
                if (!flag) { parent = curr; }
                country swap = curr->data;
                curr->data = temp->data;
                temp->data = swap;
                RemoveNode(parent, temp, swap);
            }
        }
    }

    void Remove(country input) {
        auto temp = root;
        auto parent = temp;
        bool flag = false;
        if (!temp) { return; }

        while (temp) {
            if (input.capital == temp->data.capital) { flag = true; RemoveNode(parent, temp, input); break; }
            else if (input.capital < temp->data.capital) { parent = temp; temp = temp->left; }
            else { parent = temp; temp = temp->right; }
        }

        if (!flag) { cout << "\nnot found"; }
    }

    void deletefix(node* z) {
        while (z->data.capital != root->data.capital && z->color == 0) {
            auto sibling = GetRoot();
            if (z->parent->left == z) {
                if (z->parent->right) { sibling = z->parent->right; }
                if (sibling) {
                    //CASE -- 1
                    if (sibling->color == 1) {
                        sibling->color = 0;
                        z->parent->color = 1;
                        L_rotate(z->parent);
                        sibling = z->parent->right;
                    }
                    //CASE -- 2
                    if (sibling->left == nullptr && sibling->right == nullptr) {
                        sibling->color = 1;
                        z = z->parent;
                    }
                    else if (sibling->left->color == 0 && sibling->right->color == 0) {
                        sibling->color = 1;
                        z = z->parent;
                    }
                    //CASE -- 3
                    else if (sibling->right->color == 0) {
                        sibling->left->color = 0;
                        sibling->color = 1;
                        R_rotate(sibling);
                        sibling = z->parent->right;
                    }
                    else {
                        sibling->color = z->parent->color;
                        z->parent->color = 0;
                        if (sibling->right) { sibling->right->color = 0; }
                        L_rotate(z->parent);
                        z = root;
                    }
                }
            }
            else {
                if (z->parent->right == z) {
                    if (z->parent->left) { sibling = z->parent->left; }
                    if (sibling) {
                        //CASE -- 1
                        if (sibling->color == 1) {
                            sibling->color = 0;
                            z->parent->color = 1;
                            R_rotate(z->parent);
                            sibling = z->parent->left;
                        }
                        //CASE -- 2
                        if (sibling->left == nullptr && sibling->right == nullptr) {
                            sibling->color = 1;
                            z = z->parent;
                        }
                        else if (sibling->left->color == 0 && sibling->right->color == 0) {
                            sibling->color = 1;
                            z = z->parent;
                        }
                        //CASE -- 3 
                        else if (sibling->left->color == 0) {
                            sibling->right->color = 0;
                            sibling->color = 1;
                            R_rotate(sibling);
                            sibling = z->parent->left;
                        }
                        else {
                            sibling->color = z->parent->color;
                            z->parent->color = 0;
                            if (sibling->left) { sibling->left->color = 0; }
                            L_rotate(z->parent);
                            z = root;
                        }
                    }
                }

            }
        }
        z->color = 0;
    }

    node* search(country input) {
        auto temp = GetRoot();
        if (temp == nullptr) { return nullptr; }

        while (temp) {
            if (input.capital == temp->data.capital) { return temp; }
            else if (input.capital < temp->data.capital) { temp = temp->left; }
            else { temp = temp->right; }
        }
        return nullptr;
    }

    void L_rotate(node* x) {
        node* nw_node = new node();
        if (x->right->left) { nw_node->right = x->right->left; }
        nw_node->left = x->left;
        nw_node->data = x->data;
        nw_node->color = x->color;
        x->data = x->right->data;
        x->color = x->right->color;
        x->left = nw_node;
        if (nw_node->left) { nw_node->left->parent = nw_node; }
        if (nw_node->right) { nw_node->right->parent = nw_node; }
        nw_node->parent = x;

        if (x->right->right) { x->right = x->right->right; }
        else { x->right = nullptr; }

        if (x->right) { x->right->parent = x; }
        childcheck(root);
    }

    void R_rotate(node* x) {
        node* nw_node = new node();
        if (x->left->right) { nw_node->left = x->left->right; }
        nw_node->right = x->right;
        nw_node->data = x->data;
        nw_node->color = x->color;

        x->data = x->left->data;
        x->color = x->left->color;

        x->right = nw_node;
        if (nw_node->left) { nw_node->left->parent = nw_node; }
        if (nw_node->right) { nw_node->right->parent = nw_node; }
        nw_node->parent = x;

        if (x->left->left) { x->left = x->left->left; }
        else { x->left = nullptr; }

        if (x->left) { x->left->parent = x; }
        childcheck(root);
    }
    
    void find_n(int n) {
        if (n < 0 || n > root->childs + 1) {
            cout << "N > size";
        }

        node* current = root;
        for (;;) {
            if (n == 0) {
                while (current->left != nullptr) current = current->left;
                break;
            }
            if ((current->left->childs + (current->left != nullptr)) != n) {
                if (current->left->childs >= n) {
                    current = current->left;

                }
                else {
                    n -= (current->left->childs + 1 + (current->left != nullptr));
                    current = current->right;
                }
            }
            else break;
        }
        cout << current->data.capital << endl;
    }
    void showtree(node* temp) {
        if (!temp) { return; }
        if (temp->left) {
            //      cout << "\""<< temp->data.capital << " "<< temp->childs<< "\" -> \"" << temp->left->data.capital  << " "<< temp->left->childs <<"\"" << endl;
            cout << temp->data.capital << " -> " << temp->left->data.capital << endl;
        }
        if (temp->right) {
            //        cout << "\""<< temp->data.capital << " "<< temp->childs<< "\" -> \"" << temp->right->data.capital  << " "<< temp->right->childs <<"\"" << endl;
            cout << temp->data.capital << " -> " << temp->right->data.capital << endl;
        }
        showtree(temp->left);
        showtree(temp->right);
    }
    void showcolor(node* temp) {
        if (!temp) { return; }
        if (temp->color == 1)
            cout << temp->data.capital << " [color=red]" << endl;
        if (temp->left)
            showcolor(temp->left);
        if (temp->right)
            showcolor(temp->right);
    }
    int childcheck(node* y) {
        if (y != nullptr) {
            y->childs = 0;
            y->childs += childcheck(y->left) + 1;
            y->childs += childcheck(y->right) + 1;
            return y->childs;
        }
        else return -1;
    }
};

int main() {
    RB_TREE tree;
    tree.insert({ "Ukraine","Kyiv" });
    tree.insert({ "Russia","Moscow" });
    tree.insert({ "Germany","Berlin" });
    tree.insert({ "Italy","Roma" });
    tree.insert({ "Polland","Warsaw" });
    cout << "digraph g{\n";
    tree.showtree(tree.GetRoot());
    tree.showcolor(tree.GetRoot());
    cout << "}\n";
    tree.insert({ "Spain","Madrid" });
    cout << endl;
    cout << "digraph g{\n";
    tree.showtree(tree.GetRoot());
    tree.showcolor(tree.GetRoot());
    cout << "}\n";
    

    

    tree.Remove({ "Spain","Madrid" });
    cout << "\n\n";
    cout << "digraph g{\n";
    tree.showtree(tree.GetRoot());
    tree.showcolor(tree.GetRoot());
    cout << "}\n";
    int index = 0;
    while (true) {
        if (index >= tree.GetRoot()->childs + 1) break;
        tree.find_n(index);
        index++;
    }


    return 0;
}