#include "so_long.h"

int valid_map(t_map *mapdata)
{
    int idx;
    int lnum;
    char *line = mapdata->map[0];
    idx = -1;
    while (line[++idx] != '\n')
    {
        if (line[idx] != '1')
            return (0);
    }
    line[idx] = '\0';
    if (idx < 3)
        return (0);
    mapdata->width = idx;
    lnum = 1;
    line = mapdata->map[lnum];
    while (line)
    {
        printf("checkinf line number %i\n", lnum);
        idx = -1;
        while (line[++idx] != '\n')
        {
            printf("checking position %i\n", idx);
            if (idx == mapdata->width)
                return (0);
            if (idx == 0 || idx == mapdata->width - 1)
            {
                if (line[idx] != '1')
                    return (0);
            }
            else if (line[idx] == 'P')
            {
                if (mapdata->player[0] != 0)
                    return (0);
                mapdata->player[0] = idx;
                mapdata->player[1] = lnum;
            }
            else if (line[idx] == 'E')
            {
                if (mapdata->exit[0] != 0)
                    return (0);
                mapdata->exit[0] = idx;
                mapdata->exit[1] = lnum;
            }
            else if (line[idx] == 'C')
                mapdata->goal++;
            else if (line[idx] != '1' && line[idx] != '0')
                return (0);
        }
        line[idx] = '\0';
        line = mapdata->map[++lnum];
    }
    mapdata->height = lnum;
    if (lnum < 3)
        return (0);
    line = mapdata->map[lnum - 1];
    idx = 0;
    while (line[idx])
    {
        if (line[idx++] != '1')
            return (0);
    }
    //check player, exit, at least one collectable too ?
    //check_path_exist
    return (1);
}

