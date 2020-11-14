/* The Official JRinger Header Set-Up
 *
 * Name: Christapha "He" Heho
 * Date: 1-1-1987
 * Purpose: The bite of '87
 */
#include <iostream>
#include <time.h>
#include <random>
#include "fastNoise.h"

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
            random();
        }
        void zero() {
            for (int i = 0; i < 4; i++) {
                tension[i] = 0;
            }
            compression = 0;
        }
        void random() {
            for (int i = 0; i < 4; i++) {
                tension[i] = fRand(0, 1);
            }
            compression = fRand(0, 1);
        }
        void getData(int x, int y) {
            //This is where we would be getting the data from the device
            //However since we do not have a working device prototype instead I have decided to use simplex noise to emulate the compression put on a persons leg
            FastNoiseLite noise;
            noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
            noise.SetFrequency(0.1);
            noise.SetSeed(time(NULL)); 

            //SCUFFED
            for (int i = 0; i < 4; i++) {
                tension[i] = noise.GetNoise((float)x,(float)y);
            }
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
    double threshold = 0.4;
    //DEBUG CRAP
    //for (int i = 0; i < sizeX*sizeY; i++) {
    //    for (int j = 0; j < 4; j++) {
    //        if (nodes[i].tension[j] >= threshold) {
    //            cout << "Threshold (" << i << ", " << j << ", coord(" << nodes[i].xLocal << "," << nodes[i].yLocal << ")): " << nodes[i].tension[j] << endl;
    //        }
    //    }
    //}

    //display shit monkaS they can see dowd
    //todo
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            if (nodes[x+sizeX*y].averageTension() >= threshold)
                cout << "[X]";
            else 
                cout << "[ ]";

        }
        cout << endl;
    }

    return 0;
}