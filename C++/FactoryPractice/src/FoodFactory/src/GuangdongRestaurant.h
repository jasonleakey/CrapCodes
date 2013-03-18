/*
 * @(#)GuangdongRestaurant.h   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



#ifndef GUANGDONGRESTAURANT_H
#define GUANGDONGRESTAURANT_H

#include "Restaurant.h"
#include "QingZhengFish.h"
#include "LiangBanCabbage.h"
#include <string>

/*
 * class GuangdongRestaurant
 *
 */
class GuangdongRestaurant:
    public Restaurant
{
    public:

        // Constructors/Destructors
        //

        /*
         * Empty Constructor
         */
        GuangdongRestaurant();

        /*
         * Empty Destructor
         */
        virtual ~GuangdongRestaurant();

        // Static Public attributes
        //
        // Public attributes
        //
        // Public attribute accessor methods
        //
        // Public attribute accessor methods
        //

        /*
         * @return Fish
         */
        Fish * cookFish()
        {
            return new QingZhengFish();
        }

        /*
         * @return Cabbage
         */
        Cabbage * cookCabbage()
        {
            return new LiangBanCabbage();
        }

    protected:

        // Static Protected attributes
        //
        // Protected attributes
        //

    public:

        // Protected attribute accessor methods
        //

    protected:

    public:

        // Protected attribute accessor methods
        //

    protected:

    private:

        // Static Private attributes
        //
        // Private attributes
        //

    public:

        // Private attribute accessor methods
        //

    private:

    public:

        // Private attribute accessor methods
        //

    private:
};
#endif // GUANGDONGRESTAURANT_H


//~ Formatted by Jindent --- http://www.jindent.com
