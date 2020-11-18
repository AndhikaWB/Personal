#include <iostream>
using namespace std;

struct node {
    int data;
    node *prev = nullptr;
    node *next = nullptr;
};

struct list {
    node *head = nullptr;
    node *tail = nullptr;

    void push_head(int data);
    void push_tail(int data);
    void push(int data, node *address);

    void pop_head();
    void pop_tail();
    void pop(node *address);

    void print();
    void sort(string logic = "gtr");
    node *find(int data, string logic = "equ");
};

void list::push_head(int data) {
    node *current = new node {data};
    if (current != nullptr) {
        if (head == nullptr) {
            head = tail = current;
        } else {
            current->next = head;
            head->prev = current;
            head = current;
        }
    }
}

void list::push_tail(int data) {
    node *current = new node {data};
    if (current != nullptr) {
        if (head == nullptr) {
            head = tail = current;
        } else {
            current->prev = tail;
            tail->next = current;
            tail = current;
        }
    }
}

// Push before
void list::push(int data, node *address) {
    if (address == nullptr) {
        push_tail(data);
    } else if (address == head) {
        push_head(data);
    } else {
        node *current = new node {data};
        if (current != nullptr) {
            current->prev = address->prev;
            current->next = address;
            address->prev->next = current;
            address->prev = current;
        }
    }
}

void list::pop_head() {
    node *current = head;
    if (current != nullptr) {
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete[] current;
    }
}

void list::pop_tail() {
    node *current = tail;
    if (current != nullptr) {
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete[] current;
    }
}

void list::pop(node *address) {
    if (address != nullptr) {
        if (address == head) {
            pop_head();
        } else if (address == tail) {
            pop_tail();
        } else {
            address->prev->next = address->next;
            address->next->prev = address->prev;
            delete[] address;
        }
    }
}

void list::print() {
    cout << "[";
    for (node *i = head; i != nullptr; i = i->next) {
        cout << i->data;
        if (i->next != nullptr) cout << ", ";
    }
    cout << "]" << endl;
}

// Todo: switch to merge sort
void list::sort(string logic) {
    for (node *i = head->next; i != nullptr; i = i->next) {
        for (node *j = i; j != head; j = j->prev) {
            bool condition = 0;
            if (logic == "lss") { // Descending
                condition = j->prev->data < j->data;
            } else if (logic == "gtr") { // Ascending
                condition = j->prev->data > j->data;
            }
            if (condition) {
                int temp = j->data;
                j->data = j->prev->data;
                j->prev->data = temp;
            } else break;
        }
    }
}

node *list::find(int data, string logic) {
    for (node *i = head; i != nullptr; i = i->next) {
        bool condition = 0;
        if (logic == "lss") { // Less
            condition = i->data < data;
        } else if (logic == "equ") { // Equal
            condition = i->data == data;
        } else if (logic == "gtr") { // Greater
            condition = i->data > data;
        }
        if (condition) return i;
    }
    return nullptr;
}

int main() {
    list number;

    number.push_tail(3);
    number.push_tail(1);
    number.push_tail(2);
    number.push_tail(5);
    number.print();

    number.push_head(8);
    number.push_head(7);
    number.print();

    number.sort("gtr");
    number.print();

    number.push(6, number.find(6, "gtr"));
    number.print();

    number.sort("lss");
    number.print();

    number.push(4, number.find(4, "lss"));
    number.print();

    number.pop_head();
    number.pop_tail();
    number.print();

    number.pop(number.find(6, "equ"));
    number.print();
}