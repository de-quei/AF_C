#include <stdio.h>

struct Obj {
	int hp;
	int speed;
};

int main()
{
	struct Obj player;
	player.hp = 5;
	player.speed = 7;
	printf("player HP : %d | player Speed : %d\n", player.hp, player.speed);

	struct Obj enemy;
	enemy.hp = 2;
	enemy.speed = 5;
	printf("enemy HP : %d | enemy Speed : %d\n", enemy.hp, enemy.speed);

	return 0;
}