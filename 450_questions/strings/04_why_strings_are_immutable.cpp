/*
    QUESTION    : Why are Strings immutable in Java/Python (and how std::string differs in C++)?
    Company Tags: Amazon, Google, Microsoft, Adobe
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
/*
 * ============================================================================
 * ARCHITECTURAL CONCEPTUAL EXPLANATION
 * ============================================================================
 *
 * 1. Why Strings are IMMUTABLE in Java/Python:
 *    - String Pool / Memory Optimization: Multiple references pointing to "apple"
 *      share the same memory location in heap string pool. Immutability ensures modifying
 *      one variable doesn't corrupt other references.
 *    - Thread Safety: Read-only string instances can be freely shared across concurrent
 *      threads without synchronization locks.
 *    - Security: Sensitive credentials (passwords, network sockets, DB URLs) passed
 *      as strings cannot be surreptitiously modified by malicious actors.
 *    - Hash Code Caching: String hash code is computed once during creation and cached,
 *      making them ultra-fast keys in HashMaps/HashSets.
 *
 * 2. Why `std::string` is MUTABLE in C++:
 *    - C++ prioritizes zero-overhead performance and value semantics.
 *    - In C++, strings own their dynamic contiguous char buffer on the heap and support
 *      in-place modification via `s[i] = 'a'` and `std::string_view` for non-owning read-only views.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Java/Python: String Constant Pool, Thread-safety, Security, Cached HashCode $\rightarrow$ Immutable.
 * - C++: Value semantics, in-place zero-copy mutability via `std::string`.
 */

int main() {
    string s = "Hello";
    s[0] = 'h'; // C++ allows direct in-place mutation
    cout << "Mutable C++ string: " << s << endl;
    return 0;
}
