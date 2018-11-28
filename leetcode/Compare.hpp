//
//  Compare.hpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/22.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#ifndef Compare_hpp
#define Compare_hpp

#include <iostream>
#include <utility>
typedef std::pair<int, int> MapItem;

//bool comp(MapItem item1, MapItem item2) {
//    return item1.second >= item2.second;
//}

class CompareMapVal {
public:
    bool operator() (MapItem m1, MapItem m2) {
        if (m1.second == m2.second) return true;
        return m1.second > m2.second;
    }
};

#endif /* Compare_hpp */
