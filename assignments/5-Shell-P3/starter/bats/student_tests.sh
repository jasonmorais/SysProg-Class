#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}
#!/usr/bin/env bats

# File: student_tests.sh
# Create your unit tests suit in this file

@test "Muliple pipes put together pt1" {
    run "./dsh" <<EOF
ls | grep .c | wc -l
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="3dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Cat non existent file" {
    run "./dsh" <<EOF
cat non_existent_file | grep anything
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="cat:non_existent_file:Nosuchfileordirectorydsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Multiple pipes put together pt2" {
    run "./dsh" <<EOF
echo hello | grep hello | wc -w
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="1dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Tail command functions with ls" {
    run "./dsh" <<EOF
ls | tail -n 1
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="testfile.txtdsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Grep non existent file" {
    run "./dsh" <<EOF
ls | grep non_existent_file
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Pipe with empty input" {
    run "./dsh" <<EOF
echo | grep hello
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Pipe with no output" {
    run "./dsh" <<EOF
echo "hello" | grep non_existent_word
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="dsh3>dsh3>cmdloopreturned0"

    # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Echo and awk together in pipe" {
    run "./dsh" <<EOF
echo John 30 Developer | awk {print$1}
EOF
     # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output should be 'banana' as it's the second word
    expected_output="John30Developerdsh3>dsh3>cmdloopreturned0"

   # These echo commands will help with debugging and will only print
    # if the test fails
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    # Assertions
    [ "$status" -eq 0 ]
}


#Previous Tests
@test "Previous Tests - Change directory" {
    run "./dsh" <<EOF
cd ..
ls
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="questions.mdreadme.mdstarterdsh3>dsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Previous Tests - Change directory - no args" {
    run "./dsh" <<EOF
cd
ls
EOF
    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="batsdragon.cdshdsh_cli.cdshlib.cdshlib.hmakefiletestfile.txtdsh3>dsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Previous Tests - Exit command" {
    run "./dsh" <<EOF
exit
EOF

    # Check if the shell exits (you may expect an empty output)
    [ "$status" -eq 0 ]
}

@test "Previous Tests - Grep finds sentence in test file" {
    run "./dsh" <<EOF
grep stuff testfile.txt
EOF
    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="istherestuffwithinthisfile?whoknowsdsh3>dsh3>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Previous Tests - Empty Command gives no commands message" {
    run "./dsh" <<EOF

EOF
    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="dsh3>warning:nocommandsprovideddsh3>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Invalid command with special characters" {
    run "./dsh" <<EOF
ls @#$%^&*()
EOF
    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="ls:cannotaccess'@#$%^&*()':Nosuchfileordirectorydsh3>dsh3>cmdloopreturned0"
     echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Pipe to invalid command" {
    run "./dsh" <<EOF
echo hello | invalid_command
EOF
    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="execvp:Nosuchfileordirectorydsh3>dsh3>dsh3>cmdloopreturned0"
     echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    [ "$stripped_output" = "$expected_output" ]
}

@test "Pipe with empty string input" {
    run "./dsh" <<EOF
echo "" | grep hello
EOF
    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="dsh3>dsh3>cmdloopreturned0"
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    [ "$stripped_output" = "$expected_output" ]
}

@test "Command with multiple arguments (proper space handling)" {
    run "./dsh" <<EOF
echo hello world
EOF
    stripped_output=$(echo "$output" | tr -d '[:space:]')
    expected_output="helloworlddsh3>dsh3>cmdloopreturned0"
    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    [ "$stripped_output" = "$expected_output" ]
}

@test "Cant go past 8 commands in a pipeline" {
    run "./dsh" <<EOF
echo command1 | echo command2 | echo command3 | echo command4 | echo command5 | echo command6 | echo command7 | echo command8 | echo command9
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output indicating too many commands (you can customize this message)
    expected_output="dsh3>error:pipinglimitedto8commandsdsh3>cmdloopreturned0"

    # Assertions
     echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    [ "$stripped_output" = "$expected_output" ]
}







