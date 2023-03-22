#include <iostream>
using namespace std;

template<typename T>
class Kolejka {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    Node* tail;

public:
    Kolejka() : head(nullptr), tail(nullptr) {}

    ~Kolejka() {
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void dodaj(T data) {
        Node* newNode = new Node{ data, nullptr };
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void usun() {
        if (head == nullptr) {
            return;
        }

        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    void wypisz() const {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void usunWszystkie() {
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
    }
};