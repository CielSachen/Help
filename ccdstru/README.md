# CCDSTRU Machine Project

Machine projects are usually a recreation of a board game. This repository contains the MP from A.Y. 2023-24 and I, unfortunately, cannot tell what board game the specification was based on.

The biggest standout compared to CCPROG1 and 2 MP specifications is that this course uses God knows what symbols. These are going to be simple to parse, because they're usually either set theory or propositional logic symbols.

## Context

### What Are Arrays?

Arrays are an ordered collection of values with the same data type. In C, they are implemented in this way:

- Values with the same data type placed next to each other in memory;

  | Location       | 0x00 | 0x04 | 0x08 | 0x0C | 0x10 |
  | -------------- | ---- | ---- | ---- | ---- | ---- |
  | Values (`int`) | `1`  | `2`  | `3`  | `4`  | `5`  |

- An array variable is a pointer to the array's first value;

  ```c
  #include <stdio.h>

  // The compiler infers the array size, but you can also set it for more strictness.
  // int number_array[5] = {1, 2, 3, 4, 5};
  int number_array[] = {1, 2, 3, 4, 5};

  // An asterisk dereferences the pointer, meaning that the actual value being pointed to is what we are using.
  printf("%d", *number_array == 1);  // 1 (true)
  ```

- Has a fixed length (not dynamic); and

- Is indexible starting from zero.

  | Location       | 0x00 | 0x04 | 0x08 | 0x0C | 0x10 |
  | -------------- | ---- | ---- | ---- | ---- | ---- |
  | Values (`int`) | `1`  | `2`  | `3`  | `4`  | `5`  |
  | Index          | `0`  | `1`  | `2`  | `3`  | `4`  |

  ```c
  #include <stdio.h>

  int number_array[] = {1, 2, 3, 4, 5};
  // This is the canonical way to get an array's length.
  size_t array_length = sizeof number_array / sizeof number_array[0];

  for (size_t index = 0; index < array_length; index++) {
    printf("Index = %d, Value = %d\n", index, number_array[index]);
  }
  ```

> [!WARNING]
> The `sizeof` operator will return the size of the primitive type multiplied by the array's length, but because arrays are pass-by-reference, you cannot calculate its length when inside a function it's passed to.

> [!TIP]
> The `size_t` type is used for representing sizes or lengths of objects and indexing arrays. It's guaranteed to be big enough to handle any object.
>
> C/C++ Reference: https://en.cppreference.com/w/c/types/size_t

### Character Arrays vs String Literals

Strings can be initialized in C in two ways:

- as an array of characters

  ```c
  #include <stdio.h>

  // A string that can contain up to nine characters (the 10th character is the NULL terminator).
  char string[10];

  string[0] = 'k';
  string[1] = 'r';
  string[2] = 'u';
  string[3] = 'm';
  string[4] = 'm';
  string[5] = 'h';
  string[6] = 'o';
  string[7] = 'l';
  string[8] = 'z';

  printf("%s", string);  // krummholz
  ```

- as a literal

  ```c
  #include <stdio.h>

  char* string = "krummholz";

  printf("%s", string);  // krummholz
  ```

  All strings you write, encased in double quotes, are string literals. (Even the string input of `printf()` is a string literal!)

Character array strings can also be initialized with a string literal.

```c
#include <stdio.h>

// The compiler infers the array size.
char string[] = "krummholz";

printf("%s", string);  // krummholz
```

A character array is guaranteed to be characters in memory placed next to each other, with the variable being the pointer to the first character. A string literal is also guaranteed to be characters in memory placed next to each other, with the variable being the pointer to the first character, but its location in memory is unknown.

A string literal is not mutable in the same way as a character array,

```c
char* string = "krummholz";
string = "willow";

// vs

char string[] = "krummholz";

string[0] = 'w';
string[1] = 'i';
string[2] = 'l';
string[3] = 'l';
string[4] = 'o';
string[5] = 'w';
string[6] = '\0';
string[7] = '\0';
string[8] = '\0';
```

