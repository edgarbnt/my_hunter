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

//sfSprite *runningMoleSprite;
sfTexture *hammerTexture;

static int
clickrunmole(const sfevent_t *event, game_t *data, sfFloatRect *runMoleBounds,
    sfVector2i *mousePosition)
{
    if ((*event).type == sfEvtClosed)
        sfRenderWindow_close(data->window);
    if ((*event).type == sfEvtMouseButtonPressed) {
        if (mouse_click(data) == 1)
            return 1;
        if ((*mousePosition).x >= (*runMoleBounds).left &&
            (*mousePosition).x <= (*runMoleBounds).left + (*runMoleBounds)
                    .width &&
            (*mousePosition).y >= (*runMoleBounds).top &&
            (*mousePosition).y <= (*runMoleBounds).top + (*runMoleBounds)
                    .height) {
            return 2;
        }
    }
    return 0;
}

void destroy_runningmole(game_t *data)
{
    if (data->runningMoleSprite != NULL) {
        sfSprite_destroy(data->runningMoleSprite);
        data->runningMoleSprite = NULL;
    }
}

game_t *dec_game_t(Textures *textures)
{
    game_t *data = malloc(sizeof(game_t));

    data->accelering = 0;
    data->clock = sfClock_create();
    data->clockgreen = sfClock_create();
    data->mole_cnt = 0;
    data->currentMolePosition = rand() % 9;
    data->lifes = 3;
    data->customImageSprite = sfSprite_create();
    data->hammerSprite = sfSprite_create();
    data->backgroundSprite = sfSprite_create();
    data->moleSprite = sfSprite_create();
    data->replacementClock = sfClock_create();
    window_property(data, &data->runningMoleSprite, textures);
    return data;
}

int handle_event(sfevent_t *event, game_t *data)
{
    sfTexture *runmole = sfTexture_createFromFile("sprite/ho.png", NULL);
    sfVector2f runningMolePosition = lancing_runningmole(data);
    sfFloatRect runMoleBounds = sfSprite_getGlobalBounds
            (data->runningMoleSprite);
    sfVector2i mousePosition = sfMouse_getPositionRenderWindow(data->window);

    sfSprite_setTexture(data->runningMoleSprite, runmole, sfTrue);
    sfSprite_setPosition(data->runningMoleSprite, runningMolePosition);
    return clickrunmole(event, data, &runMoleBounds, &mousePosition);
}

void
window_property(game_t *data, sfSprite **runningMoleSprite, Textures *textures)
{
    sfVector2f tempHammerPosition = {0.f, 0.f};
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};

    data->window = sfRenderWindow_create(mode, "WaM", sfDefaultStyle, NULL);
    (*runningMoleSprite) = sfSprite_create();
    data->hammerposition = tempHammerPosition;
    sfRenderWindow_setFramerateLimit(data->window, FRAME_RATE_LIMIT);
    loadtextures(textures);
    sfRenderWindow_setMouseCursorVisible(data->window, sfFalse);
    sfSprite_setTexture(data->hammerSprite, hammerTexture, sfTrue);
}

static void life_features(game_t *data, const sfVector2f *runningMolePosition)
{
    if ((*runningMolePosition).x <= 0)
        data->runningMoleMoving = 2;
    if (data->runningMoleMoving == 2)
        data->lifes--;
    if (data->lifes == 0)
        sfRenderWindow_close(data->window);
}

sfVector2f able_runningmole(game_t *data, sfClock *runningMoleClock,
    sfVector2f *runningMolePosition, sfSprite *runningMoleSprite)
{
    sfTime elapsedRunningMole = sfClock_getElapsedTime(runningMoleClock);
    float secondsRunningMole = sfTime_asSeconds(elapsedRunningMole);
    const float runningMoleInterval = 10.0f;

    if (secondsRunningMole >= runningMoleInterval) {
        data->runningMoleMoving = 1;
        sfClock_restart(runningMoleClock);
        (*runningMolePosition).x = WINDOW_WIDTH;
        (*runningMolePosition).y = 355;
    }
    if (data->runningMoleMoving == 1) {
        (*runningMolePosition).x -= 7 + data->accelering;
        moving_image((*runningMolePosition), data);
        sfSprite_setPosition(runningMoleSprite, (*runningMolePosition));
        sfRenderWindow_drawSprite(data->window, runningMoleSprite, NULL);
        life_features(data, runningMolePosition);
    }
    return (*runningMolePosition);
}
