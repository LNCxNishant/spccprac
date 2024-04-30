import re

temp_count = 1

def generate_code(expression):
    global temp_count
    lhs, rhs = expression.split('=')
    lhs = lhs.strip()
    rhs = rhs.strip()
    terms = rhs.split(' ')
    code = []

    for i in range(len(terms)):
        if terms[i] in ['+', '*']:
            op = terms[i]
            operand1 = terms[i - 1]
            operand2 = terms[i + 1]
            temp = f't{temp_count}'
            temp_count += 1
            code.append(f"{temp} = {operand1} {op} {operand2};")
            terms[i + 1] = temp

    code.append(f"{lhs} = {terms[-1]};")
    print('\n'.join(code))

def generate_conditional_code():
    global temp_count
    expression = "if (a < b) then c = d + e else c = d - e"  # Example conditional expression
    print("Expression:", expression)

    # Extract condition, then-part, and else-part
    parts = re.split(r' then | else ', expression)
    condition = parts[0][3:].strip()  # Remove "if "
    then_part = parts[1].strip()
    else_part = parts[2].strip()

    # Create labels for branching in TAC
    true_label = f'L{temp_count}'
    temp_count += 1
    end_label = f'L{temp_count}'
    temp_count += 1
    
    # Generate TAC for conditional branching
    code = [
        f"if {condition} goto {true_label};",
        f"{else_part}; goto {end_label};",
        f"{true_label}: {then_part};",
        f"{end_label}:"
    ]
    print("Three-address code:")
    print('\n'.join(code))  # Display generated TAC

def main():
    global temp_count
    while True:
        print("Generate three-address code for:")
        print("1. Assignment")
        print("2. Conditional")
        print("3. Indexed Assignment")
        print("4. Copy")
        print("5. Exit")
        
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            generate_code("a = b * c + d")
        elif choice == 2:
            generate_conditional_code()
        elif choice == 3:
            generate_code("x[2] = y + 5")
        elif choice == 4:
            print("x = y;")
        elif choice == 5:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please enter a number from 1 to 5.")
        
        print()

if __name__ == "__main__":
    main()
