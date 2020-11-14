/*
 * THE Original JRinger Header Format
 * Name: Simone Persinger
 * Date: 9-11-2001
 * Purpose: Be quite... Dandu is sleeping
*/
#include <iostream>
#include "termColor.hpp"

int main(int argc, char *argv[]) {
    int sizeX, sizeY;
    int threshCounterC = 0, threshCounterT = 0;
    std::cin >> sizeX;
    std::cin >> sizeY;
    double cThreshold = 0.4, tThreshold = 0.8;
    if (argc > 1)
        double cThreshold = strtod(argv[1],NULL), tThreshold = strtod(argv[2],NULL);
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            double tenIn, comIn;
            std::cin >> tenIn;
            std::cin >> comIn;
            if (tenIn >= tThreshold) 
                if (comIn >= cThreshold) {
                    //BOTH
                    std::cout << termcolor::red << "[#]" << termcolor::reset;
                    threshCounterC++;
                    threshCounterT++;
                }
                else {
                   //TENSION
                    std::cout << termcolor::cyan << "[-]" << termcolor::reset;
                    threshCounterT++;
                }
            else if (comIn >= cThreshold) {
                //COMPRESSION
                std::cout << termcolor::magenta << "[-]" << termcolor::reset;
                threshCounterC++;
            }
            else {
                //NONE
                std::cout << termcolor::green << "[ ]" << termcolor::reset;
            }
        }
        std::cout << std::endl;
    }
    if (threshCounterC >= 15 || threshCounterT >= 15) {
        std::cout << "BEEP BEEP BEEP BEEP" << std::endl;
        return 0;
    }
    std::cout << std::endl;
    return 0;
}