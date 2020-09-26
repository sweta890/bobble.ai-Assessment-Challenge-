#include <bits/stdc++.h>
using namespace std;

// structure for Trie

struct Trie {
	bool isEName;
	unordered_map<char, Trie*> m;
	int total;
};


// Function to create a new Trie node
Trie* getNewTrieNode()
{
	Trie* node = new Trie;
	node->isEName = false;
	return node;
}


// Function to insert a student with its frequency
// in the dictionary built using a Trie


void insert(Trie*& root, const string& s,
			const int& total)
{

	// If root is null
	if (root == NULL)
		root = getNewTrieNode();

	Trie* temp = root;

	for (int i = 0; i < s.length(); i++) {
		char x = s[i];

		// Make a new node if there is no path
		if (temp->m.find(x) == temp->m.end())
			temp->m[x] = getNewTrieNode();

		temp = temp->m[x];
	}

	// Mark end of Name and store the meaning
	temp->isEName = true;
	temp->total = total;
}


// Function to search a student in the Trie and return its totaluency if it exists

 int search(Trie * root, sing word){
     if(root == NULL) return -1;
     Trie* temp = root;

	// Search a student in the Trie

	for (int i = 0; i < word.length(); i++) {
		temp = temp->m[word[i]];
		if (temp == NULL)
			return -1;
	}

    if (temp->isEName)
		return temp->total;
    return -1;
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


    int ans = search(root, "cross");
	if(ans != -1) cout << "YES " << ans << endl;
	else cout << "NO\n";

	return 0;
}
