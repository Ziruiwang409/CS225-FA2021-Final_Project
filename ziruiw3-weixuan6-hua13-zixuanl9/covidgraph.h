#include <vector>
#include <string>
#include <utility>
#include <map>

#include "Node.h"
#include "cs225/PNG.h"
#include "Animation.h"
#pragma once

using std::vector;
using std::pair;
using std::string;
using std::map;

using cs225::PNG;

class CovidGraph 
{
    public:
        /**
         * @brief Constructor of CovidGraph class
         * initialization details are in private init() function
         * 
         */
        CovidGraph(string infoFile, string cFIle, string dFile, string rFile);

        /**
         * @brief Destructor of CovidGraph class
         * 
         */
        ~CovidGraph();

        /**
         * @brief count the number of the nodes in the graph
         * 
         * @param start the starting node to do BFS
         * @return total number of nodes in the graph
         */
        int BFS(Node* start);

        /**
         * @brief Get the Nodes of a target country
         * 
         * @param country name of the country
         * @return nodes of that country in a const vector reference
         */
        const vector<Node*> getNodesByCountry(string country);
        const vector<Node*>& getNodesByContinent(string continent);
        
        /**
         * @brief Get deaths/recovered/confirmed within a given time period
         * 
         * @param node  the target country/region
         * @param start startDate as a string
         * @param end   endDate as a string
         * @return vector<int> including all information
         */
        vector<int> getDeaths(Node* node, string start, string end);
        vector<int> getRecovered(Node* node, string start, string end);
        vector<int> getConfirmed(Node* node, string start, string end);

        /**
         * @brief Get the Global Highest Confirmed object
         * 
         * @param start startDate
         * @param end   endDate
         * @param N     number of nodes we want as output (topN)
         * @return vector<Node*> 
         */
        vector<Node*> globalTopConfirmed(string start, string end, int N);
        vector<Node*> globalTopRecovered(string start, string end, int N);
        vector<Node*> globalTopDeaths(string start, string end, int N);

        /**
         * @brief find shortest path between two nodes using Dijkstra's algorithm
         * 
         * @param A pointA
         * @param B pointB
         * @return vector<Node*> including all nodes on the path
         */
        vector<Node*> findShortestPath(Node* start, Node* end);

        /**
         * @brief latNodes_ getter
         * @return latNodes vector
         */
        const vector<Node*>& latNodes();

        /**
         * @brief lonNodes_ getter
         * @return lonNodes vector
         */
        const vector<Node*>& lonNodes();

        /**
         * @brief Link the name(string) to the node pointer
         * 
         * @param name the name of the country/state/province
         * @return the ptr corresponding to the name of the country/state/province 
         * if found, otherwise nullptr
         * 
         */
        const Node* stringToPtr(string name);

    private:
        /**
         * @brief helper function used in Constructor, initialize infoMap
         * 
         * @param infoFile 
         */
        void _initInfo(string filename);

        /**
         * @brief Constructor private helper function
         * 
         * @param CfileName 
         * @param DfileName 
         * @param RfileName 
         */
        void _initNodes(string CfileName, string DfileName, string RfileName);
        
        /**
         * @brief _initConnections helper function, return true if cand is in curr's neighbor
         * 
         */
        bool candInNeighbor(const Node* curr, const Node* cand);

        /**
         * @brief Traverse Node list and connect neighboring nodes together
         * 
         */
        void _initConnections();

        /**
         * @brief Destructor helper function
         * 
         */
        void _destroy();

        /**
         * @brief Calculate the Great-cirle distance between two nodes
         * 
         * @param A pointA
         * @param B pointB
         * @return distance as a float in miles
         */
        float Distance(Node* A, Node* B);

        /**
         * @brief convert a MM/DD string to index of C/D/R vector
         *  index 0 will be first available data, in our case: 1/22
         * @param MMDD date string to convert, in the format MM/DD
         * 
         */
        int MMDDtoIdx(string MMDD);

        /**
         * @brief private helper function for findShortestPath
         * @param mp distance map mapping node pointer to current distance to start point
         * @param vect input vector of node ptr
         * @return the index of the node ptr with the least current distance to start point
         *  defined in the map
         * 
         */
        int minDistNodeIdx(const map<Node*, float>& mp, const vector<Node*>& vect);

        /**
         * @brief continents map
         * maping coutinents' name to a vector containing all nodes in that continent
         * naming convention: AFRICA, ASIA, EUROPE, NORTHERN AMERICA, OCEANIA, SOUTHERN AMERICA
         * 
         */
        map<string, vector<Node*>> continentsMap_;

        /**
         * @brief private information map construct using info dataset
         * map country_name -> { countinent, area }
         * 
         */
        map<string, vector<string>> infoMap_;

        /**
         * @brief private map linking string (name of the country) to the Node pointer
         * map string: country_name(state_name) -> Node*: country_name(state_name)
         * 
         */
        map<string, Node*> nameMap_;

        /**
         * @brief sort nodes according to latitude and longitude respectively
         * 
         */
        vector<Node*> latNodes_;
        vector<Node*> lonNodes_;
};
