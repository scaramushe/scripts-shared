import sys
import argparse

parser = argparse.ArgumentParser(description='Remove all excluded strings from the input file')
parser.add_argument('-i','--input', help='Input file name',required=True)
parser.add_argument('-o','--output', help='Output file name',required=True)
parser.add_argument('-e','--exclude', help='Exclude string file name',required=True)

args = parser.parse_args()
# print(args)

# get the strings to exclude
exc_f = open(args.exclude, 'r')
exc_string  = exc_f.read().splitlines()
print(exc_string)
exc_f.close()

f = open(args.input, 'r') 
out_f = open(args.output, 'w')
should_print = True
for line in f:
    should_print = True
    for string in exc_string:
        if string in line:
            should_print = False
            break
    if(should_print ):
        out_f.write(line)

f.close()
out_f.close()
