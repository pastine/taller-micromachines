//
// Created by casimiro on 23/10/19.
//

#ifndef TALLER_MICROMACHINES_CAMERA_H
#define TALLER_MICROMACHINES_CAMERA_H


#include "Renderizable.h"
#include "SDLWindow.h"

#define PIXELS_TO_M 29 // 29 * 5... dimentions of car

class Camera {
public:
    Camera();
    void prepare_frame();
    void render_object(Renderizable& object, int abs_x, int abs_y, int angle = 0, int id = 0);
    void show_frame();
    void set_center(int x, int y);
private:
    bool _is_in_frame(Renderizable& object, int abs_x, int abs_y);
    SDLWindow window;
    int center_x_mts;
    int center_y_mts;
    int center_x_px;
    int center_y_px;
};


#endif //TALLER_MICROMACHINES_CAMERA_H
