#include <iostream>
using namespace std;

struct node {
    int data;
    node *next = nullptr;
};

struct sll {
    node *first = nullptr;
    node *last = nullptr;
};

void insertFirst(sll *list, int data) {
    node *current = (node*) malloc(sizeof(node));
    current->data = data;
    current->next = nullptr;

    if (list->first == nullptr) {
        list->first = list->last = current;
    } else {
        current->next = list->first;
        list->first = current;
    }
}

void insertLast(sll *list, int data) {
    node *current = (node*) malloc(sizeof(node));
    current->data = data;
    current->next = nullptr;

    if (list->first == nullptr) {
        list->first = list->last = current;
    } else {
        list->last->next = current;
        list->last = current;
    }
}

void insertAuto(sll *list, int data) {
    node *current = (node*) malloc(sizeof(node));
    current->data = data;
    current->next = nullptr;

    // Urutkan data pada list secara menaik
    //sortAscending(list);

    // Asumsikan data sudah terurut
    if (list->first == nullptr) {
        list->first = list->last = current;
    } else if (list->first->data > current->data) {
        insertFirst(list, data);
    } else if (list->last->data < current->data) {
        insertLast(list, data);
    } else {
        node *temp = list->first;
        while (temp->next->data < current->data) {
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
}

void sortAuto(sll *list, int type = 1, node *current = nullptr) {
    if (current == nullptr) current = list->first;

    if (current->next == nullptr) {
        return;
    } else {
        sortAuto(list, type, current->next);
        node temp = { current->data, nullptr };
        if (type == 1) {
            // Urutkan data pada list secara menaik
            if (current->next->data < current->data) {
                current->data = current->next->data;
                current->next->data = temp.data;
                sortAuto(list, type, current);
            }
        } else if (type == 0) {
            // Urutkan data pada list secara menurun
            if (current->next->data > current->data) {
                current->data = current->next->data;
                current->next->data = temp.data;
                sortAuto(list, type, current);
            }
        }
    }
}

void deleteFirst(sll *list) {
    node *current = list->first;

    if (list->first == nullptr) {
        return;
    } else if (list->first == list->last) {
        list->first = list->last = nullptr;
        free(current);
    } else {
        list->first = list->first->next;
        free(current);
    }
}

void deleteLast(sll *list) {
    node *current = list->last;

    if (list->first == nullptr) {
        return;
    } else if (list->first == list->last) {
        list->first = list->last = nullptr;
        free(current);
    } else {
        node *temp = list->first;
        while (temp->next != list->last) {
            temp = temp->next;
        }
        list->last = temp;
        list->last->next = nullptr;
        free(current);
    }
}

void deleteAuto(sll *list, int data) {
    node *current = nullptr;
    if (list->first == nullptr) {
        return;
    } else if (list->first->data == data) {
        deleteFirst(list);
    } else if (list->last->data == data) {
        deleteLast(list);
    } else {
        node *temp = list->first;
        while (temp->next != list->last) {
            if (temp->next->data == data) break;
            temp = temp->next;
        }
        current = temp->next;
        temp->next = temp->next->next;
        free(current);
    }
}

void deleteAll(sll *list) {
    while (list->first != nullptr) {
        deleteFirst(list);
    }
}

void showAll(sll *list) {
    node *current = list->first;
    if (list->first == nullptr) {
        cout << "NULL";
    } else {
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << endl;
}

int main() {
    sll playerScore;
    insertFirst(&playerScore, 10);
    insertFirst(&playerScore, 13);
    insertAuto(&playerScore, 9);
    insertLast(&playerScore, 12);
    insertFirst(&playerScore, 18);
    insertFirst(&playerScore, 7);
    showAll(&playerScore);

    sortAuto(&playerScore);
    insertAuto(&playerScore, 11);
    showAll(&playerScore);

    sortAuto(&playerScore, 0);
    showAll(&playerScore);

    deleteFirst(&playerScore);
    showAll(&playerScore);

    deleteAuto(&playerScore, 11);
    showAll(&playerScore);

    deleteLast(&playerScore);
    showAll(&playerScore);

    deleteAll(&playerScore);
    showAll(&playerScore);
}