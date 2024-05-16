// Ahmed Baha Eddine Alimi
#include <bits/stdc++.h>
 
using namespace std;
 
template<typename K, typename V>
class Map {
public:
    virtual void insert(const K& key, const V& value) = 0;
    virtual void remove(const K& key) = 0;
    virtual void remove(const K& key, const V& value) = 0;
    virtual vector<V>* find(const K& key) const = 0;
    virtual size_t getSize() const = 0;
    virtual ~Map() {}
};
 
template<typename K, typename V>
class Node {
public:
    K key;
    vector<V> values;
    Node* next;
 
    Node(const K& k, const V& v) : key(k), next(nullptr) {
        values.push_back(v);
    }
};
 
template<typename K, typename V>
class HashTable : public Map<K, V> {
private:
    vector<Node<K, V>*> table;
    size_t size;
 
    size_t hash(const K& key) const {
        size_t hashVal = 0;
        for (char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal % table.size();
    }
 
public:
    HashTable(size_t initialSize) : table(initialSize, nullptr), size(0) {}
 
    ~HashTable() {
        for (Node<K, V>* entry : table) {
            while (entry != nullptr) {
                Node<K, V>* next = entry->next;
                delete entry;
                entry = next;
            }
        }
    }
 
    void insert(const K& key, const V& value) override {
        size_t index = hash(key);
 
        Node<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                for (const V& val : current->values) {
                    if (val == value) {
                        return;
                    }
                }
                current->values.push_back(value);
                return;
            }
            current = current->next;
        }
 
        Node<K, V>* newNode = new Node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }
 
    void remove(const K& key) override {
        size_t index = hash(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;
 
        while (current != nullptr) {
            if (current->key == key) {
                deleteNode(current, prev, index);
                return;
            }
            prev = current;
            current = current->next;
        }
    }
 
    void remove(const K& key, const V& value) override {
        size_t index = hash(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;
 
        while (current != nullptr) {
            if (current->key == key) {
                for (auto it = current->values.begin(); it != current->values.end(); ++it) {
                    if (*it == value) {
                        current->values.erase(it);
                        if (current->values.empty()) {
                            deleteNode(current, prev, index);
                        }
                        return;
                    }
                }
                return; // Value not found
            }
            prev = current;
            current = current->next;
        }
    }
 
    void deleteNode(Node<K, V>* current, Node<K, V>* prev, size_t index) {
        if (prev == nullptr) {
            table[index] = current->next;
        } else {
            prev->next = current->next;
        }
        delete current;
        size--;
    }
 
    vector<V>* find(const K& key) const override {
        size_t index = hash(key);
        Node<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return &(current->values);
            }
            current = current->next;
        }
        return nullptr;
    }
 
    size_t getSize() const override {
        return size;
    }
};
 
int main() {
    int N;
    cin >> N;
    cin.ignore();
 
    HashTable<string, string> phonebook(10000);
 
    for (int i = 0; i < N; ++i) {
        string command;
        getline(cin, command);
 
        if (command.substr(0, 3) == "ADD") {
            size_t commaPos = command.find(',');
            string name = command.substr(4, commaPos - 4);
            string phone = command.substr(commaPos + 1);
            phonebook.insert(name, phone);
        } else if (command.substr(0, 6) == "DELETE") {
            size_t commaPos = command.find(',');
            string name = command.substr(7, commaPos - 7);
            if (commaPos != string::npos) {
                string phone = command.substr(commaPos + 1);
                phonebook.remove(name, phone);
            } else {
                phonebook.remove(name);
            }
        } else if (command.substr(0, 4) == "FIND") {
            string name = command.substr(5);
            vector<string>* result = phonebook.find(name);
            if (result == nullptr || result->empty()) {
                cout << "No contact info found for " << name << endl;
            } else {
                cout << "Found " << result->size() << " phone numbers for " << name << ": ";
                for (const string& phone : *result) {
                    cout << phone << " ";
                }
                cout << endl;
            }
        }
    }
 
    return 0;
}