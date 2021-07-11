#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MOVIES 10
#define MAX_TITLE 100

//add your functions and struct definition here.
struct Movie {
	char *title;
	int purchases;
	double average_rating;
};

int get_purchases(struct Movie *movies, char *movie_title ){
	int i;	
	for (i = 0; i < N_MOVIES && movies[i].title != NULL; i++){
		if (strcmp(movies[i].title, movie_title) == 0){			
			break;
		}
	}
	if (i == N_MOVIES || movies[i].title  == NULL){
		return -1;
	}
	else {
		int result = movies[i].purchases;
		return result;
	}
}
int add_movie(struct Movie *movies, char *movie_title, double movie_rating){
	int i;
	for (i = 0; i < N_MOVIES ; i++){
		if (movies[i].purchases == -1){
			break;
		}
	}
	if (i == N_MOVIES){
		return 0;
	}
	else {
		movies[i].title = movie_title;
		movies[i].purchases = 1;
		movies[i].average_rating = movie_rating;
		return 1;
	}
}

int compute_rating(struct Movie *movies, char *movie_title, int movie_rating){
	int i;
	for (i = 0; i < N_MOVIES && movies[i].title != NULL; i++){
		if ( strcmp(movies[i].title, movie_title) == 0){
			break;
		}
	}
	if (i == N_MOVIES || movies[i].title == NULL){
		return 0;
	}	
	else {
		double total_purcahes = movies[i].purchases * movies[i].average_rating + movie_rating;
		movies[i].purchases++;
		movies[i].average_rating = total_purcahes / movies[i].purchases;
		printf("The movie %s is updated. The number of purchases is %d. The rating is updated to %.2f.\n", movies[i].title, movies[i].purchases, movies[i].average_rating);
		return 1;
	}
}


int main()
{
	//there are initially two elements in the array. 
    struct Movie movies[N_MOVIES] = { {"Spartacus", 9, 4.0}, {"Ben Hur", 5, 1.8}};
    
	char movie_title[MAX_TITLE];
    int movie_rating, menu_selection, result;
    char input;

    for (int i = 2; i < N_MOVIES; i++)
        movies[i].purchases = -1;

    printf("Welcome to the movie database.\n");
    do {
        printf("Enter your request (1 for getting the purchases of a movie, 2 for updating the rating of a movie, 3 for exit):");
        scanf("%d", &menu_selection);

        if (menu_selection == 1) {
            printf("Enter the movie title:");
            scanf(" %[^\n]s", movie_title);

            result = get_purchases(movies, movie_title);
            if (result != -1) {
                printf("The movie %s has been purchased %d times.\n", movie_title, result);
            } else {
                printf("The movie %s could not be found in the database.\n", movie_title);
            }
        }

        else if (menu_selection == 2) {
            printf("Enter the movie title:");
            scanf(" %[^\n]s", movie_title);

            printf("Enter the movie rating (out of 5):");
            scanf("%d", &movie_rating);

            while (movie_rating < 0 || movie_rating > 5) {
                printf("Enter the movie rating (out of 5):");
                scanf("%d", &movie_rating);
            }

            result = compute_rating(movies, movie_title, movie_rating);
            if (result == 0) {
                printf("The movie %s could not be found in the database. Would you like to add this movie (Y/N):", movie_title);
                scanf(" %c", &input);

                while (input != 'Y' && input != 'N') {
                    printf("Please enter a valid input (Y/N):");
                    scanf(" %c", &input);
                }

                if (input == 'Y') {
                    result = add_movie(movies, movie_title, movie_rating);
                    if (result == 1) {
                        printf("The movie %s is added to the database with a rating of %d.\n", movie_title, movie_rating);
                    } else {
                        printf("The movie %s could not be added to the database.\n", movie_title);
                    }
                }
            }
        }
    } while (menu_selection != 3);

    return EXIT_SUCCESS;
}
