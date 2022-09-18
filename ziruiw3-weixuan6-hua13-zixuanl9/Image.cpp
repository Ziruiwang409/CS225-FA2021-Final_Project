#include "Image.h"

#include <numeric>
#include <cmath>
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

Image::Image() : cs225::PNG() {
    x_ = 0;
    y_ = 0;
}

Image::Image(Node* node, unsigned base_H, unsigned base_W) : cs225::PNG() {
    _initImage(node, base_H, base_W);
}

Image::Image(Image const & other) : cs225::PNG(other) {
    x_ = other.x_;
    y_ = other.y_;
}

void Image::_initImage(const Node* node, unsigned base_H, unsigned base_W) {
    /* convert size of the image using radius. fitting base image */
    float A_earth = 196900000;              // earth surface area (sq. mi.)
    float A_baseImg = base_H * base_W;      // px
    int img_size = (float) A_baseImg * node->area_ / A_earth;
    int w = std::sqrt(img_size);
    int h = w;
    if (node->country_ == "Russia" || node->country_ == "Brazil") {
        resize(w/2, h/2);   // Russia and Brail are blocking the picture, try shrink the size 
    } else {
        resize(w, h);       // size of the node on the map, we use squre (circle)
    }
    
    /* convert lat and lon of node to x, y (currently divided evenly) */
    x_ = (float) base_W * node->longitude_ / 360 + base_W / 2 - w / 2;
    if (x_ < 0) { x_ = 0; }
    y_ = (float) base_H - base_H * node->latitude_ / 180 - base_H / 2 - h / 2;
    if (y_ < 0) { y_ = 0; }
    // assert(x_ < base_W);
    // assert(y_ < base_H);
}

void Image::drawRiskLevelCircle(const Node* node) {
    int tot_cases = std::accumulate(node->confirmed_.begin(), node->confirmed_.end(), 0);
    float period_num = node->confirmed_.size() / 28;
    float cases_per_period = tot_cases / period_num;
    double hue = 180 + cases_per_period / 500 * 180;
    if (hue >= 360) { hue = 0; }
    _drawCircle(HSLAPixel(hue, 0.7, 0.5, 0.6));
}

void Image::drawDeathsLevelCircle(const Node* node) {
    int tot_cases = std::accumulate(node->deaths_.begin(), node->deaths_.end(), 0);
    float period_num = node->deaths_.size() / 28;
    float cases_per_period = tot_cases / period_num;
    double hue = 210 + cases_per_period / 2800 * 150;
    if (hue >= 360) { hue = 0; }
    _drawCircle(HSLAPixel(hue, 0.7, 0.5, 0.6));
}

void Image::drawRecoveredLevelCircle(const Node* node) {
    int tot_cases = std::accumulate(node->recovered_.begin(), node->recovered_.end(), 0);
    float period_num = node->recovered_.size() / 28;
    float cases_per_period = tot_cases / period_num;
    double hue = 240 - cases_per_period / 14000 * 120;
    if (hue < 120) { hue = 120; }
    _drawCircle(HSLAPixel(hue, 0.7, 0.5, 0.6));
}

void Image::drawDayConfirmedCircle(const Node* node, int dayIdx) {
    int cases = node->confirmed_[dayIdx];
    double hue = 180 + cases / 17.86 * 180;
    if (hue >= 360) { hue = 0; }            // hue: [180, 360)
    _drawCircle(HSLAPixel(hue, 0.7, 0.5, 0.6));
}

void Image::drawDayDeathsCircle(const Node* node, int dayIdx) {
    int cases = node->deaths_[dayIdx];
    double hue = 210 + cases / 100 * 150;
    if (hue >= 360) { hue = 0; }            // hue: [210, 360)
    _drawCircle(HSLAPixel(hue, 0.7, 0.5, 0.6));
}

void Image::drawDayRecoveredCircle(const Node* node, int dayIdx) {
    int cases = node->recovered_[dayIdx];
    double hue = 240 - cases / 500 * 120;   // hue: [240, 120]
    if (hue < 120) { hue = 120; }
    _drawCircle(HSLAPixel(hue, 0.7, 0.5, 0.6));
}

void Image::_drawCircle(const HSLAPixel & color) {
    int r = width() / 2;       // (centerX, centerY) = (r, r)
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            int dist = (x - r) * (x - r) + (y - r) * (y - r);
            HSLAPixel & p = getPixel(x, y);
            p.h = color.h;
            p.s = color.s;
            if (dist <= (r - 5) * (r - 5)) {
                p.a = color.a;
                p.l = color.l;
            } else if (dist > (r - 5) * (r - 5) && dist <= r * r) {
                p.l = 0.2;      // dark edge
            } else {
                p.a = 0;        // transparent
            }
        }
    }
}


unsigned Image::get_x() const { return x_; }

unsigned Image::get_y() const { return y_; }

void Image::set_x(unsigned x) { x_ = x; }

void Image::set_y(unsigned y) { y_ = y; }