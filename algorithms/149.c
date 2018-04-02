#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 * }
 */

struct Point {
    int x;
    int y;
};

struct LineHashEntry {
    struct Point line;
    int points;
    UT_hash_handle hh;
};

int getGCD(int a, int b)
{
    if (a < 0 ) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }

    while (b != 0) {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}

struct Point getLineFromTwoPoints(struct Point *p1, struct Point *p2)
{
    struct Point ret;
    int dx = p1->x - p2->x, dy = p1->y - p2->y;

    if (dx == 0) {
        ret.x = 0;
        ret.y = 1;
        return ret;
    }
    
    if (dx < 0) {
        dx = -dx;
        dy = -dy;
    }

    int gcd = getGCD(dx, dy);
    dx /= gcd;
    dy /= gcd;
    ret.x = dx;
    ret.y = dy;
    return ret;
}

struct LineHashEntry *createLineHashEntry()
{
    struct LineHashEntry *line = (struct LineHashEntry *)malloc(sizeof(struct LineHashEntry));
    memset(line, 0, sizeof(struct LineHashEntry));
    return line;
}

int maxPoints(struct Point* points, int pointsSize)
{
    if (pointsSize < 3) {
        return pointsSize;
    }

    int result = 0;
    for (int i = 0; i < pointsSize; i++) {
        struct LineHashEntry *lines = NULL, *tmp = NULL;
        int overlap = 1;
        int innerMax = 0;
        for (int j = i + 1; j < pointsSize; j++) {
            if (points[j].x == points[i].x && points[j].y == points[i].y) {
                overlap++;
                continue;
            }

            struct Point line = getLineFromTwoPoints(&(points[i]), &(points[j]));
            HASH_FIND(hh, lines, &line, sizeof(struct Point), tmp);
            if (!tmp) {
                tmp = createLineHashEntry();
                tmp->line = line;
                HASH_ADD(hh, lines, line, sizeof(struct Point), tmp);
            }
            tmp->points++;
            innerMax = (tmp->points > innerMax) ? tmp->points : innerMax;
        }
        innerMax += overlap;
        result = result > innerMax ? result : innerMax;
        HASH_CLEAR(hh, lines);
    }

    return result;
}

int main()
{
    /*
    int gcd = getGCD(15, 9);
    printf("gcd = %d\n", gcd);
    gcd = getGCD(9, 15);
    printf("gcd = %d\n", gcd);
    gcd = getGCD(-9, 15);
    printf("gcd = %d\n", gcd);
    */

    //struct Point points[] = {{0,0},{94911151,94911150},{94911152,94911151}};
    //struct Point points[] = {{0,0},{1,1},{0,0}};
    struct Point points[] = {{0,-12},{5,2},{2,5},{0,-5},{1,5},{2,-2},{5,-4},{3,4},{-2,4},{-1,4},{0,-5},{0,-8},{-2,-1},{0,-11},{0,-9}};
    //struct Point points[] = {{1,1},{1,1},{1,1}};

    int ret = maxPoints(points, sizeof(points) / sizeof (struct Point));
    printf("ret = %d\n", ret);
    return 0;
}
