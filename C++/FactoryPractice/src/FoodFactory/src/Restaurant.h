/*
 * @(#)Restaurant.h   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "Fish.h"
#include "Cabbage.h"

/*
 * class Restaurant
 *
 */
class Restaurant
{
    public:

        // Public attribute accessor methods
        //
        // Public attribute accessor methods
        //

        /*
         * @return Fish
         */
        virtual Fish * cookFish() = 0;

        /*
         * @return Cabbage
         */
        virtual Cabbage * cookCabbage() = 0;

        virtual ~Restaurant()
        {
        }

        ;

    protected:

    public:

        // Protected attribute accessor methods
        //

    protected:

    public:

        // Protected attribute accessor methods
        //

    protected:

    private:

    public:

        // Private attribute accessor methods
        //

    private:

    public:

        // Private attribute accessor methods
        //

    private:
};
#endif // RESTAURANT_H


//~ Formatted by Jindent --- http://www.jindent.com
