#pragma once
template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ������� �������� � ������ ������
    void insert_front(const T& data) {
        if (!head) {
            head = new Node(data);
            return;
        }
        Node* newNode = new Node(data);
        if (!newNode) {
            std::cerr << "Failed to allocate memory for new node." << std::endl;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    // ������� �������� � ����� ������
    void insert_back(const T& data) {
        if (!head) {                // ���� ������ ����
            insert_front(data);
            return;
        }
        Node* newNode = new Node(data);
        if (!newNode) {             // ������ ��������� ������
            std::cerr << "Failed to allocate memory for new node." << std::endl;
            return;
        }
        Node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    // ������� �������� ����� ���������� ��������
    void insert_after(const T& afterData, const T& data) {
        if (!head) { //��� ���� ������ ����
            std::cerr << "List is empty. Cannot insert after specified data." << std::endl;
            return;
        }
        Node* curr = head;
        while (curr) {
            if (curr->data == afterData) {
                Node* newNode = new Node(data);
                if (!newNode) {             // ������ ��������� ������
                    std::cerr << "Failed to allocate memory for new node." << std::endl;
                    return;
                }
                newNode->next = curr->next;
                curr->next = newNode;
                return;
            }
            curr = curr->next;
        }
        // ���� afterData �� ������
        std::cerr << "Node with specified data not found. Cannot insert after." << std::endl;
    }

    // ������� ������ ��������� ����� ���������� ��������
    void insert_group_after(const T& afterData, const std::initializer_list<T>& dataList) {
        if (!head) { //��� ���� ������ ����
            std::cerr << "List is empty. Cannot insert after specified data." << std::endl;
            return;
        }

        Node* curr = head;
        while (curr) {
            if (curr->data == afterData) {
                for (const T& data : dataList) {
                    Node* newNode = new Node(data);
                    if (!newNode) {            // ������ ��������� ������
                        std::cerr << "Failed to allocate memory for new node." << std::endl;
                        return;
                    }
                    newNode->next = curr->next;
                    curr->next = newNode;
                    curr = newNode;
                }
                return;
            }
            curr = curr->next;
        }
        // ���� afterData �� ������
        std::cerr << "Node with specified data not found. Cannot insert after." << std::endl;
    }


    // �������� ������ ��������� �� ������
    void remove_group(const std::initializer_list<T>& dataList) {
        if (!head) { //��� ���� ������ ����
            std::cerr << "List is empty. Cannot remove from an empty list." << std::endl;
            return;
        }
        for (const T& data : dataList) {
            Node* prev = nullptr;
            Node* curr = head;
            while (curr) {
                if (curr->data == data) {
                    if (prev)
                        prev->next = curr->next;
                    else
                        head = curr->next;
                    Node* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
                else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }

    // �������� �������� � ������ ������
    void remove_front() {
        if (!head) { //��� ���� ������ ����
            std::cerr << "List is empty. Cannot remove from an empty list." << std::endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // �������� �������� � ����� ������
    void remove_back() {
        if (!head) { //��� ���� ������ ����
            std::cerr << "List is empty. Cannot remove from an empty list." << std::endl;
            return;
        }

        // ������, ���� � ������ ���� �������
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }

        Node* prev = nullptr;
        Node* curr = head;
        while (curr->next) {
            prev = curr;
            curr = curr->next;
        }

        delete curr;
        prev->next = nullptr;
    }

    // ��������
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* start) : current(start) {}

        // ������������� �������� ������������� (*it), ���������� ������ �������� ����
        T& operator*() const {
            return current->data;
        }

        // ������������� �������� ���������� (++it), ���������� �������� � ���������� ����
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            else { // ���� ������� ���� ������        
                std::cerr << "Invalid iterator increment. Current node is nullptr." << std::endl;
            }
            return *this;
        }

        // ������������� �������� ����������� (!=), ���������� ��� ���������
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    // ��������� ������ ������
    Iterator begin() const {
        return Iterator(head);
    }

    // ��������� ����� ������
    Iterator end() const {
        return Iterator(nullptr);
    }

    // ����� �������� � ������, ���������� ��������
    Iterator search(const T& data) const {
        if (!head) { //��� ���� ������ ����
            std::cerr << "List is empty. Cannot search in an empty list." << std::endl;
            return end();
        }
        Node* curr = head;
        while (curr) {
            if (curr->data == data)
                return Iterator(curr);
            curr = curr->next;
        }
        // ���� ������� ������� �� ������
        std::cerr << "Element not found." << std::endl;
        return end();
    }
};