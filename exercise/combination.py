numbers=[1,2,3,4]
used = [0,0,0,0]
solution=[]

def printSolution():
  for num in solution:
    print(num, end=' ')
  print()

def permutation(index):
  if index==4:
    printSolution()
    return
  for num in numbers:
    if used[num-1]==1:
      continue
    else:
      used[num-1]=1
      solution.append(num)
      permutation(index+1)
      solution.pop()
      used[num-1]=0

print("start")
permutation(0)