#include "noughts_and_crosses.h"
#include <p6/p6.h>
#include <player.h>
#include <iostream>
#include <string>
#include <vector>

void draw_grid(p6::Context& ctx)
{
    ctx.stroke = p6::Color{1.f, 1.f, 1.f};
    ctx.line(glm::vec2{-0.333, 1}, glm::vec2{-0.333, -1});
    ctx.line(glm::vec2{0.333, 1}, glm::vec2{0.333, -1});
    ctx.line(glm::vec2{1, -0.333}, glm::vec2{-1, -0.333});
    ctx.line(glm::vec2{1, 0.333}, glm::vec2{-1, 0.333});
}

float set_hovered_cell_coord(const float& coord)
{
    if (coord < (-0.333)) {
        return (-0.666);
    }
    if (coord > (0.333)) {
        return 0.666;
    }
    return 0;
}

unsigned int convert_cell_coord(const float& coord)
{
    if (coord < (-0.333)) {
        return 0;
    }
    if (coord > (0.333)) {
        return 2;
    }
    return 1;
}

unsigned int convert_cell_position(const glm::vec2& position)
{
    return (convert_cell_coord(position.x) + 3 * convert_cell_coord(position.y));
}

float convert_index(const int& i)
{
    if (i == 0) {
        return -0.666;
    }
    if (i == 2 || i == 6) {
        return 0.666;
    }
    return 0;
}

glm::vec2 convert_cell_index(const unsigned int& i)
{
    float ligne   = convert_index(i % 3);
    float colonne = convert_index(i - (i % 3));
    return glm::vec2(ligne, colonne);
}

glm::vec2 set_hovered_cell_center(p6::Context& ctx)
{
    return glm::vec2(set_hovered_cell_coord(ctx.mouse().x), set_hovered_cell_coord(ctx.mouse().y));
}

void draw_square(p6::Context& ctx, const glm::vec2& position)
{
    ctx.fill = p6::Color{1.f, 1.f, 1.f, 0.75f};
    ctx.square(p6::Center{position},
               p6::Radius{0.3f},
               p6::Rotation{0_turn});
}

bool is_shape(const glm::vec2& cell, const std::vector<std::string>& vec)
{
    if (vec[convert_cell_position(cell)] != "") {
        return true;
    }

    return false;
}

void draw_shape(p6::Context& ctx, const glm::vec2& position)
{
    ctx.stroke_weight = 0.f;
    ctx.circle(p6::Center{position},
               p6::Radius{0.3f});
}

void draw_noughts_and_crosses(p6::Context& ctx, const std::vector<std::string>& vec, const Player& player1, const Player& player2)
{
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (vec[i] == player1.name) {
            ctx.fill = player1.color;
            draw_shape(ctx, convert_cell_index(i));
        }
        if (vec[i] == player2.name) {
            ctx.fill = player2.color;
            draw_shape(ctx, convert_cell_index(i));
        }
    }
}

Player change_current_player(const Player& current, const Player& player1, const Player& player2)
{
    if (current.name == player1.name) {
        return player2;
    }
    return player1;
}

bool compare_vec(const std::vector<unsigned int>& v1, const std::vector<unsigned int>& v2)
{
    std::vector<unsigned int> v_intersection;
    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::back_inserter(v_intersection));

    if (v_intersection.size() == 3) {
        return true;
    }
    return false;
}

bool is_player_win(const unsigned int& cell, const std::vector<std::string>& vec)
{
    std::string               active_color = vec[cell];
    std::vector<unsigned int> filter_vec;
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (vec[i] == active_color) {
            filter_vec.push_back(i);
        }
    }
    // win combinations
    std::vector<unsigned int> vec1{0, 1, 2};
    std::vector<unsigned int> vec2{3, 4, 5};
    std::vector<unsigned int> vec3{6, 7, 8};
    std::vector<unsigned int> vec4{0, 3, 6};
    std::vector<unsigned int> vec5{1, 4, 7};
    std::vector<unsigned int> vec6{2, 5, 8};
    std::vector<unsigned int> vec7{0, 4, 8};
    std::vector<unsigned int> vec8{2, 4, 6};

    if (compare_vec(vec1, filter_vec) || compare_vec(vec2, filter_vec) || compare_vec(vec3, filter_vec) || compare_vec(vec4, filter_vec) ||
        compare_vec(vec5, filter_vec) || compare_vec(vec6, filter_vec) || compare_vec(vec7, filter_vec) || compare_vec(vec8, filter_vec)) {
        return true;
    }
    return false;
}

bool is_end(const unsigned int& turn)
{
    if (turn == 9) {
        return true;
    }
    return false;
}

void play_noughts_and_crosses()
{
    Player player1;
    player1.name  = "red";
    player1.color = p6::Color{1.f, 0.f, 0.f, 1.f};

    Player player2;
    player2.name  = "blue";
    player2.color = p6::Color{0.f, 0.f, 1.f, 1.f};

    Player                   current_player = player1;
    unsigned int             turn           = 0;
    unsigned int             current_cell;
    std::vector<std::string> shapes(9);

    auto ctx = p6::Context{{720, 720, "Noughts and crosses"}};

    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});
        ctx.stroke_weight = 0.01f;

        draw_grid(ctx);

        // hover case
        glm::vec2 hovered_cell_center = set_hovered_cell_center(ctx);
        if (!is_shape(hovered_cell_center, shapes)) {
            ctx.stroke = current_player.color;
            draw_square(ctx, hovered_cell_center);
        }

        // add new shape
        ctx.mouse_pressed = [&](p6::MouseButton event) {
            if (!is_shape(event.position, shapes)) {
                current_cell         = convert_cell_position(event.position);
                shapes[current_cell] = current_player.name;
                if (is_player_win(current_cell, shapes)) {
                    ctx.stop();
                    std::cout << current_player.name << " win!" << std::endl;
                }
                current_player = change_current_player(current_player, player1, player2);
                turn++;
            }
        };

        draw_noughts_and_crosses(ctx, shapes, player1, player2);

        if (is_end(turn)) {
            std::cout << "You are all winers!" << std::endl;
            ctx.stop();
        }
    };

    ctx.start();
}