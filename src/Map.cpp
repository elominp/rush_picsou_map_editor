#include "Map.h"

Map::Map()
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            grid_map[i][j] = 0;
            grid_items[i][j] = 0;
        }
    }
    //ctor
}

char **Map::get_gridmap()
{
    char **cpy;

    if ((cpy = (char **)malloc(sizeof(char *) * 30)) == NULL)
        return (NULL);
    for (int i = 0; i < 30; i++)
    {
        if ((cpy[i] = (char *)malloc(sizeof(char) * 50)) == NULL)
            return (NULL);
        for (int j = 0; j < 50; j++)
        {
            cpy[i][j] = grid_map[i][j];
        }
    }
    return (cpy);
}

char **Map::get_griditems()
{
    char **cpy;

    if ((cpy = (char **)malloc(sizeof(char *) * 30)) == NULL)
        return (NULL);
    for (int i = 0; i < 30; i++)
    {
        if ((cpy[i] = (char *)malloc(sizeof(char) * 50)) == NULL)
            return (NULL);
        for (int j = 0; j < 50; j++)
        {
            cpy[i][j] = grid_items[i][j];
        }
    }
    return (cpy);
}

int Map::get_casemap(int x, int y)
{
    if (x < 0 || y < 0 || x > 49 || y > 29)
        return (-1);
    return (grid_map[y][x]);
}

int Map::get_caseitem(int x, int y)
{
    if (x < 0 || y < 0 || x > 49 || y > 29)
        return (-1);
    return (grid_items[y][x]);
}

void Map::set_map(int x, int y, int value)
{
    if (x < 0 || y < 0 || x >= 50 || y >= 30 || value < 0)
        return;
    grid_map[y][x] = value;
}

void Map::set_item(int x, int y, int value)
{
    if (x < 0 || y < 0 || x >= 50 || y >= 30 || value < 0)
        return;
    grid_items[y][x] = value;
}

void Map::reset()
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            grid_map[i][j] = 0;
            grid_items[i][j] = 0;
        }
    }
}

Map::~Map()
{
    //dtor
}
