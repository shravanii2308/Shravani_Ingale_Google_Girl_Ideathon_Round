/*
For Circuit File:
-The user is prompted to enter the path or name of the circuit file containing the circuit schematic.
-The program reads the circuit file line by line.
-Each line is processed to extract the internal node names and their associated expressions.
-The extracted information is stored in a vector as pairs of internal node names and expressions.

For Fault File:
-The user is prompted to enter the path or name of the fault file containing the fault details.
-The program reads the fault file line by line.
-Each line is processed to extract the fault at and fault type information.
-The fault at represents the specific node where the fault occurs, and the fault type indicates the type of fault (SA0 or SA1).

For Input Values:
-The program prompts the user to provide input values for A, B, C, and D for each combination.
-There are 16 possible combinations of these input values, ranging from (0, 0, 0, 0) to (1, 1, 1, 1).
-The program iterates through each combination and prompts the user to enter the corresponding values.

Other Considerations:
-The program takes care to remove any unnecessary spaces from the input files to ensure proper parsing.
-It checks the fault type to determine the fault value (0 or 1) for fault simulations.
-Internal node values are evaluated by resolving the expressions using the provided input values.
-The program determines the expected output and faulty output by evaluating the combinational logic based on the input values and fault simulations.
-If the expected output and faulty output differ, the program prints the combination of input values and the faulty output.

Logic Operation in Every Internal Node:
I have enforced the constraint that there will be one logic operation in every internal node of the circuit.
Each internal node represents a logical operation on one or two input variables.

Not Operation in Front of Variable:
I have considered that the NOT operation will always appear in front of the variable in the expression.
This means that if the NOT operation is present, it will be the first character in the expression, followed by the variable name.

XOR and OR Operations Between Two Variables:
I have assumed that XOR and OR operations will always appear between two variables in the expression.
If XOR operation is present, it will be represented by the "^" symbol between the two variables.
If OR operation is present, it will be represented by the "|" symbol between the two variables.
*/

#include <bits/stdc++.h>
using namespace std;

// Evaluates the combinational logic expression and returns the result
int evaluateExpression(const string &expression, unordered_map<string, int> &nodeValues)
{
    int result;

    // Check for the NOT operation
    size_t notPos = expression.find("~");
    if (notPos == 0)
    {
        string singleVariable = expression.substr(notPos + 1);
        result = !nodeValues[singleVariable];
    }
    else
    {
        // Find the position of the logic gate
        size_t gatePos = expression.find("&");
        if (gatePos == string::npos)
        {
            gatePos = expression.find("|");
            if (gatePos == string::npos)
            {
                gatePos = expression.find("^");
            }
        }

        // Extract the variables from the expression
        string firstVariable = expression.substr(0, gatePos);
        string secondVariable = expression.substr(gatePos + 1);

        // Evaluate the expression based on the logic gate
        if (expression[gatePos] == '&')
        {
            result = nodeValues[firstVariable] & nodeValues[secondVariable];
        }
        else if (expression[gatePos] == '|')
        {
            result = nodeValues[firstVariable] | nodeValues[secondVariable];
        }
        else
        {
            result = nodeValues[firstVariable] ^ nodeValues[secondVariable];
        }
    }

    return result;
}

// Evaluates the expression for a node and updates its value in the nodeValues map
void evaluateNode(const string &expression, const string &nodeName, unordered_map<string, int> &nodeValues, const string &faultAt, int faultValue, bool checkFault)
{
    int expressionValue = evaluateExpression(expression, nodeValues);

    // Check if the node is the faulty node and update its value accordingly
    if (nodeName == faultAt && checkFault)
    {
        nodeValues[nodeName] = faultValue;
    }
    else
    {
        nodeValues[nodeName] = expressionValue;
    }
}

int main()
{
    // Open the output file for writing
    ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        cout << "Failed to open output file." << endl;
        return 1;
    }
    // Get the circuit file name from the user
    string circuitFile;
    cout << "Enter the circuit file: ";
    cin >> circuitFile;

    // Read the circuit schematic file and store the internal nodes and expressions in a vector
    vector<pair<string, string>> circuit;
    ifstream file(circuitFile);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                // Remove spaces from the line
                line.erase(remove(line.begin(), line.end(), ' '), line.end());

                // Split the line into internal node and expression
                size_t equalsPos = line.find('=');
                string internalNode = line.substr(0, equalsPos);
                string expression = line.substr(equalsPos + 1);
                circuit.push_back({internalNode, expression});
            }
        }
    }
    file.close();

    // Get the fault input file name from the user
    string faultInputFile;
    cout << "Enter the fault input file: ";
    cin >> faultInputFile;

    // Read the fault input file and extract the fault_at and fault_type values
    vector<string> faultInput;
    ifstream faultFile(faultInputFile);
    if (faultFile.is_open())
    {
        string line;
        while (getline(faultFile, line))
        {
            if (!line.empty())
            {
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                size_t equalsPos = line.find('=');
                string value = line.substr(equalsPos + 1);
                faultInput.push_back(value);
            }
        }
    }
    faultFile.close();

    // Get the fault_at and fault_type values
    string faultAt = faultInput[0];
    string faultType = faultInput[1];
    int faultValue = (faultType == "SA0") ? 0 : 1;

    // Generate the combinations of A, B, C, D
    vector<vector<int>> combinations;
    for (int i = 0; i < 16; ++i)
    {
        vector<int> combination(4);
        combination[0] = (i >> 3) & 1; // A
        combination[1] = (i >> 2) & 1; // B
        combination[2] = (i >> 1) & 1; // C
        combination[3] = i & 1;        // D
        combinations.push_back(combination);
    }

    // Traverse the combinations and evaluate the circuit for each combination
    for (const auto &combination : combinations)
    {
        // Set the values of A, B, C, D from the combination
        int A = combination[0], B = combination[1], C = combination[2], D = combination[3];

        // Store the values of A, B, C, D in the nodeValues map
        unordered_map<string, int> nodeValues;
        nodeValues["A"] = A;
        nodeValues["B"] = B;
        nodeValues["C"] = C;
        nodeValues["D"] = D;

        // Evaluate the expressions for each internal node (without considering the faulty node)
        for (const auto &node : circuit)
        {
            const string &nodeName = node.first;
            const string &expression = node.second;
            evaluateNode(expression, nodeName, nodeValues, faultAt, faultValue, false);
        }
        int expectedOutput = nodeValues["Z"];

        // Evaluate the expressions for the faulty node
        for (const auto &node : circuit)
        {
            const string &nodeName = node.first;
            const string &expression = node.second;
            evaluateNode(expression, nodeName, nodeValues, faultAt, faultValue, true);
        }
        int faultyOutput = nodeValues["Z"];

        // Check if the faulty output is different from the expected output
        if (faultyOutput != expectedOutput)
        {
            // Write the output to the file
            outputFile << "[A, B, C, D] = [" << A << " " << B << " " << C << " " << D << "], ";
            outputFile << "Z = " << faultyOutput << endl;
        }
    }

    // Close the output file
    outputFile.close();

    return 0;
}
