import copy

def count_visibles(input_matrix):
  col_len = len(input_matrix[0])
  row_len = len(input_matrix)
  # everything on the edge of the graphs is always visible
  visible_counts = (2*col_len) + (2*row_len) - 4

  # search space is limited to everything one row and col inside our outmost boundaries
  # build rows left to right larger than self
  rows_left_to_right_index = copy.deepcopy(input_matrix)
  for row in range (1, row_len - 1):
    for col in range (1, col_len - 1):
      if col == 1:
        rows_left_to_right_index[row][col] = rows_left_to_right_index[row][col-1]
        continue
      a = input_matrix[row][col-1]
      b = rows_left_to_right_index[row][col-1]
      rows_left_to_right_index[row][col] = max(a, b)

  # build rows right to left larger than self
  rows_right_to_left_index = copy.deepcopy(input_matrix)
  for row in range(row_len - 2, 0, -1):
    for col in range(col_len - 2, 0, -1):
      if col == row_len-2:
        rows_right_to_left_index[row][col] = rows_right_to_left_index[row][col+1]
        continue
      a = input_matrix[row][col+1]
      b = rows_right_to_left_index[row][col+1]
      rows_right_to_left_index[row][col] = max(a, b)

  # build cols up to down larger than self
  cols_up_to_down_index = copy.deepcopy(input_matrix)
  for row in range (1, row_len - 1):
    for col in range (1, col_len - 1):
      if row == 1:
        cols_up_to_down_index[row][col] = cols_up_to_down_index[row-1][col]
        continue
      a = input_matrix[row-1][col]
      b = cols_up_to_down_index[row-1][col]
      cols_up_to_down_index[row][col] = max(a, b)
  
  # build cols down to up larger than self
  cols_down_to_up_index = copy.deepcopy(input_matrix)
  for row in range(row_len - 2, 0, -1):
    for col in range(col_len - 2, 0, -1):
      if row == row_len-2:
        cols_down_to_up_index[row][col] = cols_down_to_up_index[row+1][col]
        continue
      a = input_matrix[row+1][col]
      b = cols_down_to_up_index[row+1][col]
      cols_down_to_up_index[row][col] = max(a, b)

  # iterate over graph and seach the indexes we built above
  for row in range (1, row_len-1):
    for col in range (1, col_len-1):
      candidate = input_matrix[row][col]
      if (
        rows_left_to_right_index[row][col] < candidate or 
        rows_right_to_left_index[row][col] < candidate or 
        cols_up_to_down_index[row][col] < candidate or
        cols_down_to_up_index[row][col] < candidate
      ):
        # print(row, col)
        visible_counts+=1

  # prettyprint(input_matrix)
  # print("###############")
  # print("l-r")
  # prettyprint(rows_left_to_right_index)
  # print("###############")
  # print("r-l")
  # prettyprint(rows_right_to_left_index)
  # print("###############")
  # print("u-d")
  # prettyprint(cols_up_to_down_index)
  # print("###############")
  # print("d-u")
  # prettyprint(cols_down_to_up_index)

  return visible_counts



def max_score_tree(input_matrix):
  col_len = len(input_matrix[0])
  row_len = len(input_matrix)
  max_score = -1
  for row in range (1, row_len-1):
    for col in range (1, col_len-1):
      # calc score for row col
      sc = get_score(input_matrix, row, col)
      max_score = max(max_score, sc)
  return max_score


def get_score(input_matrix, row, col):
  candidate = input_matrix[row][col]
  up_score = 1
  
  rowcp = row-1
  while rowcp > -1 and input_matrix[rowcp][col] < candidate:
    up_score+=1
    rowcp-=1

  down_score = 1
  rowcp = row+1
  while rowcp < len(input_matrix) and input_matrix[rowcp][col] < candidate:
    down_score+=1
    rowcp+=1

  left_score = 1
  colcp = col-1
  while colcp > -1 and input_matrix[row][colcp] < candidate:
    left_score+=1
    colcp-=1

  right_score = 1
  colcp = col+1
  while colcp < len(input_matrix[0]) and input_matrix[row][colcp] < candidate:
    right_score+=1
    colcp+=1

  return left_score*right_score*up_score*down_score


def prettyprint(mat):
  for i in mat:
    print(i)

def main():
  with open('input.txt') as file:
    lines = file.readlines()

  input_matrix = [[int(k) for k in list(l.strip("\n"))] for l in lines]

  part1 = count_visibles(input_matrix)
  part2 = max_score_tree(input_matrix)

  print("p1 ", part1)

  print("p2 ", part2)

main()
