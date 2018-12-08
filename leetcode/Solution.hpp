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
    
    struct TreeNode {
        int val;
        TreeNode * left;
        TreeNode * right;
        TreeNode(int x): val(x), left(NULL), right(NULL) {}
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
    
    TreeNode * generateFullTree(const vector<int> &arr) {
        TreeNode * root = nullptr;
        TreeNode * temp = nullptr;
        int size = (int) arr.size();
        for (int i = 0; i < size; i++) {
            TreeNode * node = new TreeNode(arr[i]);
            if (!root) {
                root = node;
                temp = node;
            } else {
                if (!temp->left) {
                    temp->left = node;
                } else {
                    temp->right = node;
                    temp = temp->left;
                }
            }
        }
        
        return root;
    }
    
    int binaryDeepLevel(TreeNode * root) {
        if (!root) return 0;
        return binaryDeepLevel(root->left) + 1;
    }
    
    int countNodes(TreeNode * root) {
        /*
        if (!root) return 0;
        int leftNum = countNodes(root->left);
        int rightNum = countNodes(root->right);
        return leftNum + rightNum + 1;
         */
        if (!root) return 0;
        /*
        vector<TreeNode *> v;
        v.push_back(root);
        int result = 0;
        
        while(!v.empty()) {
            int size = (int) v.size();
            for (int i = 0; i < size; i++) {
                TreeNode * temp = v[i];
                if (temp && temp->left) v.push_back(temp->left);
                if (temp && temp->right) v.push_back(temp->right);
            }
            result += size;
            v.erase(v.begin(), v.begin() + size);
        }
        
        return result;
         */
        
        int level = binaryDeepLevel(root) + 1;
        cout << level << endl;
        cout << (1 << level) - 1 << endl;
        int fullall = (1 << level) -1;
        
        TreeNode * curr = root;
        while (curr->left != NULL) {
            int lh = binaryDeepLevel(curr->left);
            int rh = binaryDeepLevel(curr->right);
            if (rh < lh) {
                fullall -= (1 << rh);
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return fullall;
    }
    
    void testCountNode() {
        vector<int> arr = {1, 2, 3, 4, 5, 6};
        TreeNode * root = generateFullTree(arr);
        cout << countNodes(root) << endl;
    }
    
    int findTargetSumWays(vector<int> &nums, int S) {
        vector<int> v(1, S);
        int result = 0;
        int size = (int) nums.size();
        
        for (int i = 0; i < size; i++) {
            int len = (int) v.size();
//            cout << len << endl;
            for (int j = 0; j < len; j++) {
                int r = v[0];
                int add = r + nums[i];
                int minus = r - nums[i];
                v.erase(v.begin(), v.begin() + 1);
                if (i == size - 1) {
                    if (add == 0) result++;
                    if (minus == 0) result++;
                } else {
                    v.push_back(add);
                    v.push_back(minus);
                }
            }
            
//            v.erase(v.begin(), v.begin() + len);
        }
        
        return result;
        /*
        findTargetHelper(nums, S, 0, (int) nums.size());
        return count;
         */
    }
    
    int count = 0;
    
    void findTargetHelper(vector<int>& nums, int s, int index, int size) {
        if (index == size) {
            if (s == 0) count++;
            return;
        }
        
        int lastAdd = s + nums[index];
        int lastMinus = s - nums[index];
        
        findTargetHelper(nums, lastAdd, index + 1, size);
        findTargetHelper(nums, lastMinus, index + 1, size);
    }
    
    void testFindTarget() {
        vector<int> nums = {2,7,9,13,27,31,37,3,2,3,5,7,11,13,17,19,23,29,47,53};
        int s = 107;
        
        cout << findTargetSumWays(nums, s) << endl;
    }
    
    void testInsertVector() {
        vector<int> v(3, 100);
        vector<int> v2 = {1, 2, 3};
        v.insert(v.end(), v2.begin(), v2.end());
        cout << v[2] << endl;
        
    }
    
    uint32_t reverseBits(uint32_t n) {
        uint32_t r = 0;
        uint32_t mask = 0x0001;
        for (int i = 0; i < 32; i++) {
            int left = n & mask;
            r = r << 1;
            r |= left;
            n = n >> 1;
        }
        return r;
    }
    
    bool validUtf8(vector<int> &data) {
        // get length form first byte
        int size = (int) data.size();
        int i = 0;
        int mask = 0x0001;
        
        while (i < size) {
            int num = data[i];
            int len = 0;
            int fb = (num >> 7) & mask;
            while (fb == 1) {
                len++;
                fb = (num >> (7-len)) & mask;
            }
            
            if (len > 4 || len == 1) {
                return false;
            } else if (len == 0) {
                i++;
            } else {
                int n = 0;
                while (n < len - 1) {
                    ++i;
                    if (i < size) {
                        if (!isContinueUtf8Byte(data[i])) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                    ++n;
                }
                
                i++;
            }
        }
        
        
        return true;
    }
    
    bool isContinueUtf8Byte(int t) {
        int mask = 0x0001;
        int fb = (t >> 7) & mask;
        int sb = (t >> 6) & mask;
        
        if (fb == 1 && sb == 0) {
            return true;
        }
        
        return false;
    }
    
    
    void testValidUtf8() {
        vector<int> v = {235, 140, 4};
        cout << validUtf8(v) << endl;
    }
    
    bool validMountainArray(vector<int> &A) {
        int size = (int) A.size();
        if (size < 3) return false;
        int temp = A[0];
        bool isUp = true;
        for(int i = 1; i < size; i++) {
            int num = A[i];
            if (num == temp) return false;
            if (isUp) {
                if (num < temp) {
                    isUp = false;
                    if (i == 1) return false;
                }
            } else {
                if (num > temp) {
                    return false;
                }
            }
            temp = num;
        }
        return !isUp;
    }
    
    void testValidMountainArray() {
        vector<int> v = {3, 5, 5};
        cout << validMountainArray(v) << endl;
    }
    
    int uniquePath(int m, int n) {
        vector<vector<int> > path (m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                path[i][j] = path[i][j-1] + path[i-1][j];
            }
        }
        return path[m-1][n-1];
    }
    
    int longestPailndrome(string s) {
        map<char, int> m;
        int r = 0;
        int len = (int) s.size();
        for (int i = 0; i < len; i++) {
            char c = s[i];
            if (!m[c]) {
                m[c] = 1;
            } else {
                m[c] += 1;
            }
        }
        
        for (pair<const char, int> &p : m) {
            if (p.second % 2 == 0) {
                r += p.second;
            } else {
                if (r % 2 == 0) {
                    r += p.second;
                } else {
                    r += (p.second - 1);
                }
            }
        }
        return r;
    }
    
    void testLongestPailndrome() {
        string s = "abccccdd";
        cout << longestPailndrome(s) << endl;
    }
    
    // leetcode 718
    int findLength(vector<int> &A, vector<int> &B) {
        int a_len = (int) A.size();
        int b_len = (int) B.size();
        int r = 0;
        for (int i = b_len - 1; i >= 0; i--) {
            int temp = 0;
            for (int j = 0; j < a_len; j++) {
                if (i + j >= b_len) {
                    r = r > temp ? r : temp;
                    break;
                };
                
                if (A[j] == B[i + j]) {
                    temp += 1;
                } else {
                    r = r > temp ? r : temp;
                    temp = 0;
                }
            }
            r = r > temp ? r : temp;
        }
        
        for (int i = 1; i < a_len; i++) {
            int temp = 0;
            for (int j = 0; j < b_len; j++) {
                if (i + j >= a_len) {
                    r = r > temp ? r : temp;
                    break;
                }
                
                
                if (B[j] == A[i + j]) {
                    temp += 1;
                } else {
                    r = r > temp ? r : temp;
                    temp = 0;
                }
            }
            r = r > temp ? r : temp;
        }
        
        return r;
    }
    
    void testFindLength() {
        vector<int> a = {0,1,1,1,1};
        vector<int> b = {1,0,1,0,1};
        
        cout << findLength(a, b) << endl;
    }
    
    
    
    
};

#endif /* Solution_hpp */
