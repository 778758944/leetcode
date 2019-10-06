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
#include <algorithm>
#include <limits>
#include <stack>
#include <functional>
#include <unordered_set>
#include <cmath>
#include <stdlib.h> // for abs
#include <sstream>
#include <cstring>
#include <queue>
#include <iomanip>
#include "./Trie.hpp"

#define A(i) nums[(1+2*(i)) % (n|1)]

using namespace std;
//bool fncomp(pair<char, int> &lhs, pair<char, int> &rhs) {
//    return lhs.second > rhs.second;
//}
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
    
    struct EdgeNode {
        int vertex;
        EdgeNode * next;
        EdgeNode(int x): vertex(x), next(NULL) {}
    };
    
    struct AdjListNode {
        int data;
        int ind;
        EdgeNode * firstEdge;
        AdjListNode(int x): data(x), ind(0), firstEdge(NULL) {}
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
    
    // review
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
    
    // leetcode 744
    
    char nextGreatestLetter(vector<char> &letters, char target) {
        int size = (int) letters.size();
        int low = 0;
        int high = size;
        
        if (letters[size - 1] <= target) {
            return letters[0];
        }
        
        while (low <= high) {
            int mid = (low + high) / 2;
            if (letters[mid] > target) {
                high = mid - 1;
            } else if (letters[mid] < target) {
                low = mid + 1;
            } else {
                mid += 1;
                while(mid < size) {
                    if (letters[mid] > target) {
                        return letters[mid];
                    }
                    mid++;
                }
                
                return letters[0];
            }
        }
        return letters[low];
    }
    
    void testNextGreatestLetter() {
        vector<char> v = {'e','e','e','k','q','q','q','v','v','y'};
        char target = 'q';
        
        cout << nextGreatestLetter(v, target) << endl;
    }
    
    // leetcode 162
    int findPeakElement(vector<int> &nums) {
        /*
        int size = (int) nums.size();
        for (int i = 0; i < size; i++) {
            int temp = nums[i];
            int before = i - 1 < 0 ? INT_MIN : nums[i - 1];
            int after = i + 1 < size ? nums[i + 1] : INT_MIN;
            if (temp > before && temp > after) {
                return i;
            }
        }
         */
        int size = (int) nums.size();
        for (int i = 1; i < size; i++) {
            if (nums[i] < nums[i - 1]) return i - 1;
        }
        
        return size - 1;
    }
    
    void testFindPeakElement() {
        vector<int> v = {1, 2};
        cout << findPeakElement(v) << endl;
    }
    
    void testMax() {
        vector<int> v = {1, 2, 3};
        cout << max(1, 2) << endl;
    }
    
    // leetcode 743
    int networkDelayTime2(vector<vector<int> > &times, int N, int K) {
        vector<int> weight(N, INT_MAX);
        vector<vector<int> > edges(N, weight);
        for (auto &t: times) {
            edges[t[0] - 1][t[1] - 1] = t[2];
        }
        
        int start = K - 1;
        int cast = 0;
        vector<int> path;
        vector<int> table;
        vector<bool> calculate;
        for (auto &t: edges[start]) {
            table.push_back(t);
            path.push_back(start);
            calculate.push_back(false);
        }
        
        table[start] = 0;
        calculate[start] = true;
        
        for (int i = 1; i < N; i++) {
            int min = INT_MAX;
            int k = 0;
            int j = 0;
            
            while(j < N) {
                if (!calculate[j] && table[j] < min) {
                    min = table[j];
                    k = j;
                }
                j++;
            }
            
            if (min < INT_MAX) {
                calculate[k] = 1;
                for (int x = 0; x < N; x++) {
                    if (!calculate[x] && edges[k][x] < 6001 && min + edges[k][x] < table[x]) {
                        table[x] = min + edges[k][x];
                        path[x] = k;
                    }
                }
            }
            
        }
        
        for (bool t: calculate) {
            if (t == 0) return -1;
        }
        
        
        for (int t: table) {
            if (t > cast) {
                cast = t;
            }
        }
        
        
        
        
        
        return cast;
    }
    
    int networkDelayTime(vector<vector<int> > &times, int N, int K) {
        unordered_map<int, int> r;
        r[K] = 0;
        set<int> from;
        from.insert(K);
        networkDelayHelper(times, from, r, K);
        int max = -1;
        
        
        if (r.size() == N) {
            for (pair<const int, int> &t: r) {
                if (t.second > max) max = t.second;
            }
        }
        
        return max;
    }
    
    
    void networkDelayHelper(vector<vector<int> > &times, set<int> &start, unordered_map<int, int> &r, int K) {
        set<int> from;
        vector<vector<int> > t;
        int size = (int) times.size();
        for (int i = 0; i < size; i++) {
            vector<int> edge = times[i];
            if (edge[1] == K) continue;
            if (start.count(edge[0])) {
                if (r[edge[1]] > 0) {
                    if (r[edge[1]] > r[edge[0]] + edge[2]) {
                        r[edge[1]] = r[edge[0]] + edge[2];
                    }
                } else {
                    r[edge[1]] = edge[2] + r[edge[0]];
                }
                from.insert(edge[1]);
            } else {
                t.push_back(times[i]);
            }
        }
        
        if (!from.empty()) networkDelayHelper(t, from, r, K);
    }
    
    void testNetworkDelayTime() {
        vector<int> edge1 = {2, 1, 1};
        vector<int> edge2 = {2, 3, 1};
        vector<int> edge3 = {3, 4, 1};
        vector<int> edge4 = {1, 2, 1};

        vector<vector<int>> edge = {edge1, edge2, edge3};
        cout << networkDelayTime2(edge, 4, 2) << endl;
        
    }
    
    // 367
    bool isPerfectSquare(int num) {
        unsigned long low = 0;
        unsigned long high = num;
        
        while (low <= high) {
            unsigned long mid = (high + low) / 2;
            unsigned long all = mid * mid;
            if (all > num) {
                high = mid - 1;
            } else if (all < num) {
                low = mid + 1;
            } else {
                return true;
            }
        }
        return false;
    }
    
    void testIsPrefectSquare() {
        int t = 2147395600;
        cout << isPerfectSquare(t) << endl;
    }
    
    // 50
    double myPow(double x, int n) {
        if(n == 0) return 1;
        if(n == INT_MIN){
            x = x * x;
            n = n/2;
        }
        if(n < 0) {
            n = -n;
            x = 1/x;
        }
        
        return (n%2 == 0) ? myPow(x * x, n/2) : x *  myPow(x * x, n/2);
    }
    
    void testMyPow() {
        cout << myPow(2.00000, -2) << endl;
    }
    
    // 525
    int findMaxLength(vector<int> &nums) {
        int max = 0;
        int size = (int) nums.size();
        int count = 0;
        map<int, int> m;
        m[0] = -1;
        for (int i = 0; i < size; i++) {
            count += nums[i] == 0 ? -1 : 1;
            if (m.count(count)) {
                max = max > i - m[count] ? max : i - m[count];
            } else {
                m[count] = i;
            }
        }
        
        return max;
    }
    
    
    void testFindMaxLength() {
        vector<int> v = {0, 1};
        cout << findMaxLength(v) << endl;
    }
    
    //203
    ListNode * removeElements(ListNode * head, int val) {
        ListNode * temp = head;
        ListNode * before = NULL;
        while (temp) {
            if (temp->val == val) {
                if (before) {
                    before->next = temp->next;
                } else {
                    head = temp->next;
                }
            } else {
                before = temp;
            }
            temp = temp->next;
        }
        
        return head;
    }
    
    // 328
    ListNode * oddEvenList(ListNode * head) {
        ListNode * odd = NULL;
        ListNode * even = NULL;
        ListNode * oddTemp = NULL;
        ListNode * evenTemp = NULL;
        int i = 1;
        
        while (head) {
            if (i % 2 == 0) {
                if (!even) {
                    even = head;
                    evenTemp = head;
                } else {
                    evenTemp -> next = head;
                    evenTemp = head;
                }
            } else {
                if (!odd) {
                    odd = head;
                    oddTemp = head;
                } else {
                    oddTemp->next = head;
                    oddTemp = head;
                }
            }
            i++;
            head = head->next;
        }
        if (oddTemp) oddTemp->next = even;
        if (evenTemp) evenTemp->next = NULL;
        return odd;
    }
    
    void testOddEvenList() {
        vector<int> v = {1,2,3,4,5};
        ListNode * head = constructLink(v);
    }
    
    // 704
    int search(vector<int> &nums, int target) {
        int low  = 0;
        int high = (int) nums.size() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (nums[mid] > target) {
                high = mid - 1;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                return mid;
            }
        }
        
        return -1;
    }
    
    void testSearch() {
        vector<int> v = {-1, 0, 3, 5, 9, 12};
        cout << search(v, 2) << endl;
    }
    
    //34
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> v;
        int left = -1;
        int right = -1;
        int low = 0;
        int high = (int) nums.size() - 1;
        int first = -1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (nums[mid] < target) {
                low = mid + 1;
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                if (first == -1) first = mid;
                left = mid;
                high = mid - 1;
            }
        }
        
        
        if (first > -1) {
            low = first;
            high = (int) nums.size() - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (nums[mid] < target) {
                    low = mid + 1;
                } else if (nums[mid] > target) {
                    high = mid - 1;
                } else {
                    right = mid;
                    low = mid + 1;
                }
            }
        }
        
        v.push_back(left);
        v.push_back(right);
        
        return v;
    }
    
    
    void testSearchRange() {
        vector<int> v = {};
        vector<int> r = searchRange(v, 0);
        for (int i: r) {
            cout << i << endl;
        }
    }
    
    // 501
    vector<int> findMode(TreeNode * root) {
        int max = 0;
        vector<int> v;
        map<int, int> m;
        
        findModeHelper(root, m);
        
        for (pair<const int, int> p: m) {
            cout << p.first << "=" << p.second << endl;
            if (p.second > max) {
                v.clear();
                v.push_back(p.first);
                max = p.second;
            } else if (p.second == max) {
                v.push_back(p.first);
            }
        }
        
        return v;
        
    }
    
    void findModeHelper(TreeNode * node, map<int, int> &m) {
        if (!node) return;
        int val = node->val;
        if (!m[val]) {
            m[val] = 1;
        } else {
            m[val] += 1;
        }
        
        findModeHelper(node->left, m);
        findModeHelper(node->right, m);
    }
    
    int findModeCount = 0;
    int findModeMax = 0;
    
    // 538
    int convertBstSum = 0;
    TreeNode * convertBST(TreeNode * root) {
        if (root != NULL) {
            convertBST(root->right);
            convertBstSum += root->val;
            root->val = convertBstSum;
            convertBST(root->left);
        }
        return root;
    }
    
    // 371
    int getSum(int a, int b) {
        int size = (int) sizeof(int) * CHAR_BIT;
        int r = 0;
        int carry = 0;
        int mask = 0x0001;
        for (int i = 0; i < size; i++) {
            int ta = a & mask;
            int tb = b & mask;
            int ts = (ta ^ tb);
            int pos = ts ^ carry;
            
            r |= (pos << i);
            
            if ((ta && tb) || (ts && carry)) {
                carry = 1;
            } else {
                carry = 0;
            }
            a >>= 1;
            b >>= 1;
        }
        
        return r;
    }
    
    
    
    void testGetSum() {
        int a = 2;
        int b = 3;
        cout << getSum(a, b) << endl;
    }
    
    // 897
    TreeNode * increasingBST(TreeNode * root) {
        increasingBSTHelper(root);
        return increasingr;
    }
    
    void increasingBSTHelper(TreeNode * node) {
        if (!node) return;
        increasingBSTHelper(node->left);
        if (!increasingr) {
            increasingr = new TreeNode(node->val);
            increasingt = increasingr;
        } else {
            increasingt->right = new TreeNode(node->val);
            increasingt = increasingr->right;
        }
        increasingBSTHelper(node->right);
    }
    
    TreeNode * increasingr;
    TreeNode * increasingt;
    
    // 872
    bool leafSimilar(TreeNode * root1, TreeNode * root2) {
        string v1;
        string v2;
        
        getLeaf(root1, v1);
        getLeaf(root2, v2);
        
        return v1 == v2;
    }
    
    void getLeaf(TreeNode * node, string &v) {
        if (!node) return;
        getLeaf(node->left, v);
        if (!node->left && !node->right) {
            v.push_back(node->val);
        }
        getLeaf(node->right, v);
    }
    
    // 414
    int thirdMax(vector<int> &nums) {
        vector<int> maxArr;
        for (int num: nums) {
            int size = (int) maxArr.size();
            if (size == 0) {
                maxArr.push_back(num);
            } else {
                int front = maxArr.front();
                int back = maxArr.back();
                
                if (num == front || num == back) continue;
                
                if (num > front) {
                    maxArr.insert(maxArr.begin(), num);
                } else if (num > back) {
                    if (size == 1) {
                        maxArr.push_back(num);
                    } else if (size == 2) {
                        maxArr.insert(maxArr.begin() + 1, num);
                    } else {
                        int mid = maxArr[1];
                        if (num > mid) {
                            maxArr.insert(maxArr.begin() + 1, num);
                        } else if (num < mid) {
                            maxArr.insert(maxArr.begin() + 2, num);
                        }
                    }
                } else if (num < back && size < 3) {
                    maxArr.push_back(num);
                }
                
                if (maxArr.size() > 3) maxArr.pop_back();
            }
        }
        
        if (maxArr.size() == 3) return maxArr.back();
        return maxArr.front();
    }
    
    void testThirdMax() {
        vector<int> v = {1, 2, 2};
        cout << thirdMax(v) << endl;
    }
    
    // 404
    int sumOfLeftLeaves(TreeNode * root) {
        int leftNum = 0, rightNum = 0;
        if (root->left) {
            if (!root->left->left && !root->left->right) {
                leftNum = root->val;
            } else {
                leftNum = sumOfLeftLeaves(root->left);
            }
        }
        
        if (root->right) {
            rightNum = sumOfLeftLeaves(root->right);
        }
        
        return leftNum + rightNum;
    }
    
    // 242
    bool isAnagram(string s, string t) {
        int s_size = (int) s.size();
        int t_size = (int) t.size();
        if (s_size != t_size) return false;
        vector<int> v(26, 0);
        for (int i = 0; i < s_size; i++) {
            v[s[i] - 'a']++;
            v[t[i] - 'a']--;
        }
        
        for (int j = 0; j < 26; j++) {
            if (v[j] != 0) return false;
        }
        
        return true;
    }
    
    void testIsAnagram() {
        string s = "anagram";
        string t = "nagaram";
        cout << isAnagram(s, t) << endl;
    }
    
    //669
    TreeNode * trimBST(TreeNode * root, int L, int R) {
        if (!root) return NULL;
        int val = root->val;
        TreeNode * t;
        if (val < L) {
            t = trimBST(root->right, L, R);
        } else if (val > R) {
            t = trimBST(root->left, L, R);
        } else {
            t = root;
            t->left = trimBST(root->left, L, R);
            t->right = trimBST(root->right, L, R);
        }
        
        return t;
        
    }
    
    //876
    ListNode * middleNode(ListNode * head) {
        if (!head) return NULL;
        vector<ListNode *> v;
        while (head) {
            v.push_back(head);
            head = head->next;
        }
        int size = (int) v.size();
        return v[size/2];
    }
    
    // 92
    ListNode * reverseBetween(ListNode * head, int m, int n) {
        int i = 1;
        bool isInReverse = false;
        ListNode * temp = nullptr;
        ListNode * rlast = nullptr;
        ListNode * vlast = nullptr;
        ListNode * ttth = head;
        while(head) {
            ListNode * tnext = head->next;
            if (i == m) {
                isInReverse = true;
                temp = head;
                rlast = head;
            } else if (isInReverse && i <= n) {
                head->next = temp;
                temp = head;
            } else if (i > n) {
                rlast->next = head;
                if (vlast) {
                    vlast->next = temp;
                    break;
                } else {
                    ttth = temp;
                    break;
                }
            } else {
                vlast = head;
            }
            head = tnext;
            i++;
        }
        
        if (!head) {
            rlast->next = head;
            if (vlast) {
                vlast->next = temp;
            } else {
                ttth = temp;
            }
        }
        
        
        
        return ttth;
    }
    
    void testReverseBetween() {
        vector<int> v = {3, 5};
        ListNode * l = constructLink(v);
        ListNode * t = reverseBetween(l, 1, 2);
        cout << 1 << endl;
    }
    
    // 167
    vector<int> twoSum(vector<int> &numbers, int target) {
        vector<int> r;
        int size = (int) numbers.size();
        for (int i = 0; i < size; i++) {
            int n = numbers[i];
            int remain = target - n;
            int low = 0;
            int high = size - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                int cn = numbers[mid];
                if (cn > remain) {
                    high = mid - 1;
                } else if (cn < remain) {
                    low = mid + 1;
                } else {
                    if (mid != i) {
                        r.push_back(i + 1);
                        r.push_back(mid + 1);
                        return r;
                    }
                    
                    low = mid + 1;
                }
            }
        }
        
        return r;
    }
    
    void testTwoSum() {
        vector<int> t = {1, 2, 3, 4, 4, 9, 56, 90};
        int sum = 8;
        vector<int> r = twoSum(t, sum);
        for (auto t: r) {
            cout << t << endl;
        }
    }
    
    // 207
    
    bool canFinish(int numCourses, vector<pair<int, int> > &prerequisites) {
        vector<AdjListNode *> v(numCourses, nullptr);
        for (int i = 0; i < numCourses; i++) {
            v[i] = new AdjListNode(i);
        }
        
        for (pair<int, int> &p: prerequisites) {
            int target = p.first;
            int source = p.second;
            
            EdgeNode * edge = new EdgeNode(target);
            edge->next = v[source]->firstEdge;
            v[source]->firstEdge = edge;
            v[target]->ind += 1;
        }
        
        stack<int> s;
        int count = 0;
        
        for (int i = 0; i < numCourses; i++) {
            if (v[i]->ind == 0) {
                s.push(i);
            }
        }
        
        while(!s.empty()) {
            int i = s.top();
            s.pop();
            count += 1;
            EdgeNode * e;
            for (e = v[i]->firstEdge; e; e = e->next) {
                if (!(--(v[e->vertex]->ind))) {
                    s.push(e->vertex);
                }
            }
        }
        
        if (count == numCourses) return true;
        return false;
    }
    
    void testCanFinish() {
        pair<int, int> p1 = make_pair(0, 1);
        vector<pair<int, int> > prerequisites = { p1 };
        int numCourses = 2;
        cout << canFinish(numCourses, prerequisites) << endl;
    }
    
    // 496
    vector<int> nextGreaterElement(vector<int> &findNums, vector<int> &nums) {
        vector<int> r;
        stack<int> s;
        unordered_map<int, int> m;
        for (int n: nums) {
            while (!s.empty() && s.top() < n) {
                m[s.top()] = n;
                s.pop();
            }
            s.push(n);
        }
        
        for (int n: findNums) {
            r.push_back(m.count(n) == 0 ? -1: m[n]);
        }
        return r;
    }
    
    void testNextGreaterElement() {
        vector<int> findNums = {4, 1, 2};
        vector<int> nums = {1, 3, 4, 2};
        vector<int> r = nextGreaterElement(findNums, nums);
        for (int i: r) {
            cout << i << endl;
        }
    }
    
    // 210
    vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites) {
        vector<AdjListNode *> adjNodes(numCourses, nullptr);
        vector<int> r;
        for (int i = 0; i < numCourses; i++) {
            adjNodes[i] = new AdjListNode(i);
        }
        
        for (pair<int, int> &t: prerequisites) {
            int dest = t.first;
            int source = t.second;
            EdgeNode * edge = new EdgeNode(dest);
            edge->next = adjNodes[source]->firstEdge;
            adjNodes[source]->firstEdge = edge;
            adjNodes[dest]->ind += 1;
        }
        
        stack<int> s;
        for (int i = 0; i < numCourses; i++) {
            if (adjNodes[i]->ind == 0) {
                s.push(i);
            }
        }
        
        while (!s.empty()) {
            int t = s.top();
            s.pop();
            r.push_back(t);
            EdgeNode * e;
            for (e = adjNodes[t]->firstEdge; e; e = e->next) {
                if (!(--adjNodes[e->vertex]->ind)) {
                    s.push(e->vertex);
                }
            }
        }
        
        int pathsize = (int) r.size();
        
        if (pathsize != numCourses) {
            vector<int> empty;
            return empty;
        }
        
        
        return r;
        
    }
    
    void testFindOrder() {
        int numCourses = 2;
        pair<int, int> p1 = make_pair(1, 0);
        vector<pair<int, int> > p = { p1 };
        vector<int> path = findOrder(numCourses, p);
        for (int i: path) {
            cout << i << endl;
        }
    }
    
    // 257
    vector<string> binaryTreePaths(TreeNode * root) {
        vector<string> r;
        string s;
        binaryTreePathsHelper(root, s, r);
        return r;
        
    }
    
    void binaryTreePathsHelper(TreeNode * node, string s, vector<string> &r) {
        if (!node) return;
        if (s.empty()) {
            s.append(to_string(node->val));
        } else {
            s.append("->");
            s.append(to_string(node->val));
        }
        
        if (!node->left && !node->right) {
            r.push_back(s);
        } else {
            binaryTreePathsHelper(node->left, s, r);
            binaryTreePathsHelper(node->right, s, r);
        }
    }
    
    void testBinaryTreePaths() {
        string str = "hell";
        string temp = str;
        temp.push_back('O');
        cout << str << endl;
        cout << temp << endl;
    }
    
    // 894
    vector<TreeNode *> allPossibleFBT(int N) {
        map<int, vector<TreeNode *> > memo;
        
        if (!memo.count(N)) {
            vector<TreeNode *> ans;
            if (N == 1) {
                ans.push_back(new TreeNode(0));
            } else if (N % 2 == 1) {
                for (int x = 0; x < N; x++) {
                    int y = N - 1 - x;
                    for (TreeNode * left: allPossibleFBT(x)) {
                        for (TreeNode * right: allPossibleFBT(y)) {
                            TreeNode * t = new TreeNode(0);
                            t->left = left;
                            t->right = right;
                            ans.push_back(t);
                        }
                        
                    }
                }
            }
            memo[N] = ans;
        }
        return memo[N];
    }
    
    // 125
    bool isPalindrome(string s) {
        string temp;
        for (char i: s) {
            if ((i >= '0' && i <= '9') || (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z')) {
                if (i >= 'A' && i <= 'Z') {
                    i += 32;
                }
                 temp.push_back(i);
            }
        }
        
        int size = (int) temp.size();
        if (size == 0) return true;
        int i = 0;
        int j = size - 1;
        
        while (i <= j) {
            if (temp[i] != temp[j]) {
                return false;
            }
            i++;
            j--;
        }
        
        return true;
    }
    
    
    void testIsPalidrome() {
        string s = "\"`l;`` 1o1 ??;l`\"";
        cout << isPalindrome(s) << endl;
    }
    
    
    //332
    struct MGraph {
        vector<string> vertexs;
        vector<vector<int> > edges;
        int numVertex;
        int numEdges;
    };
    
    vector<string> findItinerary(vector<pair<string, string> > tickets) {
        vector<string> r = {"JFK"};
        MGraph m;
        int ssize = 150;
        for (int i = 0; i < ssize; i++) {
            vector<int> t(ssize, INT_MAX);
            m.edges.push_back(t);
        }
        for (pair<string, string> ticket: tickets) {
            string source = ticket.first;
            string dest = ticket.second;
            int source_index, dest_index, weight = 0;
            vector<string>::iterator begin = m.vertexs.begin(), end = m.vertexs.end();
            
            for (int n: dest) {
                weight += n;
            }
            
            cout << weight << endl;
            
            
            auto t = find(begin, end, source);
            if (t == end) {
                m.vertexs.push_back(source);
                source_index = (int) (end - begin);
            } else {
                source_index = (int) (t - begin);
            }
            
            begin = m.vertexs.begin();
            end = m.vertexs.end();
            
            auto et = find(begin, end, dest);
            if (et == end) {
                m.vertexs.push_back(dest);
                dest_index = (int) (end - begin);
            } else {
                dest_index = (int) (et - begin);
            }
            
            cout << source_index << " " << dest_index << endl;
            m.edges[source_index][dest_index] = weight;
        }
        
        m.numEdges = (int) tickets.size();
        m.numVertex = (int) m.vertexs.size();
        
        vector<string>::iterator it = find(std::begin(m.vertexs), std::end(m.vertexs), "JFK");
        int start = (int) (it - m.vertexs.begin());
        cout << start << endl;
        
        vector<int> lowcast(m.numVertex, INT_MAX);
        vector<string> vertex(m.numVertex, "");
        lowcast[start] = 0;
        vertex[start] = m.vertexs[start];
        for (int i = 0; i < m.numVertex; i++) {
            if (i != start) {
                lowcast[i] = m.edges[start][i];
                vertex[i] = m.vertexs[start];
            }
        }
        
        for (int i = 1; i < m.numVertex; i++) {
            int min = INT_MAX;
            int k = 0;
            for (int j = 0; j < m.numVertex; j++) {
                if (lowcast[j] != 0 && lowcast[j] < min) {
                    min = lowcast[j];
                    k = j;
                }
            }
            
            r.push_back(m.vertexs[k]);
            lowcast[k] = 0;
            cout << vertex[k] << "->" << m.vertexs[k] << endl;
            
            for (int j = 0; j < m.numVertex; j++) {
                if (lowcast[j] != 0 && m.edges[k][j] < lowcast[j]) {
                    lowcast[j] = m.edges[k][j];
                    vertex[j] = m.vertexs[k];
                }
            }
            
            
        }
        
        return r;
    }
    
    void testFindItinerary() {
        pair<string, string> p1 = make_pair("JFK", "SFO");
        pair<string, string> p2 = make_pair("JFK", "ATL");
        pair<string, string> p3 = make_pair("SFO", "ATL");
        pair<string, string> p4 = make_pair("ATL", "JFK");
        pair<string, string> p5 = make_pair("ATL", "SFO");
        
        vector<pair<string, string> > tickets = {p1, p2, p3, p4, p5};
        vector<string> path = findItinerary(tickets);
        
        for (string p: path) {
            cout << p << endl;
        }
    }
    
    // 169
    int majorityElement(vector<int> &nums) {
        /*
        unordered_map<int, int> m;
        int size = (int) nums.size();
        for (int i = 0; i < size; i++) {
            int temp = nums[i];
            if (!m[temp]) {
                m[temp] = 1;
            } else {
                m[temp] += 1;
            }
            
            if (i >= size/2) {
                if (m[temp] > size/2) {
                    return temp;
                }
            }
        }
        return 1;
         */
        /*
        sort(nums.begin(), nums.end(), greater<int>());
        return nums[nums.size()/2];
         */
        int size = (int) nums.size();
        int count = 0;
        int result = 0;
        for (int i = 0; i < size; i++) {
            if (count == 0 || result == nums[i]) {
                result = nums[i];
                count++;
            } else {
                count--;
            }
        }
        
        return result;
    }
    
    void testMajorityElement() {
        vector<int> v = {2, 2};
        cout << majorityElement(v) << endl;
    }
    
    // 318
    int maxProduct(vector<string> &words) {
        /*
        int size = (int) words.size();
        int max = 0;
        for (int i = 0; i < size - 1; i++) {
            string t = words[i];
            for (int j = i + 1; j < size; j++) {
                string d = words[j];
                string::size_type pos = -1;
                for(char c: d) {
                    pos = t.find(c);
                    if (pos != -1) {
                        break;
                    }
                }
                if (pos != -1) continue;
                
                int len = (int) (t.size() * d.size());
                max = max > len ? max : len;
            }
        }
         */
        int size = (int) words.size();
        vector<int> mask(size, 0);
        int r = 0;
        for (int i = 0; i < size; i++) {
            for (char c: words[i]) {
                mask[i] |= 1 << (c - 'a');
            }
            
            for (int j = 0; j < i; j++) {
                if (!(mask[i] & mask[j])) {
                    int len = (int) (words[i].size() * words[j].size());
                    r = len > r ? len : r;
                }
            }
        }
        
        return r;
    }
    
    void testMaxProduct() {
        vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
        cout << maxProduct(words) << endl;
    }
    
    // 349
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        /*
        vector<int> r;
        set<int> t;
        set<int> rs;
        for (int n: nums1) {
            t.insert(n);
        }
        for (int m: nums2) {
            if (t.count(m)) {
                rs.insert(m);
            }
        }
        for (int n: rs) {
            r.push_back(n);
        }
        return r;
         */
        unordered_set<int> m(nums1.begin(), nums1.end());
        vector<int> res;
        for (auto a : nums2)
            if (m.count(a)) {
                res.push_back(a);
                m.erase(a);
            }
        return res;
    }
    
    void testIntersection() {
        vector<int> v1 = {1,2,2,1};
        vector<int> v2 = {2, 2};
        vector<int> r = intersection(v1, v2);
        for (int n: r) {
            cout << n << endl;
        }
    }
    
    // 938
    int rangeSumBST(TreeNode * root, int L, int R) {
        if (!root) return 0;
        int t = root->val;
        if (t < L) {
            t += rangeSumBST(root->right, L, R);
        } else if (t > R) {
            t += rangeSumBST(root->left, L, R);
        } else {
            t += rangeSumBST(root->left, L, R);
            t += rangeSumBST(root->right, L, R);
        }
        return t;
    }
    
    // 700
    TreeNode * searchBST(TreeNode * root, int val) {
        if (!root) return NULL;
        if (val < root->val) {
            return searchBST(root->left, val);
        } else if (val > root->val) {
            return searchBST(root->right, val);
        } else {
            return root;
        }
    }
    
    // 865
    TreeNode * subtreeWithAllDeepest(TreeNode * root) {
        if (!root) return NULL;
        vector<TreeNode *> v;
        vector<TreeNode *> v2;
        v.push_back(root);
        v2.push_back(root);
        while (!v.empty()) {
            int size = (int) v.size();
            for (int i = 0; i < size; i++) {
                if (v[i]) {
                    v2.push_back(v[i]);
                    if (v[i]->left) v.push_back(v[i]->left);
                    if (v[i]->right) v.push_back(v[i]->right);
                }
            }
            if (size == (int) v.size()) {
                int index = (int) (v2.size() - size);
                return v2[index];
            } else {
                v.erase(v.begin(), v.begin() + size);
            }
        }
        
        return NULL;
    }
    
    // 922
    vector<int> sortArrayByParityII(vector<int> &A) {
        int size = (int) A.size();
        vector<int> r(size, 0);
        int x = 0, y = 1;
        for (int n: A) {
            if (n % 2 == 0) {
                r[x] = n;
                x += 2;
            } else {
                r[y] = n;
                y += 2;
            }
        }
        return r;
    }
    
    // 148
    ListNode * sortList(ListNode * head) {
        // bubble
        vector<int> v;
        ListNode * r = NULL;
        ListNode * t = NULL;
        for (; head != NULL; head = head->next) {
            v.push_back(head->val);
        }
        int size = (int) v.size();
        /*
        int size = (int) v.size();
        for (int i = 0; i < size; i++) {
            for (int j = size - 2; j >= i; j--) {
                if (v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
        
        for (int n: v) {
            cout << n << endl;
        }
        
        r = constructLink(v);
         */
        
        for (int i = 0; i < size; i++) {
            int min = i;
            for (int j = i + 1; j < size; j++) {
                if (v[j] < v[min]) {
                    min = j;
                }
            }
            
            cout << v[min] << endl;
            
            ListNode * node = new ListNode(v[min]);
            if (!r) {
                r = node;
                t = node;
            } else {
                t->next = node;
                t = node;
            }
        }
        
        return r;
    }
    
    
    void testSortList() {
        vector<int> t = {1, 2, 3, 4};
        ListNode * head = constructLink(t);
        ListNode * r = sortList(head);
        while (r) {
            cout << r->val << endl;
            r = r->next;
        }
        
    }
    
    // 191
    int hammingWeight(uint32_t n) {
        int num = 0;
        uint32_t mask = 0x0001;
        for (int i = 0; i < 32; i++, n = n >> 1) {
            int t = n & mask;
            if (t == 1) num++;
        }
        
        return num;
    }
    
    // 421
    int findMaximumXOR(vector<int> &nums) {
        TreeNode * root = new TreeNode(0);
        int size = (int) nums.size();
        TreeNode * curNode = root;
        int max = 0;
        TreeNode * maxNode = root;
        bool isMaxNode = false;
        int startBit = 31;
        for (int i = 0; i < size; i++) {
            int temp = nums[i];
            if (temp > max) {
                isMaxNode = true;
                max = temp;
            };
            for (int j = 31; j >= 0; j--) {
                int bit = temp & (1 << j);
                if (bit == 0) {
                    if (!curNode->right) {
                        curNode->right = new TreeNode(0);
                    }
                    curNode = curNode->right;
                } else {
                    if (!curNode->left) {
                        curNode->left = new TreeNode(1);
                    }
                    
                    if (isMaxNode) {
                        startBit = j;
                        isMaxNode = false;
                        maxNode = curNode;
                    }
                    curNode = curNode->left;
                }
            }
            curNode = root;
        }
        
        while (maxNode && (!maxNode->right || !maxNode->left) ) {
            startBit--;
            if (maxNode->left) {
                maxNode = maxNode->left;
            } else {
                maxNode = maxNode->right;
            }
        }
        
        if (!maxNode) {
            return 0;
        }
        
        int r = (1 << startBit) | TreeNodeXorMax(maxNode->left, maxNode->right, startBit - 1);
        
        return r;
    }
    
    int TreeNodeXorMax(TreeNode * left, TreeNode * right, int offset) {
        if (!left || !right) {
            return 0;
        }
        int max = 0;
        if (left->left && right->right) {
            int temp = (1 << offset) | TreeNodeXorMax(left->left, right->right, offset - 1);
            if (temp > max) max = temp;
        }
        
        if (left->right && right->left) {
            int temp  = (1 << offset) | TreeNodeXorMax(left->right, right->left, offset - 1);
            if (temp > max) max = temp;
        }
        
        if (max == 0) {
            int maxLeft = TreeNodeXorMax(left->left, right->left, offset - 1);
            int maxRight = TreeNodeXorMax(left->right, right->right, offset - 1);
            max = maxLeft > maxRight ? maxLeft : maxRight;
        }
        
        return max;
    }
    
    void testFindMaximumXOR() {
        vector<int> v = {4, 6, 7};
        cout << findMaximumXOR(v) << endl;
    }
    
    // 709
    string toLowerCase(string str) {
        int size = (int) str.size();
        for (int i = 0; i < size; i++) {
            char c = str[i];
            if (c >= 'A' && c <= 'Z') {
                str[i] = c + ('a' - 'A');
            }
        }
        
        return str;
    }
    
    // 219
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        int size = (int) nums.size();
        unordered_map<int, int> m;
        for (int i = 0; i < size; i++) {
            int t = nums[i];
            if (m.count(t) == 0) {
                m[t] = i;
            } else {
                if (i - m[t] <= k) {
                    return true;
                } else {
                    m[t] = i;
                }
            }
        }
        return false;
    }
    
    void testContainsNearbyDuplicate() {
        vector<int> v = {1,2,3,1};
        cout << containsNearbyDuplicate(v, 3) << endl;
    }
    
    // 692
    struct PointCmp {
        bool operator()(const pair<string, int>& lhs, const pair<string, int>& rhs) const {
            if (lhs.second == rhs.second) {
                return lhs.first < rhs.first;
            } else {
                return lhs.second > rhs.second;
            }
        }
    };
    
    vector<string> topKFrequent(vector<string> &words, int k) {
        vector<string> r;
        // default ordered by key
        map<string, int> m;
        for (string &t: words) {
            if (m.count(t) == 0) {
                m[t] = 1;
            } else {
                m[t]++;
            }
        }
        
        set<pair<string, int>, PointCmp> s;
        for (auto &p: m) {
            s.insert(p);
        }
        
        for (auto &p: s) {
            if (r.size() < k) {
                r.push_back(p.first);
            }
        }
        return r;
    }
    
    void testTopKFrequent() {
        vector<string> t = {"i", "love", "leetcode", "i", "love", "coding"};
        vector<string> r = topKFrequent(t, 2);
        for (string &s: r) {
            cout << s << endl;
        }
    }
    
    // 27
    int removeElement(vector<int> &nums, int val) {
        int size = (int) nums.size();
        for (int i = 0; i < size; i++) {
            if (nums[i] == val) {
                nums.erase(nums.begin() + i);
                size--;
                i--;
            }
        }
        
        return size;
    }
    
    // 621
    
    int leastInterval(vector<char> &tasks, int n) {
        vector<int> v(26, 0);
        int time = 0;
        for (char c: tasks) {
            cout << c << endl;
            v[c - 'A']++;
        }
        
        sort(v.begin(), v.end());
        
        while (v[25] > 0) {
            int i = 0;
            while (i <= n) {
                if (v[25] == 0) break;
                if (i < 26 && v[25 - i] >0) {
                    v[25 - i]--;
                }
                
                time++;
                i++;
            }
            sort(v.begin(), v.end());
        }
        return time;
    }
    
    
    void testLeastInterval() {
        vector<char> tasks = {'A','A','A','B','B','B'};
        cout << leastInterval(tasks, 2) << endl;
    }
    
    //973
    vector<vector<int>> kClosest(vector<vector<int>> &points, int K) {
        int size = (int) points.size();
        vector<double> dist;
        vector<vector<int> > r;
        for (vector<int> &p: points) {
            dist.push_back(kClosestHelper(p));
        }
//        QSort(dist, 0, size - 1);
        sort(dist.begin(), dist.end());
        int dk = dist[K - 1];
        
        for (vector<int> &p: points) {
            if (kClosestHelper(p) <= dk) {
                r.push_back(p);
            }
        }
        return r;
    }
    
    double kClosestHelper(vector<int> &point) {
        double d;
        d = pow(point[0], 2) + pow(point[1], 2);
        return d;
    }
    
    void QSort(vector<double> &dist, int low, int high) {
        vector<vector<int>> r;
        while (low < high) {
            int poviet = Partition(dist, low, high);
            QSort(dist, low, poviet - 1);
            low = poviet + 1;
        }
    }
    
    int Partition(vector<double> &dist, int low, int high) {
        /*
        int m = low + (high-low)/2;
        
        if (dist[low] > dist[high]) {
            double tp = dist[low];
            dist[low] = dist[high];
            dist[high] = tp;
        }
        
        if (dist[m] > dist[high]) {
            double tp = dist[m];
            dist[m] = dist[high];
            dist[high] = tp;
        }
        
        if (dist[m] > dist[low]) {
            double tp = dist[m];
            dist[m] = dist[low];
            dist[low] = tp;
        }
         */
        
        double d = dist[low];
        while (low < high) {
            
            while (low < high && dist[high] > d) {
                high--;
            }
            dist[low] = dist[high];
            
            while (low < high && dist[low] < d) {
                low++;
            }
            
            dist[high] = dist[low];
        }
        dist[low] = d;
        return low;
    }
    
    void testkClosest() {
        vector<vector<int> > v = {
            {3, 3},
            {5, -1},
            {-2, 4}
        };
        
        vector<vector<int> > r = kClosest(v, 2);
        for (vector<int> &t: r) {
            cout << t[0] << "-" << t[1] << endl;
        }
    }
    
    // 350
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
        vector<int> r;
        for (int num: nums1) {
            vector<int>::iterator t = find(nums2.begin(), nums2.end(), num);
            if (t != nums2.end()) {
                r.push_back(num);
                nums2.erase(t);
            }
        }
        return r;
    }
    
    void testIntersect() {
        vector<int> v1 = {1, 2, 2, 1};
        vector<int> v2 = {2, 2};
        vector<int> r = intersect(v1, v2);
        for (int t: r) {
            cout << t << endl;
        }
    }
    
    // 75
    void sortColors(vector<int> &nums) {
        int size = (int) nums.size();
        int t = size - 1, b = 0, i = 0;
        
        while (i <= t) {
            if (nums[i] < 1) {
                int tn = nums[i];
                nums[i] = nums[b];
                nums[b] = tn;
                b++;
                i++;
            } else if (nums[i] > 1) {
                int tn = nums[i];
                nums[i] = nums[t];
                nums[t] = tn;
                t--;
            } else {
                i++;
            }
        }
    }
    
    void testSortColor() {
        vector<int> t = {2,0,2,1,1,0};
        sortColors(t);
        for (int n: t) {
            cout << n << endl;
        }
    }
    
    // 977
    static bool absComp(int a, int b) {
        return abs(a) < abs(b);
    }
    
    vector<int> sortSquares(vector<int> &A) {
        vector<int> r;
        int size = (int) A.size();
        
        QSort3(A, 0, size - 1);
        
        for (int num: A) {
            r.push_back(num * num);
        }
        
        return r;
    }
    
    void QSort3(vector<int> &a, int low, int high) {
        while (low < high) {
            int poviet = QsortPoviet(a, low, high);
            QSort3(a, low, poviet - 1);
            low = poviet + 1;
        }
    }
    
    int QsortPoviet(vector<int> &a, int low, int high) {
        int t = a[low];
        while (low < high) {
            while (low < high && abs(a[high]) >= abs(t)) {
                high--;
            }
            a[low] = a[high];
            
            while (low < high && abs(a[low]) <= abs(t)) {
                low++;
            }
            
            a[high] = a[low];
        }
        
        a[low] = t;
        return low;
    }
    
    void testSortSquares() {
        vector<int> t = {-7,-3,2,3,11};
        vector<int> r = sortSquares(t);
        for (int num: r) {
            cout << num << endl;
        }
    }
    
    // 147
    ListNode * insertionSortList(ListNode * head) {
        /*
        vector<int> r;
        while (head) {
            r.push_back(head->val);
            head = head->next;
        }
        
        int size = (int) r.size();
        for (int i = 1; i < size; i++) {
            int t = r[i];
            int j;
            if (t < r[i - 1]) {
                // the item before bigger then t
                for (j = i - 1; r[j] > t && j >= 0; j--) {
                    // move back the current item
                    r[j + 1] = r[j];
                }
                // set the last moved item to the value of the first element of begin
                r[j + 1] = t;
            }
        }
        
        ListNode * rl = NULL, * temp = NULL;
        for (int num: r) {
            if (!rl) {
                rl = new ListNode(num);
                temp = rl;
            } else {
                temp->next = new ListNode(num);
                temp = temp->next;
            }
        }
        
        return rl;
         */
        
        /*
        
        if (!head) return NULL;
        
        ListNode * r = head;
        ListNode * cur = head->next;
        r->next = NULL;
        int prevVal = r->val;
        int i = 1;
        while (cur) {
            ListNode * next = cur->next;
//            cur->next = NULL;
            if (cur->val < prevVal) {
                // record the node before current compare
                ListNode * temp = r;
                ListNode * before = NULL;
                int j = 0;
                while (cur->val > temp->val && j < 1) {
                    before = temp;
                    temp = temp->next;
                    j++;
                }
                cur->next = temp;
                if (before) {
                    before->next = cur;
                } else {
                    r = cur;
                }
            } else {
                ListNode * temp = r;
                while (temp->next) {
                    temp = temp->next;
                }
                
                prevVal = cur->val;
                cur->next = NULL;
                temp->next = cur;
            }
            i++;
            cur = next;
        }
        return r;
         */
        
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        ListNode *pre = dummy, *cur = head;
        while (cur) {
            if ((cur -> next) && (cur -> next -> val < cur -> val)) {
                while ((pre -> next) && (pre -> next -> val < cur -> next -> val)) {
                    pre = pre -> next;
                }
                ListNode* temp = pre -> next;
                pre -> next = cur -> next;
                cur -> next = cur -> next -> next;
                pre -> next -> next = temp;
                pre = dummy;
            }
            else {
                cur = cur -> next;
            }
        }
        return dummy -> next;
    }
    
    void testInsertionSortList() {
        vector<int> v = {4, 2, 1, 3};
        ListNode * list = constructLink(v);
        ListNode * tt = insertionSortList(list);
        while(tt) {
            cout << tt->val << endl;
            tt = tt->next;
        }
        
    }
    
    // 179
    string largestNumber(vector<int> &nums) {
        vector<string> t;
        string r;
        for (int num: nums) {
            stringstream ss;
            ss << num;
            t.push_back(ss.str());
        }
        
        sort(t.begin(), t.end(), LargestHelper);
        
        stringstream rs;
        
        
        for (string& s: t) {
            rs << s;
        }
        
        r = rs.str();
        
        if (r[0] == '0') {
            r = "0";
        }
        
        return r;
        
    }
    
    static bool LargestHelper(string &s1, string &s2) {
        string t1;
        string t2;
        
        t1.append(s1);
        t1.append(s2);
        t2.append(s2);
        t2.append(s1);
        
        return t1.compare(t2) > 0;
    }
    
    void testLargestNumber() {
        vector<int> v = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//        vector<int> v = {3,30,34,5,9};
//        vector<int> v = {121, 12};
        string s = largestNumber(v);
        cout << s << endl;
    }
    
    // 766
    bool isToeplitzMatrix(vector<vector<int> > &matrix) {
        int m = (int) matrix.size();
        int n = (int) matrix[0].size();
        
        for (int i = 0; i < n - 1; i++) {
            int temp = matrix[0][i];
            for (int j = 1; j < m; j++) {
                if (i + j < n && temp != matrix[j][i + j]) {
                    return false;
                }
            }
        }
        
        for (int i = 1; i < m - 1; i++) {
            int temp = matrix[i][0];
            for (int j = i + 1; j < m; j++) {
                if (j - i < n && temp != matrix[j][j - i]) {
                    return false;
                }
            }
        }
        
        
        
        return true;
    }
    
    void testIsToeplitzMatrix() {
        vector<vector<int> > t = {
            {1, 2},
            {2, 2}
        };
        vector<vector<int> > t2 = {
            {1, 2, 3, 4},
            {5, 1, 2, 3},
            {9, 5, 1, 2},
        };
        cout << isToeplitzMatrix(t2) << endl;
    }
    
    // 611
    int triangleNumber(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int size = (int) nums.size();
        int all = 0;
        for (int x = 0; x < size; x++) {
            int b1 = nums[x];
            for (int y = x + 1; y < size; y++) {
                int b2 = nums[y];
                int temp = b1 + b2;
                /*
                for (int z = y + 1; z < size; z++) {
                    int b3 = nums[z];
                    if (b1 + b2 <= b3) break;
                    if (b1 + b3 <= b2) continue;
                    if (b2 + b3 <= b1) continue;
                    all++;
                }
                 */
                int low = y + 1;
                int high = size - 1;
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (nums[mid] >= temp) {
                        high = mid - 1;
                    } else {
                        low = mid + 1;
                    }
                }
                all += low - y - 1;
            }
        }
        return all;
    }
    
    void testTriangleNumber() {
        vector<int> t = {2,2,3,4};
        cout << triangleNumber(t) << endl;
    }
    
    // 205
    bool isIsomorphic(string s, string t) {
        char charArrS[256] = { 0 };
        char charArrT[256] = { 0 };
        int i = 0;
        while (s[i] !=0)
        {
            if (charArrS[s[i]] == 0 && charArrT[t[i]] == 0)
            {
                charArrS[s[i]] = t[i];
                charArrT[t[i]] = s[i];
            }
            else
                if (charArrS[s[i]] != t[i] || charArrT[t[i]] != s[i])
                    return false;
            i++;
        }
        
        return true;
    }
    
    void testIsIsomorphic() {
        string a = "egg";
        string b = "add";
        cout << isIsomorphic(a, b) << endl;
    }
    
    // 767
    
    map<char, int> rem;
    string reorganizeString(string S) {
        int size = (int) S.size();
        int max = 1;
        for (char c: S) {
            if (rem.count(c)) {
                rem[c]++;
                if (rem[c] > max) {
                    max = rem[c];
                }
            } else {
                rem[c] = 1;
            }
        }
        
        cout << max << endl;
        qSort5(S, 0, size - 1);
        int t = 1;
        string rs(size, '0');
        
        cout << S << endl;
        
        if (size - max < max - 1) {
            return "";
        } else {
            for (int i = 0; i < size; i++) {
                if (t >= size) {
                    t = 0;
                }
                rs[t] = S[i];
                t += 2;
            }
        }
        return rs;
    }
    
    void qSort5(string &s, int low, int high) {
        while (low < high) {
            int povient = qSort5Povient(s, low, high);
            qSort5(s, low, povient - 1);
            low = povient + 1;
        }
    }
    
    int qSort5Povient(string &s, int low, int high) {
        char temp = s[low];
        while (low < high) {
            while (low < high && (rem[s[high]] > rem[temp] || s[high] >= temp)) {
                high--;
            }
            
            s[low] = s[high];
            
            while (low < high && (rem[s[low]] <= rem[temp] || s[low] <= temp)) {
                low++;
            }
            
            s[high] = s[low];
        }
        
        s[low] = temp;
        return low;
    }
    
    
    void testReorganizeString() {
        string a = "abbabbaaab";
        cout << reorganizeString(a) << endl;
    }
    
    // 160
    ListNode * getIntersectionNode(ListNode * headA, ListNode * headB) {
        vector<ListNode *> v1;
        vector<ListNode *> v2;
        ListNode * r = nullptr;
        
        while (headA) {
            v1.push_back(headA);
            headA = headA->next;
        }
        
        while (headB) {
            v2.push_back(headB);
            headB = headB->next;
        }
        
        int i = (int) v1.size() - 1, j = (int) v2.size() - 1;
        
        
        
        for (; i >= 0 && j >= 0; i--, j--) {
            if (v1[i] != v2[j]) break;
        }
        
        if (i + 1 < v1.size()) {
            r = v1[i + 1];
        }
        
        
        return r;
    }
    
    // 817
    int numComponents(ListNode * head, vector<int> &G) {
        /*
        int r = 0;
        bool isContinue = false;
        while (head) {
            vector<int>::iterator f = find(G.begin(), G.end(), head->val);
            if (f != G.end()) {
                if (!isContinue) {
                    isContinue = true;
                    r += 1;
                }
                G.erase(f);
            } else {
                isContinue = false;
            }
            head = head->next;
        }
        
        return r;
         */
        set<int> ss(G.begin(), G.end());
        int r = 0;
        bool isContinue = false;
        /*
        for (int t: G) {
            ss.insert(t);
        }
         */
        
        while (head) {
            if (ss.count(head->val)) {
                if (!isContinue) {
                    isContinue = true;
                    r++;
                }
            } else {
                isContinue = false;
            }
            head = head->next;
        }
        
        return r;
    }
    
    // 524
    string findLongestWord(string s, vector<string> &d) {
        sort(d.begin(), d.end(), [](string a, string b){
            if (a.size() != b.size()) {
                return a.size() > b.size();
            } else {
                return a.compare(b) < 0;
            }
        });
        
        
        for (string str: d) {
            bool flag = true;
            unsigned long pos = -1;
            for (char c: str) {
                pos = s.find(c, pos + 1);
                if (pos == string::npos) {
                    flag = false;
                    break;
                }
            }
            
            if (flag) return str;
        }
        
        
        
        return "";
    }
    
    void testFindLongestWord() {
        vector<string> d = {"ale","apple","monkey","plea"};
        string s = "abpcplea";
        
        cout << findLongestWord(s, d) << endl;
    }
    
    // 66
    vector<int> plusOne(vector<int>& digits) {
        int size = (int) digits.size();
        bool isCarrie = false;
        for (int i = size - 1; i >= 0; i--) {
            digits[i] += 1;
            if (digits[i] < 10) {
                isCarrie = false;
                break;
            } else {
                isCarrie = true;
                digits[i] -= 10;
            }
        }
        
        if (isCarrie) {
            digits.insert(digits.begin(), 1);
        }
        
        return digits;
    }
    
    void testPlusOne() {
        vector<int> v = {9};
        vector<int> t = plusOne(v);
        for(int num: t) {
            cout << num << endl;
        }
    }
    
    // 19
    ListNode * removeNthFromEnd(ListNode * head, int n) {
        /*
        ListNode * temp = head;
        vector<ListNode *> v;
        while (temp) {
            v.push_back(temp);
            temp = temp->next;
        }
        
        int size = (int) v.size();
        
        if (size == 1) {
            return NULL;
        }
        
        int index = size - n;
        if (index == size - 1) {
            v[index - 1]->next = NULL;
        } else if (index == 0) {
            head = head->next;
        } else {
            v[index - 1]->next = v[index + 1];
        }
        
        return head;
         */
        ListNode ** t1 = &head, *t2 = head;
        for (int i = 1; i < n; i++) {
            t2 = t2->next;
        }
        
        while (t2->next != NULL) {
            t1 = &((*t1)->next);
            t2 = t2->next;
        }
        
        *t1 = (*t1) -> next;
        
        return head;
    }
    
    // 645
    vector<int> findErrorNums(vector<int> &nums) {
        /*
        vector<int> r;
        set<int> s;
        int dup = 0, sum = 0, o_sum, lost;
        int size = (int) nums.size();
        bool isFindDup = false;
        for (int num: nums) {
            if (!isFindDup) {
                if (s.count(num) == 1) {
                    dup = num;
                    isFindDup = true;
                } else {
                    s.insert(num);
                }
            }
            sum += num;
        }
        
        o_sum = (1 + size) * size/2;
        lost = dup + (o_sum - sum);
        
        r.push_back(dup);
        r.push_back(lost);
        return r;
         */
        vector<int> r;
        sort(nums.begin(), nums.end());
        int size = (int) nums.size();
        int dup = 0;
        for (int i = 0; i < size; i++) {
            /*
            if (i + 1 != nums[i]) {
                r.push_back(nums[i]);
                r.push_back(i + 1);
                break;
            }
             */
            dup ^= (i + 1) ^ nums[i];
            
        }
        
        cout << dup << endl;
        return r;
    }
    
    void testFindErrorNums() {
        vector<int> t = {1, 2, 2, 4};
        vector<int> r = findErrorNums(t);
        
        for (int num: r) {
            cout << num << endl;
        }
    }
    
    // 451
    string frequencySort(string s) {
        string str;
        unordered_map<char, int> frequencySortm;;
        for (char c : s) {
            if (frequencySortm[c]) {
                frequencySortm[c]++;
            } else {
                frequencySortm[c] = 1;
            }
        }
        
        sort(s.begin(), s.end(), [&frequencySortm](char lhs, char rhs) {
            if (frequencySortm[lhs] == frequencySortm[rhs]) {
                return lhs > rhs;
            } else {
                return frequencySortm[lhs] > frequencySortm[rhs];
            }
        });
        return s;
    }
    
    void testFrequencySort() {
        string s = "loveleetcode";
        cout << frequencySort(s) << endl;
    }
    
    // 344
    void reverseString(vector<char>& s) {
        int size = (int) s.size();
        for (int i = 0; i < size/2; i++) {
            char temp = s[i];
            s[i] = s[size - 1 - i];
            s[size - 1 - i] = temp;
        }
    }
    
    void testReverseString() {
        vector<char> s = {'h','e','l','l','o'};
        reverseString(s);
        for (char c: s) {
            cout << c << endl;
        }
    }
    
    // 151
    void reverseWords(string& s) {
        vector<string> v;
        string temp;
        
        int size = (int) s.size();
        for (int i = size - 1; i >= 0; i--) {
            char c = s[i];
            if (c == ' ') {
                if (!temp.empty()) {
                    v.push_back(temp);
                    temp.clear();
                }
            } else {
                temp.insert(0, 1, c);
            }
        }
        
        if (!temp.empty()) {
            v.push_back(temp);
            temp.clear();
        }
        
        
        s.clear();
        for (string &tt: v) {
            if (!s.empty()) {
                s.push_back(' ');
            }
            
            s.append(tt);
        }
        
    }
    
    void testReverseWords() {
        string s = "the sky is blue";
        reverseWords(s);
        cout << s << endl;
    }
    
    // 209
    int minSubArrayLen(int s, vector<int>& nums) {
        /*
        int size = (int) nums.size();
        int r = 0;
        for (int i = 0; i < size; i++) {
            int sum = 0;
            int j = i;
            while (sum < s && j < size) {
                sum += nums[j];
                j++;
            }
            
            if (sum >= s) {
                if (r == 0) {
                    r = j - i;
                } else if (r > j - i) {
                    r = j - i;
                }
            }
            
        }
        return r == size ? 0 : r;
         */
        int size = (int) nums.size();
        if (size == 0) return 0;
        int r = INT_MAX;
        vector<int> sums(size + 1, 0);
        for (int i = 1; i <= size; i++) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        
        for (int i = 1; i <= size; i++) {
            int to_find = s + sums[i - 1];
            auto bound = lower_bound(sums.begin(), sums.end(), to_find);
            if (bound != sums.end()) {
                int temp = static_cast<int> (bound - (sums.begin() + i - 1));
                if (temp < r) {
                    r = temp;
                }
            }
        }
        

        
        return r == INT_MAX ? 0 : r;
    }
    
    void testMinSubArrayLen() {
        vector<int> arr = {2,3,1,2,4,3};
        cout << minSubArrayLen(7, arr) << endl;
    }
    
    // 965
    bool isUnivalueTree(TreeNode * root) {
        if (!root) return true;
        int v = root->val;
        return isUnivalueTreeHelper(root->left, v) && isUnivalueTreeHelper(root->right, v);
    }
    
    bool isUnivalueTreeHelper(TreeNode * node, int v) {
        if (!node) return true;
        if (node->val != v) return false;
        return isUnivalueTreeHelper(node->left, v) && isUnivalueTreeHelper(node->right, v);
    }
    
    // 230
    vector<int> kthSarr;
    int kthSmallest(TreeNode * root, int k) {
        kthSmallestHelper(root);
        return kthSarr[k - 1];
    }
    
    void kthSmallestHelper(TreeNode * node) {
        if (!node) return;
        kthSmallestHelper(node->left);
        kthSarr.push_back(node->val);
        kthSmallestHelper(node->right);
    }
    
    // 476
    int findComplement(int num) {
        int r = 0;
        int mask = 0x80000000;
        int temp = num;
        int tt = 0;
        int i;
        for (i = 0; i < 32; i++) {
            int t = temp & mask;
            if (t == mask) {
                cout << i << endl;
                break;
            }
            
            temp = temp << 1;
        }
        
        tt = i < 32 ? i : 31;
        
        
        
        
        
        for (int i = 0; i < 32 - tt; i++) {
            int t = ~(num & 1) & 1;
            t = t << i;
            r = r | t;
            num = num >> 1;
        }
        return r;
    }
    
    void testFindComplement() {
        int t = 0;
        cout << findComplement(t) << endl;
    }
    
    //397
    int integerReplacement(int n) {
        return 1;
    }
    
    
    void testIntegerReplacement() {
        cout << integerReplacement(8) << endl;
    }
    
    // 114
    TreeNode * prev = NULL;
    void flatten(TreeNode * root) {
        if (!root) return;
        flatten(root->right);
        flatten(root->left);
        root->right = prev;
        root->left = NULL;
        prev = root;
    }
    
    // 787
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int K) {
        int max = 10000 * n + 1;
        vector<bool> finalWay(n, false);
        vector<int> d(n, max);
        vector<vector<int>> distance(n, d);
        vector<int> tod(n, max);
        vector<int> path(n, src);
        int cheapest = max;
        
        int size = (int) flights.size();
        
        for (int i = 0; i < size; i++) {
            vector<int> &t = flights[i];
            distance[t[0]][t[1]] = t[2];
        }
        
        for (int i = 0; i < n; i++) {
            tod[i] = distance[src][i];
        }
        
        tod[src] = 0;
        finalWay[src] = true;
        
        if (tod[dst] < cheapest) {
            cheapest = tod[dst];
        }
        
        for (int i = 1; i < n; i++) {
            int min = max;
            int k = 0, w;
            for (w = 0; w < n; w++) {
                if (!finalWay[w] && tod[w] < min) {
                    k = w;
                    min = tod[w];
                }
            }
            
            finalWay[k] = true;
            
            if (min < max) {
                for (w = 0; w < n; w++) {
                    if (!finalWay[w] && (min + distance[k][w]) < tod[w]) {
                        if (w == dst) {
                            int t = 0;
                            int s = k;
                            while (s != src && t <= K) {
                                s = path[s];
                                t++;
                            }
                            if (s != src || t > K) continue;
                        }
                        tod[w] = min + distance[k][w];
                        path[w] = k;
                    }
                }
            }
        }
        
        cheapest = tod[dst];
        
        return cheapest < max ? cheapest : -1;
    }
    
    void testFindCheapestPrice() {
        vector<vector<int> > flights = {
            {0, 1, 1},
            {0, 2, 5},
            {1, 2, 1},
            {2, 3, 1}
        };
        cout << findCheapestPrice(4, flights, 0, 3, 1) << endl;
    }
    
    // 783
    vector<int> arr783;
    int minDiffInBST(TreeNode * root) {
        if (!root) return 0;
        int diff;
        minDiffInBSTHelper(root);
        int size = (int) arr783.size();
        diff = arr783[size - 1] - arr783[0];
        for (int i = 1; i < size; i++) {
            int d = arr783[i] - arr783[i - 1];
            diff = diff > d ? d : diff;
        }
        return diff;
    }
    
    void minDiffInBSTHelper(TreeNode * node) {
        if (!node) return;
        minDiffInBST(node->left);
        arr783.push_back(node->val);
        minDiffInBST(node->right);
    }
    
    
    // 561
    int arrayPairSum(vector<int> &nums) {
        vector<int> hashtable(20001,0);
        for(size_t i=0;i<nums.size();i++)
        {
            hashtable[nums[i]+10000]++;
        }
        int ret=0;
        int flag=0;
        for(size_t i=0;i<20001;){
            if((hashtable[i]>0)&&(flag==0)){
                ret=ret+i-10000;
                flag=1;
                hashtable[i]--;
            }else if((hashtable[i]>0)&&(flag==1)){
                hashtable[i]--;
                flag=0;
            }else i++;
        }
        return ret;
    }
    
    void testArrayPairSum() {
        vector<int> t = {1, 4, 3, 2};
        cout << arrayPairSum(t) << endl;
    }
    
    // 238
    vector<int> productExceptSelf(vector<int> &nums) {
        int n = (int) nums.size();
        int fromBegin=1;
        int fromLast=1;
        vector<int> res(n,1);
        
        for(int i=0;i<n;i++){
            res[i]*=fromBegin;
            fromBegin*=nums[i];
            res[n-1-i]*=fromLast;
            fromLast*=nums[n-1-i];
        }
        return res;
    }
    
    void testProductExceptSelf() {
        vector<int> t = {1, 2, 3, 4};
        vector<int> r = productExceptSelf(t);
        for (int n: r) {
            cout << n << endl;
        }
    }
    
    // 438
    vector<int> findAnagrams(string s, string p) {
        int size = (int) s.size();
        int ssize = (int) p.size();
        vector<int> r;
        if (ssize > size) return r;
        vector<int> pm(26, 0);
        vector<int> sm(26, 0);
        
        for (int i = 0; i < ssize; i++) {
            ++pm[p[i] - 'a'];
            ++sm[s[i] - 'a'];
        }
        
        if (pm == sm) {
            r.push_back(0);
        }
        
        for (int i = ssize; i < size; i++) {
            ++sm[s[i] - 'a'];
            --sm[s[i - ssize] - 'a'];
            if (sm == pm) {
                r.push_back(i - ssize + 1);
            }
        }
        
        return r;
    }
    
    void testFindAnagrams() {
        string s = "aa";
        string p = "bb";
        vector<int> a1 = {1, 2, 3};
        vector<int> a2 = {1, 3, 2};
        if (a1 == a2) {
            cout << "ded" << endl;
        }
        vector<int> r = findAnagrams(s, p);
        for (int n: r) {
            cout << n << endl;
        }
    }
    
    // 560
    int subarraySum(vector<int> &nums, int k) {
        int start;
        int size = (int) nums.size();
        int r = 0;
        unordered_map<int, int> um;
        um[0] = 1;
        int sum = 0;
        for (start = 0; start < size; start++) {
            sum += nums[start];
            if (um[sum - k]) {
                r += um[sum - k];
            }
            if (!um[sum]) {
                um[sum] = 1;
            } else {
                um[sum] += 1;
            }
        }
        return r;
    }
    
    void testSubarraySum() {
        vector<int> nums = {1, 1, 1};
        int k = 2;
        cout << subarraySum(nums, k) << endl;
    }
    
    // 2
    ListNode * addTwoNumbers(ListNode * l1, ListNode * l2) {
        int carry = 0;
        ListNode * r = nullptr;
        ListNode * temp = nullptr;
        while (l1 || l2) {
            int sum = carry;
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            
            if (temp == nullptr) {
                temp = new ListNode(sum);
                r = temp;
            } else {
                temp -> next = new ListNode(sum);
                temp = temp->next;
            }
        }
        
        if (carry == 1) {
            temp->next = new ListNode(carry);
        }
        return r;
    }
    
    // 445
    ListNode * addTwoNumbers2(ListNode * l1, ListNode * l2) {
        ListNode * r = nullptr;
        ListNode * temp = nullptr;
        
        vector<int> sl1;
        vector<int> sl2;
        vector<int> sumarr;
        
        int carry = 0;
        
        while (l1 || l2) {
            if (l1) {
                sl1.push_back(l1->val);
                l1 = l1 -> next;
            }
            
            if (l2) {
                sl2.push_back(l2->val);
                l2 = l2 -> next;
            }
        }
        while (!sl1.empty() || !sl2.empty()) {
            int sum = carry;
            if (!sl1.empty()) {
                sum += sl1.back();
                sl1.pop_back();
            }
            
            if (!sl2.empty()) {
                sum += sl2.back();
                sl2.pop_back();
            }
            
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
            
            sumarr.insert(sumarr.begin(), sum);
        }
        
        if (carry == 1) sumarr.insert(sumarr.begin(), 1);
        
        for (int n: sumarr) {
            if (!temp) {
                temp = new ListNode(n);
                r = temp;
            } else {
                temp -> next = new ListNode(n);
                temp = temp->next;
            }
        }
        return r;
    }
    
    bool checkRecord(string s) {
        int as = 0, ls = 0;
        int size = (int) s.size();
        int before = 0;
        for (int i = 0; i < size; i++) {
            char c = s[i];
            if (c == 'A') {
                as++;
            } else if (c == 'L') {
                if (ls == 0) {
                    ls++;
                } else {
                    if ((i - before) == 1) {
                        ls++;
                    } else {
                        ls = 1;
                    }
                }
                before = i;
            }
            
            if (as > 1 || ls > 2) break;
        }
        
        if (as <= 1 && ls <= 2) return true;
        return false;
    }
    
    void testCheckRecord() {
        string s = "LALL";
        cout << checkRecord(s) << endl;
    }
    
    // 916
    vector<string> wordSubsets(vector<string> &A, vector<string> &B) {
        vector<string> r;
        int la = (int) A.size();
        int lb = (int) B.size();
        vector<int> m(26, 0);
        int allnum = 0;
        for (int j = 0; j < lb; j++) {
            vector<int> temp(26, 0);
            string b = B[j];
            for (char c: b) {
                temp[c - 'a'] += 1;
                if (temp[c - 'a'] > m[c - 'a']) m[c - 'a'] = temp[c - 'a'];
            }
        }
        
        for (int j = 0; j < 26; j++) {
            if (m[j] > 0) {
                allnum++;
            }
        }
        
        
        for (int i = 0; i < la; i++) {
            vector<int> temp(26, 0);
            string a = A[i];
            int bigger = 0;
            for (char c: a) {
                int index = c - 'a';
                if (temp[index] >= 0) {
                    temp[index] += 1;
                    if (m[index] && temp[index] >= m[index]) {
                        bigger += 1;
                        temp[index] = -1;
                    }
                }
            }
            
            if (bigger == allnum) r.push_back(a);
        }
        return r;
    }
    
    void testWordSubsets() {
        vector<string> a = {"amazon","apple","facebook","google","leetcode"};
        vector<string> b = {"e","oo"};
        vector<string> c = wordSubsets(a, b);
        for (string s: c) {
            cout << s << endl;
        }
    }
    
    int peakIndexInMountainArray(vector<int>& A) {
//        int size = (int) A.size();
        /*
        int r = INT_MIN;
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (A[i] > r) {
                r = A[i];
                j = i;
            }
        }
        return j;
         */
        int size = (int) A.size();
        int low = 0;
        int high = size - 1;
        int r = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int t = A[mid];
            if (t > A[mid - 1] && t > A[mid + 1]) {
                r = mid;
                break;
            } else if (t < A[mid + 1]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return r;
    }
    
    void testPeakIndexInMountainArray() {
        vector<int> arr = {0, 2, 1, 0};
        cout << peakIndexInMountainArray(arr) << endl;
    }
    
    bool searchMartix(vector<vector<int> >& matrix, int target) {
        int m = (int) matrix.size();
        if (m == 0) return false;
        int n = (int) matrix[0].size();
        int high = m * n - 1;
        int low = 0;
        bool r = false;
        
        while (low <= high) {
            int mid = low + (high-low)/2;
            int row = mid / n;
            int col = mid % n;
            int temp = matrix[row][col];
            if (temp == target) {
                r = true;
                break;
            } else if (temp > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return r;
    }
    
    void testSearchMartix() {
        vector<vector<int> > martix = {
            {1, 3, 5, 7},
            {10, 11, 16, 20},
            {23, 30, 34, 50}
        };
        
        cout << searchMartix(martix, 3) << endl;
    }
    
    // 682
    int calPoints(vector<string>& ops) {
        int size = (int) ops.size();
        stack<int> s;
        int sum = 0;
        for (int i = 0; i < size; i++) {
            string str = ops[i];
            if (str == "+") {
                stack<int> fs = s;
                int ts = (int) (fs.size() > 2 ? 2 : fs.size());
                int temp = 0;
                for (int i = 0; i < ts; i++) {
                    temp += fs.top();
                    fs.pop();
                }
                sum += temp;
                s.push(temp);
            } else if (str == "D") {
                int temp = s.top() * 2;
                sum += temp;
                s.push(temp);
            } else if (str == "C") {
                int temp = s.top();
                sum -= temp;
                s.pop();
            } else {
                int tt = stoi(str);
                sum += tt;
                s.push(tt);
            }
        }
        return sum;
    }
    
    void testCalPoints() {
        vector<string> t = {"5","-2","4","C","D","9","+","+"};
        cout << calPoints(t) << endl;
    }
    
    // 856
    int scoreOfParentheses(string S) {
        int sum = 0, bal = 0;
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == '(') {
                bal++;
            } else {
                bal--;
                if (S[i - 1] == '(') {
                    sum += 1 << bal;
                }
            }
        }
        
        return sum;
    }
    
    void testScoreOfParentheses() {
        string t = "()()()()((()(((()))((())(((((()))()()())))))))";
        cout << scoreOfParentheses(t) << endl;
    }
    
    //389
    char findTheDifference(string s, string t) {
        int size = (int) s.size();
        char r = 0;
        int i;
        for (i = 0; i < size; i++) {
            r = r^s[i]^t[i];
        }
        
        r = r ^ t[i];
        
        return r;
    }
    
    void testFindTheDifference() {
        string s = "abcd";
        string t = "abcde";
        cout << findTheDifference(s, t) << endl;
    }
    
    // 137
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (int i = 0; i < nums.size(); i++) {
            ones = (ones ^ nums[i]) & ~twos;
            twos = (twos ^ nums[i]) & ~ones;
        }
        
        return ones;
    }
    
    void testSingelNumber() {
        vector<int> nums = {2, 2, 3, 2};
        cout << singleNumber(nums) << endl;
    }
    
    //
    int findSecondMinimumValue(TreeNode * root) {
        int r = findSecondMinimumValueHelper(root);
        if (r == root->val) {
            return -1;
        }
        
        return r;
    }
    
    int findSecondMinimumValueHelper(TreeNode * root) {
        if (!root) return -1;
        if (!root->left) return root->val;
        int l = root->left->val;
        int r = root->right->val;
        if (l > r) {
            if (r != root->val) {
                return r;
            }
            int tr = findSecondMinimumValueHelper(root->right);
            if (tr == root->val) return l;
            return tr > l ? l : tr;
        } else if (r > l) {
            if (l != root->val) {
                return l;
            }
            int tl = findSecondMinimumValueHelper(root->left);
            if (tl == root->val) return r;
            return tl > r ? r : tl;
        } else if (r == l && r != root->val) {
            return l;
        } else {
            int tl = findSecondMinimumValueHelper(root->left);
            int tr = findSecondMinimumValueHelper(root->right);
            if (tl == root->val && tr == root->val) {
                return root->val;
            } else if (tl == root->val) {
                return tr;
            } else if (tr == root->val) {
                return tl;
            } else {
                return tl > tr ? tr : tl;
            }
        }
    }
    
    // 144
    vector<int> pot;
    vector<int> preorderTraversal(TreeNode * root) {
        preorderTraversalHelper(root);
        return pot;
    }
    
    void preorderTraversalHelper(TreeNode * node) {
        if (!node) return;
        pot.push_back(node->val);
        preorderTraversalHelper(node->left);
        preorderTraversalHelper(node->right);
    }
    
    // 563
    int sum563 = 0;
    int findTilt(TreeNode * root) {
        findTiltHelper(root);
        return sum563;
    }
    
    int findTiltHelper(TreeNode * node) {
        if (!node) return 0;
        int ls = findTiltHelper(node->left);
        int rs = findTiltHelper(node->right);
        sum563 += abs(ls - rs);
        return ls + rs + node->val;
    }
    
    // 988
    string smallestFromLeaf(TreeNode * root) {
        return smallestFromLeafHelper(root);
    }
    
    string smallestFromLeafHelper(TreeNode * node) {
        if (!node) return "";
        char c = 'a' + node->val;
        if (!node->left && !node->right) {
            string s;
            s.push_back(c);
            return s;
        }
        
        string lf = smallestFromLeafHelper(node->left);
        string lr = smallestFromLeafHelper(node->right);
        
        if (lf.empty()) {
            lr.push_back(c);
            return lr;
        }
        
        if (lr.empty()) {
            lf.push_back(c);
            return lf;
        }
        
        if (lf.compare(lr) < 0) {
            lf.push_back(c);
            return lf;
        } else {
            lr.push_back(c);
            return lr;
        }
    }
    
    //26
    int removeDuplicates(vector<int> &nums) {
        /*
        int size = (int) nums.size();
        if (size == 0) return 0;
        int temp = nums[0];
        vector<int>::iterator it = nums.begin();
        int start = 0;
        int len = 0;
        for (int i = 1; i < size; i++) {
            if (nums[i] == temp) {
                if (start == 0) start = i;
                len += 1;
            } else {
                temp = nums[i];
                nums.erase(it + start, it + len + start);
                i -= len;
                size -= len;
                start = 0;
                len = 0;
            }
        }
        
        if (start) {
            nums.erase(it + start, it + start + len);
            size -= len;
        }
        return size;
         */
        
        int count = 0;
        int size = (int) nums.size();
        for(int i = 1; i < size; i++){
            if(nums[i] == nums[i-1]) count++;
            else nums[i-count] = nums[i];
        }
        
        return size-count;
    }
    
    void testRemoveDuplicates() {
        vector<int> t = {1, 1, 2};
        cout << removeDuplicates(t) << endl;
    }
    
    // 64
    int minPathSum(vector<vector<int> > &grid) {
        int m, n, all, v, w;
        m = (int) grid.size();
        if (!m) return 0;
        n = (int) grid[0].size();
        if (n == 1 && m == 1) return grid[0][0];
        all = m * n;
        vector<int> dis(all, -1);
        vector<bool> isFinal(all, 0);
        vector<int> path(all, 0);
        
        dis[1] = grid[0][1];
        dis[n] = grid[1][0];
        
        dis[0] = 0;
        isFinal[0] = true;
        
        for (v = 1; v < all; v++) {
            int min = INT_MAX;
            int k = 0;
            for (w = 0; w < all; w++) {
                if (!isFinal[w] && dis[w] > 0 && dis[w] < min) {
                    k = w;
                    min = dis[w];
                }
            }
            
            isFinal[k] = 1;
            
            for (w = 0; w < all; w++) {
                if (!isFinal[w]) {
                    int px = k % n;
                    int py = k / n;
                    
                    int wx = w % n;
                    int wy = w / n;
                    
                    int disFromk;
                    
                    if (px != wx && py != wy) {
                        continue;
                    } else {
                        if (px == wx && abs(py - wy) > 1) continue;
                        if (py == wy && abs(px - wx) > 1) continue;
                        disFromk = grid[wy][wx];
                    }
                    
                    if (dis[w] < 0 || (min + disFromk) < dis[w]) {
                        dis[w] = min + disFromk;
                        path[w] = k;
                    }
                }
            }
        }
        
        
        
        
        
        

        
        
        return dis[all - 1] + grid[0][0];
    }
    
    void testMinPathSum() {
        vector<vector<int> > t = {
            {9, 1, 4, 8},
        };
        
        cout << minPathSum(t) << endl;
    }
    
    // 884
    vector<string> uncommonFromSentences(string A, string B) {
        vector<string> r;
        int start = 0, len = 0;
        int al = (int) A.size();
        int bl = (int) B.size();
        unordered_map<string, int> um;
        for (int i = 0; i < al; i++) {
            if (A[i] == ' ' || i == al - 1) {
                if (i == al - 1) len += 1;
                string temp = A.substr(start, len);
                if (!um[temp]) {
                    um[temp] = 1;
                } else {
                    um[temp] += 1;
                }
                start = i + 1;
                len = 0;
            } else {
                len += 1;
            }
        }
        
        
        start = 0;
        
        for (int i = 0; i < bl; i++) {
            if (B[i] == ' ' || i == bl - 1) {
                if (i == bl - 1) len += 1;
                string temp = B.substr(start, len);
                if (!um[temp]) {
                    um[temp] = 1;
                } else {
                    um[temp] += 1;
                }
                start = i + 1;
                len = 0;
            } else {
                len += 1;
            }
        }
        
        for (pair<const string, int> &p : um) {
            if (p.second == 1) {
                r.push_back(p.first);
            }
        }
        
        return r;
    }
    
    void testUncommonFromSentences() {
        string a = "this apple is sweet";
        string b = "this apple is sour";
        vector<string> s = uncommonFromSentences(a, b);
        for (string str: s) {
            cout << str << endl;
        }
    }
    
    TreeNode * sortedListToBST(ListNode * head) {
        if (!head) return NULL;
        ListNode * mid = findMiddleElement(head);
        
        TreeNode * r = new TreeNode(mid->val);
        if (mid == head) {
            return r;
        }
        
        r->left = sortedListToBST(head);
        r->right = sortedListToBST(mid->next);
        return r;
    }
    
    ListNode * findMiddleElement(ListNode * head) {
        ListNode * slowPtr = head;
        ListNode * fastPtr = head;
        ListNode * prevPtr = NULL;
        
        while (fastPtr != NULL && fastPtr != NULL) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }
        
        if (prevPtr != NULL) {
            prevPtr->next = NULL;
        }
        
        return slowPtr;
    }
    
    // 557
    string reverseWords3(string s) {
        int size = (int) s.size();
        for (int i = 0; i < size; i++) {
            if (s[i] != ' ') {
                int j = i + 1;
                while (s[j] != ' ' && j < size) j++;
                reverse(s.begin() + i, s.begin() + j);
                i = j - 1;
            }
        }
        
        return s;
    }
    
    void testReverseWords3() {
        string s = "Let's take LeetCode contest";
        cout << reverseWords3(s) << endl;
    }
    
    //647
    int countSubstrings(string s) {
        int size = (int) s.size();
        int r = 0;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                bool isP = true;
                int low = i;
                int high = j;
                while (low <= high) {
                    if (s[low] == s[high]) {
                        low++;
                        high--;
                    } else {
                        isP = false;
                        break;
                    }
                }
                if (isP) {
                    r += (j - i + 1) / 2;
                }
            }
        }
        r += size;
        return r;
    }
    
    void testCountSubstring() {
        string s = "fdsklf";
        cout << countSubstrings(s) << endl;
    }
    
    // 658
    vector<int> findClosestElements(vector<int> &arr, int k, int x) {
        vector<int> r;
        vector<int> diff;
        int size = (int) arr.size();
        int min = INT_MAX;
        int index = 0;
        for (int i = 0; i < size; i++) {
            int d = abs(x - arr[i]);
            if (d < min) {
                min = d;
                index = i;
            }
            diff.push_back(d);
        }
        
        r.push_back(arr[index]);
        
        int li = index - 1;
        int ri = index + 1;
        for (int i = 0; i < k - 1; i++) {
            int ld = INT_MAX;
            int rd = INT_MAX;
            if (li >= 0) {
                ld = diff[li];
            }
            
            if (ri < size) {
                rd = diff[ri];
            }
            
            if (ld <= rd) {
                li--;
            } else {
                ri++;
            }
        }
        
        vector<int> rr(arr.begin() + (li + 1), arr.begin() + ri);
        return rr;
    }
    
    void testFindClosestElements() {
        vector<int> arr = {1, 2, 3, 4, 5};
        vector<int> r = findClosestElements(arr, 4, 3);
        for (int num: r) {
            cout << num << endl;
        }
    }
    
    // 921
    
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
        stack<int> st;
        int size = (int) pushed.size();
        if (size == 0) return true;
        int popIndex = 0;
        int popItem = popped[popIndex];
        for (int i = 0; i <= size; i++) {
            if (!st.empty()) {
                int top = st.top();
                while (top == popItem) {
                    popIndex++;
                    if (popIndex >= size) break;
                    popItem = popped[popIndex];
                    st.pop();
                    if (st.empty()) break;
                    top = st.top();
                }
            }
            if (i < size) st.push(pushed[i]);
        }
        
        if (popIndex == size) return true;
        
        return false;
    }
    
    void testValidateStackSequences() {
        vector<int> v1 = {};
        vector<int> v2 = {};
        cout << validateStackSequences(v1, v2) << endl;
    }
    
    // 921
    int minAddToMakeValid(string S) {
        if (S.empty()) return 0;
        int r = 0;
        stack<char> st;
        for (char c: S) {
            if (c == ')' && st.empty()) {
                r++;
            } else if (c == ')') {
                st.pop();
            } else {
                st.push('(');
            }
        }
        
        int size = (int) st.size();
        return size + r;
    }
    
    void testMinAddToMakeValid() {
        string s = "())";
        cout << minAddToMakeValid(s) << endl;
    }
    
    // 461
    int hammingDistance(int x, int y) {
        int mask = 0x0001;
        int r = 0;
        for (int i = 0; i < 32; i++) {
            int xt = x & mask;
            int yt = y & mask;
            if (xt != yt) r++;
            x = x >> 1;
            y = y >> 1;
        }
        
        return r;
    }
    
    void testHammingDistance() {
        int x = 1;
        int y = 4;
        cout << hammingDistance(x, y) << endl;
    }
    
    // 338
    vector<int> countBits(int num) {
        vector<int> r(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            r[i] = r[i >> 1] + (i & 1);
        }
        return r;
    }
    
    void testCountBits() {
        int n = 2;
        vector<int> v = countBits(n);
        for (int num: v) {
            cout << num << endl;
        }
    }
    
    // 606
    string tree2str(TreeNode * t) {
        if (!t) return "";
        string s;
        string l = tree2str(t->left);
        string r = tree2str(t->right);
        s.append(to_string(t->val));
        
        if (!l.empty()) {
            s.append("(");
            s.append(l);
            s.append(")");
        } else if (!r.empty()) {
            s.append("()");
        }
        
        if (!r.empty()) {
            s.append("(");
            s.append(r);
            s.append(")");
        }
        
        return s;
    }
    
    // 508
    unordered_map<int, int> treeSum508;
    vector<int> tr508;
    int max508 = 0;
    vector<int> findFrequentTreeSum(TreeNode * root) {
        findFrequentTreeSumHelper(root);
        return tr508;
    }
    
    int findFrequentTreeSumHelper(TreeNode * node) {
        if (!node) return 0;
        int l = findFrequentTreeSumHelper(node->left);
        int r = findFrequentTreeSumHelper(node->right);
        
        int sum = l + r + node->val;
        if (!treeSum508[sum]) {
            treeSum508[sum] = 1;
        } else {
            treeSum508[sum]++;
        }
        
        if (treeSum508[sum] > max508) {
            max508 = treeSum508[sum];
            tr508.clear();
            tr508.push_back(sum);
        } else if (treeSum508[sum] == max508) {
            tr508.push_back(sum);
        }
        
        return sum;
    }
    
    // 653
    bool findTarget(TreeNode * root, int k) {
        if (!root) return false;
        int temp = k - root->val;
        bool isFind = findTargetHelper(root, temp);
        
        if (temp != root->val && isFind) {
            return true;
        } else {
            bool isLf = findTargetHelper(root->left, k);
            if (isLf) {
                return true;
            } else {
                bool isRf = findTargetHelper(root->right, k);
                return isRf;
            }
        }
    }
    
    bool findTargetHelper(TreeNode * root, int k) {
        if (!root) return false;
        if (k == root->val) {
            return true;
        } else if (k < root->val) {
            return findTarget(root->left, k);
        } else {
            return findTarget(root->right, k);
        }
    }
    
    // 662
    int widthOfBinaryTree(TreeNode * root) {
        vector<TreeNode *> v;
        v.push_back(root);
        int max = 0;
        while (!v.empty()) {
            int len = (int) v.size();
            cout << len << endl;
            bool isNode = false;
            int diff = 0;
            for (int i = 0; i < len; i++) {
                TreeNode * node = v[i];
                if (node) {
                    isNode = true;
                    v.push_back(node->left);
                    v.push_back(node->right);
                    if (i + 1 - diff > max) max = i + 1 - diff;
                } else {
                    if (isNode) {
                        v.push_back(nullptr);
                        v.push_back(nullptr);
                    } else {
                        diff++;
                    }
                }
            }
            v.erase(v.begin(), v.begin() + len);
        }
        
        return max;
    }
    
    // 283
    void moveZeroes(vector<int> &nums) {
        int j = 0;
        // move all the nonzero elements advance
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nums[j++] = nums[i];
            }
        }
        for (;j < nums.size(); j++) {
            nums[j] = 0;
        }
    }
    
    void testMoveZeros() {
        vector<int> t = {0, 1, 0, 3, 12};
        moveZeroes(t);
        for (int i: t) {
            cout << i << endl;
        }
    }
    
    // 39
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int> > r;
        sort(candidates.begin(), candidates.end());
        vector<int> combination;
        combinationSumHelper(candidates, target, r, combination, 0);
        return r;
    }
    
    void combinationSumHelper(vector<int> &candidates, int target, vector<vector<int> > &res, vector<int> &combination, int begin) {
        if (target == 0) {
            res.push_back(combination);
            return;
        }
        
        for (int i = begin; i != candidates.size() && target >= candidates[i]; i++) {
            combination.push_back(candidates[i]);
            combinationSumHelper(candidates, target - candidates[i], res, combination, i);
            combination.pop_back();
        }
    }
    
    void testCombinationSum() {
        vector<int> candidates = {2, 3, 6, 7};
        int target = 7;
        vector<vector<int> > r = combinationSum(candidates, target);
        for (auto v: r) {
            for (int i: v) {
                cout << i << endl;
            }
        }
    }
    
    // 811
    vector<string> subdomainVisits(vector<string> &cpdomains) {
        unordered_map<string, int> m;
        vector<string> r;
        for (string &str: cpdomains) {
            string::size_type blank, pos;
            int num;
            string domain;
            blank = str.find(' ');
            num = stoi(str.substr(0, blank));
            domain = str.substr(blank + 1);
            while (!domain.empty()) {
                if (!m[domain]) {
                    m[domain] = num;
                } else {
                    m[domain] += num;
                }
                pos = domain.find('.');
                if (pos == string::npos) {
                    domain.clear();
                } else {
                    domain = domain.substr(pos + 1);
                }
            }
        }
        for (pair<const string, int> &p: m) {
            char str[100];
            snprintf(str, 100, "%d %s", p.second, p.first.c_str());
            string s(str);
            r.push_back(s);
        }
        return r;
    }
    
    void testSubdomainVisits() {
        vector<string> s = {"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
        vector<string> r = subdomainVisits(s);
        for (string &t : r) {
            cout << t << endl;
        }
    }
    
    //648
    string replaceWords(vector<string> &dict, string sentence) {
        string::size_type start = 0;
        string::size_type end = sentence.find(' ');
        string word = sentence.substr(start, end);
        string::size_type size = sentence.size();
        string r = "";
        struct TrieNode * root = getNode();
        
        for (string &str: dict) {
            TrieInsert(root, str);
        }
        while (!word.empty()) {
            string temp = word;
            string sss = TriePrefix(root, word);
            if (!sss.empty()) {
                temp = sss;
            }
            if (r.empty()) {
                r += temp;
            } else {
                r += " ";
                r += temp;
            }
            start = end + 1;
            if (start > size) break;
            end = sentence.find(' ', start);
            if (end == string::npos) end = size;
            word = sentence.substr(start, end - start);
        }
        return r;
    }
    
    void testReplaceWords() {
        vector<string> dict = {"cat", "bat", "rat"};
        string sentence = "the cattle was rattled by the battery";
        cout << replaceWords(dict, sentence) << endl;
    }
    
    // 87
    ListNode * deleteDuplicates(ListNode * head) {
        ListNode * prev, * cur, * next;
        bool isEqual = false;
        cur = head;
        if (head == NULL) return head;
        next = head->next;
        prev = NULL;
        
        while (next != NULL) {
            if (cur->val == next->val) {
                isEqual = true;
                cur = cur->next;
                next = cur->next;
            } else {
                if (isEqual) {
                    isEqual = false;
                    if (prev != NULL) {
                        prev->next = next;
                        cur = next;
                        next = cur->next;
                    } else {
                        head = next;
                        cur = head;
                        next = head->next;
                    }
                } else {
                    prev = cur;
                    cur = cur->next;
                    next = cur->next;
                }
            }
        }
        
        if (isEqual) {
            if (prev) {
                prev->next = next;
            } else {
                head = NULL;
            }
        }
        
        return head;
    }
    
    // 415
    string addStrings(string num1, string num2) {
        string r = "";
        int carry = 0;
        int s1 = (int) num1.size();
        int s2 = (int) num2.size() - 1;
        vector<char> vc;
        for (int i = s1 - 1; i >= 0; i--) {
            int n1 = num1[i] - '0';
            int n2 = 0;
            int nsum;
            int last;
            if (s2 >= 0) {
                n2 = num2[s2] - '0';
                s2--;
            }
            nsum = n1 + n2 + carry;
            carry = nsum / 10;
            last = nsum % 10;
            char c = (char) '0' + last;
            r += c;
        }
        
        while (s2 >= 0) {
            int n2 = num2[s2] - '0';
            s2--;
            int sum = n2 + carry;
            int last = sum % 10;
            carry = sum / 10;
            char c = (char) '0' + last;
            r += c;
        }
        
        if (carry) {
            char c = (char) '0' + carry;
            r += c;
        }
        
        reverse(r.begin(), r.end());
        
        return r;
    }
    
    void testAddString() {
        string num1 = "4";
        string num2 = "69";
        cout << addStrings(num1, num2) << endl;
    }
    
    // 791
    string customSortString(string S, string T) {
        string r;
        unordered_map<char, int> mm;
        for (char c: T) {
            if (!mm[c]) {
                mm[c] = 1;
            } else {
                mm[c]++;
            }
        }
        
        for (char c: S) {
            if (mm[c]) {
                r.append(mm[c], c);
                mm.erase(c);
            }
        }
        
        for (pair<const char, int> &p: mm) {
            r.append(p.second, p.first);
        }
        return r;
    }
    
    void testCustomSortString() {
        string S = "cba";
        string T = "abcd";
        cout << customSortString(S, T) << endl;
    }
    
    // 475
    int findRadius(vector<int> &houses, vector<int> &heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int size = (int) houses.size();
        int size2 = (int) heaters.size();
        int radius = 0;
        int min = 0;
        int prev = 0;
        int i;
        for (i = 0; i < size2; i++) {
            int p = heaters[i];
            if (p < houses[0]) {
                min = houses[size - 1] - p;
            } else if (p > houses[size - 1]) {
                if (prev == 0) {
                    min = p - houses[0];
                } else {
                    int r1 = p - houses[size - 1];
                    int r2 = houses[size - 1] - prev;
                    radius = r1 > r2 ? r2 : r1;
                    if (radius > min) {
                        min = radius;
                    }
                }
                break;
            } else {
                if (i == 0) {
                    min = p - houses[0];
                } else if (prev < houses[0]) {
                    radius = p - houses[0];
                    if (radius < min) min = radius;
                } else {
                    int diff = p - prev;
                    radius = diff/2;
                    if (radius > min) min = radius;
                }
            }
            prev = p;
        }
        
        if (heaters[size2 - 1] < houses[size - 1]) {
            radius = houses[size - 1] - heaters[size2 - 1];
            if (radius > min) min = radius;
        }
        
        return min;
    }
    
    void testFindRadius() {
        vector<int> houses = {282475249,622650073,984943658,144108930,470211272,101027544,457850878,458777923};
        vector<int> hearts = {823564440,115438165,784484492,74243042,114807987,137522503,441282327,16531729,823378840,143542612};
        cout << findRadius(houses, hearts) << endl;
    }
    
    // 503
    vector<int> nextGreaterElements(vector<int> &nums) {
        int size = (int) nums.size();
        vector<int> r(size, -1);
        if (size == 0) return r;
        stack<int> s;
        int top;
        for (int i = 0; i < size; i++) {
            int temp = nums[i];
            while (!s.empty() && temp > nums[s.top()]) {
                r[s.top()] = temp;
                s.pop();
            }
            
            s.push(i);
        }

        top = s.top();
        for (int i = 0; i < size - 1; i++) {
            if (i >= top) break;
            int t = nums[i];
            while (i < top && t > nums[top]) {
                r[top] = t;
                s.pop();
                top = s.top();
            }
        }
        return r;
    }
    
    void testNextGreaterElements() {
        vector<int> nums = {100,1,11,1,120,111,123,1,-1,-100};
        vector<int> r = nextGreaterElements(nums);
        for (int i: r) {
            cout << i << endl;
        }
    }
    
    // 693
    bool hasAlternatingBits(int n) {
        int mask = 0x0001;
        int prev = -1;
        bool noOneFlag = false;
        for(int i = 0; i < 32; i++) {
            int bit = n & mask;
            if (prev != -1) {
                if (prev == bit) {
                    if (bit == 1) {
                        return false;
                    } else if (!noOneFlag) {
                        noOneFlag = true;
                    }
                }
            }
            
            if (noOneFlag && bit == 1) return false;
            prev = bit;
            n = n >> 1;
        }
        return true;
    }
    
    void testHasAlternatingBits() {
        int n = 5;
        cout << hasAlternatingBits(n) << endl;
    }
    
    //260
    vector<int> singleNumber3(vector<int> &nums) {
        vector<int> r(2, 0);
        int xr = 0;
        for (int n: nums) {
            xr ^= n;
        }
        
        // found the right most set bit;
        int diff = xr & (-xr);
        for (int n: nums) {
            if ((n & diff) == 0) {
                r[0] ^= n;
            } else {
                r[1] ^= n;
            }
        }
        return r;
    }
    
    void testSingleNumber3() {
        vector<int> t = {1, 2, 1, 3, 2, 5};
        vector<int> r = singleNumber3(t);
        for (int n: r) {
            cout << n << endl;
        }
    }
    
    //572
    bool isSubtree(TreeNode * s, TreeNode * t) {
        if (t == NULL) return true;
        return findSameRoot(s, t);
    }
    
    bool findSameRoot(TreeNode * s, TreeNode * t) {
        if (s == NULL) return NULL;
        int val = t->val;
        bool isSame = false;
        if (s->val == val) {
            isSame = compareTree(s, t);
            if (isSame) return isSame;
        }
        isSame = findSameRoot(s->left, t);
        if (isSame) return isSame;
        isSame = findSameRoot(s->right, t);
        return isSame;
    }
    
    bool compareTree(TreeNode * l, TreeNode * r) {
        if (l != NULL && r != NULL) {
            if (l->val != r->val) return false;
            return compareTree(l->left, r->left) && compareTree(l->right, r->right);
        } else if (l == NULL && r == NULL) {
            return true;
        } else {
            return false;
        }
    }
    
    // 958
    bool isCompleteTree(TreeNode * root) {
        if (root == NULL) return true;
        vector<TreeNode *> v;
        v.push_back(root);
        
        while (!v.empty()) {
            int size = (int) v.size();
            bool isBroke = false;
            for (int i = 0; i < size; i++) {
                TreeNode * node = v[i];
                int csize = (int) v.size();
                if (node->left != NULL) {
                    if (isBroke) return false;
                    v.push_back(node->left);
                } else {
                    isBroke = true;
                }
                
                if (node->right != NULL) {
                    if (isBroke) return false;
                    v.push_back(node->right);
                } else {
                    if (i == size - 1) {
                        if (size == csize) {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        isBroke = true;
                    }
                }
            }
            v.erase(v.begin(), v.begin() + size);
        }
        
        return false;
    }
    
    
    // 530
    int min530;
    int prev530;
    int getMinimumDifference(TreeNode * root) {
        min530 = INT_MAX;
        prev530 = -1;
        getMinimumDifferenceHelper(root);
        return min530;
    }
    
    void getMinimumDifferenceHelper(TreeNode * node) {
        if (node == NULL) return;
        int temp, diff;
        getMinimumDifferenceHelper(node->left);
        temp = node->val;
        if (prev530 >= 0) {
            diff = abs(temp - prev530);
            min530 = min530 > diff ? diff : min530;
        }
        prev530 = temp;
        getMinimumDifferenceHelper(node->right);
    }
    
    // 867
    vector<vector<int> > transpose(vector<vector<int> > &A) {
        vector<vector<int> > r;
        int i, j;
        int xs = (int) A.size();
        int ys = (int) A[0].size();
        for (j = 0; j < ys; j++) {
            vector<int> temp;
            for (i = 0; i < xs; i++) {
                temp.push_back(A[i][j]);
            }
            
            r.push_back(temp);
        }
        return r;
    }
    
    // 1002
    vector<string> commonChars(vector<string> &A) {
        vector<int> num(26, INT_MAX);
        vector<string> r;
        for (string &t: A) {
            vector<int> temp(26, 0);
            for (char c: t) temp[c - 'a']++;
            for (int i = 0; i < 26; i++) num[i] = min(num[i], temp[i]);
        }
        
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < num[i]; j++) {
                r.push_back(string(1, i + 'a'));
            }
        }
        
        return r;
    }
    
    void testCommonChars() {
        vector<string> s = {"bella", "label", "roller"};
        vector<string> r = commonChars(s);
        for(string &t: r) {
            cout << t << endl;
        }
    }
    
    // 1019
    vector<int> nextLargeNodes(ListNode * head) {
        vector<int> r(10001, 0);
        ListNode * p = head;
        stack<int> st;
        int i = 0;
        while (p) {
            int temp = p->val;
            int t = i;
            while (!st.empty() && st.top() < temp) {
                while (r[t - 1] != 0) {
                    t--;
                }
                r[t - 1] = temp;
                st.pop();
                t--;
            }
            st.push(temp);
            p = p->next;
            i++;
        }
        
        vector<int> rr(r.begin(), r.begin() + i);
        return rr;
    }
    
    void testNextLargeNodes() {
        vector<int> v = {2, 1, 5};
        ListNode * list = constructLink(v);
        vector<int> r = nextLargeNodes(list);
        for (int n: r) {
            cout << n << endl;
        }
    }
    
    // 696
    int countBinarySubstrings(string &s) {
        vector<int> v(2, 0);
        int r = 0;
        int size = (int) s.size();
        for (int i = 0; i < size; i++) {
            if (i > 0 && s[i] != s[i - 1]) {
                if (v[0] > 0 && v[1] > 0) {
                    int n = min(v[0], v[1]);
                    r += n;
                    v[s[i] - '0'] = 0;
                }
            }
            v[s[i] - '0']++;
        }
        
        if (v[0] > 0 && v[1] > 0) {
            int n = min(v[0], v[1]);
            r += n;
        }
        
        return r;
    }
    
    void testCountBinarySubstrings() {
        string s = "100111001";
        cout << countBinarySubstrings(s) << endl;
    }
    
    // 69
    int mySqrt(int x) {
        int low = 0, high, prev = 0, mid;
        if (x < 46340) {
            high = x;
        } else {
            high = 46340;
        }
        
        while (low <= high) {
            mid = low + ((high - low) / 2);
            int temp = mid * mid;
            if (temp == x) {
                return mid;
            } else if (temp > x) {
                high = mid - 1;
            } else {
                low = mid + 1;
                prev = mid;
            }
        }
        return prev;
    }
    
    void testMySqrt() {
        cout << mySqrt(5) << endl;
    }
    
    // 81
    bool search2(vector<int> &nums, int target) {
        int size = (int) nums.size(), index = size - 1;
        if (size == 0) return false;
        for (int i = 0; i < size - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                index = i;
                break;
            }
        }
        
        if (target >= nums[0] && target <= nums[index]) {
            int low = 0;
            int high = index;
            while (low <= high) {
                int mid = low + ((high - low) / 2);
                if (nums[mid] == target) {
                    return true;
                } else if (nums[mid] > target) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        } else {
            int low = index + 1;
            int high = size - 1;
            while(low <= high) {
                int mid = low + ((high - low) / 2);
                if (nums[mid] == target) {
                    return true;
                } else if (nums[mid] > target) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return false;
    }
    
    void testSearch2() {
        vector<int> v = {3, 1};
        cout << search2(v, 1) << endl;
    }
    
    // 1021
    string removeOuterParentheses(string S) {
        string r;
        stack<char> st;
        for (char c: S) {
            int size = (int) st.size();
            if (c == '(') {
                st.push(c);
                if (size > 0) r.push_back(c);
            } else if (c == ')') {
                st.pop();
                if (size > 1) r.push_back(c);
            }
        }
        return r;
    }
    
    void testRemoveOuterParentheses() {
        string a = "(()())(())(()(()))";
        cout << removeOuterParentheses(a) << endl;
    }
    
    // 1003
    bool isValid(string S) {
        stack<char> st;
        int size = (int) S.size();
        if (S[0] != 'a' || S[size - 1] != 'c') return false;
        for (char c: S) {
            if (c == 'c' && !st.empty()) {
                if (st.top() == 'b') {
                    st.pop();
                    if (st.top() == 'a') {
                        st.pop();
                    } else {
                        st.push('b');
                        st.push(c);
                    }
                }
            } else {
                st.push(c);
            }
        }
        return st.empty();
    }
    
    void testIsValid() {
        string str = "bcc";
        cout << isValid(str) << endl;
    }
    
    // 231
    bool isPowerOfTwo(int n) {
        int r = 0;
        int mask = 0x0001;
        for (int i = 0; i < 32; i++, n >>= 1) {
            if (n & mask) r++;
        }
        
        return r == 1;
    }
    
    void testIsPowerOfTwo() {
        int n = 218;
        cout << isPowerOfTwo(n) << endl;
    }
    
    // 477
    int totalHammingDistance(vector<int> &nums) {
        int size = (int) nums.size();
        int r = 0;
        int mask = 0x0001;
        for (int i = 0; i < 32; i++) {
            int setCount = 0;
            for (int j = 0; j < size; j++) {
                if ((nums[j] >> i) & mask) setCount ++;
            }
            
            r += setCount * (size - setCount);
        }
        return r;
    }
    
    void testTotalHammingDistance() {
        vector<int> d = {4, 14, 2};
        cout << totalHammingDistance(d) << endl;
    }
    
    // 543
    int maxDiameter = 0;
    int diameterOfBinaryTree(TreeNode * root) {
        if (root == NULL) return 0;
        maxDepthHelper(root);
        return maxDiameter;
    }
    
    int diameterOfBinaryTreeHelper(TreeNode * node) {
        if (node == NULL) return 0;
        int diameter =  diameterOfBinaryTreeHelper(node->left) + diameterOfBinaryTreeHelper(node->right);
        if (diameter > maxDiameter) maxDiameter = diameter;
        return diameter;
    }
    
    int maxDepthHelper(TreeNode * node) {
        if (node == NULL) return 0;
        int ld = maxDepthHelper(node->left);
        int rd = maxDepthHelper(node->right);
        
        if (ld + rd > maxDiameter) {
            maxDiameter = ld + rd;
        }
        
        return max(ld, rd) + 1;
    }
    
    // 814
    TreeNode * pruneTree(TreeNode * root) {
        if (!isTreeContainOne(root)) {
            root = NULL;
        }
        return root;
    }
    
    bool isTreeContainOne(TreeNode * node) {
        if (node == NULL) return false;
        bool isLeftContain = isTreeContainOne(node->left);
        bool isRightContain = isTreeContainOne(node->right);
        
        if (!isLeftContain) node->left = NULL;
        if (!isRightContain) node->right = NULL;
        
        return isLeftContain || isRightContain || node->val == 1;
        
    }
    
    // 720
    string longestWord(vector<string> &words) {
        TrieNode * root = getNode();
        int maxLen = 0;
        string r;
        for (string &s: words) {
            TrieInsert(root, s);
        }
        
        for (string &s: words) {
            int size = (int) s.size();
            if (TrieSearchAllPrefix(root, s)) {
                if (maxLen < size || (maxLen == size && r.compare(s) > 0)) {
                    maxLen = size;
                    r = s;
                }
            }
        }
        
        return r;
    }
    
    void testLongestWord() {
        vector<string> words = {"yo","ew","fc","zrc","yodn","fcm","qm","qmo","fcmz","z","ewq","yod","ewqz","y"};
        cout << longestWord(words) << endl;
    }
    
    int maxProfit(vector<int> &prices) {
        int size = (int) prices.size();
        int r = 0;
        for (int i = 1; i < size; i++) {
            if (prices[i] > prices[i - 1]) {
                r += prices[i] - prices[i - 1];
            }
        }
        return r;
    }
    
    void testMaxProfit() {
        vector<int> t = {1,2,3,4,5};
        cout << maxProfit(t) << endl;
    }
    
    int findDuplicate(vector<int> &nums) {
        int tortoise = nums[0];
        int hare = nums[0];
        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while (tortoise != hare);
        
        // Find the "entrance" to the cycle.
        int ptr1 = nums[0];
        int ptr2 = tortoise;
        while (ptr1 != ptr2) {
            ptr1 = nums[ptr1];
            ptr2 = nums[ptr2];
        }
        
        return ptr1;
    }
    
    void testFindDuplicate() {
        vector<int> nums = {1,3,4,2,2};
        cout << findDuplicate(nums) << endl;
    }
    
    // 143
    void reorderList(ListNode * head) {
        vector<ListNode *> v;
        ListNode * node = head;
        while (node != NULL) {
            v.push_back(node);
            node = node->next;
        }
        
        int t = (int) v.size(), i;
        ListNode * temp = NULL;
        ListNode * nh = NULL;
        
        for (i = 0; i < t/2; i++) {
            v[i]->next = v[t - i - 1];
            v[t - i - 1]->next = NULL;
            if (temp) {
                temp->next = v[i];
            }
            if (!nh) {
                nh = v[i];
            }
            
            temp = v[t - i - 1];
        }
        
        if (t % 2 != 0) {
            v[i]->next = NULL;
            temp->next = v[i];
        }
        
        head = nh;
    }
    
    // 575
    int distributeCandies(vector<int> &candies) {
        int size = (int) candies.size();
        set<int> s;
        for (int n: candies) {
            s.insert(n);
        }
        
        int kinds = (int) s.size();
        
        if (kinds > (size / 2)) return size / 2;
        
        return kinds;
    }
    
    void testDistributeCandies() {
        vector<int> candies = {1, 1, 2, 3};
        cout << distributeCandies(candies) << endl;
    }
    
    
    // 520
    bool detectCapticalUse(string &word) {
        bool isFirstCaptical = false;
        int size = (int) word.size();
        int allCapticalNum = 0;
        for (int i = 0; i < size; i++) {
            int temp = (int) word[i];
            if (temp > 64 && temp < 91) {
                if (i == 0) isFirstCaptical = true;
                allCapticalNum++;
            }
        }
        
        if (allCapticalNum == size || allCapticalNum == 0 || (allCapticalNum == 1 && isFirstCaptical)) return true;
        
        
        
        return false;
    }
    
    void testDetectCapticalUse() {
        string t = "FlaG";
        cout << detectCapticalUse(t) << endl;
    }
    
    // 678
    bool checkValidString(string s) {
        int size = (int) s.size();
        if (size == 0) return true;
        stack<char> st;
        int change = 0;
        for (int i = 0; i < size; i++) {
            char c = s[i];
            if (c == '(' || c == '*') {
                st.push(c);
            } else {
                if (!st.empty()) {
                    if (st.top() == '*') change += 2;
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        
        int star = 0, lp = 0 - change;
        
        while (!st.empty()) {
            if (st.top() == '(') {
                lp++;
                if (lp > star) return false;
            } else {
                star++;
            }
            
            st.pop();
        }
        
        return true;
        
    }
    
    void testCheckValidString() {
        string s = "(((";
        cout << checkValidString(s) << endl;
    }
    
    // 240
    bool searchMartix2(vector<vector<int> > &matrix, int target) {
        int sy = (int) matrix.size();
        if (sy == 0) return false;
        int sx = (int) matrix[0].size();
        if (sx == 0) return false;
        int lowx = 0, lowy = 0, highx = sx - 1, highy = sy - 1;
        while (lowx <= highx && lowy <= highy) {
            int midx = lowx + (highx - lowx) / 2;
            int midy = lowy + (highy - lowy) / 2;
            int tn = matrix[midy][midx];
            
            if (target > tn) {
                if (midx + 1 < sx && target == matrix[midy][midx + 1]) return true;
                if (midy + 1 < sy && target == matrix[midy + 1][midx]) return true;
                int tempx = midx + 1;
                int tempy = midy + 1;
                
                if (tempx < sx && tempy < sy) {
                    lowx = tempx;
                    lowy = tempy;
                } else if (tempx < sx) {
                    lowx = tempx;
                } else if (tempy < sy) {
                    lowy = tempy;
                } else {
                    return false;
                }
            } else if (target < tn) {
                if (midx - 1 >= 0 && target == matrix[midy][midx - 1]) return true;
                if (midy - 1 >= 0 && target == matrix[midy - 1][midx]) return true;
                int tempx = midx - 1;
                int tempy = midy - 1;
                
                if (tempx > 0 && tempy > 0) {
                    highx = tempx;
                    highy = tempy;
                } else if (tempx > 0) {
                    highx = tempx;
                } else if (tempy > 0) {
                    highy = tempy;
                } else {
                    return false;
                }
            } else {
                return true;
            }
            
        }
        return false;
    }
    
    void testSearchMartix2() {
        vector<vector<int> > martix = {
            {1,2,3,4,5}
        };
        cout << searchMartix2(martix, 1) << endl;
    }
    
    // 762
    int countPrimeSetBits(int L, int R) {
        int mask = 0x0001;
        int r = 0;
        for (int i = L; i <= R; i++) {
            int ob = 0, zb = 0;
            bool isStart = false;
            for (int j = 31; j >= 0; j--) {
                int t = (i >> j) & mask;
                if (t == 1) {
                    ob++;
                    isStart = true;
                } else if (isStart) {
                    zb++;
                }
            }
            if (ob >= zb) r++;
        }
        return r;
    }
    
    void testCountPrimeSetBits() {
        cout << countPrimeSetBits(6, 10) << endl;
    }
    
    // 331
    bool isValidSerialization(string preorder) {
        string::size_type start = 0, pos;
        preorder += ',';
        int capacity = 1;
        while ((pos = preorder.find(',', start)) != string::npos) {
            string temp = preorder.substr(start, pos - start);
            cout << temp << endl;
            capacity--;
            if (capacity < 0) return false;
            if (temp[0] != '#') capacity += 2;
            start = pos + 1;
        }
        return capacity == 0;
    }
    
    void testIsValidSerialization() {
        string s = "1,#";
        cout << isValidSerialization(s) << endl;
    }
    
    // 784
    vector<string> letterCasePermutation(string S) {
        vector<string> r = {""};
        int size = (int) S.size();
        for (int i = 0; i < size; i++) {
            vector<char> aparr;
            if (S[i] >= 'A' && S[i] <= 'Z') {
                aparr.push_back(S[i]);
                aparr.push_back(S[i] + 32);
            } else if (S[i] >= 'a' && S[i] <= 'z') {
                aparr.push_back(S[i]);
                aparr.push_back(S[i] - 32);
            } else {
                aparr.push_back(S[i]);
            }
            
            int size = (int) r.size();
            for (char c: aparr) {
                for (int i = 0; i < size; i++) {
                    string temp = r[i] + c;
                    r.push_back(temp);
                }
            }
            
            r.erase(r.begin(), r.begin() + size);
        }
        return r;
    }
    
    void testLetterCasePermutation() {
        string s = "a1b2";
        vector<string> r = letterCasePermutation(s);
        for (string t: r) {
            cout << t << endl;
        }
    }
    
    // 993
    int depth_x = 0, depth_y = 0;
    bool isCousins(TreeNode * root, int x, int y) {
        TreeNode * x_node = findCousinsHelper(root, x, &depth_x);
        TreeNode * y_node = findCousinsHelper(root, y, &depth_y);
        cout << depth_x << "," << depth_y << endl;
        cout << x_node->val << "," << y_node->val << endl;
        if (x_node == NULL || y_node == NULL) return false;
        if (depth_x == depth_y && x_node != y_node) return true;
        return false;
    }
    
    TreeNode * findCousinsHelper(TreeNode * node, int x, int * t) {
        if (node == NULL) return NULL;
        if (node->left && node->left->val == x) return node;
        if (node->right && node->right->val == x) return node;
        int temp = *t;
        *t = *t + 1;
        TreeNode * l = findCousinsHelper(node->left, x, t);
        if (l) return l;
        *t = temp + 1;
        TreeNode * r = findCousinsHelper(node->right, x, t);
        return r;
    }
    
    // 139
    bool wordBreak(string s, vector<string>& wordDict) {
        return false;
    }
    
    void testWordBreak() {
        string s = "leetcode";
        vector<string> wordDict = {"leet", "code"};
        
        
        cout << wordBreak(s, wordDict) << endl;
    }
    
    // 70
    int climbStairs(int n) {
        if (n == 1) {
            return 1;
        } else if (n == 2) {
            return 2;
        } else {
            int first = 1;
            int second = 2;
            int third;
            for (int i = 3; i <= n; i++) {
                third = first + second;
                first = second;
                second = third;
            }
            return third;
        }
    }
    
    void testClimbStairs() {
        int n = 44;
        cout << climbStairs(n) << endl;
    }
    
    // 581
    int findUnsortedSubarray(vector<int> &nums) {
        int start = -2, end = -2, max = 0;
        int size = (int) nums.size();
        for (int i = 0; i < size; i++) {
            if (i > 0 && max > nums[i]) {
                if (start == -2) {
                    int j = i - 1;
                    while (j >= 0 && nums[i] < nums[j]) {
                        j--;
                    }
                    start = j;
                } else {
                    int j = start + 1;
                    while (j >= 0 && nums[i] < nums[j]) {
                        j--;
                    }
                    if (j < start) start = j;
                }
                end = i;
            } else {
                max = nums[i];
            }
        }
        return end - start;
    }
    
    void testFindUnSortedSubarray() {
        vector<int> nums = {1, 2, 3, 4};
        cout << findUnsortedSubarray(nums) << endl;
    }
    
    // 189
    void rotate(vector<int> &nums, int k) {
        nums.insert(nums.begin(), k, 0);
        int index = (int) nums.size() - 1, last;
        for (int i = 0; i < k; i++) {
            last = nums[index - i];
            nums.pop_back();
            nums[k - 1 - i] = last;
        }
    }
    
    void testRotate() {
        vector<int> nums = {-1,-100,3,99};
        rotate(nums, 2);
        for (int n: nums) {
            cout << n << endl;
        }
    }
    // 202
    
    bool isHappy(int n) {
        set<int> st;
        while (n != 1) {
            int temp = 0;
            if (st.count(n) > 0) return false;
            st.insert(n);
            string str = to_string(n);
            for (char c: str) {
                temp += (c - '0') * (c - '0');
            }
            
            n = temp;
        }
        return true;
    }
    
    void testIsHappy() {
        int n = 2;
        cout << isHappy(n) << endl;
    }
    
    // 200
    int rowSize200;
    int colSize200;
    int numIslands(vector<vector<char> > &grid) {
        set<int> s;
        int r = 0;
        rowSize200 = (int) grid.size();
        if (rowSize200 == 0) return 0;
        colSize200 = (int) grid[0].size();
        
        for (int i = 0; i < rowSize200; i++) {
            for (int j = 0; j < colSize200; j++) {
                bool isIsland = numIslandsHelper(i, j, grid, s);
                if (isIsland) r++;
            }
        }
        
        return r;
    }
    
    bool numIslandsHelper(int x, int y, vector<vector<char> > &grid, set<int> &s) {
        if (grid[x][y] != '1') return false;
        int key = x + y * 17;
        if (s.count(key) == 1) return false;
        s.insert(key);
        
        if (x - 1 >= 0) numIslandsHelper(x - 1, y, grid, s);
        if (x + 1 < rowSize200) numIslandsHelper(x + 1, y, grid, s);
        if (y - 1 >= 0) numIslandsHelper(x, y - 1, grid, s);
        if (y + 1 < colSize200) numIslandsHelper(x, y + 1, grid, s);
        return true;
    }
    
    void testNumIslands() {
        vector<vector<char> > arr = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
        };
        
        cout << numIslands(arr) << endl;
    }
    
    // 88
    void merge(vector<int> & nums1, int m, vector<int> &nums2, int n) {
        if (m == 0) {
            nums1 = nums2;
            return;
        }
        int i, j;
        for (i = 0; i < n; i++) {
            int fb = nums2[i];
            for (j = m + i - 1; j >= 0 && fb < nums1[j]; j--) {
                nums1[j + 1] = nums1[j];
            }
            nums1[j + 1] = fb;
        }
    }
    
    void testMerge() {
        vector<int> a = {2, 0};
        vector<int> b = {1};
        
        merge(a, 1, b, 1);
        
        for (int n: a) {
            cout << n << endl;
        }
    }
    
    // 387
    int firstUniqChar(string s) {
        vector<int> vt(26, -1);
        set<char> st;
        int j = 0, r = -1;
        for(char c: s) {
            if (st.count(c) == 0) {
                vt[c - 'a'] = j;
                st.insert(c);
            } else {
                vt[c - 'a'] = -1;
            }
            j++;
        }
        
        for (int i = 0; i < 26; i++) {
            if (vt[i] > -1 && (vt[i] < r || r == -1)) {
                r = vt[i];
            }
        }
        
        return r;
    }
    
    void testFirstUniqChar() {
        string s = "loveleetcode";
        cout << firstUniqChar(s) << endl;
    }
    
    // 14
    string longestCommonPrefix(vector<string> &strs) {
        int size = (int) strs.size();
        if (size == 0) return "";
        string r = strs[0];
        for (int i = 1; i < size; i++) {
            string t = strs[i];
            int s = (int) (r.size() > t.size() ? t.size() : r.size());
            int j;
            for (j = 0; j < s; j++) {
                if (r[j] != t[j]) break;
            }
            r = r.substr(0, j);
        }
        return r;
    }
    
    void testLongestCommonPrefix() {
        vector<string> v = { "flower", "flow", "flight" };
        cout << longestCommonPrefix(v) << endl;
    }
    
    // 378
    int kthSmallest2(vector<vector<int> > &matrix, int k) {
        int n= (int) matrix.size();
        int l=matrix[0][0], r=matrix[n-1][n-1], mid;
        while(l<r){
            mid = l + (r - l)/2;
            int cnt=0, j=n-1;
            for(int i=0;i<n;i++){
                while(j>=0&&matrix[i][j]>mid)
                    j--;
                cnt+=j+1;
            }
            if(cnt<k)
                l=mid+1;
            else
                r=mid;
        }
        return l;
    }
    
    void testKthSmallest2() {
        vector<vector<int> > m = {
            {1, 5, 9},
            {10, 11, 13},
            {12, 13, 15},
        };
        cout << kthSmallest2(m, 8) << endl;
    }
    
    // 103
    vector<vector<int>> zigzagLevelOrder(TreeNode * root) {
        vector<TreeNode *> arr;
        vector<vector<int> > r;
        if (!root) return r;
        arr.push_back(root);
        vector<int> first = {root->val};
        r.push_back(first);
        bool isAscend = false;
        while (!arr.empty()) {
            int size = (int) arr.size();
            vector<int> temp;
            for (int i = size - 1; i >= 0; i--) {
                TreeNode * node = arr[i];
                if (node) {
                    if (isAscend) {
                        arr.push_back(node->left);
                        arr.push_back(node->right);
                        if (node->left) temp.push_back(node->left->val);
                        if (node->right) temp.push_back(node->right->val);
                    } else {
                        arr.push_back(node->right);
                        arr.push_back(node->left);
                        if (node->right) temp.push_back(node->right->val);
                        if (node->left) temp.push_back(node->left->val);
                    }
                }
            }
            
            if (!temp.empty()) r.push_back(temp);
            isAscend = !isAscend;
            arr.erase(arr.begin(), arr.begin() + size);
        }
        return r;
    }
    
    // 236
    TreeNode * lowestCommonAncestor(TreeNode * root, TreeNode * p, TreeNode * q) {
        TreeNode *t, *a1, *a2;
        if (p == q) return p;
        t = findAncestor(p, q);
        if (t != NULL) return p;
        t = findAncestor(q, p);
        if (t != NULL) return q;
        if (root == p || root == q) return root;
        a1 = p;
        a2 = q;
        while (a1 != a2) {
            if (findAncestor(a1, a2)) return a1;
            if (findAncestor(a2, a1)) return a2;
            if (a1 != root) a1 = findAncestor(root, a1);
            if (a2 != root) a2 = findAncestor(root, a2);
        }
        
        return a1;
    }
    
    TreeNode * findAncestor(TreeNode * node, TreeNode * p) {
        if (!node) return NULL;
        TreeNode * ancestor;
        if (node->left == p || node->right == p) return node;
        ancestor = findAncestor(node->left, p);
        if (ancestor != NULL) return ancestor;
        ancestor = findAncestor(node->right, p);
        return ancestor;
    }
    
    // 53 review**
    int maxSubArray(vector<int> &nums) {
        int size = (int) nums.size();
        vector<int> dp(size, 0);
        dp[0] = nums[0];
        int max = dp[0];
        
        for (int i = 1; i < size; i++) {
            dp[i] = dp[i - 1] > 0 ? dp[i - 1] + nums[i] : nums[i];
            max = dp[i] > max ? dp[i] : max;
        }
        return max;
    }
    
    void testMaxSubArray() {
        vector<int> t = {-2,1,-3,4,-1,2,1,-5,4};
        cout << maxSubArray(t) << endl;
    }
    
    // 204 review**
    int countPrimes(int n) {
        int r = 0;
        if (n <= 2) return 0;
        vector<bool> v(n, true);
        for (int i = 2; i < sqrt(n); i++) {
            if (v[i]) {
                for (int j = 0; i*i + j * i < n; j++) {
                    v[i*i + j*i] = false;
                }
            }
        }
        
        for (int i = 2; i < n; i++) {
            if (v[i]) r++;
        }
        return r;
    }
    
    void testCountPrimes() {
        int n = 10;
        cout << countPrimes(n) << endl;
    }
    
    // 38
    string countAndSay(int n) {
        string r = "1";
        for (int i = 1; i < n; i++) {
            char tc = 'a';
            char tn = 0;
            string temp;
            for (char c : r) {
                if (c == tc) {
                    tn++;
                } else {
                    if (tc != 'a') {
                        temp.append(to_string(tn));
                        temp.push_back(tc);
                    }
                    tc = c;
                    tn = 1;
                }
            }
            temp.append(to_string(tn));
            temp.push_back(tc);
            r = temp;
        }
        
        return r;
    }
    
    void testCountAndSay() {
        int n = 4;
        cout << countAndSay(n) << endl;
    }
    
    // 300
    int lengthOfLIS(vector<int> &nums) {
        int temp = 1, max = 0, i, z;
        int size = (int) nums.size();
        vector<int> sn(size, 1);
        for (i = size - 1; i >= 0; i--) {
            for (z = i + 1; z < size; z++) {
                if (nums[i] < nums[z] && sn[z] + 1 > temp) {
                    temp = sn[z] + 1;
                }
            }
            sn[i] = temp;
            if (temp > max) max = temp;
            temp = 1;
        }
        
        return max;
    }
    
    void testLengthOfLIS() {
        vector<int> t = {10,9,2,5,3,7,101,18};
        cout << lengthOfLIS(t) << endl;
    }
    
    // 150
    int evalRPN(vector<string> &tokens) {
        stack<int> st;
        int a, b;
        for (string s: tokens) {
            if (s == "+") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(a + b);
            } else if (s == "-") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(a - b);
            } else if (s == "/") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(a / b);
            } else if (s == "*") {
                a = st.top();
                st.pop();
                b = st.top();
                st.pop();
                st.push(a * b);
            } else {
                st.push(atoi(s.c_str()));
            }
        }
        return st.top();
    }
    
    void testEvalRPN() {
        vector<string> rpn = {"2", "1", "+", "3", "*"};
        cout << evalRPN(rpn) << endl;
    }
    
    // 56
    
    static bool merge56Helper(vector<int> &a, vector<int> &b) {
        if (a[0] == b[0]) return a[1] < b[1];
        else return a[0] < b[0];
    }
    vector<vector<int> > merge56(vector<vector<int> > &intervals) {
        int start = -1, end = -1;
        sort(intervals.begin(), intervals.end(), merge56Helper);
        vector<vector<int> > r;
        for (vector<int> &it: intervals) {
            if (start == -1) {
                start = it[0];
                end = it[1];
            } else {
                if (it[0] > end) {
                    vector<int> temp = {start, end};
                    r.push_back(temp);
                    start = it[0];
                }
                if (it[1] > end) end = it[1];
            }
        }
        
        if (start != -1) {
            vector<int> temp = {start, end};
            r.push_back(temp);
        }
        
        return r;
    }
    
    void testMerge56() {
        vector<vector<int> > arr = {
            {1, 4},
            {0, 0}
        };
        
        vector<vector<int> > r = merge56(arr);
        for (vector<int>& t: r) {
            cout << t[0] << "-" << t[1] << endl;
        }
    }
    
    // 98 (review**)
    bool isValidBST(TreeNode * root) {
        return isValidBSTHelper(root, NULL, NULL);
        
    }
    
    bool isValidBSTHelper(TreeNode * node, int * lower, int * upper) {
        if (node == NULL) return true;
        int val = node->val;
        
        if (lower != NULL && val <= (*lower)) return false;
        if (upper != NULL && val >= (*upper)) return false;
        
        if (!isValidBSTHelper(node->right, &val, upper)) return false;
        if (!isValidBSTHelper(node->left, lower, &val)) return false;
        
        return true;
    }
    
    // 279(review)
    
    int numSquares(int n) {
        if (n <= 0) {
            return 0;
        }
        
        vector<int> cntPerfectSquares(n + 1, INT_MAX);
        cntPerfectSquares[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                cntPerfectSquares[i] = min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
            }
        }
        
        return cntPerfectSquares.back();
    }
    
    void testNumSquares() {
        int n = 12;
        cout << numSquares(n) << endl;
    }
    
    // 3
    int lenghtOfLongestSubstring(string s) {
        map<char, int> mt;
        int start = 0, i;
        int maxLength = 0;
        int size = (int) s.size();
        for (i = 0; i < size; i++) {
            char c = s[i];
            if (mt.count(c) > 0) {
                maxLength = (i - start) > maxLength ? i - start : maxLength;
                start = mt[c] + 1 > start ? mt[c] + 1 : start;
            }
            mt[c] = i;
        }
        
        if (i - start > maxLength) maxLength = i - start;
        
        return maxLength;
    }
    
    void testLengthOfLongestSubstring() {
        string s = "abba";
        cout << lenghtOfLongestSubstring(s) << endl;
    }
    
    // 11 (review**)
    int maxArea(vector<int> &height) {
        int i = 0, j;
        int size = (int) height.size();
        j = size - 1;
        int max = 0;
        int h, area;
        while (i < j) {
            if (height[i] < height[j]) {
                h = height[i];
                i++;
            } else {
                h = height[j];
                j--;
            }
            
            area = (j - i + 1) * h;
            if (area > max) max = area;
        }
        
        return max;
        
    }
    
    void testMaxArea() {
        vector<int> v = {1,8,6,2,5,4,8,3,7};
        cout << maxArea(v) << endl;
    }
    
    // 49 (review**)
    vector<vector<string> > groupAnagrams(vector<string> &strs) {
        vector<vector<string> > r;
        map<string, vector<string> > m;
        for (string &s: strs) {
            string orignStr(s);
            sort(s.begin(), s.end());
            if (m.count(s)) {
                m[s].push_back(orignStr);
            } else {
                vector<string> temp = {orignStr};
                m[s] = temp;
            }
        }
        
        for (pair<string, vector<string> > p : m) {
            r.push_back(p.second);
        }
        
        return r;
        
    }
    
    void testGroupAnagrams() {
        vector<string> s = {"eat", "tea", "tan", "ate", "nat", "bat"};
        vector<vector<string> > r = groupAnagrams(s);
        for (vector<string> &its: r) {
            for (string &s: its) {
                cout << s << endl;
            }
        }
    }
    
    // 23
    ListNode * mergeKLists(vector<ListNode *> &lists) {
        int size = (int) lists.size();
        if (size == 0) return NULL;
        ListNode * list = lists[0];
        for (int i = 1; i < size; i++) {
            ListNode * ml = lists[i];
            ListNode * temp = list;
            while (ml != NULL) {
                ListNode * next = ml->next;
                if (temp == NULL) {
                    list = ml;
                    break;
                } else if (temp->val > ml->val) {
                    ml->next = temp;
                    list = ml;
                    ml = next;
                    temp = list;
                } else if (temp->next == NULL) {
                    temp->next = ml;
                    break;
                } else if (temp->val <= ml->val && temp->next->val >= ml->val) {
                    ListNode * tn = temp->next;
                    temp->next = ml;
                    ml->next = tn;
                    temp = temp->next;
                    ml = next;
                } else {
                    temp = temp->next;
                }
            }
        }
        return list;
    }
    
    //28 (review**)
    void get_next(string &t, vector<int> &next) {
        int i, j;
        i = 0;
        j = -1;
        next.push_back(-1);
        int size = (int) t.size();
        while (i < size) {
            if (j == -1 || t[i] == t[j]) {
                ++i;
                ++j;
                if (t[i] != t[j]) {
                    next.push_back(j);
                } else {
                    next.push_back(next[j]);
                }
            } else {
                j = next[j];
            }
        }
    }
    
    int strStr(string haystack, string needle) {
        int i = 0, j = 0;
        vector<int> next;
        get_next(needle, next);
        int hl = (int) haystack.size();
        int nl = (int) needle.size();
        while(i < hl && j <nl) {
            if (j == -1 || haystack[i] == needle[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
        }
        
        if (j == nl) return i - nl;
        
        return -1;
    }
    
    void testStrStr() {
        string haystack = "hello";
        string needle = "ll";
        
        cout << strStr(haystack, needle) << endl;
    }
    
    // 454
    int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D) {
        unordered_map<int, int> md;
        int r = 0;
        for (int n: A) {
            for (int m: B) {
                ++md[n + m];
            }
        }
        
        for (int i: C) {
            for (int j: D) {
                auto it = md.find(0 - i -j);
                if (it != md.end()) {
                    r += it->second;
                }
            }
        }
        
        return r;
    }
    
    void testFourSumCount() {
        vector<int> A = {1, 2};
        vector<int> B = {-2, -1};
        vector<int> C = {-1, 2};
        vector<int> D = {0, 2};
        cout << fourSumCount(A, B, C, D) << endl;
    }
    
    // 215
    int findKthLargest(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end(), greater<int>());
        return nums[k - 1];
    }
    
    void testFindKthLargest() {
        vector<int> arr = {3,2,1,5,6,4};
        cout << findKthLargest(arr, 2) << endl;
    }
    
    // 127
    int ladderLength(string &beginWord, string &endWord, vector<string> &wordList) {
        vector<string> v;
        v.push_back(beginWord);
        int count = 1;
        while (!v.empty()) {
            int size = (int) v.size();
            count++;
            for (int i = 0; i < size; i++) {
                string temp = v[i];
                int sl = (int) wordList.size();
                if (sl == 0) return 0;
                vector<string> last;
                for (int j = 0; j < sl; j++) {
                    string sl = wordList[j];
                    if (isOneDiff(temp, sl)) {
                        if (sl == endWord) {
                            return count;
                        }
                        v.push_back(sl);
                    } else {
                        last.push_back(sl);
                    }
                }
                wordList = last;
            }
            v.erase(v.begin(), v.begin() + size);
        }
        return 0;
    }
    
    bool isOneDiff(string &s1, string &s2) {
        int count = 0;
        int size = (int) s1.size();
        for (int i = 0; i < size; i++) {
            if (s1[i] != s2[i]) {
                count++;
            }
            
            if (count > 1) return false;
        }
        
        return count == 1;
    }
    
    void testLadderLength() {
        string beginWord = "a";
        string endWord = "c";
        vector<string> wordList = {"a", "b", "c"};
        cout << ladderLength(beginWord, endWord, wordList) << endl;
    }
    
    // 48
    void rotate(vector<vector<int> > & matrix) {
        int size = (int) matrix.size();
        vector<int> saveRow;
        int i = 0, j;
        int end = size % 2 == 0 ? size / 2 : size / 2 + 1;
        for (i = 0; i < end; i++) {
            for (j = i; j < size - 1 - i; j++) {
                int temp = matrix[i][j];
                int x = j;
                int y = (size - 1) - i;
                while (x != i || y != j) {
                    int tt = matrix[x][y];
                    matrix[x][y] = temp;
                    int tempx = x;
                    x = y;
                    y = (size - 1) - tempx;
                    temp = tt;
                }
                matrix[i][j] = temp;
            }
        }
    }
    
    void testRotate2() {
        vector<vector<int> > v = {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };
        
        vector<vector<int> > v2 = {
            {5, 1, 9,11},
            {2, 4, 8,10},
            {13, 3, 6, 7},
            {15,14,12,16}
        };
        rotate(v2);
        for (vector<int> &vv: v2) {
            for (int i: vv) {
                cout << i << endl;
            }
        }
    }
    
    // 166 (unfinished)
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == INT_MIN) {
            if (denominator == -1) {
                long nn = (long) INT_MAX + 1;
                return to_string(nn);
            } else if (denominator == 1) {
                return to_string(INT_MIN);
            }
        }
        map<long, int> t;
        string r;
        int i = 10;
        long left = (long) abs(numerator % denominator);
        int n = abs(numerator / denominator);
        bool isDot = false;
        bool flag = false;
        int rrr = 0;
        
        if ((numerator >= 0 && denominator >0) || (numerator <= 0 && denominator < 0)) {
            flag = true;
        }
        
        while (left != 0 && t.count(left) == 0) {
            if (rrr > 0 && !isDot) {
                isDot = true;
                r.append(".");
            }
            r.append(to_string(n));
            t[left] = (int) r.size();
            if (!isDot) t[left] += 1;
            n = (long) abs((left * i) / denominator);
            left = abs((left * i) % denominator);
            rrr++;
        }
        
        if (rrr > 0 && !isDot) {
            r.append(".");
        }
        
        r.append(to_string(n));
        
        
        
        
        if (left != 0) {
            r.insert(t[left], "(");
            r.append(")");
        }
        
        if (!flag) {
            r.insert(0, "-");
        }
        
        return r;
    }
    
    void testFractionToDecimal() {
        int numerator = 1, denomintor = 2;
        cout << fractionToDecimal(numerator, denomintor) << endl;
    }
    
    // 73
    void setZeroes(vector<vector<int> > &matrix) {
        int m = (int) matrix.size();
        if (m == 0) return;
        int n = (int) matrix[0].size();
        vector<vector<int> > temp;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    vector<int> t = {i, j};
                    temp.push_back(t);
                }
            }
        }
        
        for (vector<int> &t: temp) {
            for (int i = 0; i < n; i++) matrix[t[0]][i] = 0;
            for (int j = 0; j < m; j++) matrix[j][t[1]] = 0;
        }
    }
    
    // 76 (review)
    string minWindow(string s, string t) {
        int flags = 0, cf = 0;
        unordered_map<char, int> mt;
        unordered_map<char, int> ms;
        int start = 0, end = 0;
        int r = 0, mstart = 0;
        int size = (int) s.size();
        for (char c: t) {
            if (mt.count(c)) {
                mt[c]++;
            } else {
                mt[c] = 1;
                flags++;
            }
        }
        
        while (end < size) {
            char c = s[end];
            if (mt.count(c)) {
                if (ms.count(c)) {
                    ms[c]++;
                } else {
                    ms[c] = 1;
                }
                
                if (ms[c] == mt[c]) {
                    cf++;
                    while (cf == flags) {
                        if (end - start + 1 < r || r == 0) {
                            r = end - start + 1;
                            mstart = start;
                        };
                        char c = s[start];
                        if (mt.count(c)) {
                            ms[c]--;
                            if (ms[c] < mt[c]) {
                                cf--;
                            }
                        }
                        start++;
                    }
                }
            }
            end++;
        }
        
        
        
        return s.substr(mstart, r);
    }
    
    void testMinWindow() {
        string s = "aaaaaaaaaaaabbbbbcdd";
        string t = "abcdd";
        cout << minWindow(s, t) << endl;
    }
    
    // 22
    vector<string> generateParenthesis(int n) {
        vector<string> r;
        string ss(2 * n, ' ');
        generateAll(ss, 0, r);
        return r;
    }
    
    void generateAll(string &t, int pos, vector<string> &result) {
        int size = (int) t.size();
        if (pos == size) {
            if (parenthesisValid(t)) {
                result.push_back(t);
            }
        } else {
            t[pos] = '(';
            generateAll(t, pos + 1, result);
            t[pos] = ')';
            generateAll(t, pos + 1, result);
        }
    }
    
    bool parenthesisValid(string &s) {
        stack<char> st;
        for (char c: s) {
            if (c == '(') {
                st.push(c);
            } else {
                if (st.empty()) return false;
                st.pop();
            }
        }
        
        return st.empty();
    }
    
    void testGenerateParenthesis() {
        int n = 3;
        vector<string> r = generateParenthesis(n);
        for (string &s: r) {
            cout << s << endl;
        }
    }
    
    // 43
    int trap(vector<int> &height) {
        return 1;
    }
    
    void testTrap() {
        vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
        cout << trap(height) << endl;
    }
    
    // 105
    TreeNode * buildTree(vector<int>& preorder, vector<int>& inorder) {
        int size = (int) preorder.size();
        if (size == 0) return NULL;
        TreeNode * root = new TreeNode(preorder[0]);
        int t = buildTreeHelper(preorder[0], inorder);
        
        vector<int> l_inorder(inorder.begin(), inorder.begin() + t);
        vector<int> r_inorder(inorder.begin() + t + 1, inorder.end());
        int ls = (int) l_inorder.size();
        vector<int> l_preorder(preorder.begin() + 1, preorder.begin() + 1 + ls);
        vector<int> r_preorder(preorder.begin() + 1 + ls, preorder.end());
        root->left = buildTree(l_preorder, l_inorder);
        root->right = buildTree(r_preorder, r_inorder);
        
        return root;
        
    }
    
    int buildTreeHelper(int n, vector<int>& v) {
        int size = (int) v.size();
        int i;
        for (i = 0; i < size; i++) {
            if (n == v[i]) break;
        }
        
        return i;
    }
    
    void testBuildTree() {
        vector<int> preorder = {3,9,20,15,7};
        vector<int> inorder = {9,3,15,20,7};
        buildTree(preorder, inorder);
    }
    
    // 15
    vector<vector<int> > threeSum(vector<int> &nums) {
        vector<vector<int> > r;
        int size = (int) nums.size();
        if (size == 0) return r;
        sort(nums.begin(), nums.end());
        for (int i = 0; i <= size/2; i++) {
            if (i == 0 || (i > 0 && nums[i] != nums[i - 1])) {
                int lo = i + 1, hi = size - 1, complement = 0 - nums[i];
                while (lo < hi) {
                    int sum = nums[lo] + nums[hi];
                    if (sum == complement) {
                        r.push_back({nums[i], nums[lo], nums[hi]});
                        while (lo < hi && nums[lo] == nums[lo + 1]) lo++;
                        while (lo < hi && nums[hi] == nums[hi - 1]) hi--;
                        lo++;
                        hi--;
                    } else if (sum < complement) {
                        lo++;
                    } else {
                        hi--;
                    }
                }
            }
            
        }
        
        return r;
    }
    
    void testThreeSum() {
        vector<int> nums = {0,-4,-1,-4,-2,-3,2};
        vector<vector<int> > r = threeSum(nums);
        for (vector<int> &arr: r) {
            for (int n: arr) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    
    // 234
    ListNode * temp234;
    bool isPalindrome(ListNode * head) {
        temp234 = head;
        return isPalindromeHelper234(head);
    }
    
    bool isPalindromeHelper234(ListNode * node) {
        if (node == NULL) return true;
        bool r = isPalindromeHelper234(node->next) && (temp234->val == node->val);
        temp234 = temp234->next;
        return r;
    }
    
    // 10
    bool isMatch(string s, string p) {
        int i = 0, j = 0;
        vector<vector<int> > matchList;
        
        int size = (int) p.size();
        int pos;
        for (pos = size - 1; pos >= 0; pos--) {
            if (p[pos] != '*' && p[pos] != '.') break;
            if (p[pos] == '*') {
                pos--;
            } else if (p[pos] != '.') {
                break;
            }
        }
        cout << pos << endl;
        
        for (int t = 0; t < size; t++) {
            char c = p[t];
            int tt = i;
            
            if (matchList.size() <= tt) {
                vector<int> d(27, -1);
                if (t >= pos) d[26] = 1;
                matchList.push_back(d);
            }
            
            if (t + 1 < size && p[t + 1] == '*') {
                t++;
            } else {
                i++;
            }
            
            
            if (c == '.') {
                for (int temp = 0; temp < 26; temp++) {
                    if (matchList[tt][temp] == -1) matchList[tt][temp] = i;
                }
            } else {
                if (matchList[tt][c - 'a'] != -1) {
                    vector<int> d(matchList[tt].begin(), matchList[tt].end());
                    d[c - 'a'] = i;
                    if (t >= pos) d[26] = 1;
                    matchList.push_back(d);
                    matchList[tt][c - 'a'] = i;
                } else {
                    matchList[tt][c - 'a'] = i;
                }
            }
        }
        
        
        
        for (char c: s) {
            if (j >= matchList.size()) return false;
            j = matchList[j][c - 'a'];
            if (j == -1) return false;
        }
        int ms = (int) matchList.size();
        
        if (j < ms && matchList[j][26] != 1) return false;
        return true;
    }
    
    void testIsMatch() {
//        string s = "aaa";
//        string p = "a*a";
//        string s = "abcc";
//        string p = ".*c";
        
        string s = "aaa";
        string p = "aaaa";
        cout << isMatch(s, p) << endl;
    }
    
    // 4
    double findMedianSortedArray(vector<int> &nums1, vector<int> &nums2) {
        double r;
        int size1 = (int) nums1.size();
        int size2 = (int) nums2.size();
        
        if (size1 == 0) {
            int index = size2/2;
            if (size2 % 2 == 0) {
                return (double) ((nums2[index - 1] + nums2[index]) / 2.0);
            } else {
                return (double) nums2[index];
            }
            
        } else if (size2 == 0) {
            int index = size1/2;
            if (size1 % 2 == 0) {
                return (double) ((nums1[index - 1] + nums1[index]) / 2.0);
            } else {
                return (double) nums1[index];
            }
        }
        
        int size = size1 + size2;
        int nnums = size / 2;
        int i = 0, j = 0;
        for (i = 0; i <= size; i++) {
            j = nnums - i;
            if (j > size2) continue;
            
            bool islm = true, isrm = true;
            
            if (j - 1 >= 0 && i < size1) {
                islm = nums2[j - 1] <= nums1[i];
            }
            
            if (j < size2 && i - 1 > 0) {
                isrm = nums2[j] >= nums1[i - 1];
            }
            
            if (islm && isrm) break;
            
            
        }
        
        int maxLeft, minRight;
        
        if (i > 0 && j > 0) {
            int max1 = nums1[i - 1];
            int max2 = nums2[j - 1];
            maxLeft = (double) max1 > max2 ? max1 : max2;
        } else if (i == 0) {
            maxLeft = (double) nums2[j - 1];
        } else {
            maxLeft = (double) nums1[i - 1];
        }
        
        
        
        if (i < size1 && j < size2) {
            int min1 = nums1[i];
            int min2 = nums2[j];
            minRight = (double) min1 < min2 ? min1 : min2;
        } else if (j == size2) {
            minRight = nums1[i];
        } else {
            minRight = nums2[j];
        }
        
        
        if (size % 2 == 0) {
            r = (double) ((minRight + maxLeft) / 2.0);
        } else {
            r = minRight;
        }
        
        
        return r;
    }
    
    void testFindMedianSortedArray() {
        vector<int> nums1 = {1};
        vector<int> nums2 = {2, 3, 4};
        cout << findMedianSortedArray(nums1, nums2) << endl;
    }
    
    // 49 (review**)
    vector<vector<int> > permute(vector<int> &nums) {
        vector<vector<int> > r;
        vector<int> tempList;
        permuteHelper(r, tempList, nums);
        return r;
    }
    
    void permuteHelper(vector<vector<int> > &r, vector<int> &tempList, vector<int> &nums) {
        if (tempList.size() == nums.size()) {
            r.push_back(tempList);
        } else {
            for (int n: nums) {
                auto p = find(tempList.begin(), tempList.end(), n);
                if (p != tempList.end()) continue;
                tempList.push_back(n);
                permuteHelper(r, tempList, nums);
                tempList.erase(tempList.end() - 1);
            }
        }
    }
    
    void testPermute() {
        vector<int> nums = {1, 2, 3};
        vector<vector<int> > r = permute(nums);
        cout << r.size() << endl;
    }
    
    // 324
    void wiggleSort(vector<int> &nums) {
        int n = (int) nums.size();
        
        // Find a median.
        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        
    }
    
    
    void testWiggleSort() {
        vector<int> arr = {5, 6, 4, 3, 2, 6, 7, 9, 3};
        wiggleSort(arr);
        for (int n: arr) {
            cout << n << endl;
        }
    }
    
    // 1022
    int sum1022;
    int sumRootToLeaf(TreeNode * root) {
        int t = 0;
        sum1022 = 0;
        sumRootToLeafHelper(root, t);
        return sum1022;
    }
    
    void sumRootToLeafHelper(TreeNode * node, int temp) {
        if (node == NULL) return;
        
        temp = (temp << 1) | node->val;
        if (node->left == NULL && node->right == NULL) {
            sum1022 += temp;
            return;
        }
        
        sumRootToLeafHelper(node->left, temp);
        sumRootToLeafHelper(node->right, temp);
    }
    
    // 652(review)
    vector<TreeNode *> r652;
    map<string, int> s652;
    vector<TreeNode *> findDuplicateSubtrees(TreeNode * root) {
        findDuplicateSubtreesHelper(root);
        return r652;
    }
    
    string findDuplicateSubtreesHelper(TreeNode * node) {
        if (node == NULL) {
            return "#";
        }
        
        string temp = to_string(node->val) + "," + findDuplicateSubtreesHelper(node->left) + "," + findDuplicateSubtreesHelper(node->right);
        if (s652.count(temp) == 0) {
            s652[temp] = 1;
        } else {
            s652[temp]++;
        }
        
        if (s652[temp] == 2) {
            r652.push_back(node);
        }
        
        return temp;
    }
    
    // 152 (review**)
    int maxProduct2(vector<int> &nums){
        int r = nums[0];
        int size = (int) nums.size();
        int i, imin, imax;
        
        for (i = 1, imin = nums[0], imax = nums[0]; i < size; i++) {
            if (nums[i] < 0) {
                int t = imin;
                imin = imax;
                imax = t;
                
            }
            
            imax = max(nums[i], imax * nums[i]);
            imin = min(nums[i], imin * nums[i]);
            
            r = max(r, imax);
        }
        
        return r;
        
    }
    
    void testMaxProduct2() {
        vector<int> nums = {2, 3, -2, 4};
        cout << maxProduct2(nums) << endl;
    }
    
    // 953
    bool isAlienSorted(vector<string> &words, string order) {
        int i = 0, prev = -1;
        int size = (int) words.size();
        unordered_map<char, int> m;
        for (char c: order) {
            m[c] = i;
            i++;
        }
        
        
        for (int j = 0; j < size; j++) {
            string word = words[j];
            int t = m[word[0]];
            if (prev == -1) {
                prev = t;
            } else {
                if (prev > t) {
                    return false;
                } else if (prev == t) {
                    string prevWord = words[j - 1];
                    int x;
                    int pl = (int) prevWord.size();
                    int cl = (int) word.size();
                    int l = pl < cl ? pl : cl;
                    int pn, cn;
                    for (x = 1; x < l; x++) {
                        pn = m[prevWord[x]];
                        cn = m[word[x]];
                        if (pn == cn) continue;
                        if (pn > cn) return false;
                        else break;
                    }
                    if (x == l) {
                        if (pl > cl) return false;
                    }
                }
                prev = t;
            }
        }
        
        
        return true;
    }
    
    void testIsAlienSorted() {
        vector<string> words = {"zirqhpfscx","zrmvtxgelh","vokopzrtc","nugfyso","rzdmvyf","vhvqzkfqis","dvbkppw","ttfwryy","dodpbbkp","akycwwcdog"};
        string order = "khjzlicrmunogwbpqdetasyfvx";
        cout << isAlienSorted(words, order) << endl;
    }
    
    // 1171
    ListNode * removeZeroSumSublists(ListNode * head) {
        vector<int> sums;
        vector<ListNode *> nodes;
        ListNode * node = head;
        int sum = 0;
        while (node != NULL) {
            sum += node->val;
            bool isZero = false;
            
            if (sum == 0) {
                sums.clear();
                nodes.clear();
                head = node->next;
                isZero = true;
            } else {
                int size = (int) sums.size();
                for (int i = 0; i < size; i++) {
                    int tempSum = sums[i];
                    if (sum - tempSum == 0) {
                        sums.erase(sums.begin() + i + 1, sums.end());
                        nodes.erase(nodes.begin() + i + 1, nodes.end());
                        nodes[i]->next = node->next;
                        sum = sums[i];
                        isZero = true;
                        break;
                    }
                }
            }
            
            if (!isZero) {
                sums.push_back(sum);
                nodes.push_back(node);
            }
            node = node->next;
        }
        
        return head;
    }
    
    void testRemoveZeroSumSublists() {
        vector<int> v = {1,2,3,-3,4};
        ListNode * t = constructLink(v);
        ListNode * r = removeZeroSumSublists(t);
        while (r != NULL) {
            cout << r->val << endl;
            r = r->next;
        }
    }
    
    // 5 review
    string longestPalindrome(string s) {
        int size = (int) s.size();
        if (size <= 1) return s;
        vector<bool> bl(size, false);
        vector<vector<bool> > v(size, bl);
        int maxLen = 1, start = 0;
        
        for (int i = size - 1; i >= 0; i--) {
            for (int j = i; j < size; j++) {
                v[i][j] = s[i] == s[j] && ((j - i < 3) || v[i + 1][ j - 1]);
                
                if (v[i][j]) {
                    if (j - i + 1 > maxLen) {
                        maxLen = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        
        return s.substr(start, maxLen);
    }
    
    void testLongestPalindrome() {
        string s = "cbbd";
        cout << longestPalindrome(s) << endl;
    }
    
    // 875 (review for mid)
    int minEatingSpeed(vector<int> &piles, int H) {
        int low = 1;
        int high = 0;
        for (int n: piles) {
            if (n > high) high = n;
        }
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int time = 0;
            for (int n: piles) {
                float temp = (float) n / mid;
                time += ceil(temp);
            }
            
            if (time <= H) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return low;
    }
    
    void testMinEatingSpeed() {
        vector<int> piles = {312884470};
        int H = 968709470;
        cout << minEatingSpeed(piles, H) << endl;
    }
    
    // 746
    int minCostClimbingStairs(vector<int> &cost) {
        int size = (int) cost.size();
        vector<int> accumulateCost(size + 1, 0);
        for (int i = 2; i <= size ; i++) {
            int t1 = accumulateCost[i - 2] + cost[i - 2];
            int t2 = accumulateCost[i - 1] + cost[i - 1];
            accumulateCost[i] = t1 < t2 ? t1 : t2;
        }
        return accumulateCost[size];
    }
    
    void testMinCostClimbingStairs() {
        vector<int> t = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
        cout << minCostClimbingStairs(t) << endl;
    }
    
    // 90
    vector<vector<int> > subsetsWithDup(vector<int> &nums) {
        vector<vector<int> > r = {{}};
        int size = (int) nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < size;) {
            int count = 1;
            while (i + count < size && nums[i] == nums[i + count]) count++;
            
            int nz = (int) r.size();
            for (int j = 0; j < nz; j++) {
                vector<int> ins = r[j];
                for (int z = 0; z < count; z++) {
                    ins.push_back(nums[i]);
                    r.push_back(ins);
                }
            }
            i = i + count;
        }
        
        return r;
    }
    
    
    void testsubsetsWithDup() {
        vector<int> nums = {2, 2, 1};
        vector<vector<int> > r = subsetsWithDup(nums);
        for (vector<int> &arr: r) {
            for (int n: arr) {
                cout << n << ", ";
            }
            cout << endl;
        }
    }
    
    // leetcode 145
    vector<int> postorderTraversal(TreeNode * root) {
        vector<int> r;
        postorderTraversalHelper(root, r);
        return r;
    }
    
    void postorderTraversalHelper(TreeNode * node, vector<int> &arr) {
        if (node == NULL) return;
        postorderTraversalHelper(node->left, arr);
        postorderTraversalHelper(node->right, arr);
        arr.push_back(node->val);
    }
    
    // 976
    int largestPerimeter(vector<int> &A) {
        int size = (int) A.size();
        largestPerimeterHelper(A, 0, size - 1);
        for (int i = size - 1; i >= 2; i--) {
            if (A[i - 1] + A[i - 2] > A[i]) return A[i - 1] + A[i - 2] + A[i];
        }
        for (int n: A) {
            cout << n << endl;
        }
        return 0;
    }
    
    void largestPerimeterHelper(vector<int> &A, int s, int e) {
        while (s <= e) {
            int p = largestPerimeterHelperHelper(A, s, e);
            largestPerimeterHelper(A, s, p - 1);
            s = p + 1;
        }
        
    }
    
    int largestPerimeterHelperHelper(vector<int> &A, int low, int high) {
        int t = A[low];
        while (low < high) {
            while (high > low && A[high] >= t) {
                high--;
            }
            
            A[low] = A[high];
            
            while (low < high && A[low] < t) {
                low++;
            }
            
            A[high] = A[low];
        }
        
        A[low] = t;
        
        return low;
    }
    
    void testLargestPerimeter() {
        vector<int> A = {3,6,2,3};
        cout << largestPerimeter(A) << endl;
    }
    
    //979 (review)
    int dc979;
    int distributeCoins(TreeNode * root) {
        dc979 = 0;
        distributeCoinsHelper(root);
        return dc979;
    }
    
    int distributeCoinsHelper(TreeNode * node) {
        if (node == NULL) return 0;
        int L = distributeCoinsHelper(node->left);
        int R = distributeCoinsHelper(node->right);
        dc979 = abs(L) + abs(R);
        return node->val + L + R -1;
    }
    
    // 130
    int rowSize130;
    int colSize130;
    void solve(vector<vector<char> > &board) {
        rowSize130 = (int) board.size();
        if (rowSize130 == 0) return;
        colSize130 = (int) board[0].size();
        set<string> s;
        
        for (int i = 0; i < colSize130; i++) {
            solveHelper(0, i, board, s);
            solveHelper(rowSize130 - 1, i, board, s);
        }
        
        for (int j = 0; j < rowSize130; j++) {
            solveHelper(j, 0, board, s);
            solveHelper(j, colSize130 - 1, board, s);
        }
        
        for (int i = 0; i < rowSize130; i++) {
            for (int j = 0; j < colSize130; j++) {
                if (board[i][j] == 'O') {
                    string key = to_string(i);
                    key.append("+");
                    key.append(to_string(j));
                    if (s.count(key) != 1) {
                        board[i][j] = 'X';
                    }
                }
            }
        }
        
        
    }
    
    void solveHelper(int x, int y, vector<vector<char> > &board, set<string> &s) {
        if (board[x][y] != 'O') return;
        string temp = to_string(x);
        temp.append("+");
        temp.append(to_string(y));
        if (s.count(temp) == 1) return;
        s.insert(temp);
        if (x - 1 >= 0) solveHelper(x - 1, y, board, s);
        if (x + 1 < rowSize130) solveHelper(x + 1, y, board, s);
        if (y - 1 >= 0) solveHelper(x, y - 1, board, s);
        if (y + 1 < colSize130) solveHelper(x, y + 1, board, s);
    }
    
    void testSolve() {
        vector<vector<char> > c = {};
        
        solve(c);
        
        for (vector<char> &v: c) {
            for (char cc: v) {
                cout << cc << ",";
            }
            cout << endl;
        }
    }
    
    // 1008
    TreeNode * bstFromPreorder(vector<int> & preorder) {
        int size = (int) preorder.size();
        vector<TreeNode *> nodes;
        TreeNode * root;
        for (int i = 0; i < size; i++) {
            TreeNode * temp = new TreeNode(preorder[i]);
            if (i == 0) {
                root = temp;
            } else if (preorder[i] < preorder[i - 1]) {
                nodes[i - 1]->left = temp;
            } else {
                int t = i - 1;
                while (t >= 0 && preorder[i] > preorder[t]) {
                    t--;
                }
                
                TreeNode * tnode = nodes[t + 1];
                while (tnode->right != NULL) {
                    tnode = tnode->right;
                }
                tnode->right = temp;
            }
            
            nodes.push_back(temp);
        }
        
        return root;
    }
    
    void testBstFromPreorder() {
        vector<int> r = {4,5,14,20};
        TreeNode * tree = bstFromPreorder(r);
        cout << tree->val << endl;
    }
    
    // 118
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > r;
        for (int i = 1; i <= numRows; i++) {
            vector<int> temp;
            for (int t = 0; t < i; t++) {
                if (t == 0 || t == i - 1) {
                    temp.push_back(1);
                } else {
                    int sum = r[i - 2][t - 1] + r[i - 2][t];
                    temp.push_back(sum);
                }
            }
            
            r.push_back(temp);
        }
        return r;
    }
    
    void testGenerate() {
        vector<vector<int> > r = generate(5);
        for (vector<int> &row: r) {
            for (int n: row) {
                cout << n << ",";
            }
            cout << endl;
        }
    }
    
    // 36 (review**)
    bool isValidSudoku(vector<vector<char> > &board) {
        int row[9][9] = {0}, col[9][9]={0}, mt[9][9]= {0};
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char t = board[i][j];
                if (t == '.') continue;
                int num = t - '0' - 1;
                int k = (i/3) * 3 + (j/3);
                if (row[i][num] || col[j][num] || mt[k][num]) return false;
                row[i][num] = col[j][num] = mt[k][num] = 1;
            }
        }
        
        return true;
    }
    
    void testIsValidSudoku() {
        vector<vector<char> > tt = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };
        cout << isValidSudoku(tt) << endl;
    }
    
    
    // 61
    ListNode * rotateRight(ListNode * head, int k) {
        ListNode * node = head;
        if (node == NULL) return node;
        vector<ListNode *> v;
        while (node != NULL) {
            v.push_back(node);
            node = node->next;
        }
        int size = (int) v.size();
        int changeTime = k % size;
        
        while (changeTime > 0) {
            ListNode * temp = v.back();
            temp->next = head;
            head = temp;
            changeTime--;
            v.pop_back();
        }
        
        v.back()->next = NULL;
        return head;
    }
    
    void testRotateRight() {
        vector<int> v = {1, 2, 3, 4, 5};
        ListNode * head = constructLink(v);
        ListNode * r = rotateRight(head, 2);
        ListNode * node = r;
        while (node != NULL) {
            cout << node->val << endl;
            node = node->next;
        }
    }
    
    // 534
    int findPairs(vector<int> &nums, int k) {
        int size = (int) nums.size();
        map<int, int> m;
        int r = 0;
        for (int i = 0; i < size; i++) {
            int t = nums[i];
            if (m.count(t) > 0) {
                m[t] += 1;
            } else {
                m[t] = 1;
            }
        }
        
        for (pair<const int, int> &item : m) {
            if (k == 0) {
                if (item.second >= 2) r++;
            } else {
                if (m.count(item.first + k)) {
                    r++;
                }
            }
        }
        return r;
    }
    
    void testFindPairs() {
        vector<int> r = {1, 2, 3, 4, 5};
        cout << findPairs(r, -1) << endl;
    }
    
    // 17 (review**)
    vector<string> letterCombinations(string digits) {
        vector<string> r;
        map<char, string> m {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
        r = letterCombinationHelper(digits, m);
        return r;
    }
    
    vector<string> letterCombinationHelper(string digits, map<char, string> &m) {
        vector<string> r;
        if (digits.empty()) return r;
        string temp = m[digits[0]];
        string nextDigit = digits.substr(1);
        vector<string> back = letterCombinationHelper(nextDigit, m);
        
        if (back.empty()) {
            for (char c: temp) {
                string t(1, c);
                r.push_back(t);
            }
        } else {
            for (char c: temp) {
                for (string s: back) {
                    s.insert(0, 1, c);
                    r.push_back(s);
                }
            }
        }
        
        return r;
    }
    
    
    
    void testLetterCombinations() {
        string digit = "23";
        vector<string> r = letterCombinations(digit);
        for (string t: r) {
            cout << t << endl;
        }
    }
    
    // 29(review**)
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        
        int flag = dividend > 0 ^ divisor > 0 ? -1 : 1;
        long dvd = labs(dividend), dor = labs(divisor), ans = 0;
        
        while (dvd >= dor) {
            long temp = dor, m = 1;
            while (temp << 1 <= dvd) {
                temp <<= 1;
                m += 1;
            }
            
            dvd -= temp;
            ans += m;
        }
        
        return flag * ans;
    }
    
    void testDivide() {
        cout << divide(-2147483648, -1) << endl;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif /* Solution_hpp */
