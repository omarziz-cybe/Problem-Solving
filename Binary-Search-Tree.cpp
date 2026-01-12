#include <iostream>
using namespace std;
struct binary_node
{
    int data;
    binary_node* left;
    binary_node* right;
};

class binary_search_tree
{
private:
    binary_node* root;

    binary_node* make_new_node(int dd)
    {
        binary_node* p = new binary_node;
        p->data = dd;
        p->left = NULL;
        p->right = NULL;
        return p;
    }

    void rec_insertion(binary_node* ptr, int dd)
    {
        if (dd < ptr->data)
        {
            if (ptr->left == NULL)
                ptr->left = make_new_node(dd);
            else
                rec_insertion(ptr->left, dd);
        }
        else if (dd > ptr->data)
        {
            if (ptr->right == NULL)
                ptr->right = make_new_node(dd);
            else
                rec_insertion(ptr->right, dd);
        }
    }

    void rec_pre_order(binary_node* ptr)
    {
        if (ptr != NULL)
        {
            cout << ptr->data << " ";
            rec_pre_order(ptr->left);
            rec_pre_order(ptr->right);
        }
    }

    void rec_in_order(binary_node* ptr)
    {
        if (ptr != NULL)
        {
            rec_in_order(ptr->left);
            cout << ptr->data << " ";
            rec_in_order(ptr->right);
        }
    }

    void rec_post_order(binary_node* ptr)
    {
        if (ptr != NULL)
        {
            rec_post_order(ptr->left);
            rec_post_order(ptr->right);
            cout << ptr->data << " ";
        }
    }

    bool rec_search(binary_node* ptr, int dd)
    {
        if (ptr == NULL)
            return false;
        if (ptr->data == dd)
            return true;
        if (dd < ptr->data)
            return rec_search(ptr->left, dd);
        else
            return rec_search(ptr->right, dd);
    }

    binary_node* find_min(binary_node* ptr)
    {
        while (ptr->left != NULL)
            ptr = ptr->left;
        return ptr;
    }

    bool rec_delete_data(binary_node*& ptr, int key)
    {
        if (ptr == NULL)
            return false;

        if (key < ptr->data)
            return rec_delete_data(ptr->left, key);
        else if (key > ptr->data)
            return rec_delete_data(ptr->right, key);
        else
        {
            if (ptr->left == NULL && ptr->right == NULL)
            {
                delete ptr;
                ptr = NULL;
            }
            else if (ptr->left == NULL)
            {
                binary_node* temp = ptr;
                ptr = ptr->right;
                delete temp;
            }
            else if (ptr->right == NULL)
            {
                binary_node* temp = ptr;
                ptr = ptr->left;
                delete temp;
            }
            else
            {
                binary_node* temp = find_min(ptr->right);
                ptr->data = temp->data;
                rec_delete_data(ptr->right, temp->data);
            }
            return true;
        }
    }

public:
    binary_search_tree()
    {
        root = NULL;
    }

    void insert_data(int dd)
    {
        if (root == NULL)
            root = make_new_node(dd);
        else
            rec_insertion(root, dd);
    }

    bool search_data(int dd)
    {
        return rec_search(root, dd);
    }

    bool remove_data(int dd)
    {
        return rec_delete_data(root, dd);
    }

    void print_pre_order()
    {
        rec_pre_order(root);
        cout << endl;
    }

    void print_in_order()
    {
        rec_in_order(root);
        cout << endl;
    }

    void print_post_order()
    {
        rec_post_order(root);
        cout << endl;
    }
};

int main()
{
    binary_search_tree bst;

    bst.insert_data(50);
    bst.insert_data(30);
    bst.insert_data(70);
    bst.insert_data(20);
    bst.insert_data(40);
    bst.insert_data(60);
    bst.insert_data(80);

    cout << "Tree contains the following elements (In-order): ";
    bst.print_in_order();

    cout << "Pre-order traversal: ";
    bst.print_pre_order();

    cout << "Post-order traversal: ";
    bst.print_post_order();

    cout << "After deleting 50, tree contains (In-order): ";
    bst.remove_data(50);
    bst.print_in_order();

    return 0;
}

