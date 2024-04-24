from collections import namedtuple

Monkey = namedtuple("Monkey","id items op mod success fail")


def question_input():
    return [
        Monkey(0,[73, 77],lambda x:x*5,11,6,5),
        Monkey(1,[57, 88, 80],lambda x:x+5,19,6,0),
        Monkey(2,[61, 81, 84, 69, 77, 88],lambda x:x*19,5,3,1),
        Monkey(3,[78, 89, 71, 60, 81, 84, 87, 75],lambda x:x+7,3,1,0),
        Monkey(4,[60, 76, 90, 63, 86, 87, 89],lambda x:x+2,13,2,7),
        Monkey(5,[88],lambda x:x+1,17,4,7),
        Monkey(6,[84, 98, 78, 85],lambda x:x*x,7,5,4),
        Monkey(7,[98, 89, 78, 73, 71],lambda x:x+4,2,3,2),
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
                if item % monkey.mod == 0: 
                    monkeys[monkey.success].items.append(post)
                else:
                    monkeys[monkey.fail].items.append(post)
    return sorted(inspected)[-1] * sorted(inspected)[-2]

print(sim(question_input(),BORED,NONE,20))
print(sim(question_input(),NONE,POST,10000))
