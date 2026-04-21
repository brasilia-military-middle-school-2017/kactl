teste() {
    for f in "$2"/*; do
        echo "=== $f"
        cat $f
        echo "=== Out"
        $1 < $f
    done
}
# teste ./b bf
stress() {
    for ((i=1; ; i++)) do
        echo "Test $i"
        echo $i | $1 > gen_in
        $2 < gen_in > main_out
        $3 < gen_in > brute_out
        if ! diff -w main_out brute_out > /dev/null; then
            return 1
        fi
    done
}
# stress "python3 gen.py" ./main ./brute
