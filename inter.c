#include <unistd.h>

int main (int argc, char **argv)
{
    char inter [255] = {0};

    int x;
    int y;
    if (argc == 3)
    {
        x = 2;
        while (x > 0)
        {
            y = 0;

            while (argv[x][y])
            {
                if (x == 2 && !inter[(unsigned char)argv [x][y]])
                inter[(unsigned char)argv [x][y]] = 1;

                if (x == 1 && inter[(unsigned char)argv[x][y]] == 1)
                {
                    write(1, &argv[x][y], 1);
                    inter [(unsigned char) argv [x][y]] = 2; 
                }
                y++;
            }
            x--;
            
        }
        
    }
    write(1, "\n", 1);
    return (0);
}