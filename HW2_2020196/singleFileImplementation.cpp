#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

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
        
        //utility functions
        int checks(char*);
        void welcome();
        void initializeAnswersArray(char*);
        void previousData();
        char getUserChoice();
        int matchLetter(char*);
        void showUserAnswersArray(char*);
    public:
        Game();
        void run();
        void results();     
};

int main()
{
    srand(time(NULL));
    Game g;
    g.run();
    g.results();

    return 0;
}

string countries[] = 
{
    "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antigua & Deps", "Argentina", "Armenia", "Australia", "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", 
    "Barbados", "Belarus", "Belgium", "Belize", "Benin", "Bhutan", "Bolivia", "Bosnia Herzegovina", "Botswana", "Brazil", "Brunei", "Bulgaria", "Burkina", "Burundi", "Cambodia", 
    "Cameroon", "Canada", "Cape Verde", "Central African Rep", "Chad", "Chile", "China", "Colombia", "Comoros", "Congo", "Congo", "Costa Rica", "Croatia", "Cuba", 
    "Cyprus", "Czech Republic", "Denmark", "Djibouti", "Dominica", "Dominican Republic", "East Timor", "Ecuador", "Egypt", "El Salvador", "Equatorial Guinea", "Eritrea", "Estonia", 
    "Ethiopia", "Fiji", "Finland", "France", "Gabon", "Gambia", "Georgia", "Germany", "Ghana", "Greece", "Grenada", "Guatemala", "Guinea", "Guinea-Bissau", "Guyana", "Haiti", "Honduras", 
    "Hungary", "Iceland", "India", "Indonesia", "Iran", "Iraq", "Ireland {Republic}", "Israel", "Italy", "Ivory Coast", "Jamaica", "Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati", 
    "Korea North", "Korea South", "Kosovo", "Kuwait", "Kyrgyzstan", "Laos", "Latvia", "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg", "Macedonia", 
    "Madagascar", "Malawi", "Malaysia", "Maldives", "Mali", "Malta", "Marshall Islands", "Mauritania", "Mauritius", "Mexico", "Micronesia", "Moldova", "Monaco", "Mongolia", "Montenegro", 
    "Morocco", "Mozambique", "Myanmar", "Burma", "Namibia", "Nauru", "Nepal", "Netherlands", "New Zealand", "Nicaragua", "Niger", "Nigeria", "Norway", "Oman", "Pakistan", "Palau", 
    "Panama", "Papua New Guinea", "Paraguay", "Peru", "Philippines", "Poland", "Portugal", "Qatar", "Romania", "Russian Federation", "Rwanda", "St Kitts & Nevis", "St Lucia", 
    "Saint Vincent & the Grenadines", "Samoa", "San Marino", "Sao Tome & Principe", "Saudi Arabia", "Senegal", "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovakia", 
    "Slovenia", "Solomon Islands", "Somalia", "South Africa", "South Sudan", "Spain", "Sri Lanka", "Sudan", "Suriname", "Swaziland", "Sweden", "Switzerland", "Syria", "Taiwan", 
    "Tajikistan", "Tanzania", "Thailand", "Togo", "Tonga", "Trinidad & Tobago", "Tunisia", "Turkey", "Turkmenistan", "Tuvalu", "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom", 
    "United States", "Uruguay", "Uzbekistan", "Vanuatu", "Vatican City", "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe"
};

int Game::totalCountries = sizeof(countries)/sizeof(countries[0]);

void Game::welcome()
{
    cout << "\t\tWelcome to the Game:\tHANG THE MAN\n";
    cout << "Instructions:\n1. Type the letter and press Enter.\n2. Do not type more than one letter at once.\n3. You cannot repeat a mistake.\n";
    cout << "-----------------------------------PLAY-----------------------------------" << endl;
}

