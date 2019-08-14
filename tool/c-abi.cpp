#include <stdio.h>

#define BUF_SIZE 1024
char buf[1024];

int main(int argc, char **argv)
{
    FILE *fp= fopen(argv[1], "r");

    FILE *fp_out = fopen("./out.json", "w+");

    size_t len = 0;
    while((len = fread(buf, 1, BUF_SIZE, fp)) > 0)
    {
        int i = 0;
        int size = 0;
        while (i < len)
        {
            if ((buf[i] != ' ') &&
                (buf[i] != '\n'))
            {
                buf[size ++] = buf[i];
            }

            i ++;
        }

        fwrite(buf, 1, size, fp_out);
    }

    fflush(fp_out);
    fclose(fp);
    fclose(fp_out);

    return 0;
}
