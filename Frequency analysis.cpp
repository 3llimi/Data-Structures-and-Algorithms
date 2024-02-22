#include <bits/stdc++.h>
using namespace std;
 
template<typename K, typename V>
struct KeyValue {
    K key;
    V value;
};
 
template<typename K, typename V>
class Map {
public:
    virtual int getSize() = 0;
    virtual void put(K key, V value) = 0;
    virtual V get(K key) = 0;
    virtual vector<KeyValue<K, V>> entrySet() = 0;
};
 
template<typename K, typename V>
class HashMap : public Map<K, V> {
private:
    vector<KeyValue<K, V>> data;
 
public:
    int getSize() override {
        return data.size();
    }
 
    V get(K key) override {
        for (auto& keyValue : data) {
            if (keyValue.key == key) {
                return keyValue.value;
            }
        }
        return V();
    }
 
    void put(K key, V value) override {
        for (auto& keyValue : data) {
            if (keyValue.key == key) {
                keyValue.value = value;
                return;
            }
        }
        data.emplace_back(KeyValue<K, V>{key, value});
    }
 
 
    vector<KeyValue<K, V>> entrySet() override {
        return data;
    }
};
 
int main() {
    int n;
    cin >> n;
    string text;
    Map<string, int>* freq = new HashMap<string, int>();
    for (int i = 0; i < n; ++i) {
        cin >> text;
        freq->put(text, freq->get(text) + 1);
    }
    vector<KeyValue<string, int>> entries = freq->entrySet();
    for (int i = 0; i < entries.size() - 1; ++i) {
        for (int j = 0; j < entries.size() - i -1 ; ++j) {
            if (entries[j].value == entries[j + 1].value && entries[j].key > entries[j + 1].key) {
                KeyValue<string, int> temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            } else if ((entries[j].value < entries[j + 1].value )){
                KeyValue<string, int> temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }
 
    for (const auto& entry : entries) {
        cout << entry.key << " " << entry.value << endl;
    }
    return 0;
}