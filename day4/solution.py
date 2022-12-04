def contain_range(e1_range, e2_range):
  e1_contains_e2 = int(e2_range[0]) >= int(e1_range[0]) and int(e2_range[1]) <= int(e1_range[1])
  e2_contains_e1 = int(e1_range[0]) >= int(e2_range[0]) and int(e1_range[1]) <= int(e2_range[1])
  contains = e1_contains_e2 or e2_contains_e1
  return contains

def overlap(e1_range, e2_range):
  e1_before_e2 = int(e1_range[1]) < int(e2_range[0])
  e2_before_e1 = int(e2_range[1]) < int(e1_range[0])
  return not (e1_before_e2 or e2_before_e1)

def prob(container):
  res = 0
  file1 = open('./input.txt', 'r')
  lines = file1.readlines()
  for line in lines:
    line = line.rstrip()
    ps = line.split(",")
    e1 = ps[0]
    e2 = ps[1]
    if container(e1.split("-"), e2.split("-")):
      res+=1
  file1.close()
  return res

def main():
  res1 = prob(contain_range)
  res2 = prob(overlap)
  print("PART 1: ", res1)
  print("PART 2: ", res2)

main()
