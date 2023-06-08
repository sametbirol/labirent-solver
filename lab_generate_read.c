#include <stdio.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

int clean_path_recursive(char **labirent, int x, int y, int *startX, int *startY)
{
    int count;
    if (labirent[y][x] != '?')
    {
        return 1;
    }
    labirent[y][x] = '+';
    if (x == *startX && y == *startY)
    {
        return 0;
    }
    int westeast = (((*startX) - x) > 0) ? 1 : -1;
    int northsouth = (((*startY) - y) > 0) ? 1 : -1;
    count = clean_path_recursive(labirent, x + westeast, y, startX, startY);
    if (!count)
        return 0;
    count = clean_path_recursive(labirent, x, y + northsouth, startX, startY);
    if (!count)
        return 0;
    count = clean_path_recursive(labirent, x - westeast, y, startX, startY);
    if (!count)
        return 0;
    count = clean_path_recursive(labirent, x, y - northsouth, startX, startY);
    if (!count)
        return 0;
    labirent[y][x] = '?';
    return 1;
}

void clean_path(char **labirent, int *endX, int *endY, int *startX, int *startY,int limit_x,int limit_y)
{
    printf("Calculated Labirent size %d x %d\n", limit_x, limit_y);
    int count = 1;
    int x = *endX;
    int y = *endY;
    labirent[y][x] = '+';
    if (*endX == 0)
    {
        count = clean_path_recursive(labirent, x + 1, y, startX, startY);
        if (!count)
            return;
    }
    else if (*endY == 0)
    {
        count = clean_path_recursive(labirent, x, y + 1, startX, startY);
        if (!count)
            return;
    }
    else if (*endY == limit_y - 1)
    {
        count = clean_path_recursive(labirent, x, y - 1, startX, startY);
        if (!count)
            return;
    }
    else if (*endX == limit_x - 1)
    {
        count = clean_path_recursive(labirent, x - 1, y, startX, startY);
        if (!count)
            return;
    }

    // count = clean_path_recursive(labirent, x, y - northsouth, startX, startY);
    // if (!count)
    //     return;
    labirent[y][x] = '?';
}

void clean_lab(char **labirent, int x, int y, int switcher)
{
    char clean;
    char other;
    switch (switcher)
    {

    case 0:
        clean = '*';
        other = '?';
        break;
    case 1:
        clean = '?';
        other = '+';
        break;
    }

    int mark_count = 0;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (labirent[i][j] == other)
            {
                mark_count++;
                if (mark_count > 1)
                {
                    break;
                }
            }
        }
        if (mark_count > 1)
        {
            break;
        }
    }
    if (mark_count >1)
    {
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                if (labirent[i][j] == clean)
                {
                    labirent[i][j] = ' ';
                }
            }
        }
    }
}

void print_lab(char **labirent, int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            printf("%c ", labirent[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int labirent_recursive(char **labirent, int x, int y)
{
    // printf("Current point: (%d,%d)\n", x, y);
    // print_lab(labirent, 7, 7);
    if (labirent[y][x] == '?')
    {
        return 0;
    }
    else if (labirent[y][x] == 'X' || labirent[y][x] == '*')
    {
        return 1;
    }
    else
    {
        labirent[y][x] = '*';
        for (int i = 0; i < 4; i++)
        {
            int count = labirent_recursive(labirent, x + (int)cos(i * M_PI / 2.0), y + (int)sin(i * M_PI / 2.0));
            if (!count)
            {
                labirent[y][x] = '?';
                return 0;
            }
        }
    }
    return 1;
}

void labirent_solver(char **labirent, int *x, int *y)
{
    int count = 1;
    labirent[*y][*x] = '*';
    for (int i = 0; i < 4; i++)
    {
        count = labirent_recursive(labirent, *x + (int)cos(i * M_PI / 2.0), *y + (int)sin(i * M_PI / 2.0));
        if (!count)
        {
            labirent[*y][*x] = '?';
            return;
        }
    }
    labirent[*y][*x] = '*';
    return;
}

void read_from_file(char **labirent, int x, int y)
{
    FILE *readPtr;
    char temp;

    if ((readPtr = fopen("labirent.txt", "r")) == NULL)
    {
        printf("File couldn't be read");
        return;
    }

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            temp = fgetc(readPtr);
            if (temp != '\n')
            {
                labirent[i][j] = temp;
            }
            else
            {
                j--;
            }
        }
    }

    fclose(readPtr);
}

void write_to_file(char **labirent, int x, int y)
{
    FILE *writePtr;

    if ((writePtr = fopen("labirentResult.txt", "w")) == NULL)
    {
        printf("File couldn't be written");
        return;
    }

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            fprintf(writePtr, "%c", labirent[i][j]);
        }
        fprintf(writePtr, "\n");
    }

    fclose(writePtr);
}

