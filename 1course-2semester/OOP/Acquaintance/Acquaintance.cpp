﻿#include <iostream>
#include "Cube.h"

using std::cout;
using std::endl;

int main()
{
    Cube c;

    c.setLength(3.48);

    cout << "Here's the object of the class \"Cube\"." << "\n\n";
    cout << "The side length is: " << c.getLenght() << " cm" << endl;
    cout << "The Volume is: " << c.calcVolume() << " cm3;" << " The Surface is: " << c.calcSurface() << " cm2" << endl;
    
    c.setLength(2.14);
    double volume = c.calcVolume();
    double surface = c.calcSurface();

    cout << "\n---------------------------------------------------------------------" << endl;
    cout << "\nHere's the updated object of the class \"Cube\". " << "\n\n";
    cout << "The new side length is: " << c.getLenght() << "cm" << endl;
    cout << "The updated Volume is: " << volume << " cm3;" << " The updated Surface is: " << surface << " cm2" << endl;
    
    system("PAUSE");
    return 0;
}

