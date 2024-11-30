# Simple precedence parser

Shows how a (really) simple precedence parser works. Uses single-character tokens, so no distinction between characters and tokens is made.

## Usage

Compile:

    gcc parser.c -o parser

or with make:

    make

Integer literals consist of a single character. There are 4 operators:

    op  type     associativity precedence
    !   postfix  left          1
    #   prefix   right         2
    +   infix    left          3
    $   prefix   right         4

Parentheses are not supported.

Expressions to be parsed should be passed as a commandline argument, between single quotes. To show the tree structure, parentheses are inserted:

    >./parser '1!+$2+3'          ~/code/precedence_parser
    (1!) + ($(2 + 3))
