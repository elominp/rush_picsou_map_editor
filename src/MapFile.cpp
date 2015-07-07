#include "MapFile.h"

MapFile::MapFile()
{
    //ctor
    map_file = "untitled";
    file = NULL;
}

MapFile::MapFile(std::string filename)
{
    if (filename == "")
        return;
    map_file = filename;
    if ((file = fopen(map_file.c_str(), "a")) == NULL)
        return;
}

MapFile::MapFile(std::string filename, Map *lvl)
{
    if (filename == "" || lvl == NULL)
        return;
    map_file = filename;
    if ((file = fopen(map_file.c_str(), "a")) == NULL)
        return;
    append(lvl);
}

void MapFile::append(Map *lvl)
{
    char **data_map;
    char **data_items;

    if (lvl == NULL || map_file == "untitled" || map_file == "" ||
        file == NULL || (data_map = lvl->get_gridmap()) == NULL ||
        (data_items = lvl->get_griditems()) == NULL)
        return;
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
            fprintf(file, "%d%d", data_map[i][j], data_items[i][j]);
        fprintf(file, "\n");
    }
}

MapFile::~MapFile()
{
    if (file != NULL)
        fclose(file);
    //dtor
}
