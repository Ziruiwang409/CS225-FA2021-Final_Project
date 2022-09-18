/**
 * @file Node.hpp
 * CovidGraph Final Project
 * 
 */
#include "covidgraph.h"
#include <cmath>
#include <assert.h>

using std::string;

Node::Node(string state, string country, string continent, float lat, float lon, float area) 
    : state_(state), country_(country), continent_(continent), latitude_(lat), longitude_(lon), area_(area)
{
    radius_ = sqrt(area_ / M_PI);
}

Node::Node(const string& cline, const string& dline, 
                       const string& rline, const map<string, vector<string>> infoMap_) 
{
    // convert input string into vector of substrs, discard ','
    vector<string> basics;
    string s = "";
    int date_idx = 0;
    int comma_count = 0;
    for (const char & c : cline) {
        if (c == ',') {
            ++comma_count;
            basics.push_back(s);
            s = "";
        } else {
            s += c;
        }
        ++date_idx;
        if (comma_count == 4)
            break;
    }

    string s_c = "";
    for (auto it = cline.begin() + date_idx; it != cline.end(); ++it) {
        if (*it == ',') {
            confirmed_.push_back(std::stoi(s_c));
            s_c = "";
        } else {
            s_c += *it;
        }
    }
    confirmed_.push_back(std::stoi(s_c));

    string s_d = "";
    for (auto it= dline.begin() + date_idx; it != dline.end(); ++it) {
        if (*it == ',') {
            deaths_.push_back(std::stoi(s_d));
            s_d = "";
        } else {
            s_d += *it;
        }
    }
    deaths_.push_back(std::stoi(s_d));

    string s_r = "";
    for (auto it = rline.begin() + date_idx; it != rline.end(); ++it) {
        if (*it == ',') {
            recovered_.push_back(std::stoi(s_r));
            s_r = "";
        } else {
            s_r += *it;
        }
    }
    recovered_.push_back(std::stoi(s_r));

    // basics: { state, country, lat, long }
    state_ = basics[0]; 
    country_ = basics[1];
    if (infoMap_.find(basics[1]) != infoMap_.end()) {
        continent_ = infoMap_.at(basics[1])[0];
        if (state_ == "") {
            area_ = std::stof(infoMap_.at(basics[1])[1]);
            population_ = std::stoi(infoMap_.at(basics[1])[2]);
        } else {
            area_ = 100000;                  // default area for a state/region/province
            population_ = 30000000;         // default population 30M
        }
    } else {
        // printout the countries that our map does not have their info
        assert(false);
        cout << basics[1] << endl;          
        continent_ = "Default continent";   
        area_ = 0;                          
    }
    latitude_ = std::stof(basics[2]);
    longitude_ = std::stof(basics[3]);
    radius_ = sqrt(area_ / M_PI);
}
