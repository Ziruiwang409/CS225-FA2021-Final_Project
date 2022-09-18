#include "../cs225/catch/catch.hpp"

#include "../covidgraph.h"
#include "../visualization.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


CovidGraph initial(){
	CovidGraph g("data/countries-of-the-world.csv", "data/covid19-Confirmed.csv", 
                 "data/covid19-Deaths.csv", "data/covid19-Recovered.csv");
	return g;
}

CovidGraph test_initial() {
    CovidGraph g("data/countries-of-the-world.csv", "tests/ctest_data.csv", 
                 "tests/dtest_data.csv", "tests/rtest_data.csv");
	return g;
}

CovidGraph mock_initial() {
    CovidGraph g("data/countries-of-the-world.csv", "tests/mockc_data.csv", 
                 "tests/mockd_data.csv", "tests/mockr_data.csv");
	return g;
}

TEST_CASE("test_mock_init_graph") {
    CovidGraph g = mock_initial();
	string cline;
    ifstream cfile("tests/mockc_data.csv");
	int count = 0;
	if (cfile.is_open()) {
        getline(cfile, cline);
		while (getline(cfile, cline)) {
			count++;
            // cout << cline << endl;
        }
	}
    cfile.close();
	REQUIRE(g.latNodes().size() == count);
	REQUIRE(g.latNodes()[0]->state_ == "Victoria");
	REQUIRE(g.latNodes()[count - 1]->state_ == "British Columbia");
	// for (Node* node : g.latNodes()) {
	// 	cout << "current:" << node->state_ << "," << node->country_ << endl;
	// 	for (pair<Node*, float> neighbors : node->neighbors_) {
    //         cout << "neighbors are:" << neighbors.first->state_ << "," << neighbors.first->country_ << endl;
	// 	}
	// }

	REQUIRE(g.lonNodes().size() == count);
	REQUIRE(g.lonNodes()[0]->state_ == "British Columbia");
	REQUIRE(g.lonNodes()[count - 1]->state_ == "Queensland");

}

TEST_CASE("test_mock_bfs_graph") {
    CovidGraph g = mock_initial();
	REQUIRE(g.latNodes().size() == g.BFS(g.latNodes()[4]));
	REQUIRE(g.latNodes().size() == g.BFS(g.latNodes()[8]));
	REQUIRE(g.latNodes().size() == g.BFS(g.latNodes()[0]));
}

TEST_CASE("test_mock_shortestpath") {
	CovidGraph g = mock_initial();
	Node* one = g.latNodes()[0];
	Node* two = g.latNodes()[g.latNodes().size() - 1];
	vector<Node*> solution = g.findShortestPath(one, two);
	REQUIRE(solution[0] == one);
	REQUIRE(solution[4]->country_ == "Malaysia");
	REQUIRE(solution.back() == two);
}

TEST_CASE("test_test_init_graph") {
	CovidGraph g = test_initial();
	string cline;
    ifstream cfile("tests/ctest_data.csv");
	int count = 0;
	if (cfile.is_open()) {
        getline(cfile, cline);
		while (getline(cfile, cline)) {
			count++;
            // cout << cline << endl;
        }
	}
    cfile.close();
	REQUIRE(g.latNodes().size() == count);
	REQUIRE(g.latNodes()[0]->state_ == "Victoria");
	REQUIRE(g.latNodes()[count - 1]->country_ == "Finland");
	// for (Node* node : g.latNodes()) {
	// 	cout << "current:" << node->state_ << "," << node->country_ << endl;
	// 	for (pair<Node*, float> neighbors : node->neighbors_) {
    //         cout << "neighbors are:" << neighbors.first->state_ << "," << neighbors.first->country_ << endl;
	// 	}
	// }

	REQUIRE(g.lonNodes().size() == count);
	REQUIRE(g.lonNodes()[0]->state_ == "British Columbia");
	REQUIRE(g.lonNodes()[count - 4]->state_ == "From Diamond Princess");
	REQUIRE(g.latNodes().size() == g.BFS(g.latNodes()[4]));
	REQUIRE(g.lonNodes().size() == g.BFS(g.latNodes()[10]));
}

TEST_CASE("test_test_shortestpath") {
	CovidGraph g = test_initial();
	Node* one = g.latNodes()[0];
	Node* two = g.latNodes()[g.latNodes().size() - 1];
	vector<Node*> solution = g.findShortestPath(one, two);
	REQUIRE(solution[0] == one);
	REQUIRE(solution.back() == two);
	REQUIRE(solution[7]->country_ == "Japan");
}

TEST_CASE("test_getNodesByCountry") {
	CovidGraph g = test_initial();
	vector<Node*> temp = g.getNodesByCountry("Australia");
    REQUIRE(temp.size() == 5);
	REQUIRE(temp[0]->state_ == "Victoria");
	REQUIRE(temp[4]->state_ == "From Diamond Princess");
}

TEST_CASE("test_getNodesByContinent") {
	CovidGraph g = test_initial();
	vector<Node*> tempE = g.getNodesByContinent("EUROPE");
	vector<Node*> tempA = g.getNodesByContinent("ASIA");
	vector<Node*> tempO = g.getNodesByContinent("OCEANIA");
	vector<Node*> tempAF = g.getNodesByContinent("AFRICA");
	vector<Node*> tempNA = g.getNodesByContinent("NORTHERN AMERICA");
	REQUIRE(tempE.size() == 6);
	REQUIRE(tempA.size() == 10);
	REQUIRE(tempO.size() == 5);
	REQUIRE(tempAF.size() == 1);
	REQUIRE(tempNA.size() == 1);
}

