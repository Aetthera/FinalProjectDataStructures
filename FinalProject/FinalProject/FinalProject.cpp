// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <iterator>
#include <stack>
using namespace std;

typedef std::string String;
struct TreeNode {
    String medicareId; // unique identifier cannot be duplicated
    int directContacts = 0; // no. of children a node has, default 0
    int totalCases = 1; // no. of nodes rooted at this tree node including self
    TreeNode* parentPtr; // pointer to the parent node
    list<TreeNode*> directContactsPtrList; // list of pointers to children nodes
    TreeNode(String medId) { medicareId = medId; parentPtr = nullptr; };
    TreeNode(TreeNode* parentPt, String medId) { medicareId = medId; parentPtr = parentPt; };

};


class ContactTree {
private:
    TreeNode* root;
    int size;
    void IncrementTotalCases(TreeNode*);
public :
    ContactTree();
    ~ContactTree();
    bool IsEmpty();
    int GetSize();
    void AddPatient0(String medId);
    void AddContact(String parentId, String childId);
    TreeNode* LookUpContact(String id);
    void DeleteContact(String id);
    void DisplayContact(String id);
    void DisplayContact(TreeNode*);
    void Tracesource(String id);
    void PrintContactCases(String id);
    void PrintContactTree();
    void PrintHierarchicalTree();
};


ContactTree::ContactTree(){
    this->root =nullptr;
    this->size = 0;
}

bool ContactTree::IsEmpty() {
    return root == nullptr;
}

int ContactTree::GetSize() { return this->size; }

void ContactTree::AddPatient0(String medId) {
    if (IsEmpty()) {
        TreeNode* newNode = new TreeNode(medId);
        root = newNode;
    }
}

void ContactTree::AddContact(String parentId, String childId) {
    if (IsEmpty()) {
        cout << "The tree is empty" << endl;
        return;
    }

    TreeNode* parent = LookUpContact(parentId);
    if (parent == nullptr) {
        cout << "parent is not in the list" << endl;
        return;
    }
    TreeNode* newNode = new TreeNode(parent, childId);
    parent->directContactsPtrList.push_back(newNode);
    parent->directContacts++;
    IncrementTotalCases(newNode);
}

TreeNode* ContactTree::LookUpContact(String id) { 
    if (root == nullptr) {
        cout << "The contact tree is empty" << endl;
        return nullptr;
    }

    // Implementing breath first search
    queue<TreeNode*> q;
    
    q.push(root);

    while(q.empty() == false){
        TreeNode* node = q.front();
        q.pop();

        if (node->medicareId == id) { return node; }

        list<TreeNode*>::iterator it;
        for (it = node->directContactsPtrList.begin(); it != node->directContactsPtrList.end();++it) {
            q.push(*it);
        }
    }

    return nullptr;
}

void ContactTree::DisplayContact(String id) {
    TreeNode* node = LookUpContact(id);
    if (node == nullptr) {
        cout << "The patient does not exist";
        return;
    }

    DisplayContact(node);
}

void ContactTree::DisplayContact(TreeNode* node) {
    cout<<"Medicare id: " << node->medicareId << endl;
    cout << "Direct contacts: " << node->directContacts << endl;
    cout << "Total cases: " << node->totalCases << endl;
    cout << endl<<endl;
}

void ContactTree::Tracesource(String id) {
    TreeNode* node = LookUpContact(id);
    if (node == nullptr) {
        cout << "The patient does not exist";
        return;
    }

    cout << "Tracing " << id << " source" << endl;
    while (node != nullptr) {
        DisplayContact(node);
        node = node->parentPtr;
    }
}

void ContactTree::PrintContactCases(String id) {
    TreeNode* node = LookUpContact(id);
    if (node == nullptr) {
        cout << "The patient does not exist";
        return;
    }
    cout << id << " direct contacts:" << endl;
    list<TreeNode*>::iterator it;
    for (it = node->directContactsPtrList.begin(); it != node->directContactsPtrList.end();++it) {
        DisplayContact(*it);
    }
}


void ContactTree::PrintContactTree() {
    if (root == nullptr) {
        cout << "The contact tree is empty" << endl;
        return;
    }
    queue<TreeNode*> q;

    q.push(root);
    
    cout << "Printing contact tree" << endl;
    while (q.empty() == false) {
        TreeNode* node = q.front();
        q.pop();

        DisplayContact(node);

        list<TreeNode*>::iterator it;
        for (it = node->directContactsPtrList.begin(); it != node->directContactsPtrList.end();++it) {
            q.push(*it);
        }
    }

    return;
}


void ContactTree::PrintHierarchicalTree() {
    
    // Implementing depth first search
    stack<TreeNode*> s;
    s.push(root);

    while (s.empty() == false) {
        TreeNode* node = s.top();
        cout << node->medicareId << endl;
        s.pop();

        list<TreeNode*>::iterator it;
        for (it = node->directContactsPtrList.begin(); it != node->directContactsPtrList.end();++it) {
            s.push(*it);
        }
    }


}

void ContactTree::IncrementTotalCases(TreeNode* node){
    node = node->parentPtr;
    while (node != nullptr) {
        node->totalCases++;
        node = node->parentPtr;
    }
}

int main()
{
    
    cout << "\n\n\n";

    ContactTree* contactTree = new ContactTree();
    contactTree->AddPatient0("A");
    contactTree->AddContact("A","Z");
    contactTree->AddContact("A", "K");
    contactTree->AddContact("Z", "Y");
    contactTree->AddContact("Z", "M");
    contactTree->AddContact("K", "L");
    contactTree->AddContact("K", "B");
    contactTree->AddContact("A", "O");

    /*cout << "\n\n\n";
    contactTree->DisplayContact("Z");

    cout << "\n\n\n";
    contactTree->Tracesource("A");
    contactTree->Tracesource("L");

    cout << "\n\n\n";
    contactTree->PrintContactCases("K");*/

    cout << "\n\n\n";
    contactTree->PrintContactTree();

    cout << "\n\n\n";
    contactTree->PrintHierarchicalTree();


}

