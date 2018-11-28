//
//  BinaryTree.hpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/23.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp
#include <stdio.h>

struct TreeNode {
    struct TreeNode * left;
    struct TreeNode * right;
    int val;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

#endif /* BinaryTree_hpp */
