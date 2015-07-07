function	box_collide(hero, monstre)
{
    if (monstre->x + monstre->width > hero->y &&
	hero->x + hero->width > monstre->x &&
	hero->y < monstre->y + monstre->height &&
	hero->height + hero->y > monstre->y)
	    return (true);
    return (false);
}