Game::Game()
{
    runTime = mistakes = mistakeBoxLastIndex = chosenCountrySize = 0;
    chosenCountryIndex = rand()%totalCountries; // randomly chooses a country from the array of countries
    
    //determining the length (number of characters) in the chosen country
    while(countries[chosenCountryIndex][chosenCountrySize] != '\0')
        chosenCountrySize++;
}

void Game::run()
{
    Body human;
    char userAnswers[chosenCountrySize];

    //putting all blanks the user answers array
    //spaces will automatically be placed
    initializeAnswersArray(userAnswers);

    while(mistakes <= 8 && runTime <= chosenCountrySize) //stops if either 8 mistakes are made or all blanks are filled
    {
        //one of them will be used. cls does not work on mac and clear does not work on windows
        system("cls");
        system("clear");

        //game logo and instructions will be shown
        welcome();
        
        //shows the chances left and previously made mistakes
        previousData();

        //shows the updated body after each iteration
        human.draw();
        showUserAnswersArray(userAnswers);
        
        if(runTime == chosenCountrySize || mistakes == 8)
            break;
        
        //taking choice from user
        userChoice = getUserChoice();

        //running checks on user choice to see if it was already entered or not (typing a letter twice is not allowed)
        if(checks(userAnswers))
        {
            cout << "\n\n\t\t\t\tGame Paused\n\nYou typed the letter '" << userChoice << "' before. It cannot be chosen again. Press Enter to continue the game" << endl;
            cin.ignore(1);
            char b = cin.get();
            continue;
        }
        //checks stops here
    
        //see if the user-entered-letter matches the corresponding letter (taking care of lower and uppercase)
        int found = matchLetter(userAnswers);
        
        //if letter does not match, increase the mistake by 1, take a body part, and put that mistaken letter in the mistakeBox array
        if(!found)
        {
            mistakes++;
            human.takeBodyPart();
            mistakeBox[mistakeBoxLastIndex] = userChoice;
            mistakeBoxLastIndex++;
        }
    }
}

void Game::results()
{
    if(mistakes == 8)
        cout << "\t\t\t\tYou lost. \n\tThe country that Computer chose was: " << countries[chosenCountryIndex] << endl;
    else
        cout << "\n\t\t\tCongrats! You have won the game.\n\n" << endl;
}

void Game::initializeAnswersArray(char* userAnswers)
{
    for(int i=0; i<chosenCountrySize; i++)
    {
        if(countries[chosenCountryIndex][i] == ' ')
        {
            userAnswers[i] = ' ';
            runTime++;
        }
        else
            userAnswers[i] = '_';
    }
}

void Game::previousData()
{
    cout << "\nChances left: " << 8-mistakes << endl;
    cout << "Mistakes: ";

    for(int i=0; i < mistakeBoxLastIndex; i++)
        cout << mistakeBox[i] << " ";
}

char Game::getUserChoice()
{
    char choice;
    cout << "Guess a letter: ";
    cin >> choice;
    return choice;
}

int Game::matchLetter(char* userAnswers)
{
    int found = 0;
    for(int i=0; i<chosenCountrySize; i++)
    {
        if(userChoice == countries[chosenCountryIndex][i] || userChoice-32 == countries[chosenCountryIndex][i])
        {
            found = 1;
            userAnswers[i] = userChoice;
            runTime++;
        }
    }
    return found;
}

void Game::showUserAnswersArray(char* userAnswers)
{
    cout << "Country: ";
    for(int i=0; i<chosenCountrySize; i++)
        cout << userAnswers[i];
    cout << endl;
}

int Game::checks(char* userAnswers)
{
    int runAgain = 0;
    for(int i=0; i<mistakeBoxLastIndex; i++) // prevents entering a character twice
        // if that letter was already entered (as a mistake), then it must be inside mistakeBox array
        if(userChoice == mistakeBox[i])
        {
            runAgain = 1; 
            break;
        }
    if(!runAgain)
        for(int i=0; i<chosenCountrySize; i++)
            if(userAnswers[i] == userChoice)
            {
                runAgain = 1;
                break;
            }
    return runAgain;
}     

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