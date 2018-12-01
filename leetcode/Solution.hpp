//
//  Solution.hpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/23.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include "./BinaryTree.hpp"

using namespace std;
/*
struct Point {
    int x;
    int y;
    Point(int _x, int _y): x(_x), y(_y) {};
};

inline bool operator < (const Point& p1, const Point& p2) {
    if (p1.x != p2.x) {
        return p1.x < p2.x;
    } else {
        return p1.y < p2.y;
    }
}
 */

class Solution {
public:
    // convert an sorted array to balance tree
    typedef enum {
        nowhere,
        left,
        right,
        top,
        bottom
    } ExitFrom;
    
    struct Point {
        int x;
        int y;
        
        Point(int _x, int _y): x(_x), y(_y) {}
        bool operator < (const Point &rhs) const {
            if (x != rhs.x) {
                return x < rhs.x;
            } else {
                return y < rhs.y;
            }
        }
    };
    
    struct ListNode {
        int val;
        ListNode * next;
        ListNode(int _val): val(_val), next(NULL) {}
    };
    
    TreeNode * sortedArrayToBst(vector<int> arr) {
        unsigned long size = arr.size();
        TreeNode * p = new TreeNode(0);
        if (size == 0) {
            return NULL;
        }
        unsigned long pos = size/2;
        int mid = arr[pos];
        p->val = mid;
        vector<int>::iterator begin = arr.begin(),
        end = arr.end();
        vector<int> leftArr(begin, begin + pos);
        vector<int> rightArr(begin + pos + 1, end);
        p->left = sortedArrayToBst(leftArr);
        p->right = sortedArrayToBst(rightArr);
        return p;
    }
    
    void testSortedArrayToBst() {
        vector<int> arr = {-10,-3,0,5,9};
        TreeNode * t = sortedArrayToBst(arr);
        cout << t->val << endl;
    }
    
    // unique email
    int numUniqueEmails(vector<string>& emails) {
        set<string> s;
        for (string email: emails) {
            unsigned long pos = email.find('@');
            string localName = email.substr(0, pos);
            string domain = email.substr(pos);
            localName.erase(email.find('+'));
            unsigned long size = localName.size();
            unsigned long dot_index = 0;
            while (dot_index < size) {
                dot_index = localName.find('.', dot_index);
                if (dot_index == string::npos) {
                    break;
                } else {
                    localName.replace(dot_index, 1, "");
                    dot_index++;
                }
            }
            string realEmail = localName.append(domain);
            s.insert(realEmail);
        }
        return (int) s.size();
    }
    
    void testNumUniqueEmail() {
        vector<string> emails = {"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"};
        int n = numUniqueEmails(emails);
        cout << "unique email is " << n << endl;
    }
    
    string shiftingLetters(string S, vector<int> &shifts) {
        int size = (int) shifts.size();
        for (int i = 0; i < size; i++) {
            int shift = shifts[i] % 26;
            for (int j = i; j >= 0; j--) {
                char c = S[j];
                int last_dis = 'z' - c - shift;
                if (last_dis >= 0) {
                    S[j] = c + shift;
                } else {
                    S[j] = 'a' - last_dis - 1;
                }
            }
        }
        return S;
    }
    
