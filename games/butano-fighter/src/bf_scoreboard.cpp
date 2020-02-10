#include "bf_scoreboard.h"

#include "btn_display.h"
#include "btn_sprite_builder.h"
#include "btn_input_string_stream.h"
#include "btn_sprite_text_generator.h"
#include "btn_experience_bar_sprite_item.h"
#include "btn_experience_frame_sprite_item.h"
#include "btn_hero_bomb_icon_sprite_item.h"
#include "bf_hero.h"

namespace bf
{

scoreboard::scoreboard(btn::sprite_text_generator& text_generator) :
    _text_generator(text_generator)
{
    btn::point display_center = btn::display::center();
    int experience_bar_x = display_center.x() - 24;

    {
        btn::sprite_builder builder(btn::sprite_items::experience_bar);
        builder.set_position(btn::fixed_point(experience_bar_x, display_center.y() - 16));
        builder.set_bg_priority(_text_generator.bg_priority());
        builder.set_z_order(_text_generator.z_order());
        builder.set_ignore_camera(true);
        _experience_bar_sprites.push_back(builder.build());

        builder.set_position(btn::fixed_point(experience_bar_x - 16, display_center.y() - 16));
        builder.set_horizontal_flip(false);
        _experience_bar_sprites.push_back(builder.build_and_release());

        _experience_bar_palette_action.emplace(_experience_bar_sprites[0].palette(), 2, 1);
    }

    {
        btn::sprite_builder builder(btn::sprite_items::experience_frame);
        builder.set_position(btn::fixed_point(experience_bar_x, display_center.y() - 16));
        builder.set_bg_priority(_text_generator.bg_priority());
        builder.set_z_order(_text_generator.z_order());
        builder.set_ignore_camera(true);
        builder.set_horizontal_flip(true);
        _experience_bar_sprites.push_back(builder.build());

        builder.set_position(btn::fixed_point(experience_bar_x - 16, display_center.y() - 16));
        builder.set_horizontal_flip(false);
        _experience_bar_sprites.push_back(builder.build_and_release());
    }
}

void scoreboard::update(const hero& hero)
{
    btn::point display_center = btn::display::center();
    int text_y = display_center.y() - 16;
    int level = hero.level();
    int experience = hero.experience();
    int bombs_count = hero.bombs_count();
    _experience_bar_palette_action->update();

    if(level != _last_level)
    {
        _last_level = level;

        btn::string<8> text;
        btn::input_string_stream text_stream(text);
        text_stream.append("LVL: ");
        text_stream.append(level + 1);
        _level_sprites.clear();
        _text_generator.generate(8 - display_center.x(), text_y, text, _level_sprites);
    }

    if(experience != _last_experience)
    {
        _last_experience = experience;

        btn::string<16> text;
        btn::input_string_stream text_stream(text);
        text_stream.append("EXP: ");
        text_stream.append(experience);
        _experience_sprites.clear();
        _text_generator.set_alignment(btn::horizontal_alignment_type::RIGHT);
        _text_generator.generate(_experience_bar_sprites[1].x() - 24, text_y, text, _experience_sprites);
        _text_generator.set_alignment(btn::horizontal_alignment_type::LEFT);
    }

    if(bombs_count != _last_bombs_count)
    {
        _last_bombs_count = bombs_count;

        _bomb_sprites.clear();

        for(int index = 0; index < bombs_count; ++index)
        {
            btn::sprite_builder builder(btn::sprite_items::hero_bomb_icon);
            builder.set_position(btn::fixed_point(display_center.x() - ((index + 1) * 16), 16 - display_center.y()));
            builder.set_bg_priority(_text_generator.bg_priority());
            builder.set_z_order(_text_generator.z_order());
            builder.set_ignore_camera(true);
            _bomb_sprites.push_back(builder.build_and_release());
        }
    }
}

}