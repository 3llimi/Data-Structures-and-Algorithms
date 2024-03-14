//Ahmed Baha Eddine Alimi
#include <bits/stdc++.h>
 
using namespace std;
 
 
 
template<typename T>
void AhmedBahaEddineAlimi_radix_srt(vector<T>& maxBid, vector<int>& minBid, vector<int>& indices) {
    int n = maxBid.size();
    if (n <= 1)
        return;
 
    T max = maxBid[0];
    for (int i = 1; i < n; ++i) {
        if (maxBid[i] > max) {
            max = maxBid[i];
        }
    }
 
    vector<T> output(n);
    vector<int> outputMin(n);
    vector<int> outputIndices(n);
 
    array<int, 10> count;
 
    for (int exp = 1; max / exp > 0; exp *= 10) {
        count.fill(0);
 
        for (int i = 0; i < n; ++i)
            count[(maxBid[i] / exp) % 10]++;
 
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
 
        for (int i = n - 1; i >= 0; i--) {
            int digit = (maxBid[i] / exp) % 10;
            output[count[digit] - 1] = maxBid[i];
            outputMin[count[digit] - 1] = minBid[i];
            outputIndices[count[digit] - 1] = indices[i];
            count[digit]--;
        }
 
        for (int i = 0; i < n; i++) {
            maxBid[i] = output[i];
            minBid[i] = outputMin[i];
            indices[i] = outputIndices[i];
        }
    }
}
 
template <typename T>
void AhmedBahaEddineAlimi_count_srt(vector<T>& minBid, int n, vector<int>& indices) {
    int max = minBid[0];
    for (size_t i = 1; i < minBid.size(); i++) {
        if (minBid[i] > max) {
            max = minBid[i];
        }
    }
    vector<T> count(max + 1, 0);
    vector<T> output(n);
    for (int i = 0; i < n; ++i) {
        count[minBid[i]] += 1;
    }
    for (int i = 1; i <= max; ++i) {
        count[i] = count[i - 1] + count[i];
    }
 
    for (int i = n - 1; i >= 0; i--) {
        output[count[minBid[i]] - 1] = indices[i];
        count[minBid[i]]--;
    }
 
    minBid = output;
}
 
 
int main() {
    int n;
    cin >> n;
    vector<int>minBid;
    vector<int>maxBid;
    vector<int>indices;
    int min , max;
    for (int i = 0; i < n; ++i) {
        cin >> min >> max;
        minBid.push_back(min);
        maxBid.push_back(max);
        indices.push_back(i+1);
    }
    AhmedBahaEddineAlimi_radix_srt(maxBid, minBid, indices);
    for (int i = 0; i < n / 2; ++i) {
        swap(minBid[i], minBid[n - i - 1]);
        swap(maxBid[i], maxBid[n - i - 1]);
        swap(indices[i], indices[n - i - 1]);
    }
    AhmedBahaEddineAlimi_count_srt(minBid, n, indices);
    for (int i = n - 1; i >= 0; --i) {
        cout << minBid[i] << " ";
    }
    return 0;
}