#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

template<typename T>
class DoubleLinkedList {
public:
    T* head_;
    T* tail_;

public:
    DoubleLinkedList() : head_(nullptr), tail_(nullptr) {}

    void AddNode(T* new_node) {
        if (!head_) {
            head_ = tail_ = new_node;
        }
        else {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
    }

    void RemoveNode(T* node_to_remove) {
        if (!head_) {
            return;
        }
        if (head_ == node_to_remove) {
            head_ = head_->next;
            if (head_) {
                head_->prev = nullptr;
            }
            else {
                tail_ = nullptr;
            }
            delete node_to_remove;
            return;
        }
        T* current_node = head_->next;
        while (current_node) {
            if (current_node == node_to_remove) {
                current_node->prev->next = current_node->next;
                if (current_node->next) {
                    current_node->next->prev = current_node->prev;
                }
                else {
                    tail_ = current_node->prev;
                }
                delete node_to_remove;
                return;
            }
            current_node = current_node->next;
        }
    }

    T* GetFirstNode() const {
        return head_;
    }

    T* GetLastNode() const {
        return tail_;
    }

    ~DoubleLinkedList() {
        T* current_node = head_;
        while (current_node) {
            T* next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }
};

#endif // DOUBLE_LINKED_LIST_H
