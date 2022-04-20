#include "noughts_and_crosses.h"
#include <p6/p6.h>

void draw_circle(p6::Context ctx)
{
    ctx.circle(p6::Center{ctx.mouse()},
               p6::Radius{0.3f});
}

void play_noughts_and_crosses()
{
    auto ctx   = p6::Context{{720, 720, "Hello p6"}};
    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});
    };
    ctx.start();
}