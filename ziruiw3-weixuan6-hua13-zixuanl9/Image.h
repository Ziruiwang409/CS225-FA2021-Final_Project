#pragma once
#include "cs225/PNG.h"
#include "Node.h"

using cs225::HSLAPixel;

class Image : public cs225::PNG {
    public:
        Image();
        Image(Image const & other);  // copy constructor

        /**
         * @brief create an empty white image with right size 
         *  according to base picture's size and node's area
         * 
         */
        Image(Node* node, unsigned base_H, unsigned base_W);

        void scale(double factor);
        void scale(unsigned w, unsigned h);

        /**
         * @brief draw self image as a colored circle according to node's comfirmed number
         * -------------------| Lv.4(VERY HIGH) |  Lv.3(HIGH) |  Lv.2(MODERATE) |  Lv.1(LOW)
         *  new cases over    |-----------------+-------------+-----------------+---------------
         *  past 28 days      | More than 500 	|   100-500   |    50-99 	    | Less than 50
         * -------------------------------------------------------------------------------------
         * @param node The target region
         * 
         */
        void drawRiskLevelCircle(const Node* node);

        /**
         * @brief draw self image as a colored circle according to node's death number
         * -------------------| Lv.4(VERY HIGH) |  Lv.3(HIGH) |  Lv.2(MODERATE) |  Lv.1(LOW)
         *  new cases over    |-----------------+-------------+-----------------+---------------
         *  past 28 days      | More than 2800 	|   1680-2800   |    540-1680 	    | Less than 540
         * -------------------------------------------------------------------------------------
         * @param node The target region
         * 
         */
        void drawDeathsLevelCircle(const Node* node);


        /**
         * @brief draw self image as a colored circle according to node's recovered number
         * -------------------| Lv.4(VERY HIGH) |  Lv.3(HIGH) |  Lv.2(MODERATE) |  Lv.1(LOW)
         *  new cases over    |-----------------+-------------+-----------------+---------------
         *  past 28 days      | More than 14000 |   8400      |    2800 	    | Less than 2800
         * -------------------------------------------------------------------------------------
         * @param node The target region
         * 
         */
        void drawRecoveredLevelCircle(const Node* node);


        /**
         * @brief draw self image as a colored circle according to nodes' confirmed num in one day
         *                    | Lv.4(VERY HIGH) |  Lv.3(HIGH) |  Lv.2(MODERATE) |  Lv.1(LOW)
         * -------------------|-----------------+-------------+-----------------+----------------
         *    cases a DAY     | More than 17.86 |  3.6-17.86  |    1.79-3.6 	| Less than 1.79
         * --------------------------------------------------------------------------------------
         * @param node The target region
         * @param dayIdx target date as index in confirmed data vector
         * 
         */
        void drawDayConfirmedCircle(const Node* node, int dayIdx);

        /**
         * @brief draw self image as a colored circle according to nodes' deaths mum in one day
         *                    | Lv.4(VERY HIGH) |  Lv.3(HIGH) |  Lv.2(MODERATE) |  Lv.1(LOW)
         * -------------------|-----------------+-------------+-----------------+---------------
         *    cases a DAY     |  More than 100  |   60-100    |      20-60     	|   Less than 20
         * --------------------------------------------------------------------------------------
         * @param node The target region
         * @param dayIdx target date as index in dearhs data vector
         * 
         */
        void drawDayDeathsCircle(const Node* node, int dayIdx);

        /**
         * @brief draw self image as a colored circle according to nodes' recovered rate in one day
         *                    | Lv.4(VERY HIGH) |  Lv.3(HIGH) |  Lv.2(MODERATE) |  Lv.1(LOW)
         * -------------------|-----------------+-------------+-----------------+---------------
         *    cases a DAY     | More than 500   |     300     |      100     	| Less than 100
         * --------------------------------------------------------------------------------------
         * @param node The target region
         * @param dayIdx target date as index in recovered data vector
         * 
         */
        void drawDayRecoveredCircle(const Node* node, int dayIdx);

        unsigned get_x() const;
        unsigned get_y() const;
        void set_x(unsigned x);
        void set_y(unsigned y);

    private:
        /**
         * @brief Image constructor helper function
         * 
         */
        void _initImage(const Node* node, unsigned base_H, unsigned base_W);

        /**
         * @brief private helper funtion to draw the self image into a circle of the input color
         * @param color the color we want the node to be
         * 
         */
        void _drawCircle(const HSLAPixel & color);

        int x_;
        int y_;
};