//
//  ColorNode.hpp
//  leetcode
//
//  Created by WENTAO XING on 2018/12/6.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#ifndef ColorNode_hpp
#define ColorNode_hpp
#include <vector>
#define MAX_LEVEL 7

class ColorNode {
    public:
        ColorNode(unsigned int r, unsigned int g, unsigned int b, int level): _r(r), _g(g), _b(b) {
            _pixelCount = 0;
            _paletteIndex = 0;
            _reducerNode = NULL;
        }
        unsigned int getColorIndex(unsigned int r, unsigned int g, unsigned int b, int level) const;
        void addColor(uint32_t r, uint32_t g, uint32_t b, int level);
    
    private:
        unsigned int _r;
        unsigned int _g;
        unsigned int _b;
        std::vector<ColorNode *> children;
        ColorNode * _reducerNode;
        unsigned long _pixelCount;
        unsigned long _paletteIndex;
};

#endif /* ColorNode_hpp */
