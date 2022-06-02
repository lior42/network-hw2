#!/bin/bash

# setting up our programs as variables
# can later be executed with "eval $something"
p_client="client"
p_server="server"
p_proxy="proxy"

c_current_dir=$(ls | wc -l)
c_current_dir="${c_current_dir//[$'\t\r\n ']/}"

# if we're in local machine
if [ "$c_current_dir" -ne 4 ]; then
    make &>/dev/null
    p_client="build/$p_client"
    p_server="build/$p_server"
    p_proxy="build/$p_proxy"
fi

p_client="./$p_client"
p_server="./$p_server"
p_proxy="./$p_proxy"

# Create a temporary file and fill it with sentences
# later will be redirected to client as input
client_input=$(mktemp)
trap "rm -f $client_input" 0 2 3 15

client_inp_list=("hello" "this is a full sentence" "and this is another one" "oh" "i" "see")
for t in "${client_inp_list[@]}"; do
    echo "$t" >>$client_input
done
