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
class HashMap : public Map<K, V>
{
private:
    vector<KeyValue<K, V>> data;
    int size;
    int capacity;
 
public:
 
    HashMap(int capacity)
    {
        this->capacity = capacity;
        data = vector<KeyValue<K, V>>(capacity);
        size = 0;
    }
    int getSize() override
    {
        return size;
    }
 
    V get(K key) override
    {
        int position = hash<K>{}(key) % data.size();
        while (data[position].key != 0) {
            if (data[position].key == key) {
                return data[position].value;
            }
            position = (position + 1) % data.size();
        }
        return "";
    }
 
    void put(K key, V value) override
    {
        int position = hash<K>{}(key) % data.size();
        while (data[position].key != 0 && data[position].key != key) {
            position = (position + 1) % data.size();
        }
        if (data[position].key == 0) {
            size++;
        }
        data[position].key = key;
        data[position].value = value;
    }
 
    vector<KeyValue<K, V>> entrySet() override
    {
        vector<KeyValue<K, V>> result;
        for (const auto &kv: data) {
            if (kv.key != 0) {
                result.push_back(kv);
            }
        }
        return result;
    }
};
 
 
 
// Function to partition a sublist of a vector using insertion sort
template<typename V>
int partition5(vector<V>* list, int left, int right) {
    int i = left + 1;
    while (i <= right) {
        int j = i;
        while (j > left && (*list)[j-1] > (*list)[j]) {
            swap((*list)[j-1], (*list)[j]);
            j--;
        }
        i++;
    }
    return left + (right - left) / 2;
}
 
// Function to partition a sublist of a vector using pivot value
template<typename V>
int partition(vector<V>* list, int left, int right, int pivotIndex, int n) {
    int pivotValue = (*list)[pivotIndex];
    swap((*list)[pivotIndex], (*list)[right]);
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if ((*list)[i] < pivotValue) {
            swap((*list)[storeIndex], (*list)[i]);
            storeIndex++;
        }
    }
    int storeIndexEq = storeIndex;
    for (int i = storeIndex; i < right; i++) {
        if ((*list)[i] == pivotValue) {
            swap((*list)[storeIndexEq], (*list)[i]);
            storeIndexEq++;
        }
    }
    swap((*list)[right], (*list)[storeIndexEq]);
    if (n < storeIndex) {
        return storeIndex;
    }
    if (n <= storeIndexEq) {
        return n;
    }
    return storeIndexEq;
}
 
template<typename V> int pivot(vector<V> *list, int left, int right);
 
// Function to select the nth smallest element from a vector
template<typename V>
int median(vector<V> *list, int left, int right, int n) {
    while (true) {
        if (left == right) return left;
        int pivotIndex = pivot(list, left, right);
        pivotIndex = partition(list, left, right, pivotIndex, n);
        if (n == pivotIndex) {
            return n;
        } else if (n < pivotIndex) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
}
 
// Function to select the pivot for partitioning
template<typename V>
int pivot(vector<V> *list, int left, int right) {
    if (right - left < 5) {
        return partition5(list, left, right);
    }
    for (int i = left; i <= right; i+=5) {
        int subRight = i + 4;
        if (subRight > right) {
            subRight = right;
        }
        int median5 = partition5(list, i, subRight);
        swap((*list)[median5], (*list)[left + (i - left) / 5]);
    }
    int mid = (right - left) / 10 + left + 1;
    return median(list, left, left + (right - left) / 5, mid);
}
 
// Function to find the nth smallest element in a list
template<typename V>
V nthSmallest(vector<V> *list, int n) {
    int index = median(list, 0, list->size() - 1, n);
    return (*list)[index];
}
 
int main()
{
    int n;
    cin >> n;
    Map<int, string> *student = new HashMap<int, string>(1000000);
    for (int i = 0; i < n; ++i) {
        int k;
        string Fname, Lname;
        cin >> k >> Fname >> Lname;
        string text = Fname + " " + Lname;
        student->put(k, text);
    }
 
    vector<int> values;
    vector<KeyValue<int, string>> entries = student->entrySet();
    for (const auto& entry : entries) {
        values.push_back(entry.key);
    }
    int medianOfMedians = nthSmallest(&values, values.size()/2 );
    cout << student->get(medianOfMedians) << endl;
    return 0;
}