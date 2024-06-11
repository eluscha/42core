#include "so_long.h"

int main(int argc, char **argv)
{
    int fd;
    t_map *mapdata;
    int len;
    mapdata->map = ft_calloc(100, sizeof(char*)); //assuming map is rarely bigger than 100, and if it is - seaparate handling
    if (!mapdata->map)
        return (2);
    if (argc == 1)
        fd = 0;
    else
        fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (2); // and free malloc
    char *line = get_next_line(fd);
    if (line)
        mapdata->len = ft_strlen(line) - 1;
    if (!line || mapdata->len < 3)
        return (1);
    int idx = -1;
    while (line)
    {
        len = ft_strlen(line);
        if (len - 1 != mapdata->len)
            return (1); //free malloc close file, print error message
        mapdata->map[++idx] = line;
        line = get_next_line(fd);
    }
    mapdata->height = idx + 1;
    printf("len is %i, height is %i\n", mapdata->len, mapdata->height);
    return (0);
}