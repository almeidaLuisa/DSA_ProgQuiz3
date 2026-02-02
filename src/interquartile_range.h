/*
    Interquartile Range

    Given a sorted singly linked list without a tail (e.g, head -> 1 -> 2 -> 3 -> 4), 
    return the interquartile range of the data set using the slow and fast pointer 
    approach OR using a methodology that does not iterate over the linked list 
    twice. You must not iterate over the entire linked list more than once and you 
    cannot use arrays, vectors, lists or an STL implementation of List ADT in this problem.

    Sample Input:
        2 4 4 5 6 7 8
    
    Sample Output:
        3.00 
*/

// Worked with Murilo Matos

#include <iostream>
#include <iomanip>

class Node {
public:
    int value;
    Node* next = nullptr;
};

Node* insertEnd(Node* head, int key)
{
    Node* temp = new Node();
    temp->value = key;
    if(head == nullptr)
        head = temp;
    else
    {
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    return head;
}

float interQuartile(Node* head) {
    if (!head) return 0.0f;

    Node* Q1 = head;
    Node* Q3 = head;

    Node* cur = head;
    int n = 0;

    while (cur != nullptr) {
        n++;
        cur = cur->next;
        if (n % 4 == 0 && n >= 8) {
            Q1 = Q1->next;
        }
        if (n == 4) {
            Q3 = Q3->next->next;
        } else if (n % 4 == 0 && n > 4) {
            Q3 = Q3->next->next->next;
        }
    }


    // helper to avoid int overflow when averaging
    auto Average = [](int a, int b) -> float {
        long double sum = (long double)a + (long double)b; // cast BEFORE add
        return (float)(sum / 2.0L);
    };

    int r = n % 4;

    float Q1_val;
    if (r == 0 || r == 1) {
        Q1_val = Average(Q1->value, Q1->next->value);
    } else {
        Q1_val = (float)Q1->next->value;
    }
    float Q3_val;
    if (r == 0) {
        Q3_val = Average(Q3->value, Q3->next->value);
    } else if (r == 1) {
        Q3_val = Average(Q3->next->value, Q3->next->next->value);
    } else if (r == 2) {
        Q3_val = (float) Q3->next->next->value;
    } else {
        Q3_val = (float)Q3->next->next->next->value;
    }

    return Q3_val - Q1_val;
}
