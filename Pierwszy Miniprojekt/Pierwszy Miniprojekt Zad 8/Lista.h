#include <iostream>
using namespace std;

template <typename T>
class Lista {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;

public:
    Lista() {
        head = nullptr;
        tail = nullptr;
    }

    void dodajL(T value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void usunL(T value) {
        Node* currNode = head;
        Node* prevNode = nullptr;

        while (currNode != nullptr) {
            if (currNode->data == value) {
                if (prevNode == nullptr) {
                    head = currNode->next;
                }
                else {
                    prevNode->next = currNode->next;
                }
                delete currNode;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }

    void wypiszL() {
        Node* currNode = head;
        while (currNode != nullptr) {
            cout << currNode->data << " ";
            currNode = currNode->next;
        }
        cout << endl;
    }

    void usunWszystkieL() {
        Node* currNode = head;
        while (currNode != nullptr) {
            Node* nextNode = currNode->next;
            delete currNode;
            currNode = nextNode;
        }
        head = nullptr;
        tail = nullptr;
    }
};