#!/bin/bash

# ##################################################
# Stage 1 - making variables ready to use
# p_client - the client software, ready to execute
# p_server - server software.
# client_input - temporary file, contains input
# ready to be sent to the client as stdin.

# setting up our programs as variables
# can later be executed with "eval $something"
p_client="client"
p_server="server"

c_current_dir=$(ls | wc -l)
c_current_dir="${c_current_dir//[$'\t\r\n ']/}"

# if we're in local machine
if [ "$c_current_dir" -ne 4 ]; then
    make &>/dev/null
    p_client="build/$p_client"
    p_server="build/$p_server"
fi

p_client="./$p_client"
p_server="./$p_server"

# Create a temporary file and fill it with sentences
# later will be redirected to client as input
client_input=$(mktemp)
trap "rm -f $client_input" 0 2 3 15

client_inp_list=("hello" "this is a full sentence" "and this is another one" "oh" "i" "see")
for t in "${client_inp_list[@]}"; do
    echo "$t" >>$client_input
done

unset client_inp_list
unset c_current_dir

# ##################################################
# Stage 2 - run tests
eval "$p_server"
