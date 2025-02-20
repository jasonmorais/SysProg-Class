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

@test "Change directory" {
    run "./dsh" <<EOF
cd ..
ls
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="fork-exec-1.pngfork-exec-2.pngquestions.mdreadme.mdstarterdsh2>dsh2>dsh2>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Change directory - no args" {
    run "./dsh" <<EOF
cd
ls
EOF
    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="batsdragon.cdshdsh_cli.cdshlib.cdshlib.hmakefileshell_roadmap.mdtestfile.txtdsh2>dsh2>dsh2>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Exit command" {
    run "./dsh" <<EOF
exit
EOF

    # Check if the shell exits (you may expect an empty output)
    [ "$status" -eq 0 ]
}

@test "Grep finds sentence in test file" {
    run "./dsh" <<EOF
grep stuff testfile.txt
EOF
    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="istherestuffwithinthisfile?whoknowsdsh2>dsh2>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}

@test "Empty Command gives no commands message" {
    run "./dsh" <<EOF

EOF
    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Expected output with all whitespace removed for easier matching
    expected_output="dsh2>warning:nocommandsprovideddsh2>cmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"
    # Assertions
    [ "$stripped_output" = "$expected_output" ]
}






