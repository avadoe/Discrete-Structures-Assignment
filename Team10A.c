// A V Aashutosh, 2021A7PS0056H
// Saurabh K Atreya, 2021A7PS0190H

#include <stdio.h>
#define max_edges 100

int main(int argc, char **argv)
{
    // Taking file name as a command line argument
    FILE *fp = fopen(argv[1], "r");
    int f[max_edges] = {0};
    int char_check;
    int seq;

    // Scanning the file for characters in the input file, and inputting them as integers
    int j = 0;
    for (int i = 0; i < max_edges; i++)
    {
        char_check = fscanf(fp, "%d", &seq);
        if (char_check == 1)
        {
            f[j] = seq;
            j++;
        }
    }
    fclose(fp);

    // Creating an adjacency matrix, whose dimensions are the number of vertices, as mentioned in the input file
    int adj_mat[f[0]][f[0]];
    // Initialising all elements of adjacency matrix to 0
    for (int i = 0; i < f[0]; i++)
    {
        for (int j = 0; j < f[0]; j++)
        {
            adj_mat[i][j] = 0;
        }
    }

    // Running through all the beginning nodes of each edge, and assigning the value 1 to each node
    for (int i = 2; i < max_edges; i += 2)
    {
        if (f[i] != 0)
        {
            adj_mat[f[i] - 1][f[i + 1] - 1] = 1;
            adj_mat[f[i + 1] - 1][f[i] - 1] = 1;
        }
    }

    // Creating an array for an unsorted degree sequence
    int deg_seq[f[0]];
    // Initialising each degree to 0
    for (int i = 0; i < f[0]; i++)
    {
        deg_seq[i] = 0;
    }
    int deg_seq_idx = 0;

    for (int i = 0; i < f[0]; i++)
    {
        int r_sum = 0, c_sum = 0;
        for (int j = 0; j < f[0]; j++)
        {
            r_sum += adj_mat[i][j];
            c_sum += adj_mat[j][i];
        }
        deg_seq[i] = (r_sum + c_sum) / 2;
    }

    // Sorting the degree sequence to get a non-increasing order
    for (int i = 0; i < f[0] - 1; i++)
    {
        for (int j = i + 1; j < f[0]; j++)
        {
            if (deg_seq[j] > deg_seq[i])
            {
                int t = deg_seq[i];
                deg_seq[i] = deg_seq[j];
                deg_seq[j] = t;
            }
        }
    }
    // Printing the degree sequence
    printf("Printing the degree sequence: \n");
    for (int i = 0; i < f[0]; i++)
    {
        printf("%d ", deg_seq[i]);
    }
    return 0;
}
