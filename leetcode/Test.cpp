//
//  Test.cpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/28.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#include "Test.hpp"

bool operator < (const Point& p1, const Point& p2) {
    if (p1.x != p2.x) {
        return p1.x < p2.x;
    } else {
        return p1.y < p2.y;
    }
}
