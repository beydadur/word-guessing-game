#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100

char* get_random_word(char* file_name);
void display_word_status(char* word, char guessed_letters[]);
int is_word_guessed(char* word, char guessed_letters[]);
int is_guess_valid(char* word, char guessed_letters[], char guess);
int guess_word(char* word);
void play_game(char* file_name);
char get_guess();

int main() {
    
    char* file_name = "words.txt"; // play_game
    play_game(file_name); // play_game
//    char* word = get_random_word(file_name); //get_random_word
//    printf( "%s\n", word); // get_random_word
//    char guess; // get_guess
//    guess = get_guess(); // get_guess
//    printf( "%c\n", guess); // get_guess
//    char guessed_letters[] ={'O'}; //display_word_status
//    char* word= "Robot"; //display_word_status
//    display_word_status(word, guessed_letters); //display_word_status
//    char guessed_letters[] ={'O', 'T', 'R', 'B'}; // is_word_guessed
//    char* word= "Robot"; // is_word_guessed
//    int result= is_word_guessed(word, guessed_letters); // is_word_guessed
//    printf("%d\n", result); // is_word_guessed
//    char guessed_letters[] ={'O', 'T'}; //  is_guess_valid
//    char* word= "Robot"; //  is_guess_valid
//    char guess= 'R'; //  is_guess_valid
//    int result= is_guess_valid(word, guessed_letters, guess); //  is_guess_valid
//    printf("%d\n", result); //  is_guess_valid
//    char* word= "Robot"; // guess word
//    int result= guess_word(word); // guess word
//    printf("%d\n", result); // guess word
    return 0;
}


// Function to get a random word from a file
char* get_random_word(char* file_name) {
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////

    // Open the file for reading
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Could not open file %s.\n", file_name);
        exit(1);
    }

    // Count the number of words in the file
    int word_count = 0;
    char word[MAX_WORD_LEN];
    while (fscanf(fp, "%s", word) == 1) {
        word_count++;
    }
    
    // Generate a random number between 0 and word_count-1
    srand(time(NULL));
    int random_index = rand() % word_count;
    
    // Read the random word from the file
    rewind(fp);
    int i = 0;
    while (fscanf(fp, "%s", word) == 1) {
        if (i == random_index) {
            break;
        }
        i++;
    }

    // Close the file and return the random word
    fclose(fp);
    return strdup(word);

////////////////////////////////////////////////////////////////////////////////// 
}

// Function to get a valid guess from the user
char get_guess() {
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////

    char guess;
    printf("Please enter your guess: ");
    scanf(" %c", &guess); // added a space before %c to consume the newline character
    while(getchar() != '\n'); // clear input buffer
    return toupper(guess); // convert guess to uppercase

////////////////////////////////////////////////////////////////////////////////// 
}

// Function to display the status of the word with blanks for unguessed letters
void display_word_status(char* word, char guessed_letters[]) {
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////

    int word_length = strlen(word);
    int guessed_letters_length = strlen(guessed_letters);
    int is_guessed;

    // Iterate over each character of the word
    printf("Word: ");
    for (int i = 0; i < word_length; i++) {
        is_guessed = 0;

        // Check if the character has already been guessed
        for (int j = 0; j < guessed_letters_length; j++) {
            if (toupper(word[i]) == guessed_letters[j]) {
                is_guessed = 1;
                break;
            }
        }

        // Print the character or a dash depending on whether it's been guessed
        if (is_guessed) {
            printf("%c", toupper(word[i]));
        } else {
            printf("-");
        }
    }

    printf("\n");

////////////////////////////////////////////////////////////////////////////////// 
}

// Function to determine if the word has been fully guessed
int is_word_guessed(char* word, char guessed_letters[]) {
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////

    int i, j, len_word, len_guess, found;
    len_word = strlen(word);
    len_guess = strlen(guessed_letters);

    // Iterate over each character of the word
    for (i = 0; i < len_word; i++) {
        found = 0;
        
        // Check if the character has already been guessed
        for (j = 0; j < len_guess; j++) {
            if (toupper(word[i]) == guessed_letters[j]) {
                found = 1;
                break;
            }
        }
        
        if (found == 0) {
            return 0;  // Not all letters have been guessed
        }
    }
    return 1;  // All letters have been guessed

////////////////////////////////////////////////////////////////////////////////// 
}

