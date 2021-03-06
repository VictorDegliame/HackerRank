#! /bin/bash

INPUT_FILES=input/*
OUTPUT_FILES=output
MY_OUTPUT_FILE="tmpOutput.txt"

bold=$(tput bold)
normal=$(tput sgr0)
red=$(tput setaf 1)
green=$(tput setaf 2)

# This is the valid/tick character, in green
tick="✓"
cross="❌"

regex="input([0-9])+\.txt"

# Compile c++ code in main.cpp by default
g++ main.cpp -o prog -std=c++11 -g -Wall -Wpedantic

for f in $INPUT_FILES
do
  echo -e "Processing $f file..."
  num=`echo $f | sed -r 's/.+input([0-9]+)\.txt/\1/g'`
  cat $f | ./prog > $MY_OUTPUT_FILE
  # Do a diff but ignore trailing new lines
  result=`diff -wB ${MY_OUTPUT_FILE} "$OUTPUT_FILES/output$num.txt"`
  if [ "$?" -eq 0 ]
  	then
  	echo -e "${bold}${green}${tick}${normal}"
  else
  	echo -e "${bold}${red}${cross}${normal}"
    echo -e "Expected results"
    cat "$OUTPUT_FILES/output$num.txt"
    echo -e "\nYour results:"
    cat "${MY_OUTPUT_FILE}"
    echo -e "\n"
  fi
done
