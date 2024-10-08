# .ppm Image Counter
+ This is a program implemented for my C programming class at PUCPR
+ The main goal of this program is to count the amount of objects in a pre-processed image

## Implementation details
1. The first pixel contains the value for the background, based on that, the program scans the image looking for an object
2. After finding the first pixel from an object, the code will add all its neighbours to the analysis stack
3. Every pixel will add its neighbours that differ from the background, and mark them as already analysed
4. After navigating the entire stack, and marking all the pixels from that object as already analysed
5. Count how many objects in total were analysed

## Execution Example
![alt text]( "1")
![alt text]( "2")
![alt text]( "3")

## Image Example
![alt text]( "Image")

### Concepts exercised
+ Linked Stack
+ Arrays
+ Structs
+ Dinamic memory allocation
+ Linked Data Structures
+ Reading binary files
