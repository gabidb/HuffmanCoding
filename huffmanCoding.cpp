#include <bits/stdc++.h>
using namespace std;

map<char, string> codes; 

struct Node {
    char data;
    int frequency;
    Node *left, *right;

    Node(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = NULL;
    }
};

void getHuffmanCodes(struct Node* root, string str);

//compare function for sorting the nodes based on frequency
struct compare {
    bool operator()(Node *left, Node *right) {
        return left->frequency > right->frequency;
    }
};

//build Huffman tree from the given data and frequencies
Node *buildHuffmanTree(Node *nodes[], int n) {
    priority_queue<Node *, vector<Node *>, compare> pq; //using priority queue
    for (int i = 0; i < n; i++) {
        pq.push(nodes[i]); //highest priority is given to the node with least frequency
    }


    /*
        Take two nodes with least frequency (first two in the queue) and merge them to create a new node.
        Add the new node to the queue.
        Repeat the above steps until there is only one node left in the queue.
        The remaining node is the root of the Huffman tree.
    */
    while (pq.size() > 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }
    getHuffmanCodes(pq.top(), "");

    return pq.top();
}

// print huffman encoded tree
void printHuffmanEncodedTree(Node *root, string str) {
    if (root == NULL) {
        return;
    }

    if (root->data != '\0') {
        cout << root->data << " " << str << endl;
        return;
    }

    printHuffmanEncodedTree(root->left, str + "0");
    printHuffmanEncodedTree(root->right, str + "1");
}

//get character frequencies from string
void getCharacterFrequencies(string str, unordered_map<char,int> &node_info, int n) {
    for (int i = 0; i < n; i++) {
        node_info[str[i]]++;
    }
}


/*
    Decode the encoded string using the Huffman tree.
    If the current character is a 0, move to the left child of the current node.
    If the current character is a 1, move to the right child of the current node.
    If the current character is a leaf node, add the character to decoded string.
*/
string decodeHuffman(Node* root, string encoded)
{
    string decoded = "";
    Node* temp = root;
    for (int i=0; i<encoded.size(); i++)
    {
        if (encoded[i] == '0')
           temp = temp->left;
        else
           temp = temp->right;

        if (temp->data != '\0')
        {
            decoded += temp->data;
            temp = root;
        }
    }
    return decoded;
}

//Store the Huffman codes in a map
void getHuffmanCodes(struct Node* root, string str) 
{ 
    if (root==NULL) 
        return; 
    if (root->data != '\0') 
        codes[root->data]=str; 
    getHuffmanCodes(root->left, str + "0"); 
    getHuffmanCodes(root->right, str + "1"); 
} 


int main() {
    unordered_map<char,int> node_info;

    //string text = "random text to be encoded and decoded using Huffman coding algorithm";
    cout << "Enter text:" << endl;
    string text;
    getline(cin, text);
    int n = text.length();
    getCharacterFrequencies(text, node_info, n);   

    Node *nodes[node_info.size()];
 
    unordered_map<char,int>::iterator it;
    int i = 0;
     for (auto it = node_info.begin(); it != node_info.end(); ++it) {
        nodes[i] = new Node(it->first, it->second);
        i++;
    }

    Node *root = buildHuffmanTree(nodes, node_info.size());

    //printHuffmanEncodedTree(root, ""); //Uncomment in case you want to see the Huffman tree

    string encoded, decoded;
    for (auto i: text) 
        encoded+=codes[i]; 
    cout << "Encoded String: " << encoded << endl;
    decoded = decodeHuffman(root, encoded);
    cout << "Decoded String: " << decoded << endl;

    return 0;
}








