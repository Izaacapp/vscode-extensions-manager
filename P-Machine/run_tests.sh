#!/bin/bash

# Compile the C program
gcc -o vm vm.c

# Function to test a specific case
test_case() {
  input_file=$1
  expected_output_file=$2
  actual_output_file="actual_${expected_output_file}"

  # Run the C program with the input file and redirect output to a temporary file
  ./vm "$input_file" > "$actual_output_file"

  # Compare the actual output with the expected output
  diff -w "$actual_output_file" "$expected_output_file" > diff_output.txt

  if [ $? -eq 0 ]; then
    echo "Test case with $input_file passed."
  else
    echo "Test case with $input_file failed. See diff_output.txt for details."
  fi

  # Clean up
  rm "$actual_output_file"
}

# Test cases
test_case "extra_input.txt" "extra_output.txt"
test_case "factorial_input.txt" "factorial_output.txt"
test_case "modified_input.txt" "modified_output.txt"
