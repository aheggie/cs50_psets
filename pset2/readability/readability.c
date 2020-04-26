#include <stdio.h>
#include <cs50.h>
#include <math.h>

void print_grade_level(float coleman_liau_index);

float coleman_liau(int, int, int);

int count_letters(string text);

int count_sentences(string text);

int count_words(string text);

bool is_letter(char character);

bool is_lower_case_letter(char character);

bool is_upper_case_letter(char character);

bool is_space(char character);

bool is_terminating_character(char character);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int sentences = count_sentences(text);
    int words = count_words(text);

    float coleman_liau_index = coleman_liau(letters, sentences, words);
    print_grade_level(coleman_liau_index);
}

void print_grade_level(float coleman_liau_index)
{
    if (coleman_liau_index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_liau_index < 16.0)
    {
        printf("Grade %i\n", (int) round(coleman_liau_index));
    }
    else
    {
        printf("Grade 16+\n");
    }
}

float coleman_liau(int letters, int sentences, int words)
{
    float letters_per_hundred_words = (letters / (float) words) * 100;
    float sentences_per_hundred_words = (sentences / (float) words) * 100;

    float index =
        0.0588 * letters_per_hundred_words -
        0.296 * sentences_per_hundred_words -
        15.8;

    return index;
}


//this is more efficient but wont work as c wont return arrays
// int count_letters_sentences_and_words(text) {
//   int counts[3] = [0, 0, 0];
//   for (int i = 0; text[i] != '\0'; i++) {
//     char character = text[i];
//     // console.log(char);
//     if (is_letter(character)) {
//       // console.log("letter");
//       counts[0] += 1;
//     } else if (is_terminating_character(character)) {
//       counts[1] += 1;
//     } else if (is_space(character)) {
//       counts[2] += 1;
//     }
//   }
//   //to avoid off by one error - there will be one more space than words
//   counts[2] += 1;

//   // console.log(counts);
//   return counts;
// }

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (is_letter(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (is_terminating_character(text[i]))
        {
            sentences += 1;
        }
    }
    return sentences;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (is_space(text[i]))
        {
            words += 1;
        }
    }
    //this +1 is to avoid off by one error
    return words + 1;
}

bool is_letter(char character)
{
    return is_lower_case_letter(character) || is_upper_case_letter(character);
}

bool is_lower_case_letter(char character)
{
    return 'a' <= character && character <= 'z';
}

bool is_upper_case_letter(char character)
{
    return 'A' <= character && character <= 'Z';
}

bool is_space(char character)
{
    return character == ' ';
}

bool is_terminating_character(char character)
{
    return character == '.' || character == '!' || character == '?';
}
