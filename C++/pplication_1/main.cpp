/* 
 * File:   main.cpp
 * Author: jasonleakey
 *
 * Created on February 12, 2010, 12:11 AM
 */

#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> av(10);
    for (int i = 0; i != 9; i++)
    {
        av.push_back(9);
        cout << "9" << endl;
    }
    return (EXIT_SUCCESS);
}

