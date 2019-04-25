folders = (bin etc lib lib64)
for i in "{folders[@]}"
do
    if [ -d "$i" -a -d "$i"_u -a "$i"_w ]; then
        printf "%s exists, no need to remake" $i
    else
        mkdir --mode=777 $i
        mkdir --mode=777 "$i"_w
        mkdir --mode=777 "$i"_u
        mount -t overlay -o lowerdir=/"$i",upperdir="$i"_u,workdir="$i"_w overlay $i
    fi
done
