#ifndef TALLER_MICROMACHINES_CAMERA_H
#define TALLER_MICROMACHINES_CAMERA_H


#include "Renderizable.h"
#include "SDLWindow.h"
#include "CarLivesDrawer.h"
#include "SDLText.h"
#include "../../client/entities/MudSplatter.h"

class Camera {
public:
    Camera();

    void prepare_frame();

    void render_object(Renderizable &object, float abs_x, float abs_y,
                       float angle = 0, int id = 0, float speed = 0);

    void show_frame();

    void set_center(float x, float y);

    void render_car_lives(int lives);

    void render_text();

    void render_splatter();

private:
    bool _is_in_frame(Renderizable &object, float abs_x, float abs_y);

    SDLWindow window;
    float center_x_cms;
    float center_y_cms;
    float center_x_px;
    float center_y_px;
    SDLText text_creator;
};


#endif //TALLER_MICROMACHINES_CAMERA_H
