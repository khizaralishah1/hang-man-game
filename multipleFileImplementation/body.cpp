#include "body.h"
#include <iostream>
using namespace std;

Body::Body()
{
    bodyParts[0] = 'O';
    bodyParts[1] = '/';
    bodyParts[2] = '|';
    bodyParts[3] = '\\';
    bodyParts[4] = '|';
    bodyParts[5] = '/';
    bodyParts[6] = '|';
    bodyParts[7] = '\\';

    partNumber = 7; // to keep track of which part to remove (from leg to the head)
}

void Body::spaces(int n)
{
    for(int i=0; i<n; i++)
        cout << " ";
}

void Body::draw()
{
    cout << "\n\n\n\n";
    spaces(51);
    cout << bodyParts[0] << endl;
    spaces(50);
    cout << bodyParts[1] << bodyParts[2] << bodyParts[3] << endl;
    spaces(51);
    cout << bodyParts[4] << endl;
    spaces(50);
    cout << bodyParts[5] << bodyParts[6] << bodyParts[7] << endl;
}

void Body::takeBodyPart()
{
    bodyParts[partNumber] = ' ';
    partNumber--;
}