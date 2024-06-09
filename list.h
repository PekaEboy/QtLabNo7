#ifndef LIST_H
#define LIST_H
#include <QMainWindow>


struct Node {
    float val;
    Node* next;
    int number;
    Node(float _val) : val(_val), next(nullptr), number(0) {};
};

class List
{
public:
    Node* first;
    Node* last;
    List();
    bool is_empty();
    Node* find(int num);
    void push_back(float dude);
    void remove(int num);
    int length();
};

#endif // LIST_H
