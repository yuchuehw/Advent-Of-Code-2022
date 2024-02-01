#!/usr/bin/env python3
import sys
with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
sum1=sum2=0
for line in f.read().split("\n"):
    a,b=line.split(",")
    a=[int(_) for _ in a.split("-")]
    
    b=[int(_) for _ in b.split("-")]
    a[1]+=1
    b[1]+=1
    ## part 1 ##
    if b[0]<=a[0]<=a[1]<=b[1]or a[0]<=b[0]<=b[1]<=a[1]:sum1+=1
    # or
    # if set(range(*a)).issubset(set(range(*b))) or set(range(*b)).issubset(set(range(*a))):sum1+=1
    ## part 2 ##
    
    if a[1]!=b[0] and a[0]!=b[1] and(a[0]<=b[0]<=a[1] or a[0]<=b[1]<=a[1] or b[0]<=a[0]<=b[1] or b[0]<=a[1]<=b[1]):sum2+=1
    # or
    # if set(range(*a)).intersection(set(range(*b))):sum2+=1
print(sum1) # 462
print(sum2) # 835
