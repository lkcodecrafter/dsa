# 📱 Android Architecture -- FULL GUIDE WITH CODE (Staff Level)

------------------------------------------------------------------------

# 🏗️ 1. Clean Architecture (Example)

## Flow:

UI → ViewModel → UseCase → Repository → DataSource

------------------------------------------------------------------------

# 📌 Example: Get Users

## 🔹 Data Model

``` kotlin
data class User(val id: Int, val name: String)
```

------------------------------------------------------------------------

## 🔹 API Service

``` kotlin
interface ApiService {
    @GET("users")
    suspend fun getUsers(): List<User>
}
```

------------------------------------------------------------------------

## 🔹 Repository

``` kotlin
class UserRepository @Inject constructor(
    private val api: ApiService
) {
    suspend fun getUsers(): List<User> {
        return api.getUsers()
    }
}
```

------------------------------------------------------------------------

## 🔹 UseCase

``` kotlin
class GetUsersUseCase(private val repo: UserRepository) {
    suspend operator fun invoke(): List<User> {
        return repo.getUsers()
    }
}
```

------------------------------------------------------------------------

## 🔹 ViewModel

``` kotlin
@HiltViewModel
class UserViewModel @Inject constructor(
    private val useCase: GetUsersUseCase
) : ViewModel() {

    private val _state = MutableStateFlow<List<User>>(emptyList())
    val state: StateFlow<List<User>> = _state

    init {
        viewModelScope.launch {
            _state.value = useCase()
        }
    }
}
```

------------------------------------------------------------------------

## 🔹 UI (Compose)

``` kotlin
@Composable
fun UserScreen(viewModel: UserViewModel = hiltViewModel()) {
    val users by viewModel.state.collectAsState()

    LazyColumn {
        items(users) {
            Text(it.name)
        }
    }
}
```

------------------------------------------------------------------------

# 🎨 2. Compose State Handling

``` kotlin
@Composable
fun Counter() {
    var count by remember { mutableStateOf(0) }

    Column {
        Text("Count: $count")
        Button(onClick = { count++ }) {
            Text("Increase")
        }
    }
}
```

------------------------------------------------------------------------

# 🔄 3. Flow vs StateFlow

``` kotlin
// StateFlow
val stateFlow = MutableStateFlow(0)

// SharedFlow
val sharedFlow = MutableSharedFlow<Int>()

// Collect
lifecycleScope.launch {
    stateFlow.collect {
        println(it)
    }
}
```

------------------------------------------------------------------------

# ⚙️ 4. Coroutines

``` kotlin
viewModelScope.launch(Dispatchers.IO) {
    val data = api.getUsers()
    withContext(Dispatchers.Main) {
        // update UI
    }
}
```

------------------------------------------------------------------------

# 🧩 5. Repository Pattern

``` kotlin
class UserRepository(
    private val api: ApiService,
    private val db: UserDao
) {
    suspend fun getUsers(): List<User> {
        return try {
            val users = api.getUsers()
            db.insert(users)
            users
        } catch (e: Exception) {
            db.getUsers()
        }
    }
}
```

------------------------------------------------------------------------

# 💉 6. Hilt DI

``` kotlin
@Module
@InstallIn(SingletonComponent::class)
object AppModule {

    @Provides
    fun provideApi(): ApiService {
        return Retrofit.Builder()
            .baseUrl("https://api.com")
            .build()
            .create(ApiService::class.java)
    }
}
```

------------------------------------------------------------------------

# 💾 7. Room DB

``` kotlin
@Entity
data class UserEntity(
    @PrimaryKey val id: Int,
    val name: String
)

@Dao
interface UserDao {
    @Query("SELECT * FROM UserEntity")
    suspend fun getUsers(): List<UserEntity>

    @Insert
    suspend fun insert(users: List<UserEntity>)
}
```

------------------------------------------------------------------------

# 🚀 8. Paging 3

``` kotlin
val pager = Pager(PagingConfig(pageSize = 20)) {
    UserPagingSource(api)
}.flow
```

------------------------------------------------------------------------

# 🧱 9. Modularization

Modules: - app - feature-user - core - data

------------------------------------------------------------------------

# ⚡ 10. Performance Tips

-   Avoid recomposition loops
-   Use LazyColumn
-   Use ViewModel for state

------------------------------------------------------------------------

# 🔥 11. Interview Tips

-   Explain flow clearly
-   Discuss trade-offs
-   Show real-world thinking

------------------------------------------------------------------------

# 🧠 FINAL

👉 Always: - Separate concerns - Use single source of truth - Think
scalable

------------------------------------------------------------------------

# ✅ DONE -- FULL ANDROID INTERVIEW PREP WITH CODE
