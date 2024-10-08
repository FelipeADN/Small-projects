# CPF Validator
+ This is a simple algorithm in C that reads a CPF number and checks if its valid.
+ A CPF is an 11-digit general-purpose identification number for every Brazilian citizen.

## How to check if a CPF number is valid

+ The last two digits serve the purpose of validating the number

Format of a CPF number:
### 111.444.777-XX

### 1. To calculate the first validating digit (10th), we multiply and add every number from right to left starting with 2.

1	| 1	| 1	| 4	| 4	| 4 |	7 |	7 |	7
---|---|---|---|---|---|---|---|---|
10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2
10 | 9 | 8 | 28 | 24 | 20 | 28 | 21 | 14

### 2. Add the results:

10+9+8+28+24+20+28+21+14 = 162

### 3. From this result, we make an integer division to 11
162 div 11 = 14 with rest 8.  

If the rest of this division is < 2, then **first digit is 0**.  
else if rest is >= 2, the first digit is 11 - rest. (11-8), **digit is 3!**

+ Now we have the number: 111.444.777-3X

### 4. To calculate the second validating digit (11th), we do the same thing as before, but including the 10th.

1	| 1	| 1	| 4	| 4	| 4	| 7	| 7	| 7	| 3
---|---|---|---|---|---|---|---|---|---|
11	| 10	| 9	| 8	| 7	| 6	| 5	| 4	| 3	| 2
11	| 10	| 9	| 32	| 28	| 24	| 35	| 28	| 21	| 6

### 5. Add the results:
11 + 10 + 9 + 32 + 28 + 24 + 35 + 28 + 21 + 6 = 204

### 6. From this result, we make an integer division to 11.
204 div 11 = 18 with rest 6.

If the rest of this division is < 2, then **first digit is 0**.  
else if rest is >= 2, the first digit is 11 - rest. (11-6), **digit is 5!**

The final number is:
### 111.444.777-35

# Curiosity
The 9th number indicates the Fiscal Region
1. – DF, GO, MS, MT and TO;
2. – AC, AM, AP, PA, RO and RR;
3. – CE, MA and PI;
4. – AL, PB, PE and RN;
5. – BA and SE;
6. – MG;
7. – ES and RJ;
8. – SP;
9. – PR and SC;
10. – RS.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/be/Brazil%2C_administrative_divisions_%28fiscal_regions%29_-_Nmbrs_-_colored.svg/1024px-Brazil%2C_administrative_divisions_%28fiscal_regions%29_-_Nmbrs_-_colored.svg.png" height="250">
