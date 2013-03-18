/*
 * @(#)main.cpp   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



/*
 * main.cpp
 *
 *  Created on: 4 Apr, 2012
 *      Author: jasonleakey
 */

#include "Client.h"

int main(int     argc,
         char ** argv)
{
    Client * cli = new Client();

    cli -> eat();

    delete cli;

    return 0;
}


//~ Formatted by Jindent --- http://www.jindent.com
