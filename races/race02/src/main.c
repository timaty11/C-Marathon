#include "../inc/header.h"

char **maze = NULL;
char **maze2 = NULL;

int find_path1(int x, int y, int x_exit, int y_exit, int rows, int cols);
int find_path2(int x, int y, int x_exit, int y_exit, int rows, int cols);

int path_counter = 0;
bool found_exit = 0;


int main(int argc, char *argv[]) {
    if (argc != 6) {
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2]");
        mx_printerr("\n");
        return 1;
    }

    int rows_count = 0; // Количество строк в файле
    int columns = 0; // Количество символов в строке без учета запятых
    int fake_columns = 0; // Количество символов в строке с учетом запятых

    // Проверка на ввод
    char buf = 'a';
    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        mx_printerr("map does not exist");
        mx_printerr("\n");
        return 1;
    }

    // Считаем количество символов в строке
    while(buf != '\n') {
        read(file, &buf, sizeof(char));
        fake_columns++;
        if (buf == '.' || buf == '#') {
            columns++;
        }
    }
    // Проверка на прямоугольник карты - отталкиваемся от размера первой строки
    // если какая-то строка отличается размером от первой строки -
    // выводим ошибку
    int lol_tmp = 0;
    while(read(file, &buf, sizeof(char))) {
        if (buf == '\n') {
            if (lol_tmp != fake_columns - 1) {
                mx_printerr("map error");
                mx_printerr("\n");
                return 1;
            } else {
                lol_tmp = 0;
            }
        } else {
            lol_tmp++;
        }
    }
    close(file);

    // Считаем количество строк
    file = open(argv[1], O_RDONLY);
    char *row[fake_columns];
    while(read(file, row, (sizeof(char) * (fake_columns)))) {
        rows_count++;
    }
    rows_count++;
    close(file);

    // Выделяем память под нашу матрицу
    maze = (char**)malloc(rows_count * sizeof(char*));
    for (int i = 0; i < rows_count; i++) {
        maze[i] = (char*)malloc(columns * sizeof(char));
    }

    maze2 = (char**)malloc(rows_count * sizeof(char*));
    for (int i = 0; i < rows_count; i++) {
        maze2[i] = (char*)malloc(columns * sizeof(char));
    }

    char *str = mx_file_to_str(argv[1]);
    int **grid = matrix(str,&rows_count,&columns);

    // Если
    int i = 0;
    int j = 0;
    file = open(argv[1], O_RDONLY);
    while(read(file, &buf, sizeof(char))) {
        if (buf == '.' || buf == '#') {
            maze[i][j] = buf;
            maze2[i][j] = buf;
            j++;
        } else if (buf == '\n') {
            j = 0;
            i++;
        } else if (buf != ',') {
            mx_printerr("map error");
            mx_printerr("\n");
            return 1;
        }
    }

    int x1 = mx_atoi(argv[2]);
    int y1 = mx_atoi(argv[3]);
    int x2 = mx_atoi(argv[4]);
    int y2 = mx_atoi(argv[5]);

    // Проверка на корректность координат:
    // Они должны быть в пределах карты и не лежать на #
    if (x1 > columns || y1 > rows_count || x2 > columns || y2 > rows_count) {
        mx_printerr("points are out of map range");
        mx_printerr("\n");
        return 1;
    } else if (maze[y1][x1] == '#') {
        mx_printerr("entry point cannot be an obstacle");
        mx_printerr("\n");
        return 1;
    } else if (maze[y2][x2] == '#') {
        mx_printerr("exit point cannot be an obstacle");
        mx_printerr("\n");
        return 1;
    }

    maze[y1][x1] = 'S';
    maze[y2][x2] = 'G';

    close(file);

    // Если все гуд и путь найден то выводится саксесс и длинна пути
    // если путь не найден то ошибка
    mx_printstr("dist=");
    mx_printint(max(grid, x1,y1,rows_count, columns, maze2));
    mx_printstr("\n");

    if (x1 < x2) {
        if (find_path1(x1, y1, x2, y2, rows_count, columns) == 1) {
            mx_printstr("exit=");
            mx_printint(path_counter + 1);
            mx_printstr("\n");
        } else {
            mx_printerr("route not found");
            mx_printerr("\n");
            return 1;
        }
    }
    else {
        if (find_path2(x1, y1, x2, y2, rows_count, columns) == 1) {
            mx_printstr("exit=");
            mx_printint(path_counter + 1);
            mx_printstr("\n");
        } else {
            mx_printerr("route not found");
            mx_printerr("\n");
            return 1;
        }
    }

    int file_result = open("path.txt", O_WRONLY);
    if (file_result < 0)
    {
        file_result = open("path.txt", O_CREAT | O_WRONLY);
    }
    for (int i = 0; i < rows_count; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            char buffer = maze[i][j];
            write(file_result, &buffer, 1);
        }
        write(file_result, "\n", 1);
    }
    if(close(file_result) < 0) {
        write(2, "error\n", 6);
    }

    return 0;
}


