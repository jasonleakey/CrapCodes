/*
 * @(#)GUIFactory.cpp   
 * 12/04/06
 * 
 * Copyright (c) 2012 Jason Huang
 *
 * This program is released under BSD license.
 *
 */



/*
 * GUIFactory.cpp, 用工厂方法生产的Button。
 *
 *  Created on: 4 Apr, 2012
 *      Author: jasonleakey
 */

#include <iostream>

using namespace std;

/*
 * !
 * 按钮基类，作为Abstract product
 */
class Button
{
    public:
        virtual void paint() = 0;

        virtual ~Button()
        {
        }
};


/*
 * !
 * Win风格按钮，Concrete product 1
 */
class WinButton:
    public Button
{
    public:
        void paint()
        {
            cout << "我是WinButton." << endl;
        }
};


/*
 * !
 * Mac风格按钮，Concrete product 2
 */
class MacButton:
    public Button
{
    public:
        void paint()
        {
            cout << "我是MacButton" << endl;
        }

    private:
};


/*
 * !
 * 按钮工厂，Abstract Factory
 */
class GUIFactory
{
    public:
        virtual Button * createButton() = 0;

        virtual ~GUIFactory()
        {
        }
};


/*
 * !
 * Win风格按钮工厂，Concrete Factory 1
 */
class WinFactory:
    public GUIFactory
{
    public:
        WinButton * createButton()
        {
            return new WinButton();
        }
};


/*
 * !
 * Mac风格按钮工厂，Concrete Factory 2
 */
class MacFactory:
    public GUIFactory
{
    public:
        MacButton * createButton()
        {
            return new MacButton();
        }

    private:
};


/*
 * !
 * Application
 */
class Application
{
    public:
        Application(GUIFactory * factory)
        {
            Button * button = factory -> createButton();

            button -> paint();

            delete button;
            delete factory;
        }
};


GUIFactory * createOsSpecificFactory()
{
    int sys;

    cout << endl << "输入OS(0 - Win, 1 - MAC):";
    cin >> sys;

    if (0 == sys)
    {
        return new WinFactory();
    }
    else
    {
        return new MacFactory();
    }
}

int main(int     argc,
         char ** argv)
{
    Application * newApp = new Application(createOsSpecificFactory());

    delete newApp;

    return 0;
}


//~ Formatted by Jindent --- http://www.jindent.com
