/*
** EPITECH PROJECT, 2023
** my_hunter.h
** File description:
** Header file containing function prototypes and structure definitions
*/

#include <unistd.h>
#include <SFML/Graphics.h>

#ifndef MY_HUNTER_H
    #define MY_HUNTER_H
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define FRAME_RATE_LIMIT 60
    #define ANIMATION_SPEED 0.15
    #define REPLACEMENT_TIME 0.4
typedef struct {
    int lifescnt;
    int mole_cnt;
    int runningMoleMoving;
    int accelering;
    int lifes;
    int currentFrame;
    int frameCount;
    int showThirdImage;
    int currentMolePosition;
    sfClock *clockgreen;
    sfClock  *clock;
    sfSprite *hammerSprite;
    sfSprite *moleSprite;
    sfSprite *backgroundSprite;
    sfSprite *customImageSprite;
    sfVector2f hammerposition;
    sfSprite *runningMoleSprite;
    sfClock *replacementClock;
    sfTime *replacementElapsedTime;
    sfTime *elapsedTime;
    sfRenderWindow *window;
} game_t;
typedef struct Textures {
    sfTexture *moleTextures[3];
    sfTexture *backgroundTexture;
    sfTexture *hammerTexture;
    sfTexture *hammer2Texture;
    sfTexture *holemoleTexture;
    sfTexture *runningmole;
} Textures;
typedef sfEvent sfevent_t;
void loadtextures(Textures *textures);
void texture_runmole(sfTexture **textures);
void destroytextures(Textures *textures);
sfTime display_sprites(game_t *data, Textures *textures);
int my_strcmp(const char *s1, const char *s2);
int mouse_click(game_t *data);
void moving_image(sfVector2f position, game_t *data);
sfVector2f able_runningmole(game_t *data, sfClock *, sfVector2f *, sfSprite *);
sfVector2f lancing_runningmole(game_t *data);
int handle_event(sfevent_t *event, game_t *data);
void window_property(game_t *, sfSprite **, Textures *textures);
sfTime display_sprites(game_t *data, Textures *textures);
void animation_speed(sfTime *elapsedTime, game_t *data);
sfVector2f hammer_cursor(sfTime *, Textures *, game_t *data);
int high_score(void);
int change_high_score2(game_t *data);
void change_high_score(game_t *data);
void destroying_sprite(game_t *data, Textures *textures);
sfText *displaylifes(game_t *data);
sfText *displayhighscore(void);
sfText *displayscore(game_t *data);
void all_functions(sfTime *, sfTime *, game_t *, Textures *textures);
void handling_clicking(sfClock *pauseClock, game_t *data, sfevent_t *event);
sfevent_t score(sfevent_t *event, game_t *data);
game_t *dec_game_t(Textures *textures);
int opensprite(Textures *textures);
int error(game_t *data, Textures *textures);
sfevent_t event_handling(game_t *data, sfevent_t *event);
void destroy_runningmole(game_t *data);
void destroying_allsprite(Textures *textures, game_t *data);
char *my_strcat(char *dest, char const *src);
char *my_putnbr_str(int nb);
int len_nbr(int nb);
int my_strlen(char const *str);
int my_atoi(char *str);
#endif /* MY_HUNTER_H */
