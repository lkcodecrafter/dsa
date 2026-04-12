# 🧠 Kotlin Complete Guide (Beginner → Advanced)

------------------------------------------------------------------------

# 📌 1. Basics

## Variables

``` kotlin
val name = "Lalit"   // immutable
var age = 25         // mutable
```

## Data Types

-   Int, Double, Float
-   String
-   Boolean

------------------------------------------------------------------------

# 📌 2. Control Flow

``` kotlin
if (age > 18) {
    println("Adult")
} else {
    println("Minor")
}
```

``` kotlin
when (age) {
    18 -> println("Exactly 18")
    in 19..30 -> println("Young")
    else -> println("Other")
}
```

------------------------------------------------------------------------

# 📌 3. Functions

``` kotlin
fun add(a: Int, b: Int): Int {
    return a + b
}
```

Shortcut:

``` kotlin
fun add(a: Int, b: Int) = a + b
```

------------------------------------------------------------------------

# 📌 4. Classes & OOP

``` kotlin
class Person(val name: String, var age: Int)

val p = Person("Lalit", 25)
```

------------------------------------------------------------------------

# 📌 5. Data Class

``` kotlin
data class User(val id: Int, val name: String)
```

------------------------------------------------------------------------

# 📌 6. Null Safety (VERY IMPORTANT)

``` kotlin
var name: String? = null

println(name?.length)
println(name ?: "Default")
```

------------------------------------------------------------------------

# 📌 7. Collections

``` kotlin
val list = listOf(1, 2, 3)

val doubled = list.map { it * 2 }
val even = list.filter { it % 2 == 0 }
```

------------------------------------------------------------------------

# 📌 8. Higher Order Functions

``` kotlin
fun operate(a: Int, b: Int, op: (Int, Int) -> Int): Int {
    return op(a, b)
}

val result = operate(2, 3) { x, y -> x + y }
```

------------------------------------------------------------------------

# 📌 9. Extension Functions

``` kotlin
fun String.addHello(): String {
    return "Hello $this"
}

println("Lalit".addHello())
```

------------------------------------------------------------------------

# 📌 10. Sealed Class

``` kotlin
sealed class Result {
    object Loading : Result()
    data class Success(val data: String) : Result()
    data class Error(val msg: String) : Result()
}
```

------------------------------------------------------------------------

# 📌 11. Coroutines

``` kotlin
GlobalScope.launch {
    delay(1000)
    println("Hello")
}
```

------------------------------------------------------------------------

# 📌 12. Flow

``` kotlin
flow {
    emit(1)
    emit(2)
}.collect {
    println(it)
}
```

------------------------------------------------------------------------

# 📌 13. Exception Handling

``` kotlin
try {
    val x = 10 / 0
} catch (e: Exception) {
    println("Error")
}
```

------------------------------------------------------------------------

# 📌 14. Advanced Topics

-   Inline functions
-   Reified generics
-   DSL
-   Coroutines deep dive
-   Flow operators

------------------------------------------------------------------------

# 🎯 FINAL

👉 Practice daily\
👉 Use in Android

------------------------------------------------------------------------

# ✅ DONE
