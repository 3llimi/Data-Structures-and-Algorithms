#include <bits/stdc++.h>
using namespace std;
 
void knapsack(int n, int w, vector<int>& items, vector<int>& weight, vector<int>& cost) {
    vector<vector<int>> dp(n + 1, vector<int>(w + 1, 0));
 
    //Loop through each item
    for (int i = 1; i <= n; ++i) {
        //Loop through each possible weight
        for (int j = 0; j <= w; ++j) {
            //If the weight of the current item is less than or equal to the current weight limit
            if (weight[i - 1] <= j) {
                //Choose the maximum between not including the current item and including it
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i - 1]] + cost[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    //Trace back to find which items were included in the knapsack
    int i = n, j = w;
    while (i > 0 && j > 0) {
        // If the value in the current cell is not equal to the value in the cell above it,
        // it means the current item was included in the knapsack
        if (dp[i][j] != dp[i - 1][j]) {
            //Add the index of the item to the list of items included
            items.push_back(i);
            //Update the weight limit
            j -= weight[i - 1];
        }
        i--;
    }
 
    reverse(items.begin(), items.end());
}
 
int main()
{
    int n; //Number of items
    int w; //Weight limit of the knapsack
    int k;
    vector<int>weight;
    vector<int>cost;
    cin>>n>>w;
    for (int i = 0; i < n; ++i) {
        cin>>k;
        weight.push_back(k);
    }
    for (int i = 0; i < n; ++i) {
        cin>>k;
        cost.push_back(k);
    }
    vector<int> items;
    knapsack(n, w, items, weight, cost);
    cout<<items.size()<<endl;
    for (int i = 0; i < items.size(); ++i) {
        cout << items[i] << " ";
    }
    return 0;
}