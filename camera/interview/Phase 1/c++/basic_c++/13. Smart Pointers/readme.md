Smart Pointers

VERY IMPORTANT

```c++
1. unique_ptr

Single owner.

unique_ptr<Camera> cam =
make_unique<Camera>();

Cannot copy.

---

2. shared_ptr

Reference count.

shared_ptr<Camera> p1;
shared_ptr<Camera> p2 = p1;

Count:

2

----

3. weak_ptr

Break circular dependency.

Question:
Difference?

Answer:

Pointer	    Ownership
unique_ptr	Single
shared_ptr	Shared
weak_ptr	No ownership

----

References vs Pointer

Reference

int& ref = x;

Cannot be NULL.

Cannot rebind.

Pointer

int* ptr;

Can be NULL.

Can point elsewhere.


----

const
Pointer Constant
int* const ptr;

Pointer fixed.
Data changes.



----
Data Constant
const int* ptr; 

Data fixed.
Pointer changes.

Both Constant
const int* const ptr;

Nothing changes.

```

Question why do we need shared pointer, if we want to a shared object than we can use static class ? 

Answer : 

Static Variables vs shared_ptr
Static Variables:

Created once.
Exist for entire program lifetime.
Cannot be dynamically resized.
Not suitable for runtime sharing.

shared_ptr:

Tracks reference count.
Deletes when count reaches zero.
Allows dynamic sharing.
Works with templates and polymorphism.