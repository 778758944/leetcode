//
//  Trie.hpp
//  leetcode
//
//  Created by WENTAO XING on 2019/3/27.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include <iostream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    struct TrieNode * children[ALPHABET_SIZE];
    bool isEndOfWord;
};


struct TrieNode * getNode(void);
void TrieInsert(struct TrieNode * root, string key);
bool TrieSearch(struct TrieNode * root, string key);
string TriePrefix(struct TrieNode * root, string key);
bool TrieSearchAllPrefix(struct TrieNode * root, string key);




#endif /* Trie_hpp */
