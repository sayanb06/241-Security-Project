#!/bin/bash
ARRAY=( "bin" "etc" "lib" "lib64" )
cd newroot
for i in "${ARRAY[@]}"
do
    if [ -d "$i" -a -d "$i"_u -a -d "$i"_w ]; then
        printf "%s exists, no need to remake\n" $i
    else
        mkdir --mode=777 $i
        mkdir --mode=777 "$i"_w
        mkdir --mode=777 "$i"_u
        mount -t overlay -o lowerdir=/"$i",upperdir="$i"_u,workdir="$i"_w overlay $i
    fi
done
cd ../
