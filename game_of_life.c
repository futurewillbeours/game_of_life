
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define MATR_SIZE 3
#define SLEEP_TIME 1000000

int true_value_WIDTH(int x) {
    if (x < 0)
        x = WIDTH + x;
    else if (x >= WIDTH)
        x = x - WIDTH;
    return x;
}

int true_value_HEIGHT(int x) {
    if (x < 0)
        x = HEIGHT + x;
    else if (x >= HEIGHT)
        x = x - HEIGHT;
    return x;
}

void reset_field(int field[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = 0;
        }
    }
}

void draw_field(int field[][WIDTH]) {
    move(0, 0);
    for (int i = 0; i < WIDTH + 1; i++) printw("--");
    printw("\n");

    for (int i = 0; i < HEIGHT; i++) {
        printw("|");
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] != 0)
                printw("o ");
            else
                printw("  ");
        }
        printw("|");
        printw("\n");
    }

    for (int i = 0; i < WIDTH + 1; i++) printw("--");
    printw("\n");

    printw("\nEnter A/Z for game speed changing!");
    refresh();
}

void field_initial_state_set(int field[][WIDTH], int conf_matrix[][MATR_SIZE]) {
    for (int i = 0; i < MATR_SIZE; i++) {
        for (int j = 0; j < MATR_SIZE; j++) {
            field[HEIGHT / 2 + i][WIDTH / 2 + j] = conf_matrix[i][j];
        }
    }
}

void life(int field[][WIDTH]) {
    int tmp_field[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            tmp_field[i][j] = 0;
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int life_count = 0;
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    if (field[true_value_HEIGHT(i + k)][true_value_WIDTH(j + l)] == 1) life_count++;
                }
            }
            if (field[i][j] == 1)
                tmp_field[i][j] = life_count - 1;
            else
                tmp_field[i][j] = life_count;
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 0) {
                if (tmp_field[i][j] == 3) field[i][j] = 1;
            } else if (tmp_field[i][j] > 3 || tmp_field[i][j] < 2)
                field[i][j] = 0;
        }
    }
}

int finish_check(int field[][WIDTH]) {
    int count = 0;
    int finish = 0;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] != 0) {
                count++;
            }
        }
    }
    if (count == 0) finish++;
    count = 0;

    int tmp_field[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            tmp_field[i][j] = field[i][j];
        }
    }

    life(tmp_field);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (tmp_field[i][j] == field[i][j]) count++;
        }
    }

    if (count == WIDTH * HEIGHT) finish++;
    return finish;
}

int conf_choice(int conf_matrix[][MATR_SIZE]) {
    int errors = 0;
    FILE *file;
    int state = 0;
    printw("\nCycle:\t\t1\nExtinction 1:\t2\nDoesn't change:\t3\nExtinction 2:\t4\nPlanner:\t5\n\n");
    printw("Enter correct initial state of field (from 1 to 5): ");
    if (scanw("%d", &state) != 1)
        errors++;
    else if (state < 1 || state > 5)
        errors++;
    else {
        if (state == 1)
            file = fopen("conf1.txt", "r");
        else if (state == 2)
            file = fopen("conf2.txt", "r");
        else if (state == 3)
            file = fopen("conf3.txt", "r");
        else if (state == 4)
            file = fopen("conf4.txt", "r");
        else
            file = fopen("conf5.txt", "r");

        for (int i = 0; i < MATR_SIZE; i++) {
            fscanf(file, "%d%d%d", &conf_matrix[i][0], &conf_matrix[i][1], &conf_matrix[i][2]);
        }

        fclose(file);
    }
    return errors;
}

int main(void) {
    initscr();

    int conf_matrix[3][3];

    if (conf_choice(conf_matrix) != 0) {
        printw("\nNumber is incorrect!");
        refresh();
    } else {
        int field[HEIGHT][WIDTH];
        int sleep = SLEEP_TIME;
        int exit = 0;
        noecho();
        nodelay(stdscr, TRUE);
        reset_field(field);
        field_initial_state_set(field, conf_matrix);
        while (1) {
            draw_field(field);
            life(field);
            int input = getch();
            if (input == 'a' || input == 'A')
                sleep -= sleep / 2;
            else if (input == 'z' || input == 'Z')
                sleep += sleep / 2;
            else if (input == 'q' || input == 'Q')
                exit++;
            usleep(sleep);
            if (finish_check(field) != 0 || exit != 0) break;
        }
        draw_field(field);
        printw("\n\nFINISH!");
        nodelay(stdscr, FALSE);
        getch();
        endwin();
    }
}