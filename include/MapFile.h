#ifndef MAPFILE_H
#define MAPFILE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "Map.h"

class MapFile
{
    public:
        MapFile();
        MapFile(std::string filename);
        MapFile(std::string filename, Map *lvl);
        void append(Map *lvl);
        virtual ~MapFile();
    protected:
    private:
        std::string map_file;
        FILE *file;
};

#endif // MAPFILE_H
