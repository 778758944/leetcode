//
//  testtrie.cpp
//  leetcode
//
//  Created by WENTAO XING on 2019/3/27.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#include "./Trie.hpp"

int main() {
    struct TrieNode * root = getNode();
    TrieInsert(root, "the");
    TrieInsert(root, "world");
    cout << TrieSearch(root, "the") << endl;
    cout << TriePrefix(root, "thee") << endl;
    
}
