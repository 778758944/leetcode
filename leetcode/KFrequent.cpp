//
//  KFrequent.cpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/22.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#include "KFrequent.hpp"
#include <map>
#include "./Compare.hpp"
#include <functional>
#include <set>
#include <algorithm>

vector<int>
KFrequent::topKFrequent(vector<int> nums, int k) {
    vector<int> result;
    map<int, int> m;
    vector<MapItem> sortv;
    for (auto num : nums) {
        if (!m[num]) {
            m[num] = 1;
        } else {
            m[num] += 1;
        }
    }
    /*
    
    set<MapItem, CompareMapVal> s(m.begin(), m.end());
    int i = 0;
    
    for(MapItem item: s) {
        if (i == k) return result;
        result.push_back(item.first);
        i++;
    }
     */
    
    for (MapItem item: m) {
        sortv.push_back(item);
    }
    
    CompareMapVal comp;
    
    struct {
        bool operator()(MapItem a, MapItem b) const
        {
            return a.second > b.second;
        }
    } customLess;
    
    sort(sortv.begin(), sortv.end(), comp);
    
    
    
    
    
    
    return result;
}
