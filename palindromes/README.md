# Palindromes

This is an implementation of Manacher's algorithm, which finds all palindromes in a string in linear time. It is written in C and intended to be used on Linux.


## Usage

To build the 'palindromes' binary, clone the repository, navigate to it, and run 'make':

    git clone https://github.com/rubenvannieuwpoort/palindromes
    cd palindromes
    make

After building, you should be able to use the binary:

    $ ./palindromes
    Usage: ./palindromes <string> [--long] [--show] [--all]
    
    Display the length of all palindromes within the string. The string cannot use the characters @, $, and ., as these are used internally.
    
        --long       Report the center and length of the longest palindrome
        --show       Mark the palindrome and its center in the input
        --all        Show, for each letter, the length of the palindrome with the center at that letter
    
    $ ./palindromes 'One of the earliest palindromes was the Latin phrase "sator arepo tenet opera rotas"'
    "sator arepo tenet opera rotas"
    $ ./palindromes banana --long                                           ~/repos/palindromes
    Longest palindrome is 'anana', with center 6 and length 5.
    $ ./palindromes antananarivo --show                                     ~/repos/palindromes
    anana
    
                --------v--------                   
    a   n   t   a   n   a   n   a   r   i   v   o
    
    $ ./palindromes yabadabadoo --all                                       ~/repos/palindromes
    abadaba
    
    y   a   b   a   d   a   b   a   d   o   o   
    
      0   0   0   0   0   0   0   0   0   2   
    1   1   3   1   7   1   5   1   1   1   1  
