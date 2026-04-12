# 📱 Kotlin in Android Development (Deep Dive -- Staff Level)

------------------------------------------------------------------------

# 🧠 1. Kotlin + Android Philosophy

-   Concise, safe, expressive
-   Null safety avoids crashes
-   Coroutines → async made simple
-   Functional + OOP mix

------------------------------------------------------------------------

# 🏗️ 2. Project Structure (MVVM + Clean)

    UI (Compose)
    ↓
    ViewModel
    ↓
    UseCase
    ↓
    Repository
    ↓
    Data (API + DB)

------------------------------------------------------------------------

# 📌 3. ViewModel with Kotlin

``` kotlin
@HiltViewModel
class UserViewModel @Inject constructor(
    private val repo: UserRepository
) : ViewModel() {

    private val _state = MutableStateFlow<List<User>>(emptyList())
    val state: StateFlow<List<User>> = _state

    fun loadUsers() {
        viewModelScope.launch {
            _state.value = repo.getUsers()
        }
    }
}
```

------------------------------------------------------------------------

# 🔄 4. Coroutines (CORE)

## Why?

-   Replace callbacks
-   Handle async cleanly

------------------------------------------------------------------------

## Example:

``` kotlin
viewModelScope.launch {
    try {
        val data = withContext(Dispatchers.IO) {
            api.getUsers()
        }
        // update UI
    } catch (e: Exception) {
        // handle error
    }
}
```

------------------------------------------------------------------------

## ⚠️ Key Concepts:

-   launch → fire & forget
-   async → result
-   withContext → switch thread

------------------------------------------------------------------------

# 🌊 5. Flow (Reactive Streams)

``` kotlin
fun getUsers(): Flow<List<User>> = flow {
    emit(api.getUsers())
}
```

### Collect:

``` kotlin
viewModelScope.launch {
    repo.getUsers().collect {
        _state.value = it
    }
}
```

------------------------------------------------------------------------

## 🔥 StateFlow vs SharedFlow

  Feature   StateFlow   SharedFlow
  --------- ----------- ------------
  State     ✅          ❌
  Use       UI state    Events

------------------------------------------------------------------------

# 🎨 6. Jetpack Compose + Kotlin

``` kotlin
@Composable
fun UserScreen(vm: UserViewModel = hiltViewModel()) {
    val users by vm.state.collectAsState()

    LazyColumn {
        items(users) {
            Text(it.name)
        }
    }
}
```

------------------------------------------------------------------------

## ⚠️ Recomposition

Triggered when: - State changes - Flow emits new value

------------------------------------------------------------------------

# 💉 7. Dependency Injection (Hilt)

``` kotlin
@Module
@InstallIn(SingletonComponent::class)
object AppModule {

    @Provides
    fun provideRepo(api: ApiService): UserRepository {
        return UserRepository(api)
    }
}
```

------------------------------------------------------------------------

# 🧩 8. Repository Pattern

``` kotlin
class UserRepository(
    private val api: ApiService,
    private val db: UserDao
) {
    suspend fun getUsers(): List<User> {
        return try {
            val data = api.getUsers()
            db.insert(data)
            data
        } catch (e: Exception) {
            db.getUsers()
        }
    }
}
```

------------------------------------------------------------------------

# 💾 9. Room + Kotlin

``` kotlin
@Dao
interface UserDao {
    @Query("SELECT * FROM user")
    suspend fun getUsers(): List<User>

    @Insert
    suspend fun insert(users: List<User>)
}
```

------------------------------------------------------------------------

# ⚡ 10. Error Handling Pattern

``` kotlin
sealed class Result<T> {
    class Success<T>(val data: T) : Result<T>()
    class Error<T>(val msg: String) : Result<T>()
    class Loading<T> : Result<T>()
}
```

------------------------------------------------------------------------

# 🧠 11. Best Practices

-   Use `val` over `var`
-   Avoid GlobalScope
-   Use StateFlow in ViewModel
-   Handle lifecycle properly
-   Keep business logic in UseCase

------------------------------------------------------------------------

# 🚀 12. Interview Questions

### Q1: Why Coroutines over Threads?

👉 Lightweight, structured, easy cancellation

### Q2: Flow vs LiveData?

👉 Flow is more powerful, supports operators

### Q3: What causes recomposition?

👉 State change

------------------------------------------------------------------------

# 🎯 FINAL

👉 Kotlin = Backbone of Android\
👉 Coroutines + Flow = MUST MASTER\
👉 Clean architecture = Mandatory

------------------------------------------------------------------------

# ✅ DONE -- Kotlin in Android (Deep)
