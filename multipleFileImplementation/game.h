#ifndef GAME_H
#define GAME_H

#include "body.h"
#include <iostream>
using namespace std;

class Game
{
    private:
        static int totalCountries;
        int chosenCountryIndex;
        int chosenCountrySize;
        char mistakeBox[8];
        int mistakeBoxLastIndex;
        int runTime;
        int mistakes;
        char userChoice;
        Body human;
        
        //utility functions
        int checks(char*);
        void welcome();
        void initializeAnswersArray(char*);
        void previousData();
        char getUserChoice();
        int matchLetter(char*);
        void showUserAnswersArray(char*);
    public:
        Game(Body h);
        void run();
        void results();
        
};

#endif
