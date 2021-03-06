#! /usr/bin/python3

import urllib.request
import shutil
import zipfile
import dryscrape
import sys
import re
import os
import subprocess
from lxml import html

import shutil, errno

def copyAnything(src, dst):
    try:
        shutil.copytree(src, dst)
    except OSError as exc: # python >2.5
        if exc.errno == errno.ENOTDIR:
            shutil.copy(src, dst)
        else: raise

def getChallengeCategory(challengeName) :
	# Set up a web scraping session
	sess = dryscrape.Session(base_url = 'https://www.hackerrank.com')
	# We don't need images
	sess.set_attribute('auto_load_images', False)
	# Visit challenge page and extract information
	sess.visit('/challenges/' + challengeName)

	# Go through the links and find the one with the challenge's category
	p = re.compile('/domains/(.*/.*)')
	for link in sess.xpath('//a[@href]'):
		test = p.match(link['href'])
		if test:
			return test.group(1)

# url is the challenge's URL
def downloadFiles(url):

	p = re.compile('^https://www\.hackerrank\.com/challenges/(.+)$')
	# https://www.hackerrank.com/challenges/solve-me-first
	challengeName = p.search(url).group(1)
	print("Getting data for the", challengeName, "challenge")
	category = getChallengeCategory(challengeName)

	# URL to download the problem statement
	urlStatement = 'https://www.hackerrank.com/rest/contests/master/challenges/' + challengeName + '/download_pdf?language=English'
	# URL to download the test cases (input and output as zip file)
	urlTestCases = 'https://www.hackerrank.com/rest/contests/master/challenges/' + challengeName + '/download_testcases'

	# Create directory architecture
	path = category + "/" + challengeName + "/"
	os.makedirs(path, exist_ok=True)

	# Download the files
	print("Getting problem statement and saving it in '" + path + "'")
	with urllib.request.urlopen(urlStatement) as response, open(path + "problem.pdf", 'wb') as outFile:
		shutil.copyfileobj(response, outFile)
	print("Done!")

	print("Getting testCases and saving them in '" + path + "'")
	with urllib.request.urlopen(urlTestCases) as response, open(path + "test_cases.zip", 'wb') as outFile:
		shutil.copyfileobj(response, outFile)

	# Unzip the test cases
	with zipfile.ZipFile(path + "test_cases.zip","r") as sipRef:
			sipRef.extractall(path)
	print("Done!")

	os.remove(path + "test_cases.zip")
	# Create symlink to the test script
	os.symlink(os.getcwd() + "/test.sh", path + "/test.sh")
	copyAnything(os.getcwd() + "/template/main.cpp", path)

if __name__ == "__main__":
	nbArguments = 1

	if len(sys.argv) != nbArguments + 1:
		print("Invalid number of arguments,", nbArguments, "expected")
		print("Got:", sys.argv)
		sys.exit()

	downloadFiles(sys.argv[1])