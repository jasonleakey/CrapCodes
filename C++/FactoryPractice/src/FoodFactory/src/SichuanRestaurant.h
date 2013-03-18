/*
 * @(#)SichuanRestaurant.h   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



#ifndef SICHUANRESTAURANT_H
#define SICHUANRESTAURANT_H

#include "Restaurant.h"
#include "ShuiZhuFish.h"
#include "ShousiCabbage.h"
#include <string>

/*
 * class SichuanRestaurant
 *
 */
class SichuanRestaurant:
    virtual public Restaurant
{
    public:

        // Constructors/Destructors
        //

        /*
         * Empty Constructor
         */
        SichuanRestaurant();

        /*
         * Empty Destructor
         */
        virtual ~SichuanRestaurant();

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
            return new ShuiZhuFish();
        }

        /*
         * @return Cabbage
         */
        Cabbage * cookCabbage()
        {
            return new ShousiCabbage();
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
#endif // SICHUANRESTAURANT_H


//~ Formatted by Jindent --- http://www.jindent.com
