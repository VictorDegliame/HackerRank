#! /bin/bash

for i in `seq -f "%03g" 1 138` ; do mkdir -p $i/tests ; done
for i in `seq -f "%03g" 1 138` ; do curl -L "https://www.hackerrank.com/rest/contests/projecteuler/challenges/euler$i/download_testcases" > $i/tests ; done
for i in `seq -f "%03g" 1 138` ; do curl -L "https://www.hackerrank.com/rest/contests/projecteuler/challenges/euler$i/download_pdf?language=English" > $i/hr_euler_$i.pdf ; done