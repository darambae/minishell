#!/bin/bash

# Test basic command execution
echo "Testing basic command execution:"
./minishell < input_commands.txt > output_actual.txt
diff output_actual.txt expected_output.txt

# Test command with arguments
echo "Testing command with arguments:"
./minishell < input_arguments.txt > output_actual.txt
diff output_actual.txt expected_output.txt

# Add more test cases as needed...
