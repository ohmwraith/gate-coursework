#pragma once
#include "Car.h"
ref class Card :
    public Car
{
protected:
public:
    delegate void CardEventHandler();
    delegate void CardCreateHandler(int num);
    static event CardCreateHandler^ CREATE;
    Card(int number, int color, int spd, int dir) : Car(number, color, spd, dir) {
        CREATE(number);
    }
};

