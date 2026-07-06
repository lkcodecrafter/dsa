# Phase 1 - Chapter 5: Move Semantics & Rvalue References

> Embedded Camera Interview Masterclass (Condensed Edition)

## Objectives

- Understand lvalues and rvalues
- Learn move semantics
- Understand std::move
- Learn move constructor and move assignment
- Know when copying happens vs moving
- Apply move semantics in Camera HAL

---

# 1. Why Move Semantics?

Copying a large object is expensive.

```
Buffer (50 MB)
   |
Copy
   |
Another 50 MB allocated
```

Moving transfers ownership instead.

```
Buffer
 |
Move
 |
Ownership transferred
```

---

# 2. Lvalue vs Rvalue

```cpp
int a = 10;   // a is an lvalue
10;           // rvalue
```

Lvalue = has a name.
Rvalue = temporary object.

---

# 3. Rvalue Reference

```cpp
int&& x = 10;
```

`&&` binds to temporary objects.

---

# 4. std::move

```cpp
std::string s = "Camera";
std::string t = std::move(s);
```

Important:

`std::move` **does not move data by itself**. It simply converts an lvalue into an rvalue so a move constructor/assignment can be selected.

---

# 5. Move Constructor

```cpp
class Buffer{
    int* data;
public:
    Buffer(int* p):data(p){}
    Buffer(Buffer&& other) noexcept{
        data = other.data;
        other.data = nullptr;
    }
};
```

Dry Run

Before:

```
A --> Memory
B --> null
```

After:

```
A --> null
B --> Memory
```

---

# 6. Move Assignment

```cpp
a = std::move(b);
```

Steps:

1. Free current resource.
2. Steal ownership.
3. Set source to nullptr.

---

# 7. Copy vs Move

| Copy | Move |
|------|------|
| Duplicates resource | Transfers ownership |
| Expensive | Cheap |
| Two owners | One owner |

---

# 8. Why noexcept?

Containers like `std::vector` prefer move operations only when they are `noexcept`.

---

# 9. Camera HAL Example

Image buffers are large.

Bad:

```cpp
Frame f2 = f1;   // copies pixels
```

Better:

```cpp
Frame f2 = std::move(f1);
```

Ownership changes without copying image data.

---

# 10. Common Mistakes

- Using moved-from objects without reinitializing.
- Forgetting to set moved-from pointers to nullptr.
- Copying large buffers unnecessarily.

---

# 11. Interview Questions

1. What is move semantics?
2. Why was it introduced?
3. What is an lvalue?
4. What is an rvalue?
5. What is an rvalue reference?
6. What does std::move do?
7. Does std::move actually move data?
8. Difference between copy and move constructor?
9. Difference between copy and move assignment?
10. Why mark move constructor noexcept?
11. What happens to a moved-from object?
12. When is copy elision used?
13. What is Return Value Optimization (RVO)?
14. Why is move useful in embedded systems?
15. Why is move useful in Camera HAL?
16. Can unique_ptr be copied?
17. Why can unique_ptr be moved?
18. What is ownership transfer?
19. What is resource stealing?
20. What is perfect forwarding? (advanced preview)

---

# Revision

- lvalue = named object
- rvalue = temporary
- std::move enables move operations
- Move transfers ownership
- Copy duplicates resources
- Prefer move for large objects

Next Chapter:
Memory Layout, Alignment & Padding
