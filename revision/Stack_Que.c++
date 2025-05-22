#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;
    Node(int data):data(data),next(nullptr){};
};

bool isListEmpty(Node *head){
    if(head == NULL){
        return true;
    }
    return false;
}

void display(Node *head){
    while (head != NULL)
    {
        cout<<head->data << " -> ";
        head = head->next;
    }
    cout<<"NULL" << endl;
    
};


Node* addAtFirst(Node *head,int valu){
    Node *newNode = new Node(valu);
    newNode->next = head;
    head = newNode;
    return head;
};


Node *addAtEnd(Node *head,int val){
    Node *newdata =  new Node(val);

    if (isListEmpty(head))
    {
        head = newdata;
        head->next = NULL;
    }
   

    while (head != NULL)
    {
        head = head->next;
    }
    head->next = newdata;
    newdata->next = NULL;
    
    return head;

}



int main(){
    Node *node1 = new  Node(1);
    Node *node2 = new  Node(2);
    Node *node3 = new  Node(3);
    node1->next = node2;
    node2->next = node3;
    cout<<"before anything";
    Node *mylist = addAtFirst(node1,7);
    display(mylist);
    cout<<"after adding at first" <<endl ;
    Node *mylist2 = addAtEnd(node1,8);
    display(mylist2);
    cout<<"after adding at end";



    return 0;
}