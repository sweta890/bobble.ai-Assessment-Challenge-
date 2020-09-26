#include <bits/stdc++.h>
using namespace std;

// Structure for Trie

struct Trie {
  bool isEndName;
  unordered_map<char, Trie*> map;
  int freq;
    Trie *parent;
    char ch;
};

unordered_map<int, Trie*> trie_hash;
int n = 0;


// Function to create a new Trie node
Trie* getNewTrieNode(char ch, Trie* parent)
{
  Trie* node = new Trie;
  node->isEndName = false;
    node->ch = ch;
    node->parent = parent;
  return node;
}


// Function to insert a student with its frequency
// in the dictionary built using a Trie


void insert(Trie*& root, const string& str,
      const int& freq)
{

  // If root is null
  if (root == NULL)
    root = getNewTrieNode((char)0, NULL);

  Trie* temp = root;

  for (int i = 0; i < str.length(); i++) {
    char x = str[i];

    // Make a new node if there is no path
    if (temp->map.find(x) == temp->map.end())
      temp->map[x] = getNewTrieNode(x, temp);

    temp = temp->map[x];
  }

  // Mark end of Name and store the meaning
  temp->isEndName = true;
  temp->freq = freq;
    trie_hash[n++] = temp;
}


// Function to search a student in the Trie and return its frequency if it exists

 string search(int input){
     string output;
     if (trie_hash.count(input) == 0) {
         return output;
     }

     Trie *temp = trie_hash[input];
     while(temp -> parent != NULL) {
         output += temp -> ch;
         temp = temp -> parent;
     }
     for (int i=0, j=output.size() - 1; i < j; i++, j--) {
         char t = output[i];
         output[i] = output[j];
         output[j] = t;
     }
     return output;
 }

// Main function

int main()
{
  Trie* root = NULL;

  // Build the dictionary
  ifstream myFile;
  myFile.open("EnglishDictionary.csv");
  string line, word;
  string fre;
  vector<pair<string, int>> v;
  int f;

  while(getline(myFile, line)){
    stringstream ss(line);
    getline(ss, word, ',');
    getline(ss, fre, ',');
    f = stoi(fre);
    v.push_back({word,f});
  }

  for(auto it : v){
    insert(root, it.first, it.second);
  }

    int input;
    cin >> input;
    string ans = search(input);
  if(ans.size()) cout << "YES " << ans << endl;
  else cout << "NO\n";

  return 0;
}