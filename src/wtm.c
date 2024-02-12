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

sfVector2f molePositions[9] = {
    {WINDOW_WIDTH / 4.f, (11 * WINDOW_HEIGHT) / 24.f},
    {WINDOW_WIDTH / 2.f, (11 * WINDOW_HEIGHT) / 24.f},
    {(3 * WINDOW_WIDTH) / 4.f, (11 * WINDOW_HEIGHT) / 24.f},
    {WINDOW_WIDTH / 4.f, (2 * WINDOW_HEIGHT) / 3.f},
    {WINDOW_WIDTH / 2.f, (2 * WINDOW_HEIGHT) / 3.f},
    {(3 * WINDOW_WIDTH) / 4.f, (2 * WINDOW_HEIGHT) / 3.f},
    {WINDOW_WIDTH / 4.f, (13 * WINDOW_HEIGHT) / 24.f},
    {WINDOW_WIDTH / 2.f, (13 * WINDOW_HEIGHT) / 24.f},
    {(3 * WINDOW_WIDTH) / 4.f, (13 * WINDOW_HEIGHT) / 24.f}};

int mouse_click(game_t *data)
{
    sfVector2i mousePosition = sfMouse_getPositionRenderWindow(data->window);
    sfFloatRect moleBounds = sfSprite_getGlobalBounds(data->moleSprite);

    if (mousePosition.x >= moleBounds.left &&
        mousePosition.x <= moleBounds.left + moleBounds.width &&
        mousePosition.y >= moleBounds.top &&
        mousePosition.y <= moleBounds.top + moleBounds.height) {
        sfClock_restart(data->replacementClock);
        data->currentMolePosition = rand() % 9;
        sfSprite_setPosition(data->moleSprite,
                                molePositions[data->currentMolePosition]);
        data->frameCount = 0;
        data->showThirdImage = 0;
        return 1;
    } else {
        data->hammerposition.x = (float) mousePosition.x;
        data->hammerposition.y = (float) mousePosition.y;
        sfClock_restart(data->replacementClock);
    }
    return 0;
}

sfTime display_sprites(game_t *data, Textures *textures)
{
    sfTime elapsedTime;

    for (int i = 0; i < 9; ++i) {
        sfSprite_setTexture(data->customImageSprite, textures->holemoleTexture,
                            sfTrue);
        sfSprite_setPosition(data->customImageSprite, molePositions[i]);
        sfRenderWindow_drawSprite(data->window, data->customImageSprite, NULL);
    }
    elapsedTime = sfClock_getElapsedTime(data->clock);
    return elapsedTime;
}

static void draw_sprite(game_t *data, const sfText *life, const sfText *text,
    const sfText *highscore)
{
    sfRenderWindow_drawText(data->window, text, NULL);
    sfRenderWindow_drawText(data->window, life, NULL);
    sfRenderWindow_drawText(data->window, highscore, NULL);
    sfRenderWindow_display(data->window);
}

static void
set_time(sfTime *replacementElapsedTime, game_t *data, Textures *textures)
{
    sfRenderWindow_drawSprite(data->window, data->moleSprite, NULL);
    (*replacementElapsedTime) = sfClock_getElapsedTime(data->replacementClock);
    data->hammerposition = hammer_cursor(replacementElapsedTime,
                                            textures, data);
}

void animation_speed(sfTime *elapsedTime, game_t *data)
{
    if (!data->showThirdImage && data->frameCount < 3) {
        if (sfTime_asSeconds((*elapsedTime)) > ANIMATION_SPEED) {
            data->currentFrame = (data->currentFrame + 1) % 3;
            sfClock_restart(data->clock);
            data->frameCount++;
        }
    } else {
        data->currentFrame = 2;
        data->showThirdImage = 1;
    }
}

static int dash_h(int argc, char **argv)
{
    char sr[56] = "Welcome to the game Whack a Mole !\nYou will see a brown ";
    char sr2[57] = "mole in the midle of the screen, each time you whack one";
    char s3[57] = " of them, your score will increase of 1 point.\nBe careful";
    char s4[58] = " every 10 seconds there is a green whole running a the top";
    char sr5[55] = " of the football court. Each one will earn you 3 extra ";
    char sr6[170] = "points, but if you let them exceed the left edge of the "
                    "window, one of your 3 lifes will be withdrawn from you. "
                    "Once you have no more life, the program stops. Have fun!";

    if (argv[1][0] == '-')
        if (argv[1][1] == 'h' && my_strlen(argv[1]) == 2) {
            write(1, sr, 56);
            write(1, sr2, 57);
            write(1, s3, 57);
            write(1, s4, 58);
            write(1, sr5, 54);
            write(1, sr6, 170);
            return 0;
        }
    return 84;
}

static int argc_error(int argc, char **argv)
{
    if (argc == 2) {
        if (dash_h(argc, argv) == 0)
            return 0;
        else
            return 84;
    }
    if (argc != 1)
        return 84;
    return 0;
}

void all_functions(sfTime *elapsedTime, sfTime *replacementElapsedTime, game_t
    *data, Textures *textures)
{
    sfText *life = displaylifes(data);
    sfText *text = displayscore(data);
    sfText *highscore = displayhighscore();

    sfRenderWindow_clear(data->window, sfBlack);
    sfSprite_setTexture(data->backgroundSprite, textures->backgroundTexture,
                        sfTrue);
    sfRenderWindow_drawSprite(data->window, data->backgroundSprite, NULL);
    lancing_runningmole(data);
    (*elapsedTime) = display_sprites(data, textures);
    animation_speed(elapsedTime, data);
    sfSprite_setTexture(data->moleSprite,
                        textures->moleTextures[data->currentFrame], sfTrue);
    sfSprite_setPosition(data->moleSprite,
                            molePositions[data->currentMolePosition]);
    set_time(replacementElapsedTime, data, textures);
    draw_sprite(data, life, text, highscore);
}

static int env_error(char **env)
{
    int display = 0;

    if (!env || !env[0])
        return 84;
    for (int i = 0; env[i]; i++) {
        if (my_strcmp(env[i], "DISPLAY=:0") == 0)
            display = 1;
    }
    if (!display) {
        return 84;
    }
    return 0;
}

int main(int argc, char **argv, char **env)
{
    Textures *textures = malloc(sizeof(Textures));
    sfClock *pauseClock = NULL;
    sfTime elapsedTime;
    sfTime replacementElapsedTime;
    sfevent_t event;
    game_t *data;

    if (env_error(env) == 84)
        return 84;
    data = dec_game_t(textures);
    if (argc_error(argc, argv) == 84 || opensprite(textures) == 1 || argc != 1)
        return 84;
    srand((unsigned int) time(NULL));
    while (sfRenderWindow_isOpen(data->window)){
        event = score(&event, data);
        all_functions(&elapsedTime, &replacementElapsedTime, data, textures);
        handling_clicking(pauseClock, data, &event);
    }
    destroying_allsprite(textures, data);
    return 0;
}
