/* 
 * Main Program. (What would run on device)
 * This contains the creation of the matrix and matrix nodes and the assigning of tension and compression values to these nodes through
 * a random noise function to create semi-uniform areas within the matrix. This all is simulating what the actual product would do, with
 * the random values representing the measurements of the nodes.
 */

#include <iostream>
#include <time.h>
#include <random>
#include "lib/FastNoise.h"

using namespace std;

//function to generate random numbers between a maximum and minimum number
double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Class for each node in the matrix. Includes the compression and the three/four tension values and functions specific to these objects.
class MatrixNode {
    public:
        //Tension is the amount of tension pulling in 4 directions of the 
        //Compression is the ammount of compression put on the wound
        double tension[4], compression;

        MatrixNode() {
            zero();
        }
        void zero() {
            for (int i = 0; i < 4; i++) {
                tension[i] = 0;
            }
            compression = 0;
        }

        //This is where we would be getting the data from the device
        //However since we do not have a working device prototype instead I have decided to use simplex noise to emulate the compression put on a persons leg
        void getData(int x, int y) {
            
            //Creates a fastnoise object and sets up the settings for generating OpenSimplex Noise.
            //Used to simulate tension/compression being put on the device.
            FastNoiseLite noise;
            noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
            noise.SetFractalType(FastNoiseLite::FractalType_FBm);
            noise.SetFrequency(0.1);
            noise.SetFractalLacunarity(fRand(0.1,2));
            noise.SetSeed(time(NULL));

            //Creates a fastnoise object for the compression data
            FastNoiseLite comNoise;
            comNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
            comNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
            comNoise.SetFrequency(0.1);
            comNoise.SetFractalLacunarity(fRand(0.1,2));
            comNoise.SetSeed((time(NULL)+1));

            //Fills in the matrix with noise data for tension
            for (int i = 0; i < 4; i++) {
                tension[i] = noise.GetNoise((float)x,(float)y);
            }
            
            //Fills in the matrix with noise data for compression
            compression = comNoise.GetNoise((float)x,(float)y);
        }
        
        //This function is used to find the average tension measured on each node to determine the tension of that node
        //Because not every node on the garment will connect to four others (some will only connect to 3), this function checks to see if the fourth tension value is 0 before it calculates the average
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
    //OUTPUT SO THAT VISUALIZER.CPP CAN READ IT
    //lines 11-12 visualizer.cpp
    cout << sizeX << endl;
    cout << sizeY << endl;
    srand(time(NULL));
    MatrixNode nodes[sizeX*sizeY];
    //getting data from sensors (gets a noise value based on it)
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            //Gets the noise value for a specific node and then sets its data in the MatrixNode.getData() function
            nodes[x+sizeX*y].getData(x, y);
        }
    }
    //Outputs the values of each point on the Matrix grid so that visualizer.cpp can interpret them
    //lines 19-20
    for (int x = 0; x < sizeX; x++) {
        for (int y = 0; y < sizeY; y++) {
            cout << nodes[x+sizeX*y].averageTension() << endl;
            cout << nodes[x+sizeX*y].compression << endl;
        }
    }
    return 0;
}
