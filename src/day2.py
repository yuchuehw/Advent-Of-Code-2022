#!/usr/bin/env python3
import sys

with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    f = f.read()
    score=0
    for line in f.split("\n"):
        a,_,b=line
        a = ord(a)-ord("A")
        b = ord(b)-ord("X")
        score+=1+b
        if (a==0 and b==1) or (a==1 and b==2) or (a==2 and b==0):
            score+=6
        elif a==b:
            score+=3
    print(score)
    score = 0
    for line in f.split("\n"):
        a,_,b=line
        a = ord(a)-ord("A")
        score+=1
        if b == "X":
            score += (a+2)%3
        elif b == "Y":
            score += a
            score += 3
        elif b == "Z":
            score += (a+1)%3
            score += 6
        else:
            assert 0
    print(score)
