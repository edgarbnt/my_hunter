/*
** EPITECH PROJECT, 2023
** placeholder
** File description:
** placeholder
*/

#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include "../my_hunter.h"

sfevent_t score(sfevent_t *event, game_t *data)
{
    (*event) = event_handling(data, event);
    high_score();
    change_high_score(data);
    return (*event);
}

sfText *displaylifes(game_t *data)
{
    sfFont *font = sfFont_createFromFile("sprite/Valoon.ttf");
    sfText *text = sfText_create();
    char *str = malloc(sizeof(char) * 12 + len_nbr(3));
    sfVector2f textPosition = {800.f, 300};

    str[0] = '\0';
    my_strcat(str, "Lifes : \0");
    my_strcat(str, my_putnbr_str(data->lifes));
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 70);
    sfText_setFillColor(text, sfRed);
    sfText_setStyle(text, sfTextBold);
    sfText_setPosition(text, textPosition);
    free(str);
    return text;
}

static void cursor_cond(const Textures *textures, game_t *data)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(data->window);

    data->hammerposition.x = (float) mouse.x;
    data->hammerposition.y = (float) mouse.y;
    data->hammerposition.x -= 16;
    data->hammerposition.y -= 16;
    sfSprite_setPosition(data->hammerSprite, data->hammerposition);
    sfSprite_setTexture(data->hammerSprite, textures->hammerTexture,
                        sfTrue);
    sfRenderWindow_drawSprite(data->window, data->hammerSprite, NULL);
}

sfVector2f
hammer_cursor(sfTime *replacementElapsedTime, Textures *textures, game_t *data)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(data->window);

    if (sfTime_asSeconds((*replacementElapsedTime)) < REPLACEMENT_TIME) {
        data->hammerposition.x = (float) mouse.x;
        data->hammerposition.y = (float) mouse.y;
        sfSprite_setPosition(data->hammerSprite, data->hammerposition);
        sfSprite_setTexture(data->hammerSprite, textures->hammer2Texture,
                            sfTrue);
        sfRenderWindow_drawSprite(data->window, data->hammerSprite, NULL);
    } else {
        cursor_cond(textures, data);
    }
    return data->hammerposition;
}