arithmetic operations can be done on its pointer,

```c
#include <stdio.h>

char* string = "krummholz";

printf("%c\n", *string);  // k

string++;

printf("%c", *string);  // r
```

and `sizeof` will return the pointer's size in bytes, not the array's.

```c
#include <stdio.h>

char* string = "krummholz";

print("%lu", sizeof(string));  // 8

char charArray[] = "krummholz";

print("%lu", sizeof(string));  // 10
```

## Converting Maths to Code

To better understand the code implementation, it would help to go over the choices made to convert the maths to code.

> [!IMPORTANT]
> Sets don't exist in C, it's one of the oldest languages after all! We will instead make use of arrays; the two are similar in principle, the major difference being that sets contain unique values while arrays can contain repeating values.

> [!IMPORTANT]
> Ordered pairs don't exist in C either, and most languages. This could be converted into two integer member tuples, but tuples don't exist in C as well. Just like with sets, we will use arrays instead. Garbage ordered pair values will be represented by a (0, 0) pair, otherwise the compiler will complain and you will suffer more.
>
> ```c
> #define <stdint.h>
>
> typedef uint_least8_t OrderedPair[2];
> ```

<img src="https://i.redd.it/rrozgfkvaan61.png" alt="Bulllocks" width="50%" />

> [!TIP]
> See this [W3Schools page on C multidimensional arrays](https://www.w3schools.com/c/c_arrays_multi.php).

### Applicable Sets

- **U** : {x ∈ ℤ⁺ | x < 3}

  This set, though unused in code, precedes a subsequent set. It's the set of all integers greater than zero and less than three.

- **T** : {x ∈ ℤ⁺ | x < 7}

  This set, though unused in code, precedes a subsequent set. It's the set of all integers greater than zero and less than seven.

- **C** : **U** × **U**

  This was treated as a definition of a type. It's the set of the Cartesian products of the elements of set **U** and itself. It can contain up to four elements.

  ```c
  #define C_SET_SIZE 4

  typedef OrderedPair CSet[C_SET_SIZE];
  ```

- **F** : **T** × **T**

  This was treated as a definition of a type. It's the set of the Cartesian products of the elements of set **T** and itself. It can contain up to thirty-six elements.

  ```c
  #define F_SET_SIZE 36

  typedef OrderedPair FSet[F_SET_SIZE];
  ```

- **V** : {true, false}

  This was treated as a definition of a type. It's the set of true and false. _It's a bloody boolean, innit? Simple as._

  ```c
  #include <stdbool.h>

  bool  //...
  ```

- **P** : {{(1, 1), (2, 2)}, {(1, 2), (2, 1)}}

  This set was treated as a constant, down to the bone.

  ```c
  OrderedPair p[2][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};
  ```

- **S** : {{(1, 1), (1, 3), (2, 2), (3, 1), (3, 3)},
          {(4, 4), (4, 6), (5, 5), (6, 4), (6, 6)},
          {(1, 5), (2, 4), (2, 5), (2, 6), (3, 5)},
          {(4, 1), (4, 3), (5, 1), (5, 3), (6, 1), (6, 3)}}

  This set was treated as a constant, down to the bone.

  ```c
  OrderedPair s[4][6] = {{{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}, {0, 0}},
                         {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}, {0, 0}},
                         {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}, {0, 0}},
                         {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}};
  ```

### System Variables

These sets were treated as variable declarations.

- _good_ ∈ **V**

  ```c
  bool good;
  ```

- _over_ ∈ **V**

  ```c
  bool over;
  ```

- _next_ ∈ **V**

  ```c
  bool next;
  ```

- _C₁_, _C₂_ ⊆ **C**

  ```c
  CSet c1;
  CSet c2;
  ```

- _F₁_, _F₂_, _F₃_ ⊆ **F**

  ```c
  FSet f1;
  FSet f2;
  FSet f3;
  ```

### System Facts

These were treated as assertions.

- _F₃_ = **F** - (_F₁_ ∪ _F₂_)

  The variable's value is the set of the elements of F that are not in either F₁ or F₂.

  ```c
  void remove_element_from_set(const OrderedPair element, OrderedPair set[restrict], const size_t set_size);

  FSet f3 = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
             {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
             {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};

  remove_element_from_set(pos, f3, F_SET_SIZE);
  ```

- _over_ ↔ ((|_F₃_| = 0) ∨ ∃ _x_ (_x_ ∈ P(_C₁_) ∧ |_x_| > 0 ∧ _x_ ∈ **P**) ∨ ∃ _x_ (_x_ ∈ P(_C₂_) ∧ |_x_| > 0 ∧ _x_ ∈ **P**))

  The variable's value is `true` (or `1`) if:

  - _F₃_ is empty;
  - _C₁_ has more than one element and is an element of **P** (or a superset of an element of **P**); or
  - _C₂_ has more than one element and is an element of **P** (or a superset of an element of **P**).

  ```c
  size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size);

  bool is_superset_of_set_p_set(OrderedPair set[restrict], const size_t set_size);

  over = get_actual_set_size(f3, F_SET_SIZE) == 0 ||
           (get_actual_set_size(c1, C_SET_SIZE) > 0 && is_superset_of_set_p_set(c1, C_SET_SIZE)) ||
           (get_actual_set_size(c2, C_SET_SIZE) > 0 && is_superset_of_set_p_set(c2, C_SET_SIZE));
  ```

### System Initialization

These were treated as variable initializations.

- _good_ = _false_

  ```c
  bool good = false;
  ```

- _next_ = _false_

  ```c
  bool next = false;
  ```

- _C₁_ = ∅

  ```c
  CSet c1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  ```

- _C₂_ = ∅

  ```c
  CSet c2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  ```

- _F₁_ = ∅

  ```c
  FSet f1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  ```

- _F₂_ = ∅

  ```c
  FSet f2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  ```

### System States and Behavior

These were treated as function definitions.

> [!IMPORTANT]
> Refer to these functions' parameters if the variables are not defined in the code block.

- NextPlayerMove(_pos_ ∈ **F**)

  ```c
  // We add more parameters to pass on the other variables. They can't just transcend boundaries on their own.
  void next_player_move(const OrderedPair pos, const bool over, const bool next, FSet f3, bool *const good, FSet f1, FSet f2, CSet c1, CSet c2);
  ```

  - (_a_, _b_) = _pos_

    We destructure the ordered pair.

    ```c
    #define <stdint.h>

    const uint_least8_t a = pos[0];
    const uint_least8_t b = pos[1];
    ```

  - _c_ = ⌊(_a_ - 1) / 3⌋ + 1

    ```c
    #define <stdint.h>
    #include <math.h>

    const uint_least8_t c = floor((a - 1) / 3) + 1;
    ```

  - _d_ = ⌊(_b_ - 1) / 3⌋ + 1

    ```c
    #define <stdint.h>
    #include <math.h>

    const uint_least8_t d = floor((b - 1) / 3) + 1;
    ```

  - (¬ _over_ ∧ _next_ ∧ _pos_ ∈ _F₃_) → (_good_ = ¬ _good_ ∧ _F₁_ = _F₁_ ∪ {_pos_})

    ```c
    bool is_element_of_set(OrderedPair value, OrderedPair set[restrict], const size_t set_size);

    void combine_sets(OrderedPair main_set[restrict], OrderedPair set[restrict], const size_t set_size);

    FSet pos_set = {{a, b}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    if (!over && next && is_element_of_set(pos, f3, F_SET_SIZE)) {
        *good = !*good;

        combine_sets(f1, pos_set, F_SET_SIZE);
    }
    ```

  - (¬ _over_ ∧ ¬ _next_ ∧ _pos_ ∈ _F₃_) → (_good_ = _¬good_ ∧ _F₂_ = _F₂_ ∪ {_pos_})

    ```c
    bool is_element_of_set(OrderedPair value, OrderedPair set[restrict], const size_t set_size);

    void combine_sets(OrderedPair main_set[restrict], OrderedPair set[restrict], const size_t set_size);

    FSet pos_set = {{a, b}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    if (!over && !next && is_element_of_set(pos, f3, F_SET_SIZE)) {
        *good = !*good;

        combine_sets(f2, pos_set, F_SET_SIZE);
    }
    ```

  - (¬ _over_ ∧ _good_ ∧ _next_ ∧ |P(_F₁_) ∩ S| > |_C₁_|) → _C₁_ = _C₁_ ∪ {(_c_, _d_)}

    ```c
    size_t count_set_s_subsets(OrderedPair set[restrict], const size_t set_size);

    size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size);

    void combine_sets(OrderedPair main_set[restrict], OrderedPair set[restrict], const size_t set_size);

    CSet cd_set = {{c, d}, {0, 0}, {0, 0}, {0, 0}};

    if (!over && *good && next && count_set_s_subsets(f1, F_SET_SIZE) > get_actual_set_size(c1, C_SET_SIZE)) {
        combine_sets(c1, cd_set, F_SET_SIZE);
    }
    ```

  - (¬ _over_ ∧ _good_ ∧ ¬ _next_ ∧ |P(_F₂_) ∩ S| > |_C₂_|) → _C₂_ = _C₂_ ∪ {(_c_, _d_)}

    ```c
    size_t count_set_s_subsets(OrderedPair set[restrict], const size_t set_size);

    size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size);

    void combine_sets(OrderedPair main_set[restrict], OrderedPair set[restrict], const size_t set_size);

    CSet cd_set = {{c, d}, {0, 0}, {0, 0}, {0, 0}};

    if (!over && *good && !next && count_set_s_subsets(f2, F_SET_SIZE) > get_actual_set_size(c2, C_SET_SIZE)) {
        combine_sets(c2, cd_set, F_SET_SIZE);
    }
    ```

  - (¬ _over_ ∧ _good_) → _good_ = ¬ _good_

    ```c
    if (!over && *good) *good = !*good;
    ```

- GameOver(over)

  ```c
  // We add more parameters to pass on the other variables. They can't just transcend boundaries on their own.
  void game_over(const bool over, bool *const next, CSet c1, CSet c2, char **const result);
  ```

  - _result_ ∈ {"B wins", "A wins"}

    This set was treated as variable declaration.

    ```c
    // We add a default value for when both players tie.
    char *result = "A and Player B are tied";
    ```

  - (_over_ ∧ _next_ ∧ ∃ _x_ (_x_ ∈ P(_C₁_) ∧ |_x_| > 0 ∧ _x_ ∈ **P**)) → _result_ = "A wins"

    ```c
    size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size);

    bool is_superset_of_set_p_set(OrderedPair set[restrict], const size_t set_size);

    if (over && *next && get_actual_set_size(c1, C_SET_SIZE) > 0 && is_superset_of_set_p_set(c1, C_SET_SIZE)) {
        *result = "A wins";
    }
    ```

  - (¬ _over_ ∧ ¬ _next_ ∧ ∃ _x_ (_x_ ∈ P(_C₂_) ∧ |_x_| > 0 ∧ _x_ ∈ **P**)) → _result_ = "B wins"

    ```c
    size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size);

    bool is_superset_of_set_p_set(OrderedPair set[restrict], const size_t set_size);

    if (over && !*next && get_actual_set_size(c2, C_SET_SIZE) > 0 && is_superset_of_set_p_set(c2, C_SET_SIZE)) {
        *result = "B wins";
    }
    ```

  - (¬ _over_) → _next_ = ¬ _next_

    ```c
    if (!over) *next = !*next;
    ```

## Implementation

The full prim and proper implementation can be found in the [source code](./c/src/).
