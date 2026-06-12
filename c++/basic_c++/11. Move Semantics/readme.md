11. Move Semantics

vector<int> v1;

vector<int> v2 = std::move(v1);

Ownership transferred.

No copy.

Faster.
