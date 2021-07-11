#include <stdio.h>
#include <stdlib.h>

int target;

int findpoint(int point, char value) {

    switch (value) {
    case 'S':
        point = point;
        break;
    case 'D':
        point *= 2;
        break;
    case 'T':
        point *= 3;
        break;
    case 'O':
        point = 25;
        break;
    case 'I':
        point = 50;
        break;
    }
    return point;
}
int gamepoint(int new_target, int point, char value) {

    if ((new_target == target) && (value == 'D')) {
        new_target -= findpoint(point, value);
    } else if ((new_target == target) && (value != 'D')) {
        new_target = new_target;
    } else {
        new_target -= findpoint(point, value);
        if ((new_target < 0) || (new_target == 1)){
            new_target += findpoint(point, value);
        } else if (((new_target == 0) )&& (value != 'D')) {
            new_target += findpoint(point, value);
        }
    }

    return new_target;
}

int main() {
    printf("Target: ");
    scanf("%d", & target);

    int new_target = target;

    while (new_target != 0) {
        int point;
        char value;
        printf("Throw: ");
        scanf("%d %c", & point, & value);
        new_target = gamepoint(new_target, point, value);
        printf("Points: %d\n", new_target);

    }
    return EXIT_SUCCESS;
}