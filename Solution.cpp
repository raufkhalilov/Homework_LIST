#include <iostream>

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

    // Вставка элемента в начало списка
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

    // Вставка элемента в конец списка
    void insert_back(const T& data) {
        if (!head) {                // Если список пуст
            insert_front(data); 
            return;
        }
        Node* newNode = new Node(data);
        if (!newNode) {             // Ошибка выделения памяти
            std::cerr << "Failed to allocate memory for new node." << std::endl;
            return;
        }
        Node* curr = head;
        while (curr->next) { 
            curr = curr->next;
        }
        curr->next = newNode;
    }

    // Вставка элемента после указанного элемента
    void insert_after(const T& afterData, const T& data) {
        if (!head) { //Это если список пуст
            std::cerr << "List is empty. Cannot insert after specified data." << std::endl;
            return;
        }
        Node* curr = head;
        while (curr) {
            if (curr->data == afterData) {
                Node* newNode = new Node(data);
                if (!newNode) {             // Ошибка выделения памяти
                    std::cerr << "Failed to allocate memory for new node." << std::endl;
                    return;
                }
                newNode->next = curr->next;
                curr->next = newNode;
                return;
            }
            curr = curr->next;
        }
        // Если afterData не найден
        std::cerr << "Node with specified data not found. Cannot insert after." << std::endl;
    }

    // Вставка группы элементов после указанного элемента
    void insert_group_after(const T& afterData, const std::initializer_list<T>& dataList) {
        if (!head) { //Это если список пуст
            std::cerr << "List is empty. Cannot insert after specified data." << std::endl;
            return;
        }

        Node* curr = head;
        while (curr) {
            if (curr->data == afterData) {
                for (const T& data : dataList) {
                    Node* newNode = new Node(data);
                    if (!newNode) {            // Ошибка выделения памяти
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
        // Если afterData не найден
        std::cerr << "Node with specified data not found. Cannot insert after." << std::endl;
    }


    // Удаление группы элементов из списка
    void remove_group(const std::initializer_list<T>& dataList) {
        if (!head) { //Это если список пуст
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

    // Удаление элемента с начала списка
    void remove_front() {
        if (!head) { //Это если список пуст
            std::cerr << "List is empty. Cannot remove from an empty list." << std::endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Удаление элемента с конца списка
    void remove_back() {
        if (!head) { //Это если список пуст
            std::cerr << "List is empty. Cannot remove from an empty list." << std::endl;
            return;
        }

        // удаляю, если в списке один элемент
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

    // Итератор
    class Iterator {
    private:
        Node* current; 

    public:
        Iterator(Node* start) : current(start) {}

        // Перегруженный оператор разыменования (*it), возвращает данные текущего узла
        T& operator*() const {
            return current->data;
        }

        // Перегруженный оператор инкремента (++it), перемещает итератор к следующему узлу
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            else { // Если текущий узел пустой        
                std::cerr << "Invalid iterator increment. Current node is nullptr." << std::endl;
            }
            return *this;
        }

        // Перегруженный оператор неравенства (!=), сравнивает два итератора
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    // получение начала списка
    Iterator begin() const {
        return Iterator(head);
    }

    // получение конца списка
    Iterator end() const {
        return Iterator(nullptr);
    }

    // Поиск элемента в списке, возвращает итератор
    Iterator search(const T& data) const {
        if (!head) { //Это если список пуст
            std::cerr << "List is empty. Cannot search in an empty list." << std::endl;
            return end();
        }
        Node* curr = head;
        while (curr) {
            if (curr->data == data)
                return Iterator(curr); 
            curr = curr->next;
        }
        // Если искомый элемент не найден
        std::cerr << "Element not found." << std::endl;
        return end();
    }
};

int main() {
    LinkedList<int> list;

    // Вставка элементов в начало списка
    list.insert_front(3);
    list.insert_front(2);
    list.insert_front(1);

    // Вставка элементов в конец списка
    list.insert_back(4);
    list.insert_back(5);

    // Вставка элемента после указанного элемента
    list.insert_after(3, 10);

    // Вставка группы элементов после указанного элемента
    list.insert_group_after(4, { 6, 7, 8 });

    // Вывод элементов списка с помощью итератора
    std::cout << "List: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Поиск элемента в списке
    int searchValue = 6;
    auto searchResult = list.search(searchValue);
    if (searchResult != list.end()) {
        std::cout << "Element " << searchValue << " found in the list." << std::endl;
    }
    else {
        std::cout << "Element " << searchValue << " not found in the list." << std::endl;
    }

    // Удаление элементов с начала и конца списка
    list.remove_front();
    list.remove_back();

    // Удаление группы элементов из списка
    list.remove_group({ 10, 8 });

    // Вывод элементов списка после удаления
    std::cout << "List after removal: ";
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}