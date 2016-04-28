#! /usr/bin/python3

import urllib.request
import shutil
import zipfile
import sys
import re
from lxml import html



nbArguments = 1

if len(sys.argv) != nbArguments + 1:
	print("Invalid number of arguments,", nbArguments, "expected")
	print("Got:", sys.argv)
	sys.exit()

url = sys.argv[1]

with urllib.request.urlopen(url) as response:
	page = html.fromstring(response.read())
	for link in page.xpath("//a"):
		print("Name", link.text, "URL", link.get("href"))

p = re.compile('^https://www\.hackerrank\.com/challenges/(.+)$')
# https://www.hackerrank.com/challenges/solve-me-first
challengeName = p.search(url).group(1)
print("Getting data for the", challengeName, "challenge")

urlStatement = 'https://www.hackerrank.com/rest/contests/master/challenges/' + challengeName + '/download_pdf?language=English'
urlTestCases = 'https://www.hackerrank.com/rest/contests/master/challenges/' + challengeName + '/download_testcases'

# Download the file from `url` and save it locally under `file_name`:
print("Getting problem statement")
with urllib.request.urlopen(urlStatement) as response, open(challengeName + "problem.pdf", 'wb') as outFile:
	shutil.copyfileobj(response, outFile)
print("Done!")

print("Getting testCases and saving them in '" + challengeName + "'")
with urllib.request.urlopen(urlTestCases) as response, open(challengeName + "test_cases.zip", 'wb') as outFile:
	shutil.copyfileobj(response, outFile)

with zipfile.ZipFile(challengeName + "test_cases.zip","r") as sipRef:
		sipRef.extractall(challengeName)
print("Done!")