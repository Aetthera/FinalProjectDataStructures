// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;



template <typename T> class MySinglyList
{
private:
    T* head;
    T* tail;
    int size;

public:
    MySinglyList();
    ~MySinglyList();

    bool IsEmpty();
    int GetSize();

    void AppendAtTail(T*);
    void InsertAtHead(T*);

    void DeleteLastElem();
    void DeleteFirstElem();

    void DisplayElements();
};


template <typename T> MySinglyList<T>::MySinglyList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <typename T> MySinglyList<T>::~MySinglyList()
{
    T* p = this->head;
    while (this->head != nullptr) {
        p = this->head;
        this->head = this->head->next;
        delete(p);

    }
    this->tail = nullptr;
    this->size = 0;
}

template <typename T> bool MySinglyList<T>::IsEmpty()
{
    return this->size == 0;
}

template <typename T> int MySinglyList<T>::GetSize()
{
    return this->size;
}


template <typename T> void MySinglyList<T>::AppendAtTail(T* temp)
{
    if (this->IsEmpty())
    {
        head = temp;
        // InsertAtHead(elem)
    }

    else
    {
        tail->next = temp;
    }

    tail = temp;
    this->size++;
}

template <typename T> void MySinglyList<T>::InsertAtHead(T* newNode) {
    
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
        this->size++;
        return;
    }
    (newNode)->next = this->head;
    this->head = newNode;
    this->size++;
}



template <typename T> void MySinglyList<T>::DisplayElements()
{
    if (this->size == 0) {
        cout << "The list is empty" << endl;
        return;
    }
    for (T* p = head; p != nullptr; p = p->next)
    {
        cout << p->medicareId<< " ";
    }
    cout << endl;
}

template <typename T> void MySinglyList<T>::DeleteFirstElem() {
    if (this->size == 0) {
        cout << "The list is empty" << endl;
        return;
    }

    if (this->size == 1) {
        delete(this->head);
        this->tail = nullptr;
        this->size--;
        return;
    }

    T* temp = this->head;
    this->head = this->head->next;
    delete(temp);
    this->size--;
}

template <typename T> void MySinglyList<T>::DeleteLastElem() {
    T* temp = this->head;

    if (this->size <= 1) {
        DeleteFirstElem();
        return;
    }
    while (temp->next != this->tail) {
        temp = temp->next;
    }
    temp->next = nullptr;
    delete(this->tail);
    this->tail = temp;

    this->size--;
}

typedef std::string String;
struct TreeNode {
    String medicareId; // unique identifier cannot be duplicated
    int directContacts = 0; // no. of children a node has, default 0
    int totalCases = 1; // no. of nodes rooted at this tree node including self
    TreeNode* parentPtr; // pointer to the parent node
    MySinglyList<TreeNode>* directContactsPtrList; // list of pointers to children nodes
    TreeNode* next = nullptr;
    TreeNode(String medId) { medicareId = medId; parentPtr = nullptr; };
    TreeNode(TreeNode* parentPtr, String medId) { medicareId = medId; parentPtr = parentPtr; };

};



int main()
{
    std::cout << "Hello \n";
    MySinglyList<TreeNode>* myList = new MySinglyList<TreeNode>();
    cout<<myList->GetSize();
    TreeNode* one = new TreeNode("1");
    myList->AppendAtTail(one);
    TreeNode* two = new TreeNode("2");
    two->medicareId = "4";
    myList->InsertAtHead(two);
    myList->DisplayElements();
}

