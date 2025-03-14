setup() {
    ./dsh -s &
    dsh_pid=$!
    sleep 1
}

teardown() {
    kill "$dsh_pid"
}

@test "Remote Shell - Test Should fail but showcase working ls" {
    run ./dsh -c <<EOF
ls
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Get the list of files in the current directory
    files=$(ls | tr -d '\n')  # Remove newlines for comparison

    # Construct the expected output
    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>SuccessfulExecution${files}dsh4>InputError-Exitingcmdloopretur rned0"

    echo "Stripped Output: $stripped_output"
    echo "Expected Output: $expected_output"
    [ "$stripped_output" = "$expected_output" ]
}

@test "Remote Shell - Test Should fail but showcase working echo hey | grep h" {
    run ./dsh -c <<EOF
echo "hey" | grep h
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Get the list of files in the current directory
    files=$(ls | tr -d '\n')  # Remove newlines for comparison

    # Construct the expected output
    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>SuccessfulExecution${files}dsh4>InputError-Exitingcmdloopretur rned0"

    echo "Stripped Output: $stripped_output"
    echo "Expected Output: $expected_output"
    [ "$stripped_output" = "$expected_output" ]
}

@test "Remote Shell - Test Should fail but showcase working cd .. then after running ls {
    run ./dsh -c <<EOF
cd ..
ls
EOF

    stripped_output=$(echo "$output" | tr -d '[:space:]')

    # Get the list of files in the current directory
    files=$(ls | tr -d '\n')  # Remove newlines for comparison

    # Construct the expected output
    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>SuccessfulExecution${files}dsh4>InputError-Exitingcmdloopretur rned0"

    echo "Stripped Output: $stripped_output"
    echo "Expected Output: $expected_output"
    [ "$stripped_output" = "$expected_output" ]
}