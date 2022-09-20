import sys
import argparse


parser = argparse.ArgumentParser(description='Filter file - Output only strings in the filter file from the input. Optimized to work with large files')
parser.add_argument('-i','--input', help='Input file name',required=True)
parser.add_argument('-o','--output', help='Output file name',required=True)
parser.add_argument('-f','--filter', help='Filter strings file name',required=True)

args = parser.parse_args()
# print(args)

# get the strings to filter
filter_f = open(args.filter, 'r')
filter_strings  = filter_f.read().splitlines()
print("Strings to filter are:")
print(filter_strings)
filter_f.close()

f = open(args.input, 'r') 
out_f = open(args.output, 'a')
for line in f:
    for string in filter_strings:
        if string in line:
            out_f.write(line)
            # print(line)

f.close()
out_f.close()