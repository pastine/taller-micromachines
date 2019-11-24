//
// Created by casimiro on 24/11/19.
//

#include <iostream>
#include "client/ExplotionFrameResolver.h"

ExplotionFrameResolver::ExplotionFrameResolver() {
    int w = 253;
    int h = 204;
    current_frame = -1;

    frames.emplace_back(Area(0, 22, w, h));
    frames.emplace_back(Area(0, 22, w, h));

    frames.emplace_back(Area(253, 22, w, h));
    frames.emplace_back(Area(253, 22, w, h));

    frames.emplace_back(Area(253 + 253, 22, w, h));
    frames.emplace_back(Area(253 + 253, 22, w, h));

    frames.emplace_back(Area(0, 22 + 204, w, h));
    frames.emplace_back(Area(0, 22 + 204, w, h));

    frames.emplace_back(Area(253, 22 + 204, w, h));
    frames.emplace_back(Area(253, 22 + 204, w, h));

    frames.emplace_back(Area(253 + 253, 22 + 204, w, h));
    frames.emplace_back(Area(253 + 253, 22 + 204, w, h));
}

Area &ExplotionFrameResolver::resolve_frame() {
    current_frame += 1;
    std::cout << current_frame << "\n";
    return this->frames[current_frame % frames.size()];
}

bool ExplotionFrameResolver::is_done() {
    return current_frame == frames.size();
}
