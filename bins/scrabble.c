#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool DEBUG_LETTER_SCORE = false;

#define MIN_ALPHA_CHAR         97
#define MAX_ALPHA_CHAR         122
#define LETTERS_IN_ALPHABET    26


int POINTS[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };
int compute_score(string word);


int main(void){
  string word1  = get_string("Player 1: ");
  string word2  = get_string("Player 2: ");
  int    score1 = compute_score(word1);
  int    score2 = compute_score(word2);

  if (DEBUG_LETTER_SCORE) {
    fprintf(stderr,
            "Player 1: |word:%s|score:%d|"
            "\n"
            "Player 2: |word:%s|score:%d|"
            "\n",
            word1,
            score1,
            word2,
            score2
            );
  }

  if (score1 == score2) {
    printf("Tie!\n");
    return(0);
  }
  if (score1 > score2) {
    printf("Player 1 wins!\n");
    return(0);
  }

  if (score2 > score1) {
    printf("Player 2 wins!\n");
    return(0);
  }


  return(2);
}


int compute_score(const string word){
  int word_score = 0;

  for (int i = 0; i < strlen(word); i++) {
    char letter                 = tolower(word[i]);
    bool is_alphanumeric_letter = isalpha(letter);


    int index = (int)(letter);
    while (index > MAX_ALPHA_CHAR) {
      index -= LETTERS_IN_ALPHABET;
    }

    while (index < MIN_ALPHA_CHAR) {
      index += LETTERS_IN_ALPHABET;
    }

    int letter_score = POINTS[index - MIN_ALPHA_CHAR];


    if (DEBUG_LETTER_SCORE) {
      fprintf(stderr, "DEBUG>\tletter:%c|index:%d|letter score:%d|word_score:%d+%d|is_alpha:%d|\n",
              letter,
              index,
              letter_score,
              word_score,
              is_alphanumeric_letter ? letter_score : 0,
              is_alphanumeric_letter
              );
    }

    if (isalpha(letter) == 0) {
      continue;
    }

    word_score += letter_score;
  }
  return(word_score);
}
