/*
** EPITECH PROJECT, 2023
** placeholder
** File description:
** placeholder
*/

#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "../my_hunter.h"
#include <fcntl.h>

int change_high_score2(game_t *data)
{
    int file_descriptor = open("highscore", O_WRONLY | O_TRUNC);
    char *score_str = my_putnbr_str(data->mole_cnt);
    ssize_t bytes_written = write(file_descriptor,
                                score_str, len_nbr(data->mole_cnt));

    if (file_descriptor == -1)
        return 1;
    if (bytes_written == -1)
        return 1;
    free(score_str);
    close(file_descriptor);
    return 0;
}

void change_high_score(game_t *data)
{
    if (data->mole_cnt > high_score())
        change_high_score2(data);
}

void destroying_sprite(game_t *data, Textures *textures)
{
    sfSprite_destroy(data->moleSprite);
    sfSprite_destroy(data->backgroundSprite);
    sfSprite_destroy(data->hammerSprite);
    sfSprite_destroy(data->customImageSprite);
    destroytextures(textures);
    sfRenderWindow_destroy(data->window);
    sfClock_destroy(data->clock);
    sfClock_destroy(data->replacementClock);
}

void handling_clicking(sfClock *pauseClock, game_t *data, sfevent_t *event)
{
    if (handle_event(event, data)
        == 2) {
        if (data->runningMoleMoving == 1) {
            data->mole_cnt = data->mole_cnt + 3;
            data->accelering = data->accelering + 5;
        }
        data->runningMoleMoving = 0;
    }
    pauseClock = sfClock_create();
    if (pauseClock != NULL && sfTime_asSeconds(sfClock_getElapsedTime
            (pauseClock)) >= 5.0f) {
        sfClock_destroy(pauseClock);
        data->runningMoleMoving = 1;
    }
}

sfText *displayhighscore(void)
{
    sfFont *font = sfFont_createFromFile("sprite/Valoon.ttf");
    sfText *text = sfText_create();
    char *highscore = malloc(sizeof(char) * 20 + len_nbr(high_score()));
    sfVector2f textPosition = {1250.f, 950.f};

    highscore[0] = '\0';
    my_strcat(highscore, "Highscore : \0");
    my_strcat(highscore, my_putnbr_str(high_score()));
    sfText_setString(text, highscore);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 70);
    sfText_setFillColor(text, sfWhite);
    sfText_setStyle(text, sfTextBold);
    sfText_setPosition(text, textPosition);
    return text;
}
