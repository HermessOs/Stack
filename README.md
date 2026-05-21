# Stack Implementation in C

A simple **LIFO (Last In, First Out) Stack** implemented in C using a fixed-capacity array, with custom integer type aliases for portability.

---

## Data Structure

### `Node` (Stack)
The stack is represented by a single struct holding:
- `collection` — a heap-allocated array of `i16` values
- `capacity` — the maximum number of elements the stack can hold
- `size` — the current number of elements

```
index:  [0]  [1]  [2]  [3]  [4]
value:  [10] [9]  [4]  [7]  [8]
                              ^
                             top (last pushed, first popped)
```

---

## API

| Function | Description |
|---|---|
| `createStack(capacity)` | Allocates and returns a new stack with a fixed capacity |
| `destroyStack(stack)` | Frees the internal array and the stack struct |
| `isEmpty(stack)` | Returns `true` if the stack has no elements |
| `isFull(stack)` | Returns `true` if the stack has reached its capacity |
| `push(stack, item)` | Adds a value to the top — returns `false` if full |
| `pop(stack, item)` | Removes the top value into `item` — returns `false` if empty |
| `peek(stack, item)` | Reads the top value into `item` without removing it — returns `false` if empty |

> All operations return a `bool` indicating success or failure — no crashes on edge cases.

---

## How It Works

### `push`
Checks if the stack is full, then writes the value at `collection[size]` and increments `size`.

### `pop`
Checks if the stack is empty, decrements `size`, then reads `collection[size]` into the output pointer. The value isn't erased from the array — it's simply no longer within the tracked `size`.

### `peek`
Reads `collection[size - 1]` into the output pointer without modifying `size`.

### `createStack`
Validates that capacity is positive, allocates the stack struct, then allocates the internal array. If either allocation fails, it cleans up and returns `NULL`.

### `destroyStack`
Frees the internal `collection` array first, then frees the stack struct itself.

---

## Example Usage

```c
Node *stack = createStack(5);

push(stack, 10);
push(stack, 9);
push(stack, 4);
push(stack, 7);
push(stack, 8);
// Stack: [10, 9, 4, 7, 8]  (8 is on top)

i16 top;
peek(stack, &top);   // top = 8

i16 val;
pop(stack, &val);    // val = 8
// Stack: [10, 9, 4, 7]

bool ok = push(stack, 5); // ok = false if full

destroyStack(stack);
```

---

## Type Aliases

Shorthand aliases over `<stdint.h>` types used throughout the code:

| Alias | Underlying Type |
|---|---|
| `i8` / `i16` / `i32` / `i64` | Signed integers |
| `u8` / `u16` / `u32` / `u64` | Unsigned integers |
| `f32` / `f64` | `float` / `double` |

---

## Notes

- The stack stores `i16` values with a maximum capacity defined at creation time — it does not grow dynamically.
- Both `createStack` allocations are null-checked; if the array allocation fails, the stack struct is freed before returning `NULL`.
- Memory is fully cleaned up via `destroyStack` — no leaks when used correctly.
