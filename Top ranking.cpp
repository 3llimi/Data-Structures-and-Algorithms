#include<bits/stdc++.h> 
using namespace std;
// Function to heapify a subtree rooted with node i
 void heapify(int A[], string B[], int n, int i)
{
    int aux1;
    string aux2;
    int largest = i; 
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l < n && A[l] < A[largest])
        largest = l;
 
    if (r < n && A[r] < A[largest])
        largest = r;
 
    if (largest != i) {
        aux1=A[i];
        A[i]=A[largest];
        A[largest]=aux1;
        aux2=B[i];
        B[i]=B[largest];
        B[largest]=aux2;
        heapify(A, B, n, largest);
    }
}
// Function to perform heap sort on an array
void heapsort(int A[],string B[], int n)
{
    int aux1;
    string aux2;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, B, n, i);
    // Performing heap sort on the scores along with rearranging the names accordingly
    for (int i = n - 1; i >= 0; i--) {
        aux1=A[0];
        A[0]=A[i];
        A[i]=aux1;
        aux2=B[0];
        B[0]=B[i];
        B[i]=aux2;
        heapify(A,B, i, 0);
    }
}
// Function to display the leadership board
void leadership_board(int A[], string B[], int n, int k){
    if (n < k) {
        k = n;
    }
    
    heapsort(A,B, n);
    // Output the top k leaders
    for (int i = 0; i < k-1; i++)
    {
        cout<<B[i]<<" "<<A[i]<<"\n";
    }
    cout<<B[k-1]<<" "<<A[k-1];
}
 
int main() {
     int n;
    int k;
    cin >> n >> k;
    int Sarr[n];
    string Narr[n];
 
    for (int i = 0; i < n; i++) {
        cin >> Narr[i] >> Sarr[i];
    }
    // Calling the the leadership board function for the main algorithm
    leadership_board(Sarr, Narr, n, k);
    return 0;
}