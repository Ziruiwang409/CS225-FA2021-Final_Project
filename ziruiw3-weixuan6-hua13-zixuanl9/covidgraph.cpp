#include "covidgraph.h"
#include "dsets.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <limits.h>

using std::getline;
using std::ifstream;
using std::cout;
using std::endl;
using std::find;
using std::queue;
using std::unordered_set;

CovidGraph::CovidGraph(string infoFile, string cFIle, string dFile, string rFile) {
    _initInfo(infoFile);
    _initNodes(cFIle, dFile, rFile);
    _initConnections();
}

CovidGraph::~CovidGraph() {
    _destroy();
}

void CovidGraph::_initInfo(string filename) {
    string line;
    ifstream file(filename);

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            // parsed: {country, continent, population, area}
            vector<string> parsed;
            string s = "";
            for (const char & c : line) {
                if (c == ',') {
                    parsed.push_back(s);
                    s = "";
                } else {
                    s += c;
                }
                if (parsed.size() == 4) { break; }
            }
            // infoMap_ = {countryc -> {continent, area, population}}
            infoMap_[parsed[0]] = { parsed[1], parsed[3], parsed[2] };
        }
        // for (auto &p : infoMap_) {
        //     cout << "{ " << p.first << ": " << p.second[0] << ", " << p.second[1] << " }" << endl;
        // }
    }
    file.close();
}

void CovidGraph::_initNodes(string CfileName, string DfileName, string RfileName) {
    string cline;
    string dline;
    string rline;
    ifstream cfile(CfileName);
    ifstream dfile(DfileName);
    ifstream rfile(RfileName);

    // all three files should have the same country at same line, and all three have same number of lines
    if (cfile.is_open()) {
        getline(cfile, cline);
        getline(dfile, dline);
        getline(rfile, rline);
        while (getline(cfile, cline) && getline(dfile, dline) && getline(rfile, rline)) {
            Node* node = new Node(cline, dline, rline, infoMap_);
            latNodes_.push_back(node);
            lonNodes_.push_back(node);
            continentsMap_[node->continent_].push_back(node);
        }
    }
    cfile.close();
    dfile.close();
    rfile.close();

    for (Node* node : latNodes_) {
        string name = node->country_;
        
        if (node->state_ != "") {
            name += "(" + node->state_ + ")";
        }

        nameMap_[name] = node;
    }
}

bool CovidGraph::candInNeighbor(const Node* curr, const Node* cand) {
    for (auto it = curr->neighbors_.begin(); it != curr->neighbors_.end(); ++it) {
        if (it->first == cand)
            return true;
    }
    return false;
}

void CovidGraph::_initConnections() {
    /**
     * @brief neighboring edges representing in pair {another_end, distance}
     * two nodes are connected if they are neighbors. That is,
     * if `dist(curr_node, check_node) <= (curr->radius + check_node->radius)`
     * 
     * we also need to make sure:
     *  - Every nodes has at least one neighbor. This can be done by increasing
     *    searching radius when there is no nodes inside the original radius
     *  - All nodes are connected. This can be done by using desjoint set to keep
     *    track of whether at least one node in discovery_node(curr)'s neighbor
     *    is in the `major set`
     * 
     */
    std::sort(latNodes_.begin(), latNodes_.end(), [&](Node* lhs, Node* rhs) {
        return lhs->latitude_ < rhs->latitude_;
    });
    std::sort(lonNodes_.begin(), lonNodes_.end(), [&](Node* lhs, Node* rhs) {
        return lhs->longitude_ < rhs->longitude_;
    });
    // use map to find position of Nodes in lonNodes_ quickly
    map<Node*, int> idxMapLon;
    for (unsigned int i = 0; i < lonNodes_.size(); i++) {
        idxMapLon.insert(pair<Node*, int>(lonNodes_[i], i));
    }

    int SIZE = latNodes_.size();            // totoal number of nodes

    DisjointSets lon_ds;                        // 0~SIZE -> nodes in `lonNodes_` (ii)
    lon_ds.addelements(SIZE);
    int mjr_root = idxMapLon.at(latNodes_[0]);  // root of `major set`

    for (int i = 1; i < SIZE; i++) {        // i is curr's index in latNodes_
        Node* curr = latNodes_[i];
        int ii = idxMapLon.at(curr);        // ii is curr's index in lonNodes_

        bool connect_mjr = false;           // at least one curr's neighbor in in `major set`
        Node* nearest_in_mjr = NULL;
        float nim_dist = -1;
        vector< pair<const vector<Node*>&, int> > temp = {{latNodes_, i}, {lonNodes_, ii}};

        // add all neighbors in radius first
        for (auto p : temp) {                   // in both vector
            for (int off : {-1, 1}) {           // go forward and backward exhaustively
                int cand_loc = p.second + off;  // cand_loc is the index to use
                while (true) {
                    Node* cand = (cand_loc >= 0 && cand_loc < SIZE) ? p.first[cand_loc] : NULL;
                    if (!cand) { break; }
                    float dist = Distance(curr, cand);

                    // we are traversing through latNodes_ and at each step we make sure the
                    // current node to be connected to major set, so it is garantee that at least
                    // our left guy in vector is in the major set
                    if (lon_ds.find(idxMapLon[cand]) == lon_ds.find(mjr_root) && 
                        (nearest_in_mjr == NULL || dist < nim_dist))
                    {
                        nearest_in_mjr = cand;
                        nim_dist = dist;
                    }

                    if (dist <= curr->radius_ + cand->radius_) {
                        if (lon_ds.find(idxMapLon[cand]) == lon_ds.find(mjr_root)) {
                            connect_mjr = true;
                        }
                        if (!candInNeighbor(curr, cand)) {
                            // cout << curr->country_ << "(" << curr->state_ << ") <-- " << dist << " --> " 
                            //     << cand->country_ << "(" << cand->state_ << ")" << endl;
                            curr->neighbors_.push_back(pair<Node*, float>(cand, dist));
                            cand->neighbors_.push_back(pair<Node*, float>(curr, dist));
                            lon_ds.setunion(ii, idxMapLon[cand]);
                        }
                    } else { break; }           // break loop (or dist can only keep increasing)

                    cand_loc += off;
                }
            }
        }

        if (!connect_mjr) {
            // cout << "curr: " << curr->country_ << " " << curr->state_ << endl;
            curr->neighbors_.push_back(pair<Node*, float>(nearest_in_mjr, nim_dist));
            nearest_in_mjr->neighbors_.push_back(pair<Node*, float>(curr, nim_dist));
            lon_ds.setunion(ii, idxMapLon[nearest_in_mjr]);
        }
    }
}

