class CrateStacks():
  def __init__(self, num_cols):
    self._stacks = [[] for _ in range(num_cols)]

  def add_init_stack(self, item, col):
    self._stacks[col] = [item, *self._stacks[col]]

  def move_times(self, times, from_col, to_col):
    for _ in range(times):
      self._move(from_col, to_col)

  def move_multiple_at_atimes(self, times, from_col, to_col):
    rev = []
    for _ in range(times):
      rev = [self._remove_stack(from_col), *rev]
    for item in rev:
      self._add_stack(item, to_col)

  def print_stack(self):
    for idx, stack in enumerate(self._stacks):
      print(f"{idx}: {stack}")

  def get_top_str(self):
    res = ""
    for s in self._stacks:
      res+=s[-1]
    return res

  def _move(self, from_col, to_col):
    self._add_stack(self._remove_stack(from_col), to_col)
  
  def _add_stack(self, item, col):
    self._stacks[col].append(item)

  def _remove_stack(self, col):
    return self._stacks[col].pop(-1)

def parse_move_instruction(line):
  # return times, from, to
  split_lines = line.split(" ")
  return [int(split_lines[1]), int(split_lines[3])-1, int(split_lines[5])-1]
  
def rearrange(file_lines):
  init_state = [
    ['J', '_', '_', '_','F','M','_','_','_'],
    ['Z', 'F', '_', 'G','Q','F','_','_','_'],
    ['G', 'P', '_', 'H','Z','S','Q','_','_'],
    ['V', 'W', 'Z', 'P','D','G','P','_','_'],
    ['T', 'D', 'S', 'Z','N','W','B','N','_'],
    ['D', 'M', 'R', 'J','J','P','V','P','J'],
    ['B', 'R', 'C', 'T','C','V','C','B','P'],
    ['N', 'S', 'V', 'R','T','N','G','Z','W']
  ]
  crate_stack = CrateStacks(9)
  for stack in init_state:
    for col, item in enumerate(stack):
      if item == '_':
        continue
      crate_stack.add_init_stack(item, col)
  
  crate_stack.print_stack()

  print("#########")

  for line in file_lines[10:]:
    # parse line into move from and move to
    instruction = parse_move_instruction(line)
    # PART1 : 
    # crate_stack.move_times(instruction[0], instruction[1], instruction[2])
    
    # PART 2 :
    crate_stack.move_multiple_at_atimes(instruction[0], instruction[1], instruction[2])

  crate_stack.print_stack()

  print("#########")

  print(crate_stack.get_top_str())

def get_file_lines():
  file1 = open('./input.txt', 'r')
  lines = file1.readlines()
  file1.close()
  return lines

def main():
  lines = get_file_lines()
  # part 1
  rearrange(lines)

main()
