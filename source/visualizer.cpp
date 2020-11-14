/*
 * Visualizer Program. (This would run on a separate personal device as an application)
 * This contains the analyzing of the data from the garment and the displaying of said data.
 * This all simulates what would happen in the application on a separate device.
*/
#include <iostream>
#include "lib/termColor.hpp"


int main(int argc, char *argv[]) {
    int sizeX, sizeY;
    int threshCounterC = 0, threshCounterT = 0;
    //Reads sizeX and sizeY from main program
    std::cin >> sizeX;
    std::cin >> sizeY;
    //Default values for the compression and tension thresholds
    double cThreshold = 0.6, tThreshold = 0.4;
    //User input for both compression and tension threshold
    if (argc > 1) {
        double cThreshold = strtod(argv[1],NULL), tThreshold = strtod(argv[2],NULL);
    }

    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            //Reads node measurements from main program
            double tenIn, comIn;
            std::cin >> tenIn;
            std::cin >> comIn;

            //Determines if nodes are above safety limit and then outputs the result of the analysis
            if (tenIn >= tThreshold) 
                if (comIn >= cThreshold) {
                    //BOTH ABOVE LIMIT - RED
                    std::cout << termcolor::red << "[#]" << termcolor::reset;
                    threshCounterC++;
                    threshCounterT++;
                }
                else {
                   //TENSION ABOVE LIMIT - CYAN
                    std::cout << termcolor::cyan << "[-]" << termcolor::reset;
                    threshCounterT++;
                }
            else if (comIn >= cThreshold) {
                //COMPRESSION ABOVE LIMIT - MAGENTA
                std::cout << termcolor::magenta << "[-]" << termcolor::reset;
                threshCounterC++;
            }
            else {
                //NONE ABOVE LIMIT - GREEN
                std::cout << termcolor::green << "[ ]" << termcolor::reset;
            }
        }
        std::cout << std::endl;
    }
    //Alerts user if 15 or more nodes are above the safety limit
    if (threshCounterC >= 15 || threshCounterT >= 15) {
        std::cout << "BEEP BEEP BEEP BEEP" << std::endl;
        return 0;
    }
    std::cout << std::endl;
    return 0;
}