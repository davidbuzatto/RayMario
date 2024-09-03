/**
 * @file Drawable.h
 * @author Prof. Dr. David Buzatto
 * @brief Abstract class that models the behavior of drawable components.
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

class Drawable {

public:
    virtual ~Drawable() = default;
    virtual void draw() = 0;

};