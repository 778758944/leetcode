//
//  sortTest.cpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/22.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#include "sortTest.hpp"
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Item;

class CustomLess {
public:
    bool operator() (int a, int b) {
        return a < b;
    }
};

bool compItem(const Item &a, const Item &b) {
    return a.second > b.second;
}

bool compInt(int a, int b) {
    return a > b;
}

int main() {
    array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    // default acceding
    sort(s.begin(), s.end());
    for (int a : s) {
        cout << a << " ";
    }
    
    cout << '\n';
    
    //using standard library
    sort(s.begin(), s.end(), greater<int>());
    
    for (int a : s) {
        cout << a << " ";
    }
    
    cout << '\n';
    
    // using a custom function object
    CustomLess comp;
    
    sort(s.begin(), s.end(), comp);
    
    for (int a : s) {
        cout << a << " ";
    }
    
    cout << '\n';
    
    // using lambda express
    sort(s.begin(), s.end(), [] (int a, int b) {return a > b;});
    
    for (int a : s) {
        cout << a << " ";
    }
    
    cout << '\n';
    
    
    map<int, int> m;
    m[1] = 3;
    m[2] = 5;
    m[3] = 7;
    
    vector<Item> r;
    
    vector<int> r2;
    r2.push_back(4);
    r2.push_back(3);
    r2.push_back(2);
    r2.push_back(1);
    
    for (Item item: m) {
//        Item * temp = &item;
//        cout << (&item)->first << "=" << (&item)->second << endl;
        r.push_back(make_pair(item.first, item.second));
    }
    
    cout << r[0].first << endl;
    cout << r[1].first << endl;
    cout << r[2].first << endl;
    
//    for (Item * item: r) {
//        cout << item->first << "=" << item->second << endl;
//    }
    
    sort(r2.begin(), r2.end(), compInt);
    sort(r.begin(), r.end(), compItem);
    
    for (Item a: r) {
        cout << a.first << " ";
    }
    
    cout << '\n';
    
    vector<int> ss = {1, 2, 3};
    
    for (int a: ss) {
        cout << a << endl;
    }
    
    vector<int> sss(ss.end(), ss.end());
    
    cout << "sss.size = " << sss.size() << endl;
    
    for (int b : sss) {
        cout << b << endl;
    }
    
    
    
    
    
    
    return 0;
}
