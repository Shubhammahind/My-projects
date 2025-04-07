#include <iostream>
#include <stdexcept>

// Forward declarations
template <typename T> class SinglyLL;
template <typename T> class DoublyLL;
template <typename T> class SinglyCL;
template <typename T> class DoublyCL;

// Base Node structure
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev; // Only used for doubly linked lists
    
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

// Singly Linked List
template <typename T>
class SinglyLL {
private:
    Node<T>* head;
    int count;

public:
    SinglyLL() : head(nullptr), count(0) {}
    ~SinglyLL() { clear(); }

    void insertFirst(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        count++;
    }

    void insertLast(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    void insertAtPos(const T& value, int pos) {
        if (pos < 1 || pos > count + 1) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            insertFirst(value);
        } else if (pos == count + 1) {
            insertLast(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* temp = head;
            
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            newNode->next = temp->next;
            temp->next = newNode;
            count++;
        }
    }

    void deleteFirst() {
        if (!head) return;
        
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        count--;
    }

    void deleteLast() {
        if (!head) return;
        
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
        count--;
    }

    void deleteAtPos(int pos) {
        if (pos < 1 || pos > count) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            deleteFirst();
        } else if (pos == count) {
            deleteLast();
        } else {
            Node<T>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            Node<T>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            count--;
        }
    }

    void display() const {
        Node<T>* temp = head;
        std::cout << "Elements: ";
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    int size() const { return count; }

    void clear() {
        while (head) {
            deleteFirst();
        }
    }
};

// Doubly Linked List
template <typename T>
class DoublyLL {
private:
    Node<T>* head;
    int count;

public:
    DoublyLL() : head(nullptr), count(0) {}
    ~DoublyLL() { clear(); }

    void insertFirst(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    void insertLast(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        count++;
    }

    void insertAtPos(const T& value, int pos) {
        if (pos < 1 || pos > count + 1) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            insertFirst(value);
        } else if (pos == count + 1) {
            insertLast(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* temp = head;
            
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            count++;
        }
    }

    void deleteFirst() {
        if (!head) return;
        
        Node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        delete temp;
        count--;
    }

    void deleteLast() {
        if (!head) return;
        
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->prev->next = nullptr;
            delete temp;
        }
        count--;
    }

    void deleteAtPos(int pos) {
        if (pos < 1 || pos > count) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            deleteFirst();
        } else if (pos == count) {
            deleteLast();
        } else {
            Node<T>* temp = head;
            for (int i = 1; i < pos; i++) {
                temp = temp->next;
            }
            
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            count--;
        }
    }

    void display() const {
        Node<T>* temp = head;
        std::cout << "Elements (forward): ";
        while (temp) {
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    int size() const { return count; }

    void clear() {
        while (head) {
            deleteFirst();
        }
    }
};

// Singly Circular Linked List
template <typename T>
class SinglyCL {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    SinglyCL() : head(nullptr), tail(nullptr), count(0) {}
    ~SinglyCL() { clear(); }

    void insertFirst(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            newNode->next = head;
            head = newNode;
            tail->next = head;
        }
        count++;
    }

    void insertLast(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
        count++;
    }

    void insertAtPos(const T& value, int pos) {
        if (pos < 1 || pos > count + 1) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            insertFirst(value);
        } else if (pos == count + 1) {
            insertLast(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* temp = head;
            
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            newNode->next = temp->next;
            temp->next = newNode;
            count++;
        }
    }

    void deleteFirst() {
        if (!head) return;
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        count--;
    }

    void deleteLast() {
        if (!head) return;
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = head;
        }
        count--;
    }

    void deleteAtPos(int pos) {
        if (pos < 1 || pos > count) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            deleteFirst();
        } else if (pos == count) {
            deleteLast();
        } else {
            Node<T>* temp = head;
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            Node<T>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            count--;
        }
    }

    void display() const {
        if (!head) {
            std::cout << "List is empty\n";
            return;
        }
        
        Node<T>* temp = head;
        std::cout << "Elements: ";
        do {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        std::cout << "(head)\n";
    }

    int size() const { return count; }

    void clear() {
        while (head) {
            deleteFirst();
        }
    }
};

// Doubly Circular Linked List
template <typename T>
class DoublyCL {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    DoublyCL() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyCL() { clear(); }

    void insertFirst(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
        count++;
    }

    void insertLast(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = tail = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
        count++;
    }

    void insertAtPos(const T& value, int pos) {
        if (pos < 1 || pos > count + 1) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            insertFirst(value);
        } else if (pos == count + 1) {
            insertLast(value);
        } else {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* temp = head;
            
            for (int i = 1; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            count++;
        }
    }

    void deleteFirst() {
        if (!head) return;
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        count--;
    }

    void deleteLast() {
        if (!head) return;
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }
        count--;
    }

    void deleteAtPos(int pos) {
        if (pos < 1 || pos > count) {
            throw std::out_of_range("Invalid position");
        }

        if (pos == 1) {
            deleteFirst();
        } else if (pos == count) {
            deleteLast();
        } else {
            Node<T>* temp = head;
            for (int i = 1; i < pos; i++) {
                temp = temp->next;
            }
            
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            count--;
        }
    }

    void display() const {
        if (!head) {
            std::cout << "List is empty\n";
            return;
        }
        
        Node<T>* temp = head;
        std::cout << "Elements (forward): ";
        do {
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != head);
        std::cout << "(head)\n";
    }

    int size() const { return count; }

    void clear() {
        while (head) {
            deleteFirst();
        }
    }
};

// Example usage
int main() {
    // Test Singly Linked List
    std::cout << "Singly Linked List:\n";
    SinglyLL<int> sll;
    sll.insertFirst(10);
    sll.insertLast(20);
    sll.insertAtPos(15, 2);
    sll.display();
    sll.deleteAtPos(2);
    sll.display();
    
    // Test Doubly Linked List
    std::cout << "\nDoubly Linked List:\n";
    DoublyLL<int> dll;
    dll.insertFirst(5);
    dll.insertLast(25);
    dll.insertAtPos(15, 2);
    dll.display();
    dll.deleteFirst();
    dll.display();
    
    // Test Singly Circular Linked List
    std::cout << "\nSingly Circular Linked List:\n";
    SinglyCL<int> scl;
    scl.insertFirst(1);
    scl.insertLast(3);
    scl.insertAtPos(2, 2);
    scl.display();
    scl.deleteLast();
    scl.display();
    
    // Test Doubly Circular Linked List
    std::cout << "\nDoubly Circular Linked List:\n";
    DoublyCL<int> dcl;
    dcl.insertFirst(100);
    dcl.insertLast(300);
    dcl.insertAtPos(200, 2);
    dcl.display();
    dcl.deleteAtPos(2);
    dcl.display();
    
    return 0;
}