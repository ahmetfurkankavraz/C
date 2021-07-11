#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

    int year = 0, month = 0, day = 0;
    printf("Enter date [year month day]: ");
    scanf("%d %d %d", & year, & month, & day);

    int firstyear = year + 1;

    //is date valid?
    int result;
    if (day <= 0) {
        result = 1;
    } else if ((month < 0) || (month > 12)) {
        result = 1;
    } else if (month == 2 && day > 28) {
        result = 1;
    } else if (((month == 4) || (month == 6) || (month == 9) || (month == 11)) && (day > 30)) {
        result = 1;
    } else if (((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) && (day > 31)) {
        result = 1;
    } else {
        result = 0;
    }

    //checking valid date
    if (result == 1) {
        printf("Invalid date.\n");
        return EXIT_FAILURE;
    } else {
        int endyear;
        printf("Enter end year: ");
        scanf("%d", & endyear);

        ///finding date is which weekday
        if ((month == 1) || (month == 2)) {
            month += 12;
            year -= 1;
            endyear -= 1;
        }
        int yearFirst = year / 100;
        int yearEnd = year % 100;

        int weekday = ((day + ((13 * (month + 1)) / 5) + yearEnd + (yearEnd / 4) + (yearFirst / 4) + (yearFirst * 5)) % 7);

        switch (weekday) {
        case 0:
            printf("It's a Saturday.\n");
            break;
        case 1:
            printf("It's a Sunday.\n");
            break;
        case 2:
            printf("It's a Monday.\n");
            break;
        case 3:
            printf("It's a Tuesday.\n");
            break;
        case 4:
            printf("It's a Wednesday.\n");
            break;
        case 5:
            printf("It's a Thursday.\n");
            break;
        case 6:
            printf("It's a Friday.\n");
            break;
        }
        //////////////////////////////

        ///
        int i = year + 1;

        int counter = 0;

        while (i <= endyear) {
            int iEnd = i % 100;
            int iFirst = i / 100;
            int iWeekday = (day + ((13 * (month + 1)) / 5) + iEnd + (iEnd / 4) + (iFirst / 4) + (iFirst * 5)) % 7;

            if (weekday == iWeekday) {
                counter += 1;
            }
            i += 1;
        }

        int countday = counter;

        if ((month == 13) || (month == 14)) {
            endyear += 1;
        }

        printf("Same day-and-month on same weekday between %d and %d: %d\n", firstyear, endyear, countday);
        return EXIT_SUCCESS;
    }
}