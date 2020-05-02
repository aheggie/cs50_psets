#include <cs50.h>
#include <stdio.h>

int get_height(string);

void repeat_string(int, string);

void repeat_hash(int);

void repeat_space(int);

void single_pyramid_line(int, int);

void forward_pyramid_line(int, int);

void pyramid(int);

int main(void)
{
    //ask for height
    int height = get_height("Height: ");
    pyramid(height);
}

void pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        single_pyramid_line(height, i + 1);
        printf("\n");
    }
}

void single_pyramid_line(int length, int num_hashes)
{
    forward_pyramid_line(length, num_hashes);
    printf("  ");
    repeat_hash(num_hashes);
}

void forward_pyramid_line(int length, int num_hashes)
{
    repeat_space(length - num_hashes);
    repeat_hash(num_hashes);
}

void repeat_space(int times)
{
    repeat_string(times, " ");
}

void repeat_hash(int times)
{
    repeat_string(times, "#");
}

void repeat_string(int times, string str)
{
    for (int i = 0; i < times; i++)
    {
        printf("%s", str);
    }
}

int get_height(string prompt)
{
    int height = 0;
    while (height <= 0 || height > 8)
    {
        height = get_int("%s", prompt);
    }
    return height;
}