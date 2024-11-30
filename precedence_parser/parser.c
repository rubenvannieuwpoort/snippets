#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// data type for the parse tree
typedef struct node* node;
struct node {
	char value;
	node left, right;
};

node new_node(char op, node left, node right) {
	node n = malloc(sizeof(struct node));
	n->value = op;
	n->left = left;
	n->right = right;
	return n;
}

// ptr points somewhere in the stream, token will contain next token
char *ptr, token;

// set token to the next one in the stream
void next(void) {
	ptr++;
	while (*ptr == ' ') {
		ptr++;
	}
	token = *ptr;
}

// returns the current token
char pop_token(void) {
	char result = token;
	next();
	return result;
}

bool is_postfix(char op) {
	return op == '!';
}

bool is_prefix(char op) {
	return op == '$' || op == '#';
}

int precedence(char op) {
	if (op == '!') return 1;
	if (op == '#') return 2;
	if (op == '+') return 3;
	if (op == '$') return 4;
	assert(false);
}

bool is_left_assoc(char op) {
	if (op == '+' || op == '!') return true;
	if (op == '$' || op == '#') return false;
	assert(false);
}

bool is_right_assoc(char op) {
	if (op == '+' || op == '!') return false;
	if (op == '$' || op == '#') return true;
	assert(false);
}

// parse an atom (in this case, a single-digit literal)
node parse_atom(void) {
	assert('0' <= token && token <= '9');
	return new_node(pop_token(), 0, 0);
}

// print the parsed tree using parentheses
void print_tree(node root, bool firstlevel) {
	if (!root->left && !root->right) {
		printf("%c", root->value);
		return;
	}
	if (!firstlevel) printf("(");
	if (root->left) print_tree(root->left, false);
	if (root->left && root->right) printf(" ");
	printf("%c", root->value);
	if (root->left && root->right) printf(" ");
	if (root->right) print_tree(root->right, false);
	if (!firstlevel) printf(")");
}

// p is the precedence. Lower precedences bind tighter!
node prec_parse(int p) {
	node left = 0;
		
	// parse prefix token
	if (token && is_prefix(token)) {
		char op = pop_token();
		left = new_node(op, 0, prec_parse(precedence(op)));
	}
	else {
		left = parse_atom();
	}
	
	while (token && precedence(token) <= p) {
		char op = pop_token();
		node right = 0;
		if (!is_postfix(op)) {
			if (is_left_assoc(op)) right = prec_parse(precedence(op) - 1);
			else if (is_right_assoc(op)) right = prec_parse(precedence(op));
		}
		
		left = new_node(op, left, right);
	}
	return left;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Please enter the expression to be parsed as an argument:\n\t%s <expression>\n", argv[0]);
		printf("It is recommended to use single quotes.\n");
		exit(1);
	}
	
	ptr = argv[1];
	token = *ptr;
	
	print_tree(prec_parse(4), true);
	printf("\n");
	return 0;
}
