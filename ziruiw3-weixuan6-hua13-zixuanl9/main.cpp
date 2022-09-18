#include "covidgraph.h"
#include "visualization.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "Animation.h"

#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using cs225::PNG;

int main() {
    CovidGraph g("data/countries-of-the-world.csv", "data/covid19-Confirmed.csv", 
                 "data/covid19-Deaths.csv", "data/covid19-Recovered.csv");

    Image baseImg;
    baseImg.readFromFile("data/world-map-small.png");
    Visualization visual(baseImg);

    /* Below are some sameple function calls */

    PNG png = visual.riskLevelPNG(g.getNodesByContinent("ASIA"));
    png.writeToFile("sample-output/asia-risk-level.png");
    
    //Animation gif = visual.confirmedGIF(g.latNodes(), "1/22", "3/23");
    //gif.write("sample-output/2020-risk-level-animation.gif");

    return 0;
}
