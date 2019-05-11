//Yicheng Shen
//HW_1 
//1/24/2019

#include <stdlib.h>
#include <stdio.h>

double processOp(double amt, char op, double val);
double processPlus(double amt, double val);
double processMinus(double amt, double val);
double processTimes(double amt, double val);
double processDivide(double amt, double val);
double processPrint(double amt);
double processClear();
int takesNoArgs(char op);

    
    int main() {
        double amt = 0;  // the current value of the calculator
        char op;           // the operation to be performed
        double val;         // the value of the operation
        
        printf("CS 2271 Calculator\n");
        while (1) {
            // Read an input line. The first char of each line is the operation.
            // Arithmetic operations are followed by whitespace and a number.
        
            int ic = getchar();
	    while ( ic == '\n' || ic == ' ' ) { ic = getchar(); }
            if (ic < 0) break;   //EOF
            op = (char) ic;
            if (op == 'Q') break;
                
            if (takesNoArgs(op))
                val = 0.0;
            else {
                scanf("%lf", &val);
		while (val == ' ') { scanf("%lf", &val); }
	    }
            // Call a fn to process the op and its val.
            amt = processOp(amt, op, val);
        }
        printf("Thank you and goodbye!\n");
    return 0;
    }
    
    int takesNoArgs(char op) {
	return (op == 'C') || (op == '=');
	
    }

 
    double processOp(double amt, char op, double val) {
        if (op == '+')
            return processPlus(amt, val);
        else if (op == '-')
            return processMinus(amt, val);
        else if (op == '*')
            return processTimes(amt, val);
        else if (op == '/')
            return processDivide(amt, val);
        else if (op == '=')
            return processPrint(amt);
        else if (op == 'C')
            return processClear();
        else {
            printf("Bad Operator\n");
            return amt;
        }
    }
    
    double processPlus(double amt, double val) {
        return amt + val;
    }
    
    double processMinus(double amt, double val) {
        return amt - val;
    }
    
    double processTimes(double amt, double val) {
        return amt * val;
    }
    
    double processDivide(double amt, double val) {
        return amt / val;
    }
    
    double processPrint(double amt) {
        printf("%f\n", amt);
        return amt;
    }
    
    double processClear() {
        return 0;
    }

