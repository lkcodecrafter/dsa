```c++

Constructor:

Camera()
{
}

Runs during creation.

Destructor:

~Camera()
{
}

Runs during destruction.

```

7. Copy Constructor

```c++

Camera c1;

Camera c2 = c1;

Invokes:

Camera(const Camera& obj)
{
}
```

```c++
8. Deep Copy vs Shallow Copy

Interview favorite.

Shallow
ptr1 ---> Memory

ptr2 ---> Same Memory

Problem:
Double free.
-----
Deep

ptr1 ---> Memory1

ptr2 ---> Memory2

Independent copy.

