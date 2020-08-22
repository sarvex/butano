#include "bf_game_stage_3.h"

#include "btn_display.h"
#include "btn_music_items.h"
#include "btn_sound_items.h"
#include "btn_regular_bg_items_stage_3.h"
#include "btn_sprite_items_stage_3_intro.h"
#include "btn_sprite_items_stage_3_blonde.h"
#include "btn_sprite_items_stage_3_intro_alt.h"
#include "btn_sprite_items_stage_3_monsters_1.h"
#include "btn_sprite_items_stage_3_monsters_2.h"
#include "btn_sprite_items_stage_3_dragon_man.h"
#include "btn_regular_bg_items_mountain_clouds.h"
#include "btn_sprite_items_stage_3_characters_1.h"
#include "btn_sprite_items_stage_3_characters_2.h"
#include "bf_constants.h"
#include "bf_game_bullet_util.h"

namespace bf::game::stage_3
{

namespace
{
    constexpr const int start_y = -(btn::display::height() + 64) / 2;

    constexpr const btn::span<const enemy_bullet_event> no_bullets;

    [[nodiscard]] constexpr btn::fixed move_y(btn::fixed y)
    {
        return y + constants::background_speed;
    }

    [[nodiscard]] constexpr btn::array<enemy_data::graphics_indexes_group, 4> _create_graphics_indexes(
        int initial_index)
    {
        return btn::array<enemy_data::graphics_indexes_group, 4> {
            enemy_data::graphics_indexes_group{ uint16_t(initial_index), uint16_t(initial_index + 1),
                        uint16_t(initial_index), uint16_t(initial_index + 2) },
            enemy_data::graphics_indexes_group{ uint16_t(initial_index), uint16_t(initial_index + 1),
                        uint16_t(initial_index), uint16_t(initial_index + 2) },
            enemy_data::graphics_indexes_group{ uint16_t(initial_index), uint16_t(initial_index + 1),
                        uint16_t(initial_index), uint16_t(initial_index + 2) },
            enemy_data::graphics_indexes_group{ uint16_t(initial_index), uint16_t(initial_index + 1),
                        uint16_t(initial_index), uint16_t(initial_index + 2) }
        };
    }


    // blonde:

    constexpr const enemy_data blonde(
        btn::sprite_items::stage_3_blonde, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::enemy_death_ninja_14, btn::fixed_size(46, 62), _create_graphics_indexes(0), 10, 10);

    constexpr const enemy_move_event blonde_moves[] = {
        enemy_move_event(btn::fixed_point(0.75, move_y(0.15)), 75, false),
        enemy_move_event(btn::fixed_point(0.75, move_y(-1.1)), 1,  false),
    };

    constexpr const enemy_move_event blonde_flipped_moves[] = {
        blonde_moves[0].flipped(),
        blonde_moves[1].flipped(),
    };


    // white_caveman:

    constexpr const btn::array<enemy_data::graphics_indexes_group, 4> white_caveman_graphics_indexes = {
        enemy_data::graphics_indexes_group{ 0, 1, 0, 2 },
        enemy_data::graphics_indexes_group{ 5, 5, 5, 5 },
        enemy_data::graphics_indexes_group{ 3, 3, 4, 4 },
        enemy_data::graphics_indexes_group{ 0, 1, 0, 2 }
    };

    constexpr const enemy_data white_caveman(
        btn::sprite_items::stage_3_characters_1, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_4, btn::fixed_size(38, 52), white_caveman_graphics_indexes, 22, 22);

