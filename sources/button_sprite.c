/*
** EPITECH PROJECT, 2021
** button_sprite.c
** File description:
** fct button mangament
*/

#include "../include/my.h"
#include "../include/p.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

int if_button_s_pressed(struct button_s *b, sfRenderWindow *wind,
sfVector2i mouse, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed &&
        pos_is_inrect(mouse, vect(850 * b->scale_panel.x,
        850 * b->scale_panel.y), b->pos_panel) == 1) {
        if (b->is_pressed == 0) {
            b->is_pressed = 1;
            sfClock_restart(b->clock);
        }
        return 1;
    }
    return 0;
}

void help_draw_button_s(struct button_s *b, sfRenderWindow *wind,
sfVector2i mouse)
{
    if (b->is_pressed == 1) {
        sfSprite_setScale(b->sign,
        vect(b->scale_sign.x * 0.8, b->scale_sign.y * 0.8));
        sfSprite_setPosition(b->sign,
        vect(b->pos_sign.x + 5, b->pos_sign.y + 5));
        b->time = sfClock_getElapsedTime(b->clock);
        if (b->time.microseconds > 100000) {
            sfSprite_setScale(b->sign, b->scale_sign);
            sfSprite_setPosition(b->sign, b->pos_sign);
            b->is_pressed = 0;
        }
    }
    sfRenderWindow_drawSprite(wind, b->panel, NULL);
    sfRenderWindow_drawSprite(wind, b->sign, NULL);
}

void draw_button_s(struct button_s *b, sfRenderWindow *wind, sfVector2i mouse)
{
    if (pos_is_inrect(mouse, vect(850 * b->scale_panel.x,
        850 * b->scale_panel.y), b->pos_panel) == 1) {
        sfSprite_setScale(b->panel, vect(b->scale_panel.x * 1.2,
        b->scale_panel.y * 1.2));
        sfSprite_setPosition(b->panel, vect(b->pos_panel.x - 10,
        b->pos_panel.y - 10));
        sfRenderWindow_drawSprite(wind, b->info->info, NULL);
        sfRenderWindow_drawText(wind, b->info->text, NULL);
    } else {
        sfSprite_setScale(b->panel, b->scale_panel);
        sfSprite_setPosition(b->panel, b->pos_panel);
    }
    help_draw_button_s(b, wind, mouse);
}

void help_create_button_s(struct button_s *b, sfVector2f pos,
sfVector2f scale_sign, sfVector2f scale_panel)
{
    b->pos_panel = pos;
    b->scale_sign = scale_sign;
    b->scale_panel = scale_panel;
    b->clock = sfClock_create();
    b->is_pressed = 0;
}

struct button_s *create_button_s(char *path_sprite, sfVector2f pos,
sfVector2f scale_sign, sfVector2f scale_panel)
{
    struct button_s *b = malloc(sizeof(struct button_s) * 2);
    sfVector2f pos_sign = vect(pos.x + 15, pos.y + 15);

    b->info = create_info_button(vect(0, 0), vect(0.3, 0.3),
    "sprite/chat.png");
    if (b == NULL || b->info == NULL)
        return NULL;
    b->sign = sfSprite_create();
    b->t_sign = sfTexture_createFromFile(path_sprite, NULL);
    sfSprite_setTexture(b->sign, b->t_sign, sfFalse);
    sfSprite_setPosition(b->sign, pos_sign);
    sfSprite_setScale(b->sign, scale_sign);
    b->panel = sfSprite_create();
    b->t_panel = sfTexture_createFromFile("sprite/panel.png", NULL);
    sfSprite_setTexture(b->panel, b->t_panel, sfFalse);
    sfSprite_setPosition(b->panel, pos);
    sfSprite_setScale(b->panel, scale_panel);
    b->pos_sign = pos_sign;
    help_create_button_s(b, pos, scale_sign, scale_panel);
    return b;
}
