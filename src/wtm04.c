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
#include <time.h>
#include "../my_hunter.h"
#include <fcntl.h>

sfVector2f lancing_runningmole(game_t *data)
{
    static sfClock *runningMoleClock = NULL;
    static sfVector2f runningMolePosition = {WINDOW_WIDTH, 355};
    static sfSprite *runningMoleSprite = NULL;

    if (runningMoleClock == NULL){
        runningMoleClock = sfClock_create();
        runningMoleSprite = sfSprite_create();
    }
    runningMolePosition = able_runningmole(data, runningMoleClock,
                                            &runningMolePosition,
                                            runningMoleSprite);
    return runningMolePosition;
}

void destroying_allsprite(Textures *textures, game_t *data)
{
    destroying_sprite(data, textures);
    destroy_runningmole(data);
}

int high_score(void)
{
    int file_descriptor;
    char contenu[10];
    ssize_t bytes_read;
    char nomFichier[] = "highscore";

    file_descriptor = open(nomFichier, O_RDONLY);
    bytes_read = read(file_descriptor, contenu, 10 - 1);
    contenu[bytes_read] = '\0';
    close(file_descriptor);
    return my_atoi(contenu);
}

sfevent_t event_handling(game_t *data, sfevent_t *event)
{
    while (sfRenderWindow_pollEvent(data->window, event)) {
        if (handle_event(event, data)
            == 1)
            data->mole_cnt++;
    }
    return (*event);
}

sfText *displayscore(game_t *data)
{
    sfVector2f textPosition = {10.f, 950.f};
    sfFont *font = sfFont_createFromFile("sprite/Valoon.ttf");
    sfText *text = sfText_create();
    char *str = malloc(sizeof(char) * 12 + len_nbr(data->mole_cnt));

    str[0] = '\0';
    my_strcat(str, "Score : \0");
    my_strcat(str, my_putnbr_str(data->mole_cnt));
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 70);
    sfText_setFillColor(text, sfWhite);
    sfText_setStyle(text, sfTextBold);
    sfText_setPosition(text, textPosition);
    return text;
}
