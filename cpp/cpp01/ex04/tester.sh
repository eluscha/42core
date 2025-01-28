#!/bin/bash

# Function to run a single test case
run_test() {
    local test_name="$1"
    local input_file="$2"
    local search_string="$3"
    local replace_string="$4"
    
    sed "s/$search_string/$replace_string/g" $input_file > expected_output_file

    echo "Running test: $test_name"
    
    # Copy input file to avoid modifying the original
    cp "$input_file" test_input.txt

    # Run the program
    ./mysed test_input.txt "$search_string" "$replace_string"

    # Check if output file exists
    if [[ ! -f "test_input.txt.replace" ]]; then
        echo "❌ Test failed: Output file not created"
        return 1
    fi

    # Compare the actual output with the expected output
    if diff -q "test_input.txt.replace" "expected_output_file" > /dev/null; then
        echo "✅ Test passed"
    else
        echo "❌ Test failed: Output does not match expected result"
        echo Expected:
        cat expected_output_file
        echo Got:
        cat test_input.txt.replace
    fi

    # Clean up
    rm -f test_input.txt test_input.txt.replace expected_output_file
}

# Test cases
mkdir -p test_cases
echo "Hello World!" > test_cases/input1.txt

echo "A lazy cat meets a lazy dog.
It jumps a bit.
Nah.. Too lazy to run." > test_cases/input2.txt

echo "abcd efgh ijkl abcd efgh
ab cd
abcdabcdabcd
bcd
a   bcd    abcd" > test_cases/input3.txt

echo "In the end
there is no 
newline char" > test_cases/input4.txt 
truncate -s -1 test_cases/input4.txt 

# Run the tests
run_test "Test 1: Basic substitution" "test_cases/input1.txt" "World" "Universe" 
run_test "Test 2: Replace word in a multiline file" "test_cases/input2.txt" "lazy" "cute"
run_test "Test 3: Replace repeated word in a multiline file" "test_cases/input3.txt" "abcd" "xyz"
run_test "Test 4: An input file without newline char in the end" "test_cases/input4.txt" "no" "really no"

#run_test "Test 5: Replace a str with nl" "test_cases/input2.txt" "a bit.
#" "but "    

# Cleanup test cases directory
# rm -rf test_cases
