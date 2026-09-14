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
