#include <bits/stdc++.h>
using namespace std;
 
string restoring_spaces(const string& corrupted, const vector<string>& dictionary , int a) {
    //Initialize a vector to track possible splits
    vector<bool> dp(a + 1, false);
    //Base case: an empty string can always be segmented
    dp[0] = true;
    vector<int> last_split(a + 1, -1);
    //Iterate through all positions in the corrupted text
    for (int i = 1; i <= a; ++i) {
        //Check if any word in the dictionary matches the substring ending at position i
        for (const string& word : dictionary) {
            if (i >= word.length() && corrupted.substr(i - word.length(), word.length()) == word && dp[i - word.length()]) {
                //If a match is found and the preceding substring can be segmented, mark dp[i] as true
                dp[i] = true;
                // Update the last split position for position i
                last_split[i] = i - word.length();
                //Break the loop if a match is found
                break;
            }
        }
    }
    //Reconstruct the original text based on the last split positions
    vector<string> words;
    int i = a;
    while (i > 0) {
        words.push_back(corrupted.substr(last_split[i], i - last_split[i]));
        i = last_split[i];
    }
    //Build the solution string by joining the words with spaces
    string solution;
    for (int j = words.size() - 1; j >= 0; --j) {
        solution += words[j];
        if (j > 0) {
            solution += " ";
        }
    }
    //Return text with spaces
    return solution;
}
 
int main()
{
    int N, K;
    string dict;
    string text;
    vector<string>dictionary;
    cin>>N>>K;
    for (int i = 0; i < N; ++i) {
        cin>>dict;
        dictionary.push_back(dict);
    }
    cin>>text;
    cout<<restoring_spaces(text,dictionary,K);
    return 0;
}