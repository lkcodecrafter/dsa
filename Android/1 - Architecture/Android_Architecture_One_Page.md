# 📱 Android Architecture -- One Page Guide (Staff Engineer Level)

------------------------------------------------------------------------

## 🏗️ 1. Clean Architecture Overview

    UI Layer (Compose / Activity / Fragment)
    ↓
    Presentation Layer (ViewModel)
    ↓
    Domain Layer (UseCases / Business Logic)
    ↓
    Data Layer (Repository)
    ↓
    Data Sources (API / DB / Cache)

------------------------------------------------------------------------

## 🎯 2. MVVM (Model-View-ViewModel)

### Flow:

UI → ViewModel → Repository → Data Source

### Key Points:

-   ViewModel holds UI state
-   Survives configuration changes
-   No direct DB/API calls from UI

------------------------------------------------------------------------

## 🎨 3. Jetpack Compose Architecture

-   Declarative UI
-   State-driven rendering
-   Recomposition happens when state changes

### State Types:

-   `remember`
-   `rememberSaveable`
-   `StateFlow / LiveData`

------------------------------------------------------------------------

## 🔄 4. State Management

### StateFlow vs SharedFlow

  Feature       StateFlow   SharedFlow
  ------------- ----------- --------------
  Holds State   ✅          ❌
  Replay        1           Configurable
  Use Case      UI State    Events

------------------------------------------------------------------------

## ⚙️ 5. Coroutines

### Key Concepts:

-   `launch` → fire & forget
-   `async` → returns result
-   Dispatchers:
    -   IO → network/db
    -   Main → UI
    -   Default → CPU work

### Structured Concurrency:

-   ViewModelScope
-   LifecycleScope

------------------------------------------------------------------------

## 🧩 6. Repository Pattern

Acts as single source of truth

    ViewModel → Repository → API/DB

Handles: - Caching - API calls - DB operations

------------------------------------------------------------------------

## 💉 7. Dependency Injection (Hilt)

### Benefits:

-   Decoupling
-   Testability
-   Scalability

### Key Annotations:

-   @Inject
-   @Module
-   @Provides
-   @Singleton

------------------------------------------------------------------------

## 💾 8. Data Layer

### Tools:

-   Retrofit → API
-   Room → Database
-   DataStore → Key-Value storage

------------------------------------------------------------------------

## 🧱 9. Modular Architecture

### Types:

-   App Module
-   Feature Modules
-   Core Modules
-   Data Modules

### Benefits:

-   Faster builds
-   Scalable teams
-   Clean separation

------------------------------------------------------------------------

## 🚀 10. Paging (Large Data)

-   Use Paging 3
-   Handles infinite scrolling
-   Works with Flow

------------------------------------------------------------------------

## ⚡ 11. Performance Best Practices

-   Avoid memory leaks
-   Use ViewModel properly
-   Minimize recomposition
-   Optimize app startup

------------------------------------------------------------------------

## 🔥 12. Interview Key Points

-   Explain architecture clearly
-   Talk about trade-offs
-   Show scalability thinking
-   Discuss real-world usage

------------------------------------------------------------------------

## 🧠 Final Tip

Always think:

👉 Separation of Concerns\
👉 Single Source of Truth\
👉 Lifecycle Awareness\
👉 Scalability

------------------------------------------------------------------------

# ✅ You are ready for Android Architecture Interviews!
