#include <stdio.h>
#include <stdlib.h>

int error(char *message);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return error("usage: ./recover filename\n");
    }
    char *filepath = argv[1];
    printf("%s\n", filepath);
}

int error(char *message)
{
    printf("%s", message);
    return 1;
}

