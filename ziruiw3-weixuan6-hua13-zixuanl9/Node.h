#include <vector>
#include <string>
#include <utility>
#include <map>

#pragma once

using std::vector;
using std::pair;
using std::string;
using std::map;

class Node {
    public:
        Node(string state, string country, string continent, float lon, float lat, float area);
                
        Node(const string& cline, const string& dline, const string& rline, 
            const map<string, vector<string>> infoMap_);

        
        string state_;
        string country_;
        string continent_;
        float latitude_;
        float longitude_;
        float area_;        // sq. mi.
        float radius_;      // mi.
        int population_;

        vector<int> confirmed_;
        vector<int> deaths_;
        vector<int> recovered_;

        /**
         * @brief neighboring edges representing in pair {another_end, distance}
         * two nodes are connected if they are neighbors. That is,
         * if `dist(curr_node, check_node) <= (curr->radius + check_node->radius)`
         */
        vector<pair<Node*, float>> neighbors_;
};