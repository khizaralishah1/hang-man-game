#ifndef BODY_H
#define BODY_H

class Body
{
    private:
        char bodyParts[8];
        int partNumber;
        void spaces(int); // draws n number of spaces (utility function)
    public:
        Body();
        void draw();
        void takeBodyPart(); //removes a body part

};

#endif