// Function to determine if a guess is valid (not already guessed and in the word)
int is_guess_valid(char* word, char guessed_letters[], char guess) {
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////
 
    int len_guess = strlen(guessed_letters);
    int len_word = strlen(word);
    int found = 0;
    
    // Check if the guess is a letter
    if (!isalpha(guess)) {
        printf("Invalid guess. Please enter a letter.\n");
        return 0; // If the "guess" is not letter, return 0
    }
    
    // Check if the guess is in the secret word
    for (int j = 0; j < len_word; j++) {
        if (toupper(word[j]) == guess) {
            found = 1;
            break; 
        } 
    }
    
    if (found) {
        return 1; // If the word contains "guess", return 1
    } else {
        printf("The word does not contain %c\n", guess);
        return -1; // If the word does not contain "guess", return -1
    }
    
    // Check if the guess has already been guessed correctly
    for (int i = 0; i < len_guess; i++) {
        if (guess == toupper(guessed_letters[i])) {
            printf("Invalid guess. You already guessed %c\n", guess);
            return 0; // If the "guess" already guessed, return 0
        }
    }
    
////////////////////////////////////////////////////////////////////////////////// 
}

// A single round of the game.
int guess_word(char* word) {
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////

    int i, len_word, guess_left;
    
    char* guessed_letters = calloc(MAX_WORD_LEN, sizeof(char)); // Allocate memory for the guessed_letters array and initialize it to zero
    len_word = strlen(word);
    guess_left = len_word;
    i = 0;

    printf("Welcome to the word guessing game! The word has %i letters.\n", guess_left);
    
    while (0 < guess_left) { // Start a loop that continues until the player runs out of guesses
        printf("You have %i guesses left.\n", guess_left);
        display_word_status(word, guessed_letters);
        char guess = get_guess();
        int validation_checker = is_guess_valid(word, guessed_letters, guess);
        if (validation_checker == -1) { // If the guess is not valid, decrement the number of guesses left
            guess_left--;
        }
        guessed_letters[i] = guess; // Store the guess in the guessed_letters array
        guessed_letters[i+1] = '\0'; // Add a null terminator after the last guessed letter
        i++;
        if (is_word_guessed(word, guessed_letters)) { // Check if the word has been completely guessed
            printf("Congratulations, you guessed the word!\nThe word was %s.\n", word);
            return 1;
        }
    }
    printf("You ran out of guesses. Game over.\nThe word was %s.\n", word); // If the player runs out of guesses, return 0

    free(guessed_letters); // Free the memory allocated for the guessed_letters array

    return 0;
    
////////////////////////////////////////////////////////////////////////////////// 
}


// Function to play the word guessing game
void play_game(char* file_name){
//////////////////////////////////////////////////////////////////////////////////
////////////////////Implement your code here//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

    const int MAX_NUM_PLAYS = 100;
    char checker = 'Y';
    int num_plays = 0;
    int num_win_plays = 0;
    int index = 0;
    char* word;
    char** word_list = calloc(MAX_NUM_PLAYS, sizeof(char*));

    // Main game loop
    while (toupper(checker) == 'Y') {
        
        // Get a random word
        word = get_random_word(file_name);
        
        char new_word[MAX_WORD_LEN+1] = ""; // Initialize to empty string
        if (guess_word(word)) {
            strcpy(new_word, "*"); // Copy the "*" character to the new string
            strcat(new_word, word); // Concatenate the original string to the new string
            word_list[index] = malloc(sizeof(char) * (strlen(new_word) + 1)); // Allocate memory for the new word
            strcpy(word_list[index], new_word); // Copy the new word to the word list
            num_win_plays++;
        }
        else {
            word_list[index] = malloc(sizeof(char) * (strlen(word) + 1)); // Allocate memory for the original word
            strcpy(word_list[index], word); // Copy the original word to the word list
        }

        char gamer_decision;
        printf("Do you want to play again? (Y/N)\n"); // Ask the user if they want to play again
        scanf(" %c", &gamer_decision); // Read a single character
        checker = gamer_decision;

        index++;
        num_plays++;
    }
    
    // Print results
    printf("You played %i times and won %i of them.\nWords:\n", num_plays, num_win_plays);
    for (int i = 0; i < num_plays; i++) {
        printf("%i) %s\n", i+1, word_list[i]);
        free(word_list[i]); // free the memory allocated for each word
    }
    free(word_list); // free the memory allocated for the word list
    
//////////////////////////////////////////////////////////////////////////////////  
}

