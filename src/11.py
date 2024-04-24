from copy import deepcopy
from collections import namedtuple

Monkey = namedtuple("Monkey","id items op test success fail")

# question example
# monkeys = [
#     Monkey(0,[79,98],lambda x:x*19,lambda x:x%23==0,2,3),
#     Monkey(1,[56,65,75,74],lambda x:x+6,lambda x:x%19==0,2,0),
#     Monkey(2,[79, 60, 97],lambda x:x*x,lambda x:x%13==0,1,3),
#     Monkey(3,[74],lambda x:x+3,lambda x:x%17==0,0,1)
# ]


def question_input():
    return [
        Monkey(0,[73, 77],lambda x:x*5,lambda x:x%11==0,6,5),
        Monkey(1,[57, 88, 80],lambda x:x+5,lambda x:x%19==0,6,0),
        Monkey(2,[61, 81, 84, 69, 77, 88],lambda x:x*19,lambda x:x%5==0,3,1),
        Monkey(3,[78, 89, 71, 60, 81, 84, 87, 75],lambda x:x+7,lambda x:x%3==0,1,0),
        Monkey(4,[60, 76, 90, 63, 86, 87, 89],lambda x:x+2,lambda x:x%13==0,2,7),
        Monkey(5,[88],lambda x:x+1,lambda x:x%17==0,4,7),
        Monkey(6,[84, 98, 78, 85],lambda x:x*x,lambda x:x%7==0,5,4),
        Monkey(7,[98, 89, 78, 73, 71],lambda x:x+4,lambda x:x%2==0,3,2),
        
    ]


BORED = lambda x:x//3
POST = lambda x:x%(11*19*5*3*13*17*7*2)
NONE = lambda x:x

def sim(monkeys,BORED,POST,rounds):
    inspected = [0]*len(monkeys)
    
    for i in range(rounds):
        for monkey in monkeys:
            while monkey.items:
                inspected[monkey.id] += 1
                item = monkey.items.pop(0)
                item = monkey.op(item)
                item = BORED(item)
                post = POST(item)
                if monkey.test(item):
                    monkeys[monkey.success].items.append(post)
                else:
                    monkeys[monkey.fail].items.append(post)

    return sorted(inspected)[-1] * sorted(inspected)[-2]

print(sim(question_input(),BORED,NONE,20))
print(sim(question_input(),NONE,POST,10000))
