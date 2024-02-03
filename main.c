#include <stdio.h>
#include <stdlib.h>

float **sub_matrix(float **mat, size_t n, int row, int col) {
	float **new_mat = (float **)malloc((n - 1) * sizeof(float *));

	for (size_t i = 0, k = 0; i < n; i++) {
		if (i == row) continue;

		new_mat[k] = (float *)malloc((n - 1) * sizeof(float));

		for (size_t j = 0, l = 0; j < n; j++) {
			if (j == col) continue;

			new_mat[k][l] = mat[i][j];
			l++;
		}

		k++;
	}

	return new_mat;
}

float det(float **mat, size_t n) {
	if (n == 1) return mat[0][0];

	float res = 0.f;
	for (size_t i = 0; i < n; i++) {
		float **sub = sub_matrix(mat, n, 0, i);
		float sign = (i % 2) ? -1.f : 1.f;
		res += sign * mat[0][i] * det(sub, n - 1);
	}

	for (size_t i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);

	return res;
}

float **read_matrix(const char *filename, size_t *n) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	if (fscanf(file, "%zu", n) != 1) {
		fprintf(stderr, "Error reading matrix size\n");
		exit(EXIT_FAILURE);
	}

	float **matrix = (float **)malloc(*n * sizeof(float *));
	for (size_t i = 0; i < *n; i++) {
		matrix[i] = (float *)malloc(*n * sizeof(float));
		for (size_t j = 0; j < *n; j++) {
			if (fscanf(file, "%f", &matrix[i][j]) != 1) {
				fprintf(stderr,
					"Error reading matrix element at (%zu, "
					"%zu)\n",
					i, j);
				exit(EXIT_FAILURE);
			}
		}
	}

	fclose(file);
	return matrix;
}

void print_matrix(float **mat, size_t n) {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			printf("%f", mat[i][j]);
			if (j != n - 1) {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(int argc, char **args) {
	size_t n;
	float **mat = read_matrix("input.txt", &n);

	printf("Finding determinant for %zux%zu matrix:\n", n, n);
	print_matrix(mat, n);

	float res = det(mat, n);

	printf("Determinant: %f\n", res);

	return EXIT_SUCCESS;
}