TEST_CASE("test_getDeaths") {
	CovidGraph g = test_initial();
	Node* node = g.getNodesByCountry("Singapore")[0];
	vector<int> result = g.getDeaths(node, "1/22", "1/26");
    REQUIRE(result[0] == 0);
	REQUIRE(result[1] == 0);
	REQUIRE(result[2] == 1);
	REQUIRE(result[3] == 3);
	REQUIRE(result[4] == 4);
}

TEST_CASE("test_getRecovered") {
	CovidGraph g = test_initial();
	Node* node = g.getNodesByCountry("Cambodia")[0];
	vector<int> result = g.getRecovered(node, "1/22", "1/26");
    REQUIRE(result[0] == 0);
	REQUIRE(result[1] == 1);
	REQUIRE(result[2] == 1);
	REQUIRE(result[3] == 1);
	REQUIRE(result[4] == 1);
}

TEST_CASE("test_getConfirmed") {
	CovidGraph g = test_initial();
	Node* node = g.getNodesByCountry("Thailand")[0];
	vector<int> result = g.getConfirmed(node, "1/22", "1/26");
    REQUIRE(result[0] == 14);
	REQUIRE(result[1] == 15);
	REQUIRE(result[2] == 18);
	REQUIRE(result[3] == 21);
	REQUIRE(result[4] == 22);
}

TEST_CASE("test_globalTopConfirmed") {
    CovidGraph g = test_initial();
	vector<Node*> result = g.globalTopConfirmed("1/22", "1/26", 3);
    REQUIRE(result[0]->country_ == "India");
	REQUIRE(result[1]->country_ == "Thailand");
	REQUIRE(result[2]->country_ == "Singapore");
}

TEST_CASE("test_globalTopDeath") {
    CovidGraph g = test_initial();
	vector<Node*> result = g.globalTopDeaths("1/22", "1/26", 3);
    REQUIRE(result[0]->country_ == "Singapore");
	REQUIRE(result[1]->country_ == "India");
	REQUIRE(result[2]->country_ == "Japan");
}

TEST_CASE("test_globalTopRecovered") {
    CovidGraph g = test_initial();
	vector<Node*> result = g.globalTopRecovered("1/22", "1/26", 3);
    REQUIRE(result[0]->country_ == "Singapore");
	REQUIRE(result[1]->country_ == "Japan");
	REQUIRE(result[2]->country_ == "India");
}

TEST_CASE("test_visualization_riskLevelPNG") {
	CovidGraph g = initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    PNG out = visual.riskLevelPNG(g.latNodes());
	out.writeToFile("tests/riskLevelPNG.png");
	REQUIRE(out.height() == sourcePNG.height());
	REQUIRE(out.width() == sourcePNG.width());
}

TEST_CASE("test_visualization_deathsLevelPNG") {
	CovidGraph g = initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    PNG out = visual.deathsLevelPNG(g.latNodes());
	out.writeToFile("tests/deathsLevel.png");
	REQUIRE(out.height() == sourcePNG.height());
	REQUIRE(out.width() == sourcePNG.width());
}

TEST_CASE("test_visualization_recoveredLevelPNG") {
	CovidGraph g = initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    PNG out = visual.recoveredLevelPNG(g.latNodes());
	out.writeToFile("tests/recoveredLevel.png");
	REQUIRE(out.height() == sourcePNG.height());
	REQUIRE(out.width() == sourcePNG.width());
}

TEST_CASE("test_confirmedGIF") {
	CovidGraph g = initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    Animation out = visual.confirmedGIF(g.latNodes(), "1/22", "3/23");
	out.write("tests/confirmed.gif");
	REQUIRE(1==1);
}

TEST_CASE("test_deathsGIF") {
	CovidGraph g = initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    Animation out = visual.deathsGIF(g.latNodes(), "1/22", "3/23");
	out.write("tests/deaths.gif");
	REQUIRE(1==1);
}

TEST_CASE("test_recoveredGIF") {
	CovidGraph g = initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    Animation out = visual.recoveredGIF(g.latNodes(), "1/22", "3/23");
	out.write("tests/recovered.gif");
	REQUIRE(1==1);
}

TEST_CASE("test_test_visualization_riskLevelPNG") {
	CovidGraph g = test_initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    PNG out = visual.riskLevelPNG(g.latNodes());
	out.writeToFile("tests/test_riskLevelPNG.png");
	REQUIRE(out.height() == sourcePNG.height());
	REQUIRE(out.width() == sourcePNG.width());
}

TEST_CASE("test_test_visualization_deathsLevelPNG") {
	CovidGraph g = test_initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    PNG out = visual.deathsLevelPNG(g.latNodes());
	out.writeToFile("tests/test_deathsLevel.png");
	REQUIRE(out.height() == sourcePNG.height());
	REQUIRE(out.width() == sourcePNG.width());
}

TEST_CASE("test_test_visualization_recoveredLevelPNG") {
	CovidGraph g = test_initial();
	Image sourcePNG;
	sourcePNG.readFromFile("data/world-map-small.png");
	Visualization visual = Visualization(sourcePNG);
    PNG out = visual.recoveredLevelPNG(g.latNodes());
	out.writeToFile("tests/test_recoveredLevel.png");
	REQUIRE(out.height() == sourcePNG.height());
	REQUIRE(out.width() == sourcePNG.width());
}