    void testShiftLetters() {
        string s("z");
        vector<int> v {52};
        cout << shiftingLetters(s, v) << endl;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int size = (int) board.size();
        for (int i = 0; i < size; i++) {
            int len = (int) board[i].size();
            for (int j = 0; j < len; j++) {
                if (board[i][j] == word[0]) {
                    set<Point> visited;
                    visited.insert(Point(i, j));
                    if (exitHelper(board, i, j, word, 1, visited)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    
    bool exitHelper(vector<vector<char>> &board, int i, int j, string word, int idx, set<Point> &visited) {
        int v_arr = (int) board.size();
        int h_arr = (int) board[i].size();
        if (idx >= word.size()) return true;
        
        char c = word[idx];
        // left
        if (j - 1 >= 0 && visited.count(Point(i, j-1)) == 0) {
            if (c == board[i][j-1]) {
                set<Point> temp(visited.begin(), visited.end());
                temp.insert(Point(i, j - 1));
                if (exitHelper(board, i, j - 1, word, idx + 1, temp)) {
                    return true;
                }
            }
        }
        
        // right
        if (j + 1 < h_arr && visited.count(Point(i, j + 1)) == 0) {
            if (c == board[i][j+1]) {
                set<Point> temp(visited.begin(), visited.end());
                temp.insert(Point(i, j + 1));
                if (exitHelper(board, i, j + 1, word, idx + 1, temp)) {
                    return true;
                }
            }
        }
        
        // top
        if (i - 1 >= 0 && visited.count(Point(i - 1, j)) == 0) {
            if (c == board[i-1][j]) {
                set<Point> temp(visited.begin(), visited.end());
                temp.insert(Point(i - 1, j));
                if (exitHelper(board, i - 1, j, word, idx + 1, temp)) {
                    return true;
                }
            }
        }
        
        // bottom
        if (i + 1 < v_arr && visited.count(Point(i + 1, j)) == 0) {
            if (c == board[i+1][j]) {
                set<Point> temp(visited.begin(), visited.end());
                temp.insert(Point(i + 1, j));
                if (exitHelper(board, i + 1, j, word, idx + 1, temp)) {
                    return true;
                }
            }
        }
        
        
        return false;
    }
    
    void testExist() {
        vector<vector<char>> board {
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'E', 'S'},
            {'A', 'D', 'E', 'E'}
        };
        
        vector<vector<char>> board2 {
            {'a', 'a', 'a', 'a'},
            {'a', 'a', 'a', 'a'},
            {'a', 'a', 'a', 'a'}
        };
        
        string word("ABCESEEEFS");
        
        cout << exist(board, word) << endl;
    }
    
    vector<ListNode *> splitListToParts(ListNode * root, int k) {
        vector<ListNode *> result;
        vector<ListNode *> temp;
        
        while(root) {
            temp.push_back(root);
            root = root->next;
        }
        
        int size = (int) temp.size();
        int chunkSize = size/k;
        int mod = size % k;
        int index = 0;
        
        for (int i = 0; i < k; i++) {
            int len = (i < mod) ? chunkSize + 1 : chunkSize;
            cout << len << endl;
            if (index >= size) {
                result.push_back(NULL);
            } else {
                result.push_back(temp[index]);
                index += len;
                if (index <= size) temp[index-1]->next = NULL;
            }
        }
        
        return result;
    }
    
    ListNode * constructLink(vector<int> &arr) {
        ListNode * root = NULL;
        ListNode * temp = NULL;
        for (int i : arr) {
            if (!root) {
                root = new ListNode(i);
                temp = root;
            } else {
                ListNode * l = new ListNode(i);
                temp->next = l;
                temp = l;
            }
        }
        
        return root;
    }
    
    void testSplitListToParts() {
        vector<int> v {1, 2, 3, 4, 5, 6, 7};
        ListNode * root = constructLink(v);
        splitListToParts(root, 3);
    }
    
    bool wordPattern(string pattern, string str) {
        unsigned long index = 0;
        unordered_map<char, string> m;
        set<string> st;
        int size = (int) pattern.size();
        if (size == 0 && str.size() != 0) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            char c = pattern[i];
            unsigned long space_index = str.find(' ', index);
            string word = str.substr(index, space_index-index);
            // 真值判断
            if (m[c].empty()) {
                m[c] = word;
            }
            st.insert(word);
            
            if (m[c] != word || m.size() != st.size()) {
                return false;
            }
            
            if (i == size - 1 && space_index != string::npos) {
                i = -1;
            }
            
            if (space_index == string::npos && i != size - 1) {
                return false;
            }
            index = space_index + 1;
        }
        
        return true;
    }
    
    
    void testWordPattern() {
        cout << wordPattern("ab", "aa bb aa bb") << endl;
    }
    
    
    
    
};

#endif /* Solution_hpp */
