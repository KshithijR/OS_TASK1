## OPERATING SYSTEM – Task 1

### Problem Statement

Implement a Producer-Consumer problem using threads in Java.

---

## Objective

The objective of this program is to demonstrate the Producer-Consumer problem using Java threads.

The program uses a shared buffer between a Producer and a Consumer. The Producer adds items to the buffer, while the Consumer removes items from the buffer.

Thread synchronization is used to make sure that the Producer and Consumer access the shared buffer safely.

---

## Technologies Used

- Java
- Java Threads
- `Runnable`
- `synchronized`
- `wait()`
- `notifyAll()`
- `ArrayDeque`

---

## Producer-Consumer Problem

The Producer-Consumer problem is a synchronization problem where:

- The **Producer** produces items and adds them to a shared buffer.
- The **Consumer** consumes items from the shared buffer.
- The buffer has a limited capacity.
- The Producer must wait when the buffer is full.
- The Consumer must wait when the buffer is empty.

In this program:

```text
Buffer Capacity = 5
Number of Items = 10

# Matrix Multiplication Using Threads


## Problem Statement

Implement matrix multiplication of two matrices using threads. The matrices should have a minimum of 100 rows and 100 columns.

In this project, two **100 × 100 matrices** are multiplied using **POSIX threads (`pthread`)** in C++.

A separate worker thread is created for every element of the result matrix. Therefore, since the result matrix contains 10,000 elements, the program creates **10,000 worker threads**.

The program also contains a separate progress thread that displays a progress bar in the terminal while the matrix multiplication is being performed.

---

## Objective

The main objective of this project is to demonstrate how **multithreading** can be used to perform matrix multiplication.

Normally, matrix multiplication can be performed sequentially using nested loops. In this project, the calculation is divided among multiple threads.

Each worker thread is responsible for calculating exactly **one element** of the result matrix.

For a 100 × 100 result matrix:

```text
100 × 100 = 10,000 elements
