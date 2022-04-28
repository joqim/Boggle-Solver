#include "Dictionary.h"

// Your code here

//default constructor
Dictionary::Dictionary() {
    root=new Node();
    numWords=0;
}

//destructor
Dictionary::~Dictionary() {

}

//copy constructor
Dictionary::Dictionary(const Dictionary &otherDict) {
    root=new Node();
    numWords=0;
    copyOther(otherDict);
}

//parameterized constructor
Dictionary::Dictionary(string filename) {
    root=new Node();
    numWords=0;
    LoadDictionaryFile(filename);
}

// = operator overloading
Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    if (this != &otherDict) {
        copyOther(otherDict);   // Copy contents of other into *this.
        numWords = otherDict.numWords;
    }

    // return self
    return *this;
}


//loads words from dictionary into file
void Dictionary::LoadDictionaryFile(string filename) {
    cout<<"\n Inside load dictionary";
    ifstream file;
    file.open (filename);
    if (!file)
    {
        throw "File failed to open";
    }

    string word;
    while (file >> word)
    {
        AddWord(word);
    }
    //closing file
    file.close();
}

//saves dictionary to file
void Dictionary::SaveDictionaryFile(string filename) {
    ofstream file;
    file.open (filename);
    if (!file)
    {
        throw DictionaryError(filename + "failed to open");
    }

    for(int i=0; i<NUM_CHARS; i++) {
        SaveDictionaryHelper(root->children[i], i, "", file);
    }

    //close the file
    file.close();
}

//helper method
void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, int iterator, string currPrefix, ofstream &outFile) {
    //cout<<"\n Inside recursive call";
    if(curr == nullptr) return;

    //add index-character
    currPrefix += (char) (iterator + (int)'a');
    if(curr->isWord) {
        outFile << currPrefix <<endl;
    }

    for(int i=0; i<NUM_CHARS; i++) {
        if(curr->children[i]!= nullptr) {
            SaveDictionaryHelper(curr->children[i],i, currPrefix, outFile);
        }
    }
}

//adds word to dictionary
void Dictionary::AddWord(string word) {
    //cout<<"\n Inside AddWord "<< word;
    //check if this word is already exists in dictionary
    if(IsWord(word)) return;
    //Increase word count
    ++numWords;
    //traverse from the root
    //and add nodes where the index is NULL
    Node *temp=root;
    int n=word.length();
    for(int i=0;i<n;++i){
        int index=(int)word[i]-(int)'a';
        //if character not between 'a' and 'z' throw DictionaryError
        if(index<0 || index>25) throw DictionaryError("Invalid character");
        if(temp->children[index]==NULL){
            temp->children[index]=new Node();
        }
        temp=temp->children[index];
    }
    //Make isword to true which indicates that it is word
    temp->isWord=true;
}

void Dictionary::MakeEmpty() {
    // Remove original tree
    destroyHelper(root);

    // Rebuild root and reset number of words
    root = new Node;
    numWords = 0;
}

bool Dictionary::IsWord(string word) {
    //length of word
    int n=word.length();
    //start from the root
    Node *temp=root;
    //traverse each word and check is there any node from that children
    //If not exists i.e null return false as no prefix
    //else move the pointer to it's children of that index
    for(int i=0;i<n;++i){
        int index=(int)word[i]-(int)'a';
        if(temp->children[index]==NULL)
            return false;
        temp=temp->children[index];
    }
    //check if this node's isWord is true or false return accordingly
    return (temp!=NULL && temp->isWord==true);
    //return false;
}

bool Dictionary::IsPrefix(string word) {
    //length of word
    int n=word.length();
    //start from root
    Node *temp=root;
    //traverse each word and check is there any node from that children
    //If not exists i.e null return false as no prefix
    //else move the pointer to it's children of that index
    for(int i=0;i<n;++i){
        int index=(int)word[i]-(int)'a';
        if(temp->children[index]==NULL)
            return false;
        temp=temp->children[index];
    }
    return true;
    //return false;
}

int Dictionary::WordCount() {
    return numWords; //return total number of words in dictionary
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();
    numWords = otherDict.numWords;

    copyHelper(root, otherDict.root);
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if (otherTree == nullptr) {
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->isWord = otherTree->isWord;

    for(int i=0; i<NUM_CHARS; i++) {
        copyHelper(thisTree->children[i], otherTree->children[i]);
    }
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if (thisTree == nullptr)
        return;

    for(int i=0; i<NUM_CHARS; i++) {
        destroyHelper(thisTree->children[i]);
    }
    delete thisTree;
}