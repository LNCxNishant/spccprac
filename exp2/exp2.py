# Open input and output files
with open("input1.txt", "r") as input_file, open("output2.txt", "w") as output_file:
    # Initialize counters
    line_number = 1
    token_number = 0

    # Set of keywords
    keywords = {"int", "main", "if", "else", "do", "while", "include", "stdio",
                "malloc", "for", "printf", "scanf", "ctype", "stdlib", "string",
                "math", "void", "char", "getchar", "type", "isalpha", "toascii",
                "switch", "case", "break", "exit", "return"}

    # Write header to output file
    output_file.write("Line No.\tToken No.\tToken Type\tValue\n")

    # Loop through input file
    while True:
        ch = input_file.read(1)
        if not ch:
            break  # End of file
        elif ch == '\n':
            line_number += 1  # Increment line number
        elif ch in "+-*/":
            output_file.write(f"{line_number}\t\t\t{token_number}\t\t\tOperator\t\t\t{ch}\n")
            token_number += 1
        elif ch in ";{}()?@!%":
            output_file.write(f"{line_number}\t\t\t{token_number}\t\t\tSpecial Symbol\t\t\t{ch}\n")
            token_number += 1
        elif ch.isdigit():
            output_file.write(f"{line_number}\t\t\t{token_number}\t\t\tDigit\t\t\t{ch}\n")
            token_number += 1
        elif ch.isalpha():
            identifier = ch
            while True:
                next_ch = input_file.read(1)
                if not next_ch or not next_ch.isalnum() or next_ch == ' ':
                    break
                identifier += next_ch

            is_keyword = identifier in keywords
            output_file.write(f"{line_number}\t\t\t{token_number}\t\t\t{'Keyword' if is_keyword else 'Identifier'}\t\t\t{identifier}\n")
            token_number += 1
