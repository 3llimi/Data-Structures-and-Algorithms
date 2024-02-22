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
    int size;
    int capacity;
 
public:
 
    HashMap(int capacity) {
        this->capacity = capacity;
        data = vector<KeyValue<K, V>>(capacity);
        size = 0;
    }
    int getSize() override {
        return data.size();
    }
 
    V get(K key) override {
        int position = hash<K>{}(key)%data.size();
        if (data[position].key == "") {
            return -1;
        }
        while (data[position].key != key) {
            position = (position + 1)%data.size();
            if (position == hash<K>{}(key)%data.size()) {
                return -1;
            }
            if (data[position].key == "") {
                return -1;
            }
        }
        return data[position].value;
    }
 
    void put(K key, V value) override {
        int position = hash<K>{}(key)%data.size();
        if (get(key) != -1) {
            while (data[position].key != key) {
                position = (position + 1)%data.size();
            }
            data[position].value = value;
            return;
        }
        while (data[position].key != "") {
            position = (position + 1)%data.size();
        }
        data[position].key = key;
        data[position].value = value;
    }
 
    vector<KeyValue<K, V>> entrySet() override {
        return data;
    }
};
 
int main() {
    int n;
    cin >> n;
    string text;
    Map<string, int>* freq = new HashMap<string, int>(1000000);
    for (int i = 0; i < n; ++i) {
        cin >> text;
        if (freq->get(text) == -1) {
            freq->put(text, 1);
            continue;
        }
        freq->put(text, freq->get(text) + 1);
    }
    int k;
    cin >> k;
    int acc = 0;
    Map<string, int>* freq2 = new HashMap<string, int>(1000000);
    vector<string> results;
    for (int i = 0; i < k; ++i) {
        cin >> text;
        if (freq->get(text) != -1) continue;
        if (freq2->get(text) == -1) {
            freq2->put(text, 1);
            acc++;
            results.push_back(text);
        }
        freq2->put(text, freq2->get(text) + 1);
    }
    cout << acc << endl;
    for (auto x: results) {
        cout << x << endl;
    }
    return 0;
}