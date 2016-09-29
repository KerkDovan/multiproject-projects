import sys

sys.stdin = open("j.in")
sys.stdout = open("j.out", "w")

def main():
  digit_count = [0] * 10
  for test in range(int(input())):
    k, m, x = map(int, input().split())
    for i in range(10):
      digit_count[i] = 0
    t = x
    while t:
      t, rem = divmod(t, 10)
      digit_count[rem] += 1
    is_creeper = (#digit_count[8] == digit_count[9] == 0 and (
      digit_count[1] >= 1 and digit_count[2] >= 1 and digit_count[3] >= 2 and digit_count[4] >= 3 or #and
      #digit_count[5] == digit_count[6] == digit_count[7] == 0 or
      #digit_count[1] == digit_count[2] == digit_count[3] == digit_count[4] == 0 and
      digit_count[5] >= 2 and digit_count[6] >= 2 and digit_count[7] >= 4
    )
    if is_creeper:
      print(k, "C 1")
      continue

    used = { x }
    for index in range(2, m + 1):
      # Reverse.
      a = x
      b = 0
      while a:
        a, m = divmod(a, 10)
        b = b * 10 + m
      # Add.
      x += b

      # Then Sort.
      for i in range(10):
        digit_count[i] = 0
      while x:
        x, m = divmod(x, 10)
        digit_count[m] += 1

      for i in range(1, 10):
        for j in range(digit_count[i]):
          x = x * 10 + i

      is_creeper = (#digit_count[8] == digit_count[9] == 0 and (
        digit_count[1] >= 1 and digit_count[2] >= 1 and digit_count[3] >= 2 and digit_count[4] >= 3 or #and
        #digit_count[5] == digit_count[6] == digit_count[7] == 0 or
        #digit_count[1] == digit_count[2] == digit_count[3] == digit_count[4] == 0 and
        digit_count[5] >= 2 and digit_count[6] >= 2 and digit_count[7] >= 4
      )
      if is_creeper:
        print(k, 'C', index)
        break

      if x in used:
        print(k, 'R', index)
        break

      used.add(x)
    else:
      print(k, x)

if __name__ == "__main__":
  main()
