#include "noughts_and_crosses.h"
#include <p6/p6.h>

void play_noughts_and_crosses()
{
    auto ctx   = p6::Context{{720, 720, "Hello p6"}};
    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});
        ctx.stroke        = p6::Color{1.f, 1.f, 1.f, 0.75f};
        ctx.stroke_weight = 0.01f;
        ctx.line(glm::vec2{float(-2) / 6, 1}, glm::vec2{float(-2) / 6, -1});
        ctx.line(glm::vec2{float(2) / 6, 1}, glm::vec2{float(2) / 6, -1});
        ctx.line(glm::vec2{1, float(-2) / 6}, glm::vec2{-1, float(-2) / 6});
        ctx.line(glm::vec2{1, float(2) / 6}, glm::vec2{-1, float(2) / 6});
    };
    ctx.start();
}