/*
** EPITECH PROJECT, 2023
** placeholder
** File description:
** placeholder
*/

#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include "../my_hunter.h"

int opensprite(Textures *textures)
{
    if (!textures->moleTextures[0])
        return 1;
    if (!textures->moleTextures[1])
        return 1;
    if (!textures->moleTextures[2])
        return 1;
    if (!textures->backgroundTexture)
        return 1;
    if (!textures->hammerTexture)
        return 1;
    if (!textures->hammerTexture)
        return 1;
    if (!textures->holemoleTexture)
        return 1;
    return 0;
}

void loadtextures(Textures *textures)
{
    textures->moleTextures[0] = sfTexture_createFromFile("sprite/mole1.png",
                                                            NULL);
    textures->moleTextures[1] = sfTexture_createFromFile("sprite/mole2.png",
                                                            NULL);
    textures->moleTextures[2] = sfTexture_createFromFile("sprite/mole3.png",
                                                            NULL);
    textures->backgroundTexture = sfTexture_createFromFile("sprite/bg.png",
                                                            NULL);
    textures->hammerTexture = sfTexture_createFromFile("sprite/h."
                                                            "png", NULL);
    textures->hammer2Texture = sfTexture_createFromFile("sprite/h2."
                                                            "png", NULL);
    textures->holemoleTexture = sfTexture_createFromFile("sprite/ho."
                                                            "png", NULL);
}

void destroytextures(Textures *textures)
{
    for (int i = 0; i < 3; ++i) {
        sfTexture_destroy(textures->moleTextures[i]);
    }
    sfTexture_destroy(textures->backgroundTexture);
    sfTexture_destroy(textures->hammerTexture);
    sfTexture_destroy(textures->hammer2Texture);
    sfTexture_destroy(textures->holemoleTexture);
}

void texture_runmole(sfTexture **textures)
{
    if (textures[0] == NULL) {
        textures[0] = sfTexture_createFromFile("sprite/runmole01.png", NULL);
        textures[1] = sfTexture_createFromFile("sprite/runmole02.png", NULL);
        textures[2] = sfTexture_createFromFile("sprite/runmole03.png", NULL);
    }
}

void moving_image(sfVector2f position, game_t *data)
{
    static int currentTextureIndex = 0;
    static sfTexture *textures[3];
    sfSprite *sprite = sfSprite_create();
    sfTime deltaTimegreen = sfClock_getElapsedTime(data->clockgreen);
    float deltaSeconds = sfTime_asSeconds(deltaTimegreen);
    const float timeInterval = 2.0f;
    static float timeElapsed = 0.0f;

    texture_runmole(textures);
    sfSprite_setTexture(sprite, textures[currentTextureIndex], sfTrue);
    sfSprite_setPosition(sprite, position);
    timeElapsed += deltaSeconds;
    if (timeElapsed >= timeInterval) {
        timeElapsed = 0.0f;
        currentTextureIndex = (currentTextureIndex + 1) % 3;
    }
    sfRenderWindow_drawSprite(data->window, sprite, NULL);
    sfSprite_destroy(sprite);
}
