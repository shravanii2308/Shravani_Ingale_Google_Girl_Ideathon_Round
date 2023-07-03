# Shravani_Ingale_Google_Girl_Ideathon_Round
Repository for Google Girl Hackathon Ideathon Round

## Description
This program simulates faults in a circuit based on user-provided input files. It reads the circuit schematic, evaluates the combinational logic expressions for each internal node, and simulates faults to determine if the faulty output differs from the expected output. The program supports various logic gates such as AND, OR, and XOR, and handles the NOT operation as well.

## Features
- Parses circuit files: The program prompts the user to enter the path or name of the circuit file containing the circuit schematic. It reads the file, extracts the internal node names and their associated expressions, and stores them for further evaluation.
- Parses fault files: The user is prompted to enter the path or name of the fault file containing the fault details. The program reads the file, extracts the fault-at and fault-type information, and uses it to simulate faults in the circuit.
- Handles input values: The program prompts the user to provide input values for the input variables (A, B, C, and D) for each combination. It supports 16 possible combinations of input values and evaluates the circuit for each combination.
- Evaluates combinational logic: The program evaluates the combinational logic expressions for each internal node using the provided input values. It considers the logic gates (AND, OR, XOR) and handles the NOT operation, updating the internal node values accordingly.
- Simulates faults: The program determines the expected output and faulty output by evaluating the combinational logic based on the input values and fault simulations. If the faulty output differs from the expected output, it indicates a fault in the circuit.
- Generates output file: The program writes the combinations of input values and corresponding faulty outputs to an output file named "output.txt".

## Getting Started
1. Clone the repository: `git clone https://github.com/shravanii2308/Shravani_Ingale_Google_Girl_Ideathon_Round.git`
2. Navigate to the project directory: `cd Shravani_Ingale_Google_Girl_Ideathon_Round`
3. Compile the code: `g++ main.cpp -o Shravani_Ingale_Google_Girl_Ideathon_Round`
4. Run the program: `./Shravani_Ingale_Google_Girl_Ideathon_Round`

## Usage
1. Enter the path or name of the circuit file when prompted.
2. Enter the path or name of the fault file when prompted.
3. Provide the input values (A, B, C, D) for each combination as requested.
4. The program will evaluate the circuit for each combination and simulate faults.
5. The faulty combinations and corresponding faulty outputs will be written to the output file "output.txt".

## File Formats
### Circuit File
- The circuit file contains the circuit schematic.
- Each line represents an internal node and its associated expression.
- The format of each line is: `<node_name> = <expression>`
- Example circuit file:
```
net_x = A & B
net_y = C | D
Z = net_x ^ net_y
```

### Fault File
- The fault file contains the fault details.
- Each line represents a specific fault and its type.
- The format of the fault file is as follows:
```
fault_at = <node_name>
fault_type = <SA0 or SA1>
```
- Example fault file:
```
fault_at = Z
fault_type = SA0
```

## Dependencies
- The program requires a C++ compiler that supports C++11 or later.

## Limitations
- The program assumes that there will be one logic operation in every internal node of the circuit.
- The NOT operation is assumed to always appear in front of the variable in the expression.
- XOR and OR operations are assumed to always appear between two variables in the expression.

## References
- [C++ Reference](https://en.cppreference.com/w/)
