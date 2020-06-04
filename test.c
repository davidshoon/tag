#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Location
{
	int x;
	int y;
};

enum Wall {
	/* can access all directions */
	OPEN = 	0x00,
	/* block north */
	NORTH_WALL = 0x01,
	/* block south */
	SOUTH_WALL = 0x02,
	/* block east */
	EAST_WALL = 0x04,
	/* block west */
	WEST_WALL = 0x08
};

struct SceneDetail
{
	struct Location location;
	const char *details;
	enum Wall wall_type;
};

struct SceneDetail scene_detail_list[] = 
{
	{ {0, 0}, "This is the starting point", OPEN },
	{ {0, 1}, "This is south of starting point", SOUTH_WALL|EAST_WALL|WEST_WALL },
	{ {0, -1}, "This is north of starting point", NORTH_WALL|EAST_WALL|WEST_WALL },
	{ {1, 0}, "This is east of starting point", EAST_WALL|NORTH_WALL|SOUTH_WALL },
	{ {-1, 0}, "This is west of starting point", WEST_WALL|NORTH_WALL|SOUTH_WALL }
};

struct Location current_location = {0, 0};

int get_scene_detail(int x, int y)
{
	int i;

	/* This is abit slow if there's a huge map, since it goes through each element - O(n) time - would be faster with a hash_map or something similar. */

	for (i = 0; i < sizeof(scene_detail_list) / sizeof(struct SceneDetail); i++) {
		if ((scene_detail_list[i].location.x == current_location.x) && (scene_detail_list[i].location.y == current_location.y)) {
			return i;
		}
	}

	return -1;
}

void go_north()
{
	int i = get_scene_detail(current_location.x, current_location.y);

	if (i >= 0) {
		if (scene_detail_list[i].wall_type & NORTH_WALL) {
			printf("Can't go north!\n");
			return;
		}
	}

	current_location.y--;
}

void go_south()
{
	int i = get_scene_detail(current_location.x, current_location.y);

	if (i >= 0) {
		if (scene_detail_list[i].wall_type & SOUTH_WALL) {
			printf("Can't go south!\n");
			return;
		}
	}

	current_location.y++;
}

void go_east()
{
	int i = get_scene_detail(current_location.x, current_location.y);

	if (i >= 0) {
		if (scene_detail_list[i].wall_type & EAST_WALL) {
			printf("Can't go east!\n");
			return;
		}
	}

	current_location.x++;
}

void go_west()
{
	int i = get_scene_detail(current_location.x, current_location.y);

	if (i >= 0) {
		if (scene_detail_list[i].wall_type & WEST_WALL) {
			printf("Can't go west!\n");
			return;
		}
	}

	current_location.x--;
}

void print_current_scene()
{
	int i;

	printf("You are here. x = %d, y = %d\n", current_location.x, current_location.y);


	i = get_scene_detail(current_location.x, current_location.y);

	if (i >= 0) {
		printf("%s\n", scene_detail_list[i].details);
	}

	printf("Where do you want to go? <n,s,e,w> ");
}

int main()
{
	char buf[1024];

	while(1) {

		print_current_scene();

		if (fgets(buf, sizeof(buf), stdin) == NULL)
			break;

		switch(buf[0]) {
			case 'n':
				go_north();
			break;

			case 's':
				go_south();
			break;

			case 'e':
				go_east();
			break;

			case 'w':
				go_west();
			break;
		}
	}

	return 0;
}
