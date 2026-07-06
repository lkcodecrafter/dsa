11. Move Semantics

vector<int> v1;

vector<int> v2 = std::move(v1);

Ownership transferred.

No copy.

Faster.

Move semantics allow resources to be transferred from temporary objects instead of copying them. This improves performance, especially for objects that manage dynamic memory.

