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
    Card(int number, int color, int spd, int HEIGHT) : Car(number, color, spd, HEIGHT) {
        CREATE(number);
    }
};

