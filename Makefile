all:
	gcc -Wall -Werror -Wextra game_of_life.c -o game.out -lncurses
rebuild:
	rm game.out
	gcc -Wall -Werror -Wextra game_of_life.c -o game.out -lncurses
clean:
	rm game.out