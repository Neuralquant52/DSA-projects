# Treap

A C++ implementation of a **treap**: a hybrid between a binary search tree (BST) and a heap.

## How it works

Each node holds a **key** and a randomly assigned **priority**. The tree maintains two invariants at once:

- **BST property** on keys: for every node, smaller keys go to the left and larger keys to the right.
- **Heap property** on priorities: every node has a higher (or lower, depending on the convention) priority than its children.

When an insertion or deletion breaks the heap property, the tree restores it with **rotations**. Since priorities are random, the tree stays balanced with high probability: the expected height is **O(log n)**, and search, insert and delete run in **O(log n)** expected time.

## Treap vs BST

The project includes a comparison of the height of a treap and a plain BST as a function of the number of inserted elements. A plain BST degrades toward O(n) height on sorted input, while the treap stays logarithmic.

## Project Structure

| Path | Description |
|---|---|
| `benchmarks/` | Benchmarks of the treap functions using [Google Benchmark](https://github.com/google/benchmark) |
| `tests/` | Test cases of the treap functions using [Google Test](https://github.com/google/googletest) |
