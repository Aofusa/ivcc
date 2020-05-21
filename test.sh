#! /bin/bash

assert() {
    expected="$1"
    input="$2"

    ./ivcc "${input}" > tmp.s
    cc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "${actual}" = "${expected}" ]; then
        echo "${input} => ${actual}"
    else
        echo "${input} => ${expected} expected, but got ${actual}"
        exit 1
    fi
}

assert 0 "0;"
assert 42 "42;"

assert 21 "5+20-4;"
assert 41 "12 + 34 - 5;"

assert 47 "5+6*7;"
assert 15 "5*(9-6);"
assert 4 "(3+5)/2;"

assert 1 "+1;"
assert 10 "-10+20;"
assert 50 "-1*100+150;"
assert 5 "10+(-4-1);"
assert 5 "10/(-2)*-1;"

assert 1 "1 == 1;"
assert 0 "1 == 2;"
assert 0 "1 != 1;"
assert 1 "1 != 2;"
assert 0 "1 > 2;"
assert 0 "1 > 1;"
assert 1 "2 > 1;"
assert 0 "1 >= 2;"
assert 1 "1 >= 1;"
assert 1 "2 >= 1;"
assert 1 "1 < 2;"
assert 0 "1 < 1;"
assert 0 "2 < 1;"
assert 1 "1 <= 2;"
assert 1 "1 <= 1;"
assert 0 "2 <= 1;"
assert 1 "10 + ( -4 - 1 ) == 10 / ( - 2 ) * -1;"

assert 10 "a=10;"
assert 0 "b=10; b-(-1+11);"
assert 2 "c=10; c = c-(1+11); -c;"
assert 2 "a=1; b=2; a*b;"

echo OK

