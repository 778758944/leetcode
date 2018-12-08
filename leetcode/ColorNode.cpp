//
//  ColorNode.cpp
//  leetcode
//
//  Created by WENTAO XING on 2018/12/6.
//  Copyright © 2018 WENTAO XING. All rights reserved.
//

#include "ColorNode.hpp"

unsigned int
ColorNode::getColorIndex(unsigned int r, unsigned int g, unsigned int b, int level) const {
    uint32_t index = 0;
    uint16_t mask = 0x80 >> level;
    
    if (r & mask) index |= 0x4;
    if (g & mask) index |= 0x2;
    if (b & mask) index |= 0x1;
    
    
    return index;
}

void
ColorNode::addColor(uint32_t r, uint32_t g, uint32_t b, int level) {
    if (level > MAX_LEVEL) {
        
    }
}

