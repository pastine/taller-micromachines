//
// Created by casimiro on 23/10/19.
//

#ifndef TALLER_MICROMACHINES_CAMERA_H
#define TALLER_MICROMACHINES_CAMERA_H


#include "Renderizable.h"
#include "SDLWindow.h"

class Camera {
public:
    Camera();
    void prepare_frame();
    void render_object(Renderizable& object, int abs_x, int abs_y, int angle = 0);
    void show_frame();
private:
    bool _is_in_frame(Renderizable& object, int abs_x, int abs_y);
    SDLWindow window;
};


#endif //TALLER_MICROMACHINES_CAMERA_H
