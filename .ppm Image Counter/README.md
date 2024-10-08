# .ppm Image Counter
+ This is a program implemented for my C programming class at PUCPR
+ The main goal of this program is to count the amount of objects in a pre-processed image

## Implementation details
1. The first pixel contains the value for the background, based on that, the program scans the image looking for an object
2. After finding the first pixel from an object, the code will add all its neighbors to the analysis stack
3. Every pixel will add its neighbors that differ from the background, and mark them as already analyzed
4. After navigating the entire stack and marking all the pixels from that object as already analyzed
5. Count how many objects in total were analyzed

## Execution Example
<img src="https://github.com/FelipeADN/Small-projects/blob/main/.ppm%20Image%20Counter/example.gif" alt="Execution example gif" title="Execution example" width="200">

## Image Examples
<img src="https://github.com/FelipeADN/Small-projects/blob/main/.ppm%20Image%20Counter/Imagens/07.bmp" alt="Bottles image" title="Bottles" width="200">
<img src="https://github.com/FelipeADN/Small-projects/blob/main/.ppm%20Image%20Counter/Imagens/18.bmp" alt="Cells Image" title="Cells" width="200">
<img src="https://github.com/FelipeADN/Small-projects/blob/main/.ppm%20Image%20Counter/Imagens/19.bmp" alt="People Jumping Image" title="People" width="200">

### Concepts exercised
+ Linked Stack
+ Arrays
+ Structs
+ Dynamic memory allocation
+ Linked Data Structures
+ Reading binary files