    constexpr const enemy_move_event white_caveman_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  30, 0,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0)),    5,  1,  false),
        enemy_move_event(btn::fixed_point(1, move_y(0.5)),  60, 2,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0)),    5,  1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  1,  0,  false),
    };

    constexpr const enemy_move_event white_caveman_flipped_moves[] = {
        white_caveman_moves[0].flipped(),
        white_caveman_moves[1].flipped(),
        white_caveman_moves[2].flipped(),
        white_caveman_moves[3].flipped(),
        white_caveman_moves[4].flipped(),
    };


    // black_caveman:

    constexpr const btn::array<enemy_data::graphics_indexes_group, 4> black_caveman_graphics_indexes = {
        enemy_data::graphics_indexes_group{ 6, 7, 6, 8 },
        enemy_data::graphics_indexes_group{ 9, 10, 11, 11 },
        enemy_data::graphics_indexes_group{ 6, 7, 6, 8 },
        enemy_data::graphics_indexes_group{ 6, 7, 6, 8 }
    };

    constexpr const enemy_data black_caveman(
        btn::sprite_items::stage_3_characters_1, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_5, btn::fixed_size(38, 52), black_caveman_graphics_indexes, 16, 16);

    constexpr const enemy_move_event black_caveman_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  45, 0,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0)),    30, 1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  1,  0,  false),
    };

    constexpr const enemy_move_event black_caveman_flipped_moves[] = {
        black_caveman_moves[0].flipped(),
        black_caveman_moves[1].flipped(),
        black_caveman_moves[2].flipped(),
    };

    constexpr const enemy_bullet_event black_caveman_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_BIG,      1,   45 + 15),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_SMALL,    1,   8),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_SMALL,    1,   8),
    };

    constexpr const enemy_bullet_event black_caveman_flipped_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_BIG,      1,   45 + 15),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_SMALL,    1,   8),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_SMALL,    1,   8),
    };


    // green_cavegirl:

    constexpr const btn::array<enemy_data::graphics_indexes_group, 4> green_cavegirl_graphics_indexes = {
        enemy_data::graphics_indexes_group{ 12, 13, 12, 14 },
        enemy_data::graphics_indexes_group{ 15, 15, 15, 15 },
        enemy_data::graphics_indexes_group{ 12, 13, 12, 14 },
        enemy_data::graphics_indexes_group{ 12, 13, 12, 14 },
    };

    constexpr const enemy_data green_cavegirl(
        btn::sprite_items::stage_3_characters_1, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::enemy_death_ninja_11, btn::fixed_size(46, 60), green_cavegirl_graphics_indexes, 12, 12);

    constexpr const enemy_move_event green_cavegirl_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  60, 0,  false),

        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  true),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  true),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  true),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.1)),  4,  1,  true),

        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  1,  0,  false),
    };

    constexpr const enemy_move_event green_cavegirl_flipped_moves[] = {
        green_cavegirl_moves[0].flipped(),

        green_cavegirl_moves[1].flipped(),
        green_cavegirl_moves[2].flipped(),
        green_cavegirl_moves[3].flipped(),
        green_cavegirl_moves[4].flipped(),
        green_cavegirl_moves[5].flipped(),
        green_cavegirl_moves[6].flipped(),
        green_cavegirl_moves[7].flipped(),
        green_cavegirl_moves[8].flipped(),

        green_cavegirl_moves[9].flipped(),
    };

    constexpr const enemy_bullet_event green_cavegirl_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(1, 1, 0.9),   60),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(-1, 1, 0.9),  4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(0, 1, 0.9),   4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(-1, -1, 0.9), 4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(-1, 0, 0.9),  4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(1, -1, 0.9),  4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(1, 0, 0.9),   4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(0, -1, 0.9),  4),
    };


    // cavebat:

    constexpr const enemy_data cavebat(btn::sprite_items::stage_3_monsters_1, enemy_data::death_anim_type::ROTATE,
                                       btn::sound_items::dinosaur_5, btn::fixed_size(26, 18), 0, 1, 8, 10);

    constexpr const enemy_move_event cavebat_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.25)), 1, false),
    };

    constexpr const enemy_move_event cavebat_flipped_moves[] = {
        cavebat_moves[0].flipped()
    };

    constexpr const enemy_bullet_event cavebat_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::SMALL, 0.9,                           60),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(0, 1, 0.9),   4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(-1, 1, 0.9),  4),
        enemy_bullet_event(enemy_bullet_type::SMALL, direction_vector(1, 1, 0.9),   4),
    };


    // lizard:

    constexpr const btn::array<enemy_data::graphics_indexes_group, 4> grasshopper_graphics_indexes = {
        enemy_data::graphics_indexes_group{ 2, 2, 2, 2 },
        enemy_data::graphics_indexes_group{ 3, 4, 3, 4 },
        enemy_data::graphics_indexes_group{ 2, 2, 2, 2 },
        enemy_data::graphics_indexes_group{ 2, 2, 2, 2 },
    };

    constexpr const enemy_data grasshopper(
        btn::sprite_items::stage_3_monsters_1, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::dinosaur_4, btn::fixed_size(56, 22), grasshopper_graphics_indexes, 22, 22);

    constexpr const enemy_move_event grasshopper_moves[] = {
        enemy_move_event(btn::fixed_point(0,    move_y(0)),     30, 0,  false),

        enemy_move_event(btn::fixed_point(1.5,  move_y(0.7)),   30, 1,  false),
        enemy_move_event(btn::fixed_point(0,    move_y(0)),     30, 0,  false),

        enemy_move_event(btn::fixed_point(-1.5, move_y(0.7)),   30, 1,  true),
        enemy_move_event(btn::fixed_point(0,    move_y(0)),     30, 0,  true),

        enemy_move_event(btn::fixed_point(1.5,  move_y(0.7)),   30, 1,  false),
        enemy_move_event(btn::fixed_point(0,    move_y(0)),     30, 0,  false),

        enemy_move_event(btn::fixed_point(-1.5, move_y(0.7)),   30, 1,  true),
        enemy_move_event(btn::fixed_point(0,    move_y(0)),     30, 0,  true),
    };

    constexpr const enemy_move_event grasshopper_flipped_moves[] = {
        grasshopper_moves[0].flipped(),

        grasshopper_moves[1].flipped(),
        grasshopper_moves[2].flipped(),

        grasshopper_moves[3].flipped(),
        grasshopper_moves[4].flipped(),

        grasshopper_moves[5].flipped(),
        grasshopper_moves[6].flipped(),

        grasshopper_moves[7].flipped(),
        grasshopper_moves[8].flipped(),
    };


    // lizard:

    constexpr const enemy_data lizard(
        btn::sprite_items::stage_3_monsters_1, enemy_data::death_anim_type::HORIZONTAL_SCALE,
        btn::sound_items::dinosaur_3, btn::fixed_size(62, 42), _create_graphics_indexes(5), 28, 28);

    constexpr const enemy_move_event lizard_moves[] = {
        enemy_move_event(btn::fixed_point(0.3,  move_y(0.5)),   1,  false),
    };

    constexpr const enemy_move_event lizard_flipped_moves[] = {
        lizard_moves[0].flipped()
    };


    // dragon_man:

    constexpr const enemy_data dragon_man(
        btn::sprite_items::stage_3_dragon_man, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::dinosaur_2, btn::fixed_size(42, 62), _create_graphics_indexes(0), 280, 200);

    constexpr const enemy_move_event dragon_man_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(-0.25)), 270, true),
        enemy_move_event(btn::fixed_point(-0.2, 0),          240, true),
        enemy_move_event(btn::fixed_point(-0.2, 0),          240, false),
        enemy_move_event(btn::fixed_point(0, move_y(-0.25)), 1,   false),
    };

    constexpr const enemy_bullet_event dragon_man_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0, 1, 1),     100),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, 1, 1),  1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, 1, 1),   1),

        enemy_bullet_event(enemy_bullet_type::BIG,      1,  80),
        enemy_bullet_event(enemy_bullet_type::SMALL,    1,  10),
        enemy_bullet_event(enemy_bullet_type::SMALL,    1,  10),

        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0, 1, 1),     80),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, 1, 1),  1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, 1, 1),   1),

        enemy_bullet_event(enemy_bullet_type::HUGE,      0.9,  80),

        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0, 1, 1),     80),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, 1, 1),  1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, 1, 1),   1),

        enemy_bullet_event(enemy_bullet_type::BIG,      1,  80),
        enemy_bullet_event(enemy_bullet_type::SMALL,    1,  10),
        enemy_bullet_event(enemy_bullet_type::SMALL,    1,  10),

        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0, 1, 1),     80),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, 1, 1),  1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, 1, 1),   1),

        enemy_bullet_event(enemy_bullet_type::HUGE,     0.9,  80),
    };

    // red_cavegirl:

    constexpr const btn::array<enemy_data::graphics_indexes_group, 4> red_cavegirl_graphics_indexes = {
        enemy_data::graphics_indexes_group{ 0, 1, 0, 2 },
        enemy_data::graphics_indexes_group{ 4, 4, 4, 4 },
        enemy_data::graphics_indexes_group{ 5, 5, 5, 5 },
        enemy_data::graphics_indexes_group{ 0, 1, 0, 2 },
    };

    constexpr const enemy_data red_cavegirl(
        btn::sprite_items::stage_3_characters_2, enemy_data::death_anim_type::ROTATE,
        btn::sound_items::enemy_death_ninja_14, btn::fixed_size(46, 60), red_cavegirl_graphics_indexes, 16, 16);

    constexpr const enemy_move_event red_cavegirl_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  60, 0,  false),

        enemy_move_event(btn::fixed_point(0, move_y(0)),    10, 2,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  50, 0,  false),

        enemy_move_event(btn::fixed_point(0, move_y(0)),    10, 1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  50, 0,  false),
    };

    constexpr const enemy_move_event red_cavegirl_flipped_moves[] = {
        red_cavegirl_moves[0].flipped(),

        red_cavegirl_moves[1].flipped(),
        red_cavegirl_moves[2].flipped(),

        red_cavegirl_moves[3].flipped(),
        red_cavegirl_moves[4].flipped(),
    };

    constexpr const enemy_bullet_event red_cavegirl_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::SMALL,    1, 60),
        enemy_bullet_event(enemy_bullet_type::BIG,      1, 60),
    };

    // egg_caveman:

    constexpr const btn::array<enemy_data::graphics_indexes_group, 4> egg_caveman_graphics_indexes = {
        enemy_data::graphics_indexes_group{ 6, 7, 6, 8 },
        enemy_data::graphics_indexes_group{ 9, 10, 11, 11 },
        enemy_data::graphics_indexes_group{ 6, 7, 6, 8 },
        enemy_data::graphics_indexes_group{ 6, 7, 6, 8 }
    };

    constexpr const enemy_data egg_caveman(
        btn::sprite_items::stage_3_characters_2, enemy_data::death_anim_type::VERTICAL_SCALE,
        btn::sound_items::scream_6, btn::fixed_size(42, 62), egg_caveman_graphics_indexes, 18, 18);

    constexpr const enemy_move_event egg_caveman_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  45, 0,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0)),    30, 1,  false),
        enemy_move_event(btn::fixed_point(0, move_y(0.5)),  1,  0,  false),
    };

    constexpr const enemy_move_event egg_caveman_flipped_moves[] = {
        egg_caveman_moves[0].flipped(),
        egg_caveman_moves[1].flipped(),
        egg_caveman_moves[2].flipped(),
    };

    constexpr const enemy_bullet_event egg_caveman_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_SMALL,            direction_vector(1, 0, 0.9),        45 + 15),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_SMALL,            direction_vector(0.5, 0.5, 0.9),    1),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_SMALL,            direction_vector(0, 1, 0.9),        1),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_SMALL,            0.9,                                1),
    };

    constexpr const enemy_bullet_event egg_caveman_flipped_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_SMALL,    direction_vector(-1, 0, 0.9),       45 + 15),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_SMALL,    direction_vector(-0.5, 0.5, 0.9),   1),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_SMALL,    direction_vector(0, 1, 0.9),        1),
        enemy_bullet_event(enemy_bullet_type::CAVEMAN_FLIPPED_SMALL,    0.9,                                1),
    };


    // minidino:

    constexpr const enemy_data minidino(btn::sprite_items::stage_3_monsters_2, enemy_data::death_anim_type::VERTICAL_SCALE,
                                      btn::sound_items::dinosaur_2, btn::fixed_size(58, 46), _create_graphics_indexes(0), 26, 26);

    constexpr const enemy_move_event minidino_moves[] = {
        enemy_move_event(btn::fixed_point(1.2, move_y(0.6)), 60, false),
        enemy_move_event(btn::fixed_point(-1.2, move_y(0.6)), 60, true),
        enemy_move_event(btn::fixed_point(1.2, move_y(0.6)), 60, false),
        enemy_move_event(btn::fixed_point(-1.2, move_y(0.6)), 1, true),
    };

    constexpr const enemy_move_event minidino_flipped_moves[] = {
        minidino_moves[0].flipped(),
        minidino_moves[1].flipped(),
        minidino_moves[2].flipped(),
        minidino_moves[3].flipped(),
    };

    constexpr const enemy_bullet_event minidino_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, 0.5, 0.9),     60),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-1, 0, 0.9),         1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, -0.5, 0.9),    1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    0.9,                                  1),

        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, 0.5, 0.9),      57),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(1, 0, 0.9),          1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, -0.5, 0.9),     1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    0.9,                                  1),
    };

    constexpr const enemy_bullet_event minidino_flipped_bullets[] = {
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, 0.5, 0.9),      60),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(1, 0, 0.9),          1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(0.5, -0.5, 0.9),     1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    0.9,                                  1),

        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, 0.5, 0.9),     57),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-1, 0, 0.9),         1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    direction_vector(-0.5, -0.5, 0.9),    1),
        enemy_bullet_event(enemy_bullet_type::SMALL,    0.9,                                  1),
    };


    // turtle:

    constexpr const enemy_data turtle(btn::sprite_items::stage_3_monsters_2, enemy_data::death_anim_type::VERTICAL_SCALE,
                                      btn::sound_items::enemy_death_rpg_12, btn::fixed_size(52, 30), _create_graphics_indexes(3), 22, 22);

    constexpr const enemy_move_event turtle_moves[] = {
        enemy_move_event(btn::fixed_point(0, move_y(0.4)), 1, false),
    };

    constexpr const enemy_move_event turtle_flipped_moves[] = {
        turtle_moves[0].flipped()
    };


    // enemy events:

    constexpr const enemy_event enemy_events[] = {

        // level 5 slow (22s)

        enemy_event(grasshopper, btn::fixed_point(-20, start_y), grasshopper_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(grasshopper, btn::fixed_point(50, start_y), grasshopper_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(cavebat, btn::fixed_point(-35, start_y), cavebat_moves, cavebat_bullets, 60, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(35, start_y), cavebat_flipped_moves, cavebat_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(-55, start_y), blonde_moves, no_bullets, 85, enemy_drop_type::GEM),

        enemy_event(white_caveman, btn::fixed_point(-35, start_y), white_caveman_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(white_caveman, btn::fixed_point(35, start_y), white_caveman_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(black_caveman, btn::fixed_point(-50, start_y), black_caveman_moves, black_caveman_bullets, 60, enemy_drop_type::NONE),
        enemy_event(black_caveman, btn::fixed_point(50, start_y), black_caveman_flipped_moves, black_caveman_flipped_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(-55, start_y), blonde_moves, no_bullets, 60, enemy_drop_type::GEM),

        enemy_event(cavebat, btn::fixed_point(-50, start_y), cavebat_moves, cavebat_bullets, 60, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(0, start_y), cavebat_flipped_moves, cavebat_bullets, 60, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(50, start_y), cavebat_flipped_moves, cavebat_bullets, 70, enemy_drop_type::NONE),

        enemy_event(grasshopper, btn::fixed_point(-20, start_y), grasshopper_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(grasshopper, btn::fixed_point(50, start_y), grasshopper_flipped_moves, no_bullets, 70, enemy_drop_type::NONE),

        enemy_event(black_caveman, btn::fixed_point(-50, start_y), black_caveman_moves, black_caveman_bullets, 70, enemy_drop_type::NONE),
        enemy_event(white_caveman, btn::fixed_point(-35, start_y), white_caveman_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(black_caveman, btn::fixed_point(50, start_y), black_caveman_flipped_moves, black_caveman_flipped_bullets, 70, enemy_drop_type::NONE),
        enemy_event(white_caveman, btn::fixed_point(35, start_y), white_caveman_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 90, enemy_drop_type::GEM),

        // level 5 fast (23s)

        enemy_event(lizard, btn::fixed_point(35, start_y), lizard_flipped_moves, no_bullets, 50, enemy_drop_type::NONE),
        enemy_event(lizard, btn::fixed_point(-35, start_y), lizard_moves, no_bullets, 50, enemy_drop_type::NONE),

        enemy_event(cavebat, btn::fixed_point(-50, start_y), cavebat_moves, cavebat_bullets, 50, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(50, start_y), cavebat_flipped_moves, cavebat_bullets, 50, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(-20, start_y), cavebat_flipped_moves, cavebat_bullets, 70, enemy_drop_type::NONE),

        enemy_event(green_cavegirl, btn::fixed_point(35, start_y), green_cavegirl_flipped_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(-35, start_y), green_cavegirl_moves, green_cavegirl_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 80, enemy_drop_type::GEM),

        enemy_event(grasshopper, btn::fixed_point(50, start_y), grasshopper_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(grasshopper, btn::fixed_point(-50, start_y), grasshopper_moves, no_bullets, 80, enemy_drop_type::NONE),

        enemy_event(green_cavegirl, btn::fixed_point(35, start_y), green_cavegirl_flipped_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(-35, start_y), green_cavegirl_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(50, start_y), green_cavegirl_flipped_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(-50, start_y), green_cavegirl_moves, green_cavegirl_bullets, 70, enemy_drop_type::NONE),

        enemy_event(white_caveman, btn::fixed_point(35, start_y), white_caveman_flipped_moves, no_bullets, 55, enemy_drop_type::NONE),
        enemy_event(white_caveman, btn::fixed_point(-35, start_y), white_caveman_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(lizard, btn::fixed_point(35, start_y), lizard_flipped_moves, no_bullets, 50, enemy_drop_type::NONE),
        enemy_event(lizard, btn::fixed_point(-35, start_y), lizard_moves, no_bullets, 50, enemy_drop_type::NONE),

        enemy_event(black_caveman, btn::fixed_point(50, start_y), black_caveman_flipped_moves, black_caveman_flipped_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(0, start_y), green_cavegirl_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(black_caveman, btn::fixed_point(-50, start_y), black_caveman_moves, black_caveman_bullets, 50, enemy_drop_type::NONE),

        enemy_event(black_caveman, btn::fixed_point(50, start_y), black_caveman_flipped_moves, black_caveman_flipped_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(0, start_y), green_cavegirl_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(black_caveman, btn::fixed_point(-50, start_y), black_caveman_moves, black_caveman_bullets, 50, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 70, enemy_drop_type::GEM),

        // level 5 mid boss (15s)

        enemy_event(dragon_man, btn::fixed_point(50, start_y), dragon_man_moves, dragon_man_bullets, 0, enemy_drop_type::HERO_BOMB),

        // level 6 slow (25s)

        enemy_event(turtle, btn::fixed_point(0, start_y), turtle_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-35, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(35, start_y), turtle_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-50, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(50, start_y), turtle_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(black_caveman, btn::fixed_point(-50, start_y), black_caveman_moves, black_caveman_bullets, 60, enemy_drop_type::NONE),
        enemy_event(black_caveman, btn::fixed_point(50, start_y), black_caveman_flipped_moves, black_caveman_flipped_bullets, 80, enemy_drop_type::NONE),

        enemy_event(minidino, btn::fixed_point(-35, start_y), minidino_moves, minidino_bullets, 60, enemy_drop_type::NONE),
        enemy_event(minidino, btn::fixed_point(35, start_y), minidino_flipped_moves, minidino_flipped_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 90, enemy_drop_type::GEM),

        enemy_event(lizard, btn::fixed_point(35, start_y), lizard_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(lizard, btn::fixed_point(-35, start_y), lizard_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-35, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(35, start_y), turtle_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(green_cavegirl, btn::fixed_point(50, start_y), green_cavegirl_flipped_moves, green_cavegirl_bullets, 60, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(-50, start_y), green_cavegirl_moves, green_cavegirl_bullets, 80, enemy_drop_type::NONE),

        enemy_event(minidino, btn::fixed_point(35, start_y), minidino_flipped_moves, minidino_flipped_bullets, 60, enemy_drop_type::NONE),
        enemy_event(minidino, btn::fixed_point(-35, start_y), minidino_moves, minidino_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 70, enemy_drop_type::GEM),

        enemy_event(grasshopper, btn::fixed_point(50, start_y), grasshopper_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(grasshopper, btn::fixed_point(-50, start_y), grasshopper_moves, no_bullets, 70, enemy_drop_type::NONE),

        enemy_event(cavebat, btn::fixed_point(-50, start_y), cavebat_moves, cavebat_bullets, 1, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(50, start_y), cavebat_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(cavebat, btn::fixed_point(-35, start_y), cavebat_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(35, start_y), cavebat_flipped_moves, cavebat_bullets, 60, enemy_drop_type::NONE),

        enemy_event(cavebat, btn::fixed_point(50, start_y), cavebat_flipped_moves, cavebat_bullets, 80, enemy_drop_type::NONE),

        enemy_event(minidino, btn::fixed_point(-50, start_y), minidino_moves, minidino_bullets, 60, enemy_drop_type::NONE),
        enemy_event(minidino, btn::fixed_point(50, start_y), minidino_flipped_moves, minidino_flipped_bullets, 60, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 70, enemy_drop_type::GEM),

        // level 6 fast (27s)

        enemy_event(egg_caveman, btn::fixed_point(50, start_y), egg_caveman_flipped_moves, egg_caveman_flipped_bullets, 50, enemy_drop_type::NONE),

        enemy_event(egg_caveman, btn::fixed_point(-50, start_y), egg_caveman_moves, egg_caveman_bullets, 50, enemy_drop_type::NONE),
        enemy_event(egg_caveman, btn::fixed_point(50, start_y), egg_caveman_flipped_moves, egg_caveman_flipped_bullets, 70, enemy_drop_type::NONE),

        enemy_event(white_caveman, btn::fixed_point(-35, start_y), white_caveman_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(white_caveman, btn::fixed_point(35, start_y), white_caveman_flipped_moves, no_bullets, 70, enemy_drop_type::NONE),

        enemy_event(green_cavegirl, btn::fixed_point(-50, start_y), green_cavegirl_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(green_cavegirl, btn::fixed_point(50, start_y), green_cavegirl_flipped_moves, green_cavegirl_bullets, 50, enemy_drop_type::NONE),

        enemy_event(red_cavegirl, btn::fixed_point(-35, start_y), red_cavegirl_moves, red_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(red_cavegirl, btn::fixed_point(35, start_y), red_cavegirl_flipped_moves, red_cavegirl_bullets, 70, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 80, enemy_drop_type::GEM),

        enemy_event(turtle, btn::fixed_point(55, start_y), turtle_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-55, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(0, start_y), turtle_flipped_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(55, start_y), turtle_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),

        enemy_event(black_caveman, btn::fixed_point(-50, start_y), black_caveman_moves, black_caveman_bullets, 50, enemy_drop_type::NONE),
        enemy_event(egg_caveman, btn::fixed_point(50, start_y), egg_caveman_flipped_moves, egg_caveman_flipped_bullets, 50, enemy_drop_type::NONE),

        enemy_event(egg_caveman, btn::fixed_point(-50, start_y), egg_caveman_moves, egg_caveman_bullets, 50, enemy_drop_type::NONE),
        enemy_event(black_caveman, btn::fixed_point(50, start_y), black_caveman_flipped_moves, black_caveman_flipped_bullets, 60, enemy_drop_type::NONE),

        enemy_event(grasshopper, btn::fixed_point(50, start_y), grasshopper_flipped_moves, no_bullets, 60, enemy_drop_type::NONE),
        enemy_event(grasshopper, btn::fixed_point(-50, start_y), grasshopper_moves, no_bullets, 90, enemy_drop_type::NONE),

        enemy_event(minidino, btn::fixed_point(35, start_y), minidino_flipped_moves, minidino_flipped_bullets, 50, enemy_drop_type::NONE),
        enemy_event(minidino, btn::fixed_point(-35, start_y), minidino_moves, minidino_bullets, 50, enemy_drop_type::NONE),

        enemy_event(red_cavegirl, btn::fixed_point(50, start_y), red_cavegirl_flipped_moves, red_cavegirl_bullets, 50, enemy_drop_type::NONE),
        enemy_event(red_cavegirl, btn::fixed_point(-50, start_y), red_cavegirl_moves, red_cavegirl_bullets, 60, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-55, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(0, start_y), turtle_flipped_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(55, start_y), turtle_flipped_moves, no_bullets, 50, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-55, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(0, start_y), turtle_flipped_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(55, start_y), turtle_flipped_moves, no_bullets, 50, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-55, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(0, start_y), turtle_flipped_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(55, start_y), turtle_flipped_moves, no_bullets, 50, enemy_drop_type::NONE),

        enemy_event(turtle, btn::fixed_point(-55, start_y), turtle_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(0, start_y), turtle_flipped_moves, no_bullets, 1, enemy_drop_type::NONE),
        enemy_event(turtle, btn::fixed_point(55, start_y), turtle_flipped_moves, no_bullets, 50, enemy_drop_type::NONE),

        enemy_event(cavebat, btn::fixed_point(-50, start_y), cavebat_moves, cavebat_bullets, 1, enemy_drop_type::NONE),
        enemy_event(cavebat, btn::fixed_point(50, start_y), cavebat_flipped_moves, cavebat_bullets, 80, enemy_drop_type::NONE),

        enemy_event(blonde, btn::fixed_point(55, start_y), blonde_flipped_moves, no_bullets, 50, enemy_drop_type::GEM),
    };


    // stage (start with level 5, exp 2350):

    constexpr const stage stage_3(
        btn::regular_bg_items::stage_3, btn::regular_bg_items::mountain_clouds, btn::sprite_items::stage_3_intro,
        btn::sprite_items::stage_3_intro_alt, "STAGE 3", "GIANT MOUNTAIN", btn::music_items::stardstm,
        enemy_events, boss::type::GIGABAT);
}

const stage& get()
{
    return stage_3;
}

}
