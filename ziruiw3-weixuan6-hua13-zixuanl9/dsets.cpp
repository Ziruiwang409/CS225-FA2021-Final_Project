#include "dsets.h"
#include <iostream>
#include <vector>

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        data_.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (data_[elem] < 0) {
        return elem;
    } else {
        int root = find(data_[elem]);
        data_[elem] = root;
        return root;
    }
}

void DisjointSets::setunion(int a, int b) {
    int a_idx = find(a);
    int b_idx = find(b);
    if (a_idx == b_idx) { return; }

    int new_size = data_[a_idx] + data_[b_idx];
    if (-a_idx < -b_idx) {
        data_[a_idx] = b_idx;
        data_[b_idx] = new_size;
    } else if (-b_idx < -a_idx) {
        data_[b_idx] = a_idx;
        data_[a_idx] = new_size;
    } else {
        data_[b_idx] = a_idx;
        data_[a_idx] = new_size;
    }
}

int DisjointSets::size(int elem) {
    int idx = find(elem);
    return -data_[idx];
}
