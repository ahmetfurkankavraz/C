#include <stdio.h>
#include <stdlib.h>

int abssub(int a, int b) {
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

int main() {

    int size = 0;
    int car_number = 0;

    //input size
    while (size <= 0 || size > 50) {
        printf("Size: ");
        scanf("%d", & size);

        if (size <= 0 || size > 50) {
            printf("Size must be between 50 and 1");
        }
    }

    //input cars
    printf("Cars: ");
    scanf("%d", & car_number);

    //situations of cars-sizes
    if (size * size == car_number) {
        printf("Best Slot Found In: 0 0\n");
    } 
	
	else if (car_number == 0) {
        printf("Best Slot Found In: 1 1\n");
    } 
	
	else {

        int list[size][size]; //list is two dimensional list which has 0 or 1 for park is full or empty
        int x_list[car_number];
        int y_list[car_number];

        //input the Locations
        for (int i = 0; i < car_number; i++) {

            printf("Locations: ");
            int x, y;
            scanf("%d %d", &x, &y);

            if (x <= size && y <= size && list[x - 1][y - 1] == 0) {
                list[x - 1][y - 1] += 1;
                x_list[i] = x; //full park areas' x values
                y_list[i] = y; //full park areas' y values
            }
			else if (x <= size && y <= size && list[x - 1][y - 1] != 0){
                x_list[i] = x; //full park areas' x values
                y_list[i] = y; //full park areas' y values				
			}

        }
        int newlist[size][size]; //newliste is two dimentional list that has the largest distance to the nearest car

        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                int num = 1000000;

                for (int i = 0; i < car_number; i++) {

                    int value = abssub(x_list[i], x + 1) + abssub(y_list[i], y + 1);
                    if (value < num) {
                        num = value;
                    }
                }
                newlist[x][y] = num; //the largest distance to the nearest car for each slot
            }
        }

        int big = 0;
        int resultx = 0;
        int resulty = 0;

        for (int a = 0; a < size; a++) {
            for (int b = 0; b < size; b++) {

                if ((newlist[a][b] > big) && list[a][b] != 1) {

                    big = newlist[a][b]; //finding the maximum of the values
                    resultx = a + 1;  //finding the x of the value
                    resulty = b + 1;  //finding the y of the value

                }
            }
        }

        printf("Best Slot Found In: %d %d\n", resultx, resulty);

    }
    return EXIT_SUCCESS;
}