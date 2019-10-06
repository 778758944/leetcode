//
//  Trie.cpp
//  leetcode
//
//  Created by WENTAO XING on 2019/3/27.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "Trie.hpp"


struct TrieNode * getNode() {
    struct TrieNode * pNode = new TrieNode();
    pNode -> isEndOfWord = false;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
    }
    
    return pNode;
}

void TrieInsert(struct TrieNode * root, string key) {
    struct TrieNode * cur = root;
    for (char c: key) {
        int index = c - 'a';
        if (cur->children[index] == NULL) {
            cur->children[index] = getNode();
        }
        
        cur = cur->children[index];
    }
    cur->isEndOfWord = true;
}

bool TrieSearch(struct TrieNode * root, string key) {
    struct TrieNode * cur = root;
    for (char c: key) {
        int index = c - 'a';
        if (cur->children[index] == NULL) {
            return false;
        }
        
        cur = cur->children[index];
    }
    
    return cur != NULL && cur->isEndOfWord;
}

string TriePrefix(struct TrieNode * root, string key) {
    struct TrieNode * cur = root;
    string r;
    for (char c: key) {
        int index = c - 'a';
        if (cur->children[index] == NULL) {
            return "";
        }
        
        r.push_back(c);
        
        if (cur->children[index]->isEndOfWord) {
            return r;
        }
        
        cur = cur->children[index];
    }
    
    return "";
}

bool TrieSearchAllPrefix(struct TrieNode * root, string key) {
    struct TrieNode * cur = root;
    int size = (int) key.size();
    for (int i = 0; i < size - 1; i++) {
        int index = key[i] - 'a';
        if (cur->children[index] == NULL || !cur->children[index]->isEndOfWord) return false;
        cur = cur->children[index];
    }
    
    return true;
}

