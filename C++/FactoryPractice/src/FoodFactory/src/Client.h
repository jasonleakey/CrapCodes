/*
 * @(#)Client.h   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "Cabbage.h"
#include "Fish.h"
#include "Restaurant.h"
#include "GuangdongRestaurant.h"
#include "SichuanRestaurant.h"
#include <iostream>

using namespace std;

/*
 * class Client
 *
 */
class Client
{
    public:

        // Constructors/Destructors
        //

        /*
         * Empty Constructor
         */
        Client()
        {
        }

        ;

        /*
         * Empty Destructor
         */
        virtual ~Client()
        {
        }

        ;

        // Static Public attributes
        //
        // Public attributes
        //
        // Public attribute accessor methods
        //
        // Public attribute accessor methods
        //

        /*
         */
        void eat()
        {
            Restaurant * restaurant = new SichuanRestaurant();
            Fish *       cabb       = restaurant -> cookFish();

            cout << "我把" << cabb -> DishName() << "吃了！" << endl;

            delete cabb;
            delete restaurant;
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
#endif // CLIENT_H


//~ Formatted by Jindent --- http://www.jindent.com
