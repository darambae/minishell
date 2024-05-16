#!/bin/bash

make re

# Test command execution
echo "Testing basic command execution:"
./minishell < input_commands.txt > output_actual.txt
diff output_actual.txt expected_output.txt

# Test Valgrind
valgrind --leak-check=full --show-leak-kinds=all ./minishell
rm minishell

# Add more test cases as needed...