void CovidGraph::_destroy() {
    for (auto it : latNodes_) {
        delete it;
    }
    latNodes_.clear();
}

const Node* CovidGraph::stringToPtr(string name)
{
    return nameMap_[name];
}

float CovidGraph::Distance(Node* A, Node* B) {
    float A_lat = A->latitude_ * (2 * M_PI) / 360;
    float A_lon = A->longitude_ * (2 * M_PI) / 360;
    float B_lat = B->latitude_ * (2 * M_PI) / 360;
    float B_lon = B->longitude_ * (2 * M_PI) / 360;
    float latidiff = abs(A_lat - B_lat);
    float longdiff = abs(A_lon - B_lon);
    float latisum = A_lat + B_lat;
    float earthRadius = 3958.8;
    float hav = pow(sin(latidiff/2), 2) 
                + (1-pow(sin(latidiff/2), 2)-pow(sin(latisum/2), 2))
                * pow(sin(longdiff/2), 2);
    float dist = 2*earthRadius*asin(sqrt(hav));
    return dist;
}

int CovidGraph::BFS(Node* start) 
{   
    unordered_set<Node*> visited;
    queue<Node*> q;
    q.push(start);

    while (!q.empty()) {
        Node* curr = q.front();
        visited.insert(curr);

        for (pair<Node*, float> & pair : curr->neighbors_) {
            if (visited.find(pair.first) == visited.end()) {
                q.push(pair.first);
            }
        }
        q.pop();
    }

    return visited.size();

    // for (Node* n : latNodes_) {
    //     cout << n->country_ << "(" << n->state_ << "): ";
    //     for (auto & p : n->neighbors_) {
    //         cout << p.first->country_ << "(" << p.first->state_ << "),";
    //     }
    //     cout << "\n";
    //     cout << "\n";
    // }
    // return 0;
}

vector<Node*> CovidGraph::findShortestPath(Node* start, Node* end) 
{   
    vector<Node*> shortestPath;
    map<Node*, float> distance;
    map<Node*, Node*> parent;
    unordered_set<Node*> visited;
    vector<Node*> Q;

    for (Node* node : latNodes_) {
        distance[node] = INFINITY;
    }

    distance[start] = 0;
    Q.push_back(start);

    while (true) {
        int frontIdx = minDistNodeIdx(distance, Q);
        Node* currNode = Q[frontIdx];
        float currDistance = distance[currNode];

        if (currNode == end) { break; }  

        for (const pair<Node*, float> & p : currNode->neighbors_) {
            
            Node* neighborNode = p.first;
            float neighborDistance = p.second;

            if (visited.find(neighborNode) == visited.end()) {
                float newDistance = currDistance + neighborDistance;
                if (distance[neighborNode] == INFINITY) {
                    Q.push_back( neighborNode );
                }

                if (newDistance < distance[neighborNode]) {
                    distance[neighborNode] = newDistance;
                    parent[neighborNode] = currNode;
                }
            }
        }

        visited.insert(currNode);
        Q.erase(Q.begin() + frontIdx);
    }

    shortestPath.insert(shortestPath.begin(), end);
    Node* currNode = end;

    while (currNode != start) {
        shortestPath.insert(shortestPath.begin(), parent[currNode]);
        currNode = parent[currNode];
    }

    return shortestPath;
}

int CovidGraph::minDistNodeIdx(const map<Node*, float>& mp, const vector<Node*>& vect) {
    assert(!vect.empty());
    int res = 0;
    float minDist = INFINITY;
    for (unsigned i = 0; i < vect.size(); i++) {
        if (mp.at(vect[i]) < minDist) {
            minDist = mp.at(vect[i]);
            res = i;
        }
    }
    return res;
}
