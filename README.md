# cboxes

Simple collections library for C

## Build

**Requirements**:

- GNU Make
- LLVM Clang
- (optional) [Criterion](https://github.com/Snaipe/Criterion) (for unittesting)

```bash
make all
```

## Run tests

Be sure to install Criterion unittesting library and run this command:

```bash
make clean all tests
```

## To Do

- [X] Linked List
- [ ] Dynamic Array
- [X] Hash Map
- [ ] 2D Dynamic Array
- [ ] BST

## Convenction

- PascalCase structs and 'methods'
- 'method' - functions with struct name prefixes (like: `List_PushBack(...)`)
- overloads marked with letter in the end of function (like: `List_Get(...); List_GetN(...)`)

