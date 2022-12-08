from collections import defaultdict
import re

with open('input.txt') as file:
    lines = file.readlines()

sizes = defaultdict(int)
path = []
numbers = ("^\d+")

for line in lines:
    if line.startswith("$ cd"):
        d = line.split()[-1]
        if d == '..':
            path.pop()
            print("Moving up %s" % path)
        else:
            if d == "/":
                path.append("root")
            else:
                path.append(d)
                print("Moving down to %s" % path)
    elif line.startswith("$ ls"):
        print("Listing stuff - nothing to do here")
        continue
    elif line.startswith('dir'):
        print("Listing directory %s" % line)
        continue
    elif re.match(numbers, line):
        print("File: %s" % line)
        size, _ = line.split()
        if re.match(numbers, size): # I know it'S dumb 
            for i in range(len(path)):
                sizes["/".join(path[:i+1])] += int(size)

# Part 1

amount = 0

for key, value in sizes.items():
    if value < 10**5:
	    amount += value
	
print("PART1: %d" % amount)

# Part 2

total_disk_space = 7*10**7
desired_free_disk_space = 3*10**7

free_space = total_disk_space - sizes["root"]
needed_for_update = desired_free_disk_space - free_space

s = [s for s in sorted(sizes.values()) if s >= needed_for_update]	

print("The smallest directory that, if deleted, would free up enough space on the filesystem to run the update has the total size: %d" % int(s[0]))
