#pragma once
#include "Image.h"
#include "cs225/PNG.h"
#include "covidgraph.h"
#include "Animation.h"

#include <vector>

using cs225::PNG;

class Visualization {
    public:
        Visualization(const Image &basePic);
        ~Visualization();
        Visualization(const Visualization &other);
        const Visualization & operator=(const Visualization &other);
        void addSticker(Image* sticker);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        PNG render() const;
        
        /**
         * @brief risk level of all target nodes to a single static PNG
         * @param nodes vector containing nodes of target locations
         * @return a static PNG representing target locations' riskLevel avaiable in 2020,
         * determined by the confirmed data
         * 
         */ 
        PNG riskLevelPNG(const vector<Node*> & nodes);

        /**
         * @brief risk level of all target nodes to a single static PNG
         * @param nodes vector containing nodes of target locations
         * @return a static PNG representing target locations' deathLevel avaiable in 2020,
         * determined by the deaths data
         * 
         */ 
        PNG deathsLevelPNG(const vector<Node*> & nodes);

        /**
         * @brief risk level of all target nodes to a single static PNG
         * @param nodes vector containing nodes of target locations
         * @return a static PNG representing target locations' recoveredLevel avaiable in 2020,
         * determined by the recovered data
         * 
         */ 
        PNG recoveredLevelPNG(const vector<Node*> & nodes);
        
        /**
         * @brief Animate all nodes' confirmed status in the given period of time,
         *  assuming valid input
         * @param nodes vector containing nodes of target locations
         * @param start start date in format: MM/DD
         * @param end end date in format: MM/DD
         * @return an Animation object representing nodes' confirmed status
         * 
         */
        Animation confirmedGIF(const vector<Node*> & nodes, string start, string end);

        /**
         * @brief Animate all nodes' deaths status in the given period of time,
         *  assuming valid input
         * @param nodes vector containing nodes of target locations
         * @param start start date in format: MM/DD
         * @param end end date in format: MM/DD
         * @return an Animation object representing nodes' deaths status
         * 
         */
        Animation deathsGIF(const vector<Node*> & nodes, string start, string end);

        /**
         * @brief Animate all nodes' recovered status in the given period of time,
         *  assuming valid input
         * @param nodes vector containing nodes of target locations
         * @param start start date in format: MM/DD
         * @param end end date in format: MM/DD
         * @return an Animation object representing nodes' recovered status
         * 
         */
        Animation recoveredGIF(const vector<Node*> & nodes, string start, string end);
    
    private:
        void _clearImgVec();
        void copy(const Visualization &other);

        /**
         * @brief convert a MM/DD string to index of C/D/R vector
         *  index 0 will be first available data, in our case: 1/22
         * @param MMDD date string to convert, in the format MM/DD
         * 
         */
        int MMDDtoIdx(string MMDD);
        
        /**
         * @brief base picture of the visualization, share by all functions
         * 
         */
        Image* basePicture;

        /**
         * @brief imgVec to help visualization, MUST BE CLEARED after every usage,
         * because different function share the same imgVec
         * 
         */
        std::vector<Image*> imgVec;
 };
