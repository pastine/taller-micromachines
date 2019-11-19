#ifndef TALLER_MICROMACHINES_CAMERA_H
#define TALLER_MICROMACHINES_CAMERA_H


#include "Renderizable.h"
#include "SDLWindow.h"
#include "CarLivesDrawer.h"
#include "SDLText.h"

class Camera {
public:
    Camera();

    void prepare_frame();

    void render_object(Renderizable &object, int abs_x, int abs_y,
                       int angle = 0, int id = 0, bool moving = false);

    void show_frame();

    void set_center(int x, int y);

    void render_car_lives(int lives);

    void render_text();

private:
    bool _is_in_frame(Renderizable &object, int abs_x, int abs_y);

    SDLWindow window;
    int center_x_cms;
    int center_y_cms;
    int center_x_px;
    int center_y_px;
    SDLText text_creator;
};


#endif //TALLER_MICROMACHINES_CAMERA_H
