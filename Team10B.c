// A V Aashutosh, 2021A7PS0056H
// Saurabh K Atreya, 2021A7PS0190H

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to generate permutations of an array of size n, and returns the rth iteration array
// We use this on the list-of-vertex array
int *permutation(int *array, int n, int r)
{
    int *temp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        temp[i] = array[i];
    }
    for (int i = 1; i < n; i++)
    {
        int j = r % (i + 1);
        swap(&temp[i], &temp[j]);
        r /= (i + 1);
    }
    return temp;
}

int main(int argc, char **argv)
{
    // Taking file names as a command line argument
    FILE *fp1 = fopen(argv[1], "r");
    int n_vert1, n_edge1;
    fscanf(fp1, "%d", &n_vert1);
    fscanf(fp1, "%d", &n_edge1);
    int *edge_seq1 = malloc(n_edge1 * 2 * sizeof(int));
    int tv;
    for (int i = 0; i < n_edge1 * 2; i++)
    {
        fscanf(fp1, "%d", &tv);
        edge_seq1[i] = tv;
    }
    fclose(fp1);

    FILE *fp2 = fopen(argv[2], "r");
    int n_vert2, n_edge2;
    fscanf(fp2, "%d", &n_vert2);
    fscanf(fp2, "%d", &n_edge2);
    int *edge_seq2 = malloc(n_edge2 * 2 * sizeof(int));
    for (int i = 0; i < n_edge2 * 2; i++)
    {
        fscanf(fp2, "%d", &tv);
        edge_seq2[i] = tv;
    }
    fclose(fp2);

    // Creating adjacency matrices, whose dimensions are the number of vertices, as mentioned in the input file
    int adj_mat_1[n_vert1][n_vert1];
    // Initialising all elements of adjacency matrix to 0
    for (int i = 0; i < n_vert1; i++)
    {
        for (int j = 0; j < n_vert1; j++)
        {
            adj_mat_1[i][j] = 0;
        }
    }
    int adj_mat_2[n_vert2][n_vert2];
    // Initialising all elements of adjacency matrix to 0
    for (int i = 0; i < n_vert2; i++)
    {
        for (int j = 0; j < n_vert2; j++)
        {
            adj_mat_2[i][j] = 0;
        }
    }

    // Running through all the beginning nodes of each edge, and assigning the value 1 to each required node
    for (int i = 0; i < n_edge1 * 2; i += 2)
    {
        if (edge_seq1[i] != 0)
        {
            adj_mat_1[edge_seq1[i] - 1][edge_seq1[i + 1] - 1] = 1;
            adj_mat_1[edge_seq1[i + 1] - 1][edge_seq1[i] - 1] = 1;
        }
    }
    for (int i = 0; i < n_edge2 * 2; i += 2)
    {
        if (edge_seq2[i] != 0)
        {
            adj_mat_2[edge_seq2[i] - 1][edge_seq2[i + 1] - 1] = 1;
            adj_mat_2[edge_seq2[i + 1] - 1][edge_seq2[i] - 1] = 1;
        }
    }

    // Creating an array of size = number of vertices, for an unsorted degree sequence
    int deg_seq_1[n_vert1];
    // Initialising each degree to 0
    for (int i = 0; i < n_vert1; i++)
    {
        deg_seq_1[i] = 0;
    }

    for (int i = 0; i < n_vert1; i++)
    {
        int r_sum = 0, c_sum = 0;
        for (int j = 0; j < n_vert1; j++)
        {
            r_sum += adj_mat_1[i][j];
            c_sum += adj_mat_1[j][i];
        }
        deg_seq_1[i] = (r_sum + c_sum) / 2;
    }

    int deg_seq_2[n_vert2];
    // Initialising each degree to 0
    for (int i = 0; i < n_vert2; i++)
    {
        deg_seq_2[i] = 0;
    }

    for (int i = 0; i < n_vert2; i++)
    {
        int r_sum = 0, c_sum = 0;
        for (int j = 0; j < n_vert2; j++)
        {
            r_sum += adj_mat_2[i][j];
            c_sum += adj_mat_2[j][i];
        }
        deg_seq_2[i] = (r_sum + c_sum) / 2;
    }

    // Sorting the degree sequence to get a non-increasing order
    for (int i = 0; i < n_vert1 - 1; i++)
    {
        for (int j = i + 1; j < n_vert1; j++)
        {
            if (deg_seq_1[j] > deg_seq_1[i])
            {
                int t = deg_seq_1[i];
                deg_seq_1[i] = deg_seq_1[j];
                deg_seq_1[j] = t;
            }
        }
    }
    for (int i = 0; i < n_vert2 - 1; i++)
    {
        for (int j = i + 1; j < n_vert2; j++)
        {
            if (deg_seq_2[j] > deg_seq_2[i])
            {
                int t = deg_seq_2[i];
                deg_seq_2[i] = deg_seq_2[j];
                deg_seq_2[j] = t;
            }
        }
    }

    if ((n_edge1 != n_edge2) || (n_vert1 != n_vert2))
    // If the number of edges isn't the same, or the number of vertices isn't the same, we can directly conclude
    // that the graphs aren't isomorphic
    {
        printf("Not Isomorphic, no bijection found.\n");
        return 0;
    }

    // If the number of edges are the same, we can proceed to check whether the decreasing order of degree sequence
    // is the same. If it isn't so, we conclude that the graphs aren't isomorphic and exit the program
    for (int m = 0; m < n_vert1; m++)
    {
        if (deg_seq_1[m] != deg_seq_2[m])
        {
            printf("Not Isomorphic, no bijection found.");
            return 0;
        }
        m++;
    }

    int *temp_vertex_seq = malloc(n_vert1 * sizeof(int));
    // We are creating a temporary vertex sequence array, and assigning names to the vertices/nodes of the graph
    // The names, according to the expected output, will be 1, 2, 3, ...

    int v_seq1[n_vert1], v_seq2[n_vert2];

    for (int h = 0; h < n_vert2; h++)
    {
        v_seq1[h] = h + 1;
        v_seq2[h] = h + 1;
    }

    int num_permutations = 1;
    for (int i = 1; i <= n_vert2; i++) // n_vert1 = n_vert2
    {
        num_permutations *= i;
        // We know that the number of permutations is given by n!, but we are proving that with this function
    }

    for (int x = 0; x < num_permutations; x++)
    {
        // After generating all possible permutations of the vertex sequence array, we are inputting the edge sequence
        // into the adjacency matrix accordingly

        // This is done in this order because writing code to generate all permutations of a 2D array is much harder,
        // and since we know that the matrix has to be symmetric, we can simply to the permuting in the 1D array that is
        // generating the adjacency matrix in the first place
        int temp_adj_mat[n_vert1][n_vert1];
        for (int r1 = 0; r1 < n_vert2; r1++)
        {
            for (int r2 = 0; r2 < n_vert1; r2++)
            {
                temp_adj_mat[r1][r2] = 0;
            }
        }
        for (int i = 0; i < n_edge2 * 2; i += 2)
        {
            if (edge_seq1[i] != 0)
            {
                temp_adj_mat[edge_seq2[i] - 1][edge_seq2[i + 1] - 1] = 1;
                temp_adj_mat[edge_seq2[i + 1] - 1][edge_seq2[i] - 1] = 1;
            }
        }
        int flag = 0;
        for (int p = 0; p < n_vert2; p++)
        {
            if (flag == 1)
            {
                break;
            }
            for (int q = 0; q < n_vert2; q++)
            {
                if (temp_adj_mat[p][q] != adj_mat_1[p][q])
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            printf("Isomorphic.\n");
            for (int i = 0; i < n_vert2; i++) // n_vert1 = n_vert2
            {
                printf("%d %d\n", v_seq1[i], v_seq2[i]);
            }
            return 0;
        }

        // we are iteratively checking for each permutation of the vertex and corresponding edge sequence
        // therefore, at each iteration, we are calling a new permutation of the n! possible ones for the array
        //  changes the vertex sequence and edge sequence for the next iteration
        temp_vertex_seq = permutation(v_seq2, n_vert1, x); // n_vert1 = n_vert2
        // change edge seq here
        for (int k = 0; k < n_edge1 * 2; k++)
        {
            int index;
            for (index = 0; index < n_vert2; index++)
            {
                if (v_seq2[index] == edge_seq2[k])
                {
                    break;
                }
            }
            edge_seq2[k] = temp_vertex_seq[index];
        }

        for (int i = 0; i < n_vert2; i++) // n_vert1 = n_vert2
        {
            v_seq2[i] = temp_vertex_seq[i];
        }
    }
    printf("Not Isomorphic, no bijection found.\n");
    return 0;
}