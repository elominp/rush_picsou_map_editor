#ifndef MAP_H
#define MAP_H

#include <cstdlib>

class Map
{
    public:
        Map();
        char **get_gridmap();
        char **get_griditems();
        int get_casemap(int x, int y);
        int get_caseitem(int x, int y);
        void set_map(int x, int y, int value);
        void set_item(int x, int y, int value);
        void reset();
        virtual ~Map();
    protected:
    private:
        char grid_map[30][50];
        char grid_items[30][50];
};

#endif // MAP_H
