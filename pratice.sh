#!/bin/bash

# 1. Even or Odd
check_even_odd() {
    if (( $1 % 2 == 0 )); then
        echo "$1 is Even"
    else
        echo "$1 is Odd"
    fi
}

# 2. Leap Year
check_leap_year() {
    local year=$1
    if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
        echo "$year is a Leap Year"
    else
        echo "$year is NOT a Leap Year"
    fi
}

# 3. Palindrome (Strings or Numbers)
check_palindrome() {
    local input=$1
    local reverse=$(echo "$input" | rev)
    
    if [[ "$input" == "$reverse" ]]; then
        echo "$input is a Palindrome"
    else
        echo "$input is NOT a Palindrome"
    fi
}

# 4. Fibonacci Series (Prints up to N terms)
print_fibonacci() {
    local n=$1
    local a=0
    local b=1
    echo "Fibonacci series up to $n terms:"
    for (( i=0; i<n; i++ ))
    do
        echo -n "$a "
        local fn=$((a + b))
        a=$b
        b=$fn
    done
    echo "" # New line
}

# --- Testing the Functions ---
read -p "Enter a number to check Even/Odd & Leap Year: " num
check_even_odd $num
check_leap_year $num

read -p "Enter a string to check Palindrome: " str
check_palindrome "$str"

read -p "How many Fibonacci terms to print? " terms
print_fibonacci $terms
