#include "noughts_and_crosses.h"
#include <p6/p6.h>
#include <iostream>

void draw_grid(p6::Context& ctx)
{
    ctx.line(glm::vec2{-0.333, 1}, glm::vec2{-0.333, -1});
    ctx.line(glm::vec2{0.333, 1}, glm::vec2{0.333, -1});
    ctx.line(glm::vec2{1, -0.333}, glm::vec2{-1, -0.333});
    ctx.line(glm::vec2{1, 0.333}, glm::vec2{-1, 0.333});
}

float set_hovered_cell_coord(float coord)
{
    if (coord < (-0.333)) {
        return (-0.666);
    }
    if (coord > (0.333)) {
        return 0.666;
    }
    return 0;
}

glm::vec2 set_hovered_cell_center(p6::Context& ctx)
{
    return glm::vec2(set_hovered_cell_coord(ctx.mouse().x), set_hovered_cell_coord(ctx.mouse().y));
}

void draw_square(p6::Context& ctx, glm::vec2& position)
{
    ctx.square(p6::Center{position},
               p6::Radius{0.3f},
               p6::Rotation{0_turn});
}

void play_noughts_and_crosses()
{
    auto ctx = p6::Context{{720, 720, "Hello p6"}};

    ctx.fill = p6::Color{1.f, 1.f, 1.f, 0.75f};

    ctx.update = [&]() {
        // fill background
        ctx.background({0.f, 0.f, 0.f});
        ctx.stroke        = p6::Color{1.f, 1.f, 1.f, 0.75f};
        ctx.stroke_weight = 0.01f;
        draw_grid(ctx);

        glm::vec2 hovered_cell_center = set_hovered_cell_center(ctx);

        draw_square(ctx, hovered_cell_center);

        ctx.mouse_pressed = [&](p6::MouseButton event) {
            draw_square(ctx, hovered_cell_center);
            ctx.fill = p6::Color{0.f, 1.f, 1.f, 1.f};
            std::cout << event.position.x << std::endl;
        };
    };

    ctx.start();
}