/*
** EPITECH PROJECT, 2023
** my_strcmp
** File description:
** placeholder
*/

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
