#!/bin/sh

function sort_by_time()
{
    usleep "$1"
    # sleep "$1"    
    echo "$1"
}

while [ -n  "$1" ]
do

    sort_by_time "$1" & shift
done

wait
