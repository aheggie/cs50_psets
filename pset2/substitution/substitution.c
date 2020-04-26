#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const int LOWER_OFFSET = 97;
const int UPPER_OFFSET = 65;

int error(string error_message);

bool contains_whole_alphabet(string key);

string encypher(string plaintext, string key);

bool is_lower_case_letter(char character);

bool is_upper_case_letter(char character);

int main(int argc, string argv[])
{
    ///if arc !==2
    if (argc != 2)
    {
      return error("Usage: ./substitution key\n");
    }

    const string key = argv[1];

    if (strlen(key) != 26)
    {
      return error("Key must contain exactly 26 characters\n");
    }

    if (!contains_whole_alphabet(key))
    {
      return error("Key must contain entire alphabet\n");
    }

    const string plaintext = get_string("Text: ");
    const string cyphertext = encypher(plaintext, key);

    printf("ciphertext: %s\n", cyphertext);
    return 0;
}

int error(string error_message)
{
    printf("%s", error_message);
    return 1;
}

//we confirm that every character is a letter
//and that their uppercase codepoints
//sum to 2015 - the total sum of 65 to 90 inclusive
bool contains_whole_alphabet(string key)
{
    //one counting element for each letter of the alphabet
    int alphabet_checks[26] = { 0 };

    //note: this makes this an more accurate function in the abstract but
    //is not strictly needed in this particular program
    //as this is first checked indepedently in main
    if (strlen(key) != 26)
    {
      return false;
    }

    for (int i = 0; i < strlen(key); i++)
    {
      if (is_lower_case_letter(key[i]))
      {
        alphabet_checks[(int) key[i] - LOWER_OFFSET] += 1;
      }
      else if (is_upper_case_letter(key[i]))
      {
        alphabet_checks[(int) key[i] - UPPER_OFFSET] += 1;
      }
      else
      {
        //if its not a lower case or an upper case letter then its noy a letter an is invalid
        return false;
      }
    }


    for (int i = 0; i < 26; i++)
    {
      if (alphabet_checks[i] != 1)
      {
        return false;
      }
    }
    return true;
}
string encypher(string plaintext, string key)
{
    //this is a hack to get  astring of same length
    string output = plaintext;
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (is_lower_case_letter(plaintext[i]))
        {
          //you have to force toLowerCase here because the key can be in either case
          //from business rules
          output[i] = tolower(key[(int) plaintext[i] - LOWER_OFFSET]);
        }
        else if (is_upper_case_letter(plaintext[i]))
        {
          //you have to force toUpperCase here because the key can be in either case
          //from business rules
          output[i] = toupper(key[(int) plaintext[i] - UPPER_OFFSET]);
        }
        else
        {
          output[i] = plaintext[i];
        }
    }
    return output;
}

bool is_lower_case_letter(char character)
{
    return 'a' <= character && character <= 'z';
}

bool is_upper_case_letter(char character)
{
    return 'A' <= character && character <= 'Z';
}