void determine_start(char **labirent, int *startX, int *startY, int x, int y, int count)
{
    count = rand() % (count - 1) + 1;

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (labirent[i][j] == ' ')
            {
                count--;
                if (count == 0)
                {
                    *startX = j;
                    *startY = i;
                    return;
                }
            }
        }
    }
}

void determine_exit(int *exitX, int *exitY, int limit_x, int limit_y)
{
    int x = rand() % 3;
    int y;
    switch (x)
    {
    case 0:
        *exitY = 0;
        *exitX = rand() % (limit_x - 3) + 1;
        break;
    case 1:
        *exitY = limit_y - 1;
        *exitX = rand() % (limit_x - 3) + 1;
        break;
    case 2:
        y = rand() % 2;
        switch (y)
        {
        case 0:
            *exitX = 0;
            *exitY = rand() % (limit_y - 3) + 1;
            break;
        case 1:
            *exitX = limit_x - 1;
            *exitY = rand() % (limit_y - 3) + 1;
            break;
        }
        break;
    }
}

void determine_block(int *block_type)
{
    int x = rand() % 7;
    int y = rand() % 5;
    *block_type = (x >= y) ? 1 : 0;
}

void generate_lab(int *xPtr, int *yPtr, int *spPtr, int *exitX, int *exitY)
{
    FILE *flPtr;
    int block = 0;
    int *blockPtr = &block;

    if ((flPtr = fopen("labirent.txt", "w")) == NULL)
    {
        printf("File couldn't be opened!");
        return;
    }

    srand(time(NULL));
    *xPtr = rand() % 20 + 4;
    *yPtr = rand() % 20 + 4;
    int x = *xPtr;
    int y = *yPtr;

    determine_exit(exitX, exitY, x, y);

    for (int i = 0; i < y; i++)
    {
        for (int k = 0; k < x; k++)
        {
            if (k == *exitX && i == *exitY)
            {
                fprintf(flPtr, "?");
                if (k == x - 1 && i != y - 1)
                {
                    fprintf(flPtr, "\n");
                }
                continue;
            }

            if (i == 0 || i == (y - 1) || k == 0 || k == x - 1)
            {
                fprintf(flPtr, "X");
                if (k == x - 1 && i != y - 1)
                {
                    fprintf(flPtr, "\n");
                }
                continue;
            }

            determine_block(blockPtr);

            if (*blockPtr)
            {
                fprintf(flPtr, " ");
                (*spPtr)++;
            }
            else
            {
                fprintf(flPtr, "X");
            }
        }
    }

    fclose(flPtr);
}

int main(void)
{
    clock_t start_time, end_time;

    // Your code here

    start_time = clock();

    // Code segment to measure
    int exit_x = 0;
    int exit_y = 0;
    int *exitX = &exit_x;
    int *exitY = &exit_y;
    int x = 0;
    int y = 0;
    int *xPtr = &x;
    int *yPtr = &y;
    int sp_count = 0;
    int *spPtr = &sp_count;
    int start_x = 0;
    int start_y = 0;
    int *startX = &start_x;
    int *startY = &start_y;

    generate_lab(xPtr, yPtr, spPtr, exitX, exitY);

    char **labirent = (char **)malloc((*yPtr) * sizeof(char *));
    for (int i = 0; i < y; i++)
    {
        labirent[i] = (char *)malloc((*xPtr) * sizeof(char));
    }

    read_from_file(labirent, x, y);
    // print_lab(labirent, x, y);
    determine_start(labirent, startX, startY, x, y, sp_count);
    printf("Space Count: %d\n", sp_count);
    printf("Start point is (%d, %d)\n", *startX, *startY);
    labirent_solver(labirent, startX, startY);
    clean_lab(labirent, x, y, 0);
    clean_path(labirent, exitX, exitY, startX, startY,x,y);
    clean_lab(labirent, x, y, 1);
    // print_lab(labirent, x, y);
    printf("Start point was (%d, %d)\n", *startX, *startY);
    write_to_file(labirent, x, y);

    for (int i = 0; i < y; i++)
    {
        free(labirent[i]);
    }
    free(labirent);

    end_time = clock();

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.5f seconds\n", elapsed_time);
    printf("Labirent size %d x %d\n", *xPtr, *yPtr);
    return 0;
}
