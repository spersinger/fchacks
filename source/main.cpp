/* The Official JRinger Header Set-Up
 *
 * Name: Christapha "He" Heho
 * Date: 1-1-1987
 * Purpose: Swaggy Pone Pone
 */

/* Checklist:
 * Send data from main to visualizer ☑️
 * Recieve data from some kind of file to main ☑️
 * Edit threshold in main from visualizer ☑️
 * Generate random noise data into file for main ☑️
 * mAKE IT lok good 
 * errors for patient and doctor if the tension+compression reaches the threshold set by the doctor ☑️
 */

#include <iostream>
#include <time.h>
#include <random>
#include "FastNoise.h"
#include "termColor.hpp"

using namespace std;

//Code from stackoverflow.com
double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
// Class for each node in the matrix. Includes the compression and the three/four tension values and functions specific to these objects.
class MatrixNode {
    public:
        double tension[4], compression;
        int xLocal, yLocal;

        MatrixNode() {
            zero();
        }
        void zero() {
            for (int i = 0; i < 4; i++) {
                tension[i] = 0;
            }
            compression = 0;
        }
        void getData(int x, int y) {
            
            //This is where we would be getting the data from the device
            //However since we do not have a working device prototype instead I have decided to use simplex noise to emulate the compression put on a persons leg
            FastNoiseLite noise;
            noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
            noise.SetFractalType(FastNoiseLite::FractalType_FBm);
            noise.SetFrequency(0.1);
            noise.SetFractalLacunarity(fRand(0.1,2));
            //DO NMOT TOUCH
            noise.SetSeed(time(NULL));

            FastNoiseLite comNoise;
            comNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
            comNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
            comNoise.SetFrequency(0.1);
            comNoise.SetFractalLacunarity(fRand(0.1,2));
            //DO NMOT TOUCH
            comNoise.SetSeed((time(NULL)+1));

            for (int i = 0; i < 4; i++) {
                double val = noise.GetNoise((float)x,(float)y);
                tension[i] = val;
            }
            double val = comNoise.GetNoise((float)x,(float)y);
            compression = val;
        }
        double averageTension() {
            double avg;
            if (tension[3] == 0)
                avg = (tension[0]+tension[1]+tension[2])/3;
            else
                avg = (tension[0]+tension[1]+tension[2]+tension[3])/4;
            return avg;
        }
};
// Main Function
int main (int argc, char *argv[]) {

    int sizeX = 20, sizeY = 20;
    //OUTPUT TO STDIN SO THAT VISUALIZER.CPP CAN READ IT
    //lines 11-12 visualizer.cpp
    cout << sizeX << endl;
    cout << sizeY << endl;
    srand(time(NULL));
    MatrixNode nodes[sizeX*sizeY];
    //getting data from sensors (gets a noise value based on it)
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            nodes[x+sizeX*y].getData(x, y);
            nodes[x+sizeX*y].xLocal = x;
            nodes[x+sizeX*y].yLocal = y;
        }
    }
    //todo
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            nodes[x+sizeX*y].getData(x, y);
            cout << nodes[x+sizeX*y].averageTension() << endl;
            cout << nodes[x+sizeX*y].compression << endl;
        }
    }
    return 0;
}
