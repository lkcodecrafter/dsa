# Phase 1 - Chapter 6: Memory Layout, Alignment, Padding & Endianness

## Objectives
- Understand process memory layout
- Learn stack vs heap
- Learn alignment and padding
- Understand little vs big endian
- Prepare for embedded interviews

## 1. Process Memory Layout

```
+----------------------+
| Code (.text)         |
+----------------------+
| Initialized (.data)  |
+----------------------+
| Uninitialized (.bss) |
+----------------------+
| Heap   (grows up)    |
|                      |
|                      |
| Stack  (grows down)  |
+----------------------+
```

- .text : program instructions
- .data : initialized global/static variables
- .bss : uninitialized global/static variables
- Heap : dynamic memory (new/malloc)
- Stack : local variables and function calls

## 2. Stack vs Heap

| Stack | Heap |
|---|---|
| Automatic | Manual / RAII |
| Fast | Slower |
| Small | Large |
| Auto cleanup | Explicit cleanup |

## 3. Stack Frame

```
main()
 |
 +-- foo()
      |-- return address
      |-- local variables
```

Each function call creates a new stack frame.

## 4. Memory Alignment

CPU accesses aligned data faster.

```cpp
struct A{
    char c;
    int i;
};
```

Likely size:

```
char 1 byte
padding 3 bytes
int 4 bytes

Total = 8 bytes
```

## 5. Structure Padding

Padding improves performance by aligning members.

Tips:
- Place larger members first.
- Group similar-sized members.

## 6. #pragma pack

```cpp
#pragma pack(push,1)
struct Packet{
    char a;
    int b;
};
#pragma pack(pop)
```

Removes padding. Use carefully because it may reduce performance.

## 7. Endianness

Little Endian:

```
0x12345678

78 56 34 12
```

Big Endian:

```
12 34 56 78
```

## 8. Why It Matters

- Network protocols
- Binary file formats
- Camera sensors
- DMA transfers

## 9. Camera HAL Example

Image buffers often require aligned memory for DMA and cache efficiency.

Misalignment can reduce performance or violate hardware requirements.

## 10. Debug Exercise

```cpp
struct Demo{
    char c;
    int x;
};
```

Question:
Predict sizeof(Demo).

Answer:
Typically 8 bytes because of alignment.

## 11. Interview Questions

1. What is stack memory?
2. What is heap memory?
3. Difference between stack and heap?
4. What is .text section?
5. What is .data section?
6. What is .bss?
7. What is memory alignment?
8. Why is alignment needed?
9. What is padding?
10. Why does sizeof(struct) surprise people?
11. How to reduce padding?
12. What is #pragma pack?
13. When should you avoid packed structs?
14. What is little endian?
15. What is big endian?
16. How do you detect endianness?
17. Why does endianness matter?
18. What is a stack frame?
19. Why can stack overflow happen?
20. Why is alignment important in embedded systems?

## Revision

- Stack = automatic lifetime
- Heap = dynamic lifetime
- Alignment improves CPU access
- Padding satisfies alignment
- Little Endian stores least-significant byte first
- DMA and Camera HAL often require aligned memory
