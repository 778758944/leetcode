//
//  Test.hpp
//  leetcode
//
//  Created by WENTAO XING on 2018/11/28.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#ifndef Test_hpp
#define Test_hpp

#include <iostream>
#include <set>
using namespace std;

struct Point {
    int x;
    int y;
    Point(int _x, int _y): x(_x), y(_y) {};
};

class Test {
    public:
        void testSet() {
            Point p = Point(1, 2);
            cout << p.x << p.y << endl;
            set<Point> s;
            s.insert(Point(1, 2));
        }
};

#endif /* Test_hpp */
