# Sample CCDSTRU Machine Project

_The complete and original specifications for this OLD MP are located [here](<./Specifications%20(Term%202,%20AY%202023-2024).pdf>). Read it alongside this brainrotted mess of a beauty pagent paper._

**_I no bother to check grammaw_**

## Breaking Down the Specs

The specifications for this course's MPs are always provided in some modernized and bastardized form of hieroglyphics. Therefore, a decoding process is necessary to understand what kind of **_board game_** it is that you have to code.

### Applicable Sets

> One may wonder what it would be like to be in a relationship. But one mustn't, because one can never attain it.

This section defines some assertions and constants for the system variables, _and beyond!_

#### Assertions

- **U**: { x ∈ Z⁺ | x < 3 }

  **U** is the set of all positive numbers—excluding zero (0)—less than three (3).

  ```java
  assert x > 0 && x < 3;
  ```

- **T**: { x ∈ Z⁺ | x < 7 }

  **T** is the set of all positive numbers—excluding zero (0)—less than seven (7).

  ```java
  assert x > 0 && x < 7;
  ```

- **C**: **U** × **U**

  **C** is the set of all ordered pairs formed from the elements of set **U**.

  ```java
  // Given coordinates named `pair`.
  assert pair.x() > 0 && pair.x() < 3 && pair.y() > 0 && pair.y() < 3;
  ```

- **F**: **T** × **T**

  **F** is the set of all ordered pairs formed from the elements of set **T**.

  ```java
  // Given coordinates named `pair`.
  assert pair.x() > 0 && pair.x() < 7 && pair.y() > 0 && pair.y() < 7;
  ```

- **V**: { true, false }

  **V** is a type alias for `Boolean`. No yucky maths needed here.

  ```java
  boolean x;
  ```

#### Constants

These don't need more explanation; I don't want to hurt myself. These will never gonna change.

- **P**:

  ```txt
  {
    { (1, 1), (2, 2) },
    { (1, 2), (2, 1) }
  }
  ```

- **s**:

  ```txt
  {
    { (1, 1), (1, 3), (2, 2), (3, 1), (3, 3) },
    { (4, 4), (4, 6), (5, 5), (6, 4), (6 ,6) },
    { (1, 5), (2, 4), (2, 5), (2, 6), (3, 5) },
    { (4, 1), (4, 3), (5, 1), (5, 3), (6, 1), (6, 3) }
  }
  ```

### System Variables

> If you've gotten so far as to start petting anime girls appearing in your crusty laptop's screen, consider supporting [assisted dying](https://web.senate.gov.ph/lisdata/34342743!.pdf).

This is very self-explanatory. Move on, it's bad for you to keep pretending like it's still not over.

### System Facts

> the water is turning the frogs gay

- **F₃** is the set of all the elements of **F** that neither **F₁** nor **F₂** has. Simple as. - Barry, 63
- The game is **over** if, _cough_:
  - The size of **F₃** is equal to zero (0);
  - The size of **C₁** is greater than zero (0) and it contains all of the elements of an element of **P**; or
  - The prior one, but **C₂**.

> [!WARNING]
> Reading can be difficult. DYSLEXIA MENTIONED????????

### System Initialization

> [!TIP]
> A `HashSet` is simply an implementation of a `Set` where the elements are unordered. It relies on the elements' hash codes for tracking, hence the name.

> [!NOTE]
> The `Coordinates` type is a custom record that I made. It is exactly what you think it is and is defined [here](./src/net/cielsachen/machineproject/Coordinates.java).

This section is a continuation of the previous one; this is where the system variables are defined.

```java
// V is a boolean.
boolean good = false;
boolean next = false;

// The size of C is 4.
var C1 = new HashSet<Coordinates>(4); // ∅
var C2 = new HashSet<Coordinates>(4); // ∅

// The size of F is 36.
var F1 = new HashSet<Coordinates>(36); // ∅
var F2 = new HashSet<Coordinates>(36); // ∅
```

### System States and Behavior

Giddy up and dive into the code for this one, chief. This can be found [here](./src/net/cielsachen/machineproject/Main.java).

#### Some Points

- ¬ is equal to `!`.
- ∧ is equal to `&&`.
- `NextPlayerMove(pos ∈ F₃)` condition of `thing that goes after next or ¬next` is basically: the number of elements of **F₁** or **F₂** that intersect **S** is greater than the size of **C₁** or **C₂**.
- `GameOver(over)` condition of `thing that goes after next or ¬next` is basically the second (2nd) and third (3rd) [winning conditions](#system-facts).
