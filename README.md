# BitBank – Banking System in C

## Overview
BitBank is a modular banking system written in C.  
It uses linked lists and abstract data types (ADTs) to manage bank accounts, transactions, and reporting operations.  
This project demonstrates strong skills in pointers, memory allocation, and data structure design.

## Features
- Create new bank accounts  
- Delete existing accounts  
- Deposit and withdraw money  
- Search for accounts  
- Linked list structure for storing all accounts  
- Clean separation between `.h` and `.c` files  
- Error handling and input validation  

## Technologies Used
- C programming  
- Linked lists  
- Dynamic memory allocation (malloc/free)  
- Header/implementation architecture  

## Project Structure
/BitBank
│── main.c
│── bitbank.c
│── bitbank.h
│── linked_list.c
│── linked_list.h
│── pr2cbitbank.h
│── Makefile
└── README.md


## How to Compile
Use GCC:
bash:
gcc main.c bitbank.c linked_list.c -o bitbank

## How to Run
./bitbank

