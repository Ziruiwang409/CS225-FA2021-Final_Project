#include "visualization.h"
#include "cs225/HSLAPixel.h"

Visualization::Visualization(const Image &basePic) {
    basePicture = new Image(basePic);
}

Visualization::~Visualization() {
    delete basePicture;
    _clearImgVec();
}

void Visualization::_clearImgVec() {
    for (Image* img_ptr : imgVec) {
        delete img_ptr;
    }
    imgVec.erase(imgVec.begin(), imgVec.end());
}

Visualization::Visualization(const Visualization &other) {
    copy(other);
}

void Visualization::copy(const Visualization &other) {
    basePicture = new Image(*(other.basePicture));
    for (unsigned int idx = 0; idx < other.imgVec.size(); idx++) {
        imgVec.push_back(new Image(*(other.imgVec[idx])));
    }
}

const Visualization& Visualization::operator=(const Visualization &other) {
    _clearImgVec();
    copy(other);
    return *this;
}

void Visualization::addSticker(Image* sticker) {
    imgVec.push_back(sticker);
}

void Visualization::removeSticker(unsigned index) {
    // possible need to check valid index
    if ((index < imgVec.size()) && (index >= 0)) {
        delete imgVec[index];
        imgVec.erase(imgVec.begin() + index);
    }
}

Image* Visualization::getSticker(unsigned index) {
    if (index >= 0 && index < imgVec.size()) {
        return imgVec[index];
    }
    return NULL;
}

PNG Visualization::riskLevelPNG(const vector<Node*> & nodes) {
    for (Node* n : nodes) {
        Image* sticker = new Image(n, basePicture->height(), basePicture->width());
        sticker->drawRiskLevelCircle(n);
        addSticker(sticker);
    }
    PNG res = render();
    _clearImgVec();
    return res;
}

PNG Visualization::deathsLevelPNG(const vector<Node*> & nodes) {
    for (Node* n : nodes) {
        Image* sticker = new Image(n, basePicture->height(), basePicture->width());
        sticker->drawDeathsLevelCircle(n);
        addSticker(sticker);
    }
    PNG res = render();
    _clearImgVec();
    return res;
}

PNG Visualization::recoveredLevelPNG(const vector<Node*> & nodes) {
    for (Node* n : nodes) {
        Image* sticker = new Image(n, basePicture->height(), basePicture->width());
        sticker->drawRecoveredLevelCircle(n);
        addSticker(sticker);
    }
    PNG res = render();
    _clearImgVec();
    return res;
}


Animation Visualization::confirmedGIF(const vector<Node*> & nodes, string start, string end) {
    Animation res;
    for (int i = MMDDtoIdx(start); i <= MMDDtoIdx(end); i++) {
        for (Node* n : nodes) {
            Image* sticker = new Image(n, basePicture->height(), basePicture->width());
            sticker->drawDayConfirmedCircle(n, i);
            addSticker(sticker);
        }
        PNG oneFrame = render();
        res.addFrame(oneFrame);
        _clearImgVec();
    }
    return res;
}

Animation Visualization::deathsGIF(const vector<Node*> & nodes, string start, string end) {
    Animation res;
    for (int i = MMDDtoIdx(start); i <= MMDDtoIdx(end); i++) {
        for (Node* n : nodes) {
            Image* sticker = new Image(n, basePicture->height(), basePicture->width());
            sticker->drawDayDeathsCircle(n, i);
            addSticker(sticker);
        }
        PNG oneFrame = render();
        res.addFrame(oneFrame);
        _clearImgVec();
    }
    return res;
}

Animation Visualization::recoveredGIF(const vector<Node*> & nodes, string start, string end) {
    Animation res;
    for (int i = MMDDtoIdx(start); i <= MMDDtoIdx(end); i++) {
        for (Node* n : nodes) {
            Image* sticker = new Image(n, basePicture->height(), basePicture->width());
            sticker->drawDayRecoveredCircle(n, i);
            addSticker(sticker);
        }
        PNG oneFrame = render();
        res.addFrame(oneFrame);
        _clearImgVec();
    }
    return res;
}

int Visualization::MMDDtoIdx(string MMDD) {
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

PNG Visualization::render() const {
    PNG result(*basePicture);

    for (unsigned int idx = 0; idx < imgVec.size(); idx++) {  // iterate through imgs

        Image* curr_img = imgVec[idx];
        unsigned check_wid = curr_img->get_x() + curr_img->width();
        unsigned check_hei = curr_img->get_y() + curr_img->height();

        if (check_wid > result.width() && check_hei > result.height()) {
            result.resize(check_wid, check_hei);
        } else if (check_wid > result.width()) {
            result.resize(check_wid, result.height());
        } else if (check_hei > result.height()) {
            result.resize(result.width(), check_hei);
        }

        for (unsigned int x = 0; x < curr_img->width(); x++) {
            for (unsigned int y = 0; y < curr_img->height(); y++) {
                cs225::HSLAPixel& pixel = curr_img->getPixel(x, y);
                cs225::HSLAPixel& toDraw = result.getPixel(curr_img->get_x() + x, curr_img->get_y() + y);
                if (pixel.a != 0) {
                    toDraw.a = pixel.a;
                    toDraw.h = pixel.h;
                    toDraw.l = pixel.l;
                    toDraw.s = pixel.s;
                }
            }
        }
    }

    return result;
}
