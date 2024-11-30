#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int *palindromes(char *s);
int max(int a, int b) { return a > b ? a : b; }

bool _long = false, all = false, show = false;
char *input = 0;

int handle_cmd_args(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <string> [--long] [--show] [--all]\n\nDisplay the length of all palindromes within the string. The string cannot use the characters @, $, and ., as these are used internally.\n\n    --long       Report the center and length of the longest palindrome\n    --show       Mark the palindrome and its center in the input\n    --all        Show, for each letter, the length of the palindrome with the center at that letter\n\n", argv[0]);
		return 1;
	}
	
	for (int i = 1; i < argc; i++) {
		if (strlen(argv[i]) == 0 || argv[i][0] != '-') input = argv[i];
		else if (!strcmp(argv[i], "--show")) show = true;
		else if (!strcmp(argv[i], "--all")) all = true;
		else if (!strcmp(argv[i], "--long")) _long = true;
		else {
			printf("Unknown commandline option '%s'.\n", argv[i]);
			return 1;
		}
	}
	
	if (input == 0) {
		printf("No input found. Aborting.\n");
		return 1;
	}
	
	return 0;
}

int main(int argc, char *argv[]) {
	int retcode = handle_cmd_args(argc, argv);
	if (retcode) return retcode;
	
	int n = strlen(input);
	int *palindrome_length = palindromes(input);
	
	int longest_palindrome = 0, index_of_longest_pal = 0;
	for (int i = 0; i < 2 * n - 1; i++)
		if (palindrome_length[i] > longest_palindrome) {
			longest_palindrome = palindrome_length[i];
			index_of_longest_pal = i;
		}
	
	int start = (index_of_longest_pal + 1) / 2 - longest_palindrome / 2;
	char temp = input[start + longest_palindrome];
	
	input[start + longest_palindrome] = '\0';
	if (_long) {
		printf("Longest palindrome is '%s', with center %i and length %i.\n", &(input[start]), index_of_longest_pal, longest_palindrome);
	}
	else printf("%s\n", &(input[start]));
	input[start + longest_palindrome] = temp;
	
	if (show || all) printf("\n");
	
	// Print a line marking the palindrome
	if (show) {
		for (int i = 0; i < 4 * n; i++) {
			if (i == index_of_longest_pal * 2) printf("v");
			else if (i >= start * 4 && i < (start + longest_palindrome) * 4 - 3) printf("-");
			else printf(" ");
		}
		printf("\n");
	}
	
	// Show the letters of the input with some space between them
	if (all || show) {
		for (int i = 0; i < n; i++)
			printf("%c   ", input[i]);
		printf("\n");
	}
	
	// For each position, output the length of the palindrome with the center here
	if (all) {
		printf("\n  ");
		for (int i = 1; i < 2 * n - 1; i += 2)
			printf("%-4d", palindrome_length[i]);
		printf("\n");
		for (int i = 0; i < 2 * n - 1; i += 2)
			printf("%-4d", palindrome_length[i]);
		printf("\n");
	}
	
	if (all || show) printf("\n");
}

int *palindromes(char *input) {
	int len = strlen(input), n = 2 * len + 3;
	int *p = calloc(sizeof(int), n);
	char *s = malloc(n);
	
	// Copy the word with delimiters and intersperse with '.'. Example:
	// "hello" becomes "@.h.e.l.l.o.$". This uses extra space, but avoids
	// tedious checks and special cases.
	s[0] = '@';
	for (int k = 0; k < len; k++) s[(k + 1) * 2] = input[k];
	for (int k = 1; k < n; k += 2) s[k] = '.';
	s[n - 1] = '$';
	
	// Start at the center 2 (i is set so the test is true at the start)
	for (int c = 2, i = c, j; i < n - 2; ) {
		
		// Expand the palindrome around center c.
		while (s[c - p[c] - 1] == s[c + p[c] + 1]) p[c]++;
		
		// Copy palindrome lengths until we find a palindrome that is
		// not properly contained in the palindrome around center c.
		for (i = c + 1, j = c - 1; c - p[c] < j - p[j] && j + p[j] < c + p[j]; i++, j--)
			p[i] = p[j];
		
		p[i] = max(c + p[c] - i, 0);
		c = i;
	}
	return &(p[2]);
}
