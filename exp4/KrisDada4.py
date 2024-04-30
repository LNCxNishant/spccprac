import re

op = set("+-/*")
address = 100
count = 0

def arithematic(exp):
    global count
    symbols = []
    operators = []

    for i in exp:
        if i in op:
            operators.append(i)
        else:
            symbols.insert(0, i)

    if "=" in symbols:
        while True:
            s = symbols.pop()
            if s == "=":
                break
            symbols.insert(0, s)

    for i in operators:
        count += 1
        e = "temp{0} = {1} {2} {3}".format(
            count, symbols.pop(), i, symbols.pop())
        symbols.append("temp{}".format(count))
        print(e)

    if len(symbols) != 2:
        return

    temp = symbols.pop()
    print("{} = {}".format(symbols.pop(), temp))


def relation(exp):
    global address
    tokens = re.split(r">=|<=|==|>|<", exp)
    operators = re.findall(r">=|<=|==|>|<", exp)

    print("{0} if {2} {3} {1} goto {4}".format(
        address, tokens.pop(), tokens.pop(), operators.pop(), address + 3))
    print("{} T := 0 ".format(address + 1))
    print("{} goto {}".format(address+2, address+4))
    print("{} T := 1".format(address + 3))
    address += 4
    print(address)


if __name__ == "__main__":
    while True:
        option = input(
            "1 Assignment\n2 Arithmetic\n3 Relation\n4 Exit\nEnter choice : ")
        if option == "1":
            exp = input("Enter an expression : ")
            arithematic(exp)
        if option == "2":
            exp = input("Enter an expression : ")
            arithematic(exp)
        if option == "3":
            exp = input("Enter an expression : ")
            relation(exp)
        if option == "4":
            break
        print()
