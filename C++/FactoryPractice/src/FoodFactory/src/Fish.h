/*
 * @(#)Fish.h   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



#ifndef FISH_H
#define FISH_H

#include <string>

using namespace std;

/*
 * class Fish
 *
 */
class Fish
{
    public:

        // Constructors/Destructors
        //

        /*
         * Empty Constructor
         */
        Fish();

        /*
         * Empty Destructor
         */
        virtual ~Fish();

        virtual string DishName() = 0;
};
#endif // FISH_H


//~ Formatted by Jindent --- http://www.jindent.com
