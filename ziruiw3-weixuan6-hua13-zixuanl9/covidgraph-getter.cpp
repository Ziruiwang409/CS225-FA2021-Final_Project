#include "covidgraph.h"

#include <iostream>
#include <numeric>
#include <queue>

using std::cout;
using std::endl;
using std::priority_queue;

const vector<Node*> CovidGraph::getNodesByCountry(string country){
    vector<Node*> res;
    for (Node* n : latNodes_) {
        if (n->country_ == country) {
            res.push_back(n);
        }
    }
    return res;
}

const vector<Node*>& CovidGraph::getNodesByContinent(string continent){
    return continentsMap_.at(continent);
}

vector<int> CovidGraph::getDeaths(Node* node, string start, string end){
    int startIdx = MMDDtoIdx(start);
    int endIdx = MMDDtoIdx(end);
    vector<int> deaths;
    
    for (int i = startIdx; i <= endIdx;i++){
        deaths.push_back(node->deaths_[i]);
    }
    return deaths;
}

vector<int> CovidGraph::getRecovered(Node* node, string start, string end){
    int startIdx = MMDDtoIdx(start);
    int endIdx = MMDDtoIdx(end);
    vector<int> Recovered;
    
    for (int i = startIdx; i <= endIdx;i++){
        Recovered.push_back(node->recovered_[i]);
    }
    return Recovered;
}


vector<int> CovidGraph::getConfirmed(Node* node, string start, string end){
    int startIdx = MMDDtoIdx(start);
    int endIdx = MMDDtoIdx(end);
    vector<int> Confirmed;

    for (int i = startIdx; i <= endIdx;i++){
        Confirmed.push_back(node->confirmed_[i]);
    }
    return Confirmed;
}

vector<Node*> CovidGraph::globalTopConfirmed(string start, string end, int N){
    vector<Node*> res;
    priority_queue<pair<int, Node*>> pq;

    for (Node* n : latNodes_) {
        vector<int> confirmed = getConfirmed(n, start, end);
        int tot = std::accumulate(confirmed.begin(), confirmed.end(), 0);
        pq.push({tot, n});
    }

    for (int i = 0; i < N; i++) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}

vector<Node*> CovidGraph::globalTopRecovered(string start, string end, int N){
    vector<Node*> res;
    priority_queue<pair<int, Node*>> pq;

    for (Node* n : latNodes_) {
        vector<int> recovered = getRecovered(n, start, end);
        int tot = std::accumulate(recovered.begin(), recovered.end(), 0);
        pq.push({tot, n});
    }

    for (int i = 0; i < N; i++) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}

vector<Node*> CovidGraph::globalTopDeaths(string start, string end, int N){
    vector<Node*> res;
    priority_queue<pair<int, Node*>> pq;

    for (Node* n : latNodes_) {
        vector<int> deaths = getDeaths(n, start, end);
        int tot = std::accumulate(deaths.begin(), deaths.end(), 0);
        pq.push({tot, n});
    }

    for (int i = 0; i < N; i++) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}

const vector<Node*>& CovidGraph::latNodes() {
    return latNodes_;
}

const vector<Node*>& CovidGraph::lonNodes() {
    return lonNodes_;
}


int CovidGraph::MMDDtoIdx(string MMDD) {
    string::iterator slash = find(MMDD.begin(), MMDD.end(), '/');
    int MM = stoi(string(MMDD.begin(), slash));
    int DD = stoi(string(slash + 1, MMDD.end()));
    vector<int> monthMap = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int res = -22 + DD;             // our data sets starts on 1/22
    for (int m = 0; m < MM; m++) {
        res += monthMap[m];
    }
    return res;
}