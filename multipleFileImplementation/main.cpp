#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "body.h"
#include "game.h"

using namespace std;


/*------------------NOTE-----------------------
1. PLEASE PUT ALL 5 FILES IN THE SAME FOLDER
2. RUN CMD IN THAT FOLDER
3. Type: 
        g++ main.cpp body.cpp game.cpp -o anyName
4. Then Type:
        .\anyName   OR  ./anyName
5. If not working, use the singleFileImplementation.cpp
*/

int main()
{
    srand(time(NULL));
    Body b;

    Game g(b);
    
    g.run();
    g.results();

    return 0;
}


