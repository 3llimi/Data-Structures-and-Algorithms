#include<bits/stdc++.h> 
using namespace std;
 
// Function to perform Bubble Sort on an array
void bubblesort( int A[], int n){
    int aux;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        for (int i = 0; i < n-1; i++)
        {
            if (A[i]>A[i+1])
            {
                aux=A[i];
                A[i]=A[i+1];
                A[i+1]=aux;
                swapped = true;
            }
            
        }
        
    }
}
int main() {
    int n;
    cin>>n;
    int arr[n];
    // Inputing array elements
    for (int i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
     // Using the bubblesort function to sort the array
    bubblesort(arr,n);
    // Outputing the sorted array
    for (int i = 0; i < n-1; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<arr[n-1];// Output the last element without a space
    return 0;
}