int find_path1(int x, int y, int x_exit, int y_exit, int rows, int cols) {
    // If x,y is outside maze, return false.
    if (x < 0 || x > rows - 1 || y < 0 || y > cols - 1) return 0;

    // If x,y is the goal, return true.
    if (maze[y][x] == 'G') {
        maze[y][x] = '*';
        // found_exit = 1;
        return 1;
    } else if (x > 0 && maze[y][x] != '#' && maze[y][x - 1] == 'G') {
        maze[y][x] = '*';
        maze[y][x - 1] = '*';
        // found_exit = 1;
        return 1;
    } else if (x < rows - 1 && maze[y][x] != '#' && maze[y][x + 1] == 'G') {
        maze[y][x] = '*';
        maze[y][x + 1] = '*';
        // found_exit = 1;
        return 1;
    } else if (y > 0 && maze[y][x] != '#' &&  maze[y - 1][x] == 'G') {
        maze[y][x] = '*';
        maze[y - 1][x] = '*';
        // found_exit = 1;
        return 1;
    } else if (y < cols - 1 && maze[y][x] != '#' && maze[y + 1][x] == 'G') {
        maze[y][x] = '*';
        maze[y + 1][x] = '*';
        // found_exit = 1;
        return 1;
    }

    // If x,y is not open, return false.
    if (maze[y][x] != '.' && maze[y][x] != 'S') return 0;

    maze[y][x] = '*';
    path_counter++;

    if (x > x_exit) {
        // If find_path West of x,y is true, return true.
        if (find_path1(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path North of x,y is true, return true.
        if (find_path1(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path East of x,y is true, return true.
        if (find_path1(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path South of x,y is true, return true.
        if (find_path1(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;
    } else if (x < x_exit) {
        // If find_path East of x,y is true, return true.
        if (find_path1(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path South of x,y is true, return true.
        if (find_path1(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path North of x,y is true, return true.
        if (find_path1(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path West of x,y is true, return true.
        if (find_path1(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;
    } else if (y > y_exit) {
        // If find_path South of x,y is true, return true.
        if (find_path1(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path North of x,y is true, return true.
        if (find_path1(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path West of x,y is true, return true.
        if (find_path1(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path East of x,y is true, return true.
        if (find_path1(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;
    } else {
        // If find_path North of x,y is true, return true.
        if (find_path1(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path South of x,y is true, return true.
        if (find_path1(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path West of x,y is true, return true.
        if (find_path1(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path East of x,y is true, return true.
        if (find_path1(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;
    }

    // Unmark x,y as part of solution path.
    maze[y][x] = 'x';
    path_counter--;
    if (maze[y][x] == 'x')
    {
        maze[y][x] = '.';
    }

    return 0;
}

int find_path2(int x, int y, int x_exit, int y_exit, int rows, int cols) {
    // If x,y is outside maze, return false.
    if (x < 0 || x > rows - 1 || y < 0 || y > cols - 1) return 0;

    // If x,y is the goal, return true.
    if (maze[y][x] == 'G') {
        maze[y][x] = '*';
        // found_exit = 1;
        return 1;
    } else if (x > 0 && maze[y][x] != '#' && maze[y][x - 1] == 'G') {
        maze[y][x] = '*';
        maze[y][x - 1] = '*';
        // found_exit = 1;
        return 1;
    } else if (x < rows - 1 && maze[y][x] != '#' && maze[y][x + 1] == 'G') {
        maze[y][x] = '*';
        maze[y][x + 1] = '*';
        // found_exit = 1;
        return 1;
    } else if (y > 0 && maze[y][x] != '#' &&  maze[y - 1][x] == 'G') {
        maze[y][x] = '*';
        maze[y - 1][x] = '*';
        // found_exit = 1;
        return 1;
    } else if (y < cols - 1 && maze[y][x] != '#' && maze[y + 1][x] == 'G') {
        maze[y][x] = '*';
        maze[y + 1][x] = '*';
        // found_exit = 1;
        return 1;
    }

    // If x,y is not open, return false.
    if (maze[y][x] != '.' && maze[y][x] != 'S') return 0;

    maze[y][x] = '*';
    path_counter++;

    if (x > x_exit) {
        // If find_path West of x,y is true, return true.
        if (find_path2(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path South of x,y is true, return true.
        if (find_path2(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path East of x,y is true, return true.
        if (find_path2(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path North of x,y is true, return true.
        if (find_path2(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

    } else if (x < x_exit) {
        // If find_path East of x,y is true, return true.
        if (find_path2(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path South of x,y is true, return true.
        if (find_path2(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path North of x,y is true, return true.
        if (find_path2(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path West of x,y is true, return true.
        if (find_path2(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;
    } else if (y > y_exit) {
        // If find_path South of x,y is true, return true.
        if (find_path2(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path North of x,y is true, return true.
        if (find_path2(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path West of x,y is true, return true.
        if (find_path2(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path East of x,y is true, return true.
        if (find_path2(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;
    } else {
        // If find_path North of x,y is true, return true.
        if (find_path2(x, y - 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path South of x,y is true, return true.
        if (find_path2(x, y + 1, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path West of x,y is true, return true.
        if (find_path2(x - 1, y, x_exit, y_exit, rows, cols) == 1) return 1;

        // If find_path East of x,y is true, return true.
        if (find_path2(x + 1, y, x_exit, y_exit, rows, cols) == 1) return 1;
    }

    // Unmark x,y as part of solution path.
    maze[y][x] = 'x';
    path_counter--;
    if (maze[y][x] == 'x')
    {
        maze[y][x] = '.';
    }

    return 0;
}

