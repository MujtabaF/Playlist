# Playlist (CMPT 225) — Technical Description

## Purpose

A **C++ educational assignment** implementing a **singly linked list** playlist of **`Song`** objects. The user manipulates the playlist through a **text menu** (insert, remove, swap, print, quit). The assignment stresses **dynamic memory**, **the Rule of Three/Five** (copy constructor, destructor, assignment), **position-based ADT operations**, and **complexity analysis** documented in `a1main.cpp` comments.

Use this for **data structures**, **C++ memory management**, and **Big-O reasoning** interviews.

---

## Files

| File | Role |
|------|------|
| `Song.h` / `Song.cpp` | Immutable-ish song record: name, artist, length |
| `PlayList.h` | Declares `PlayListNode` and `PlayList` ADT |
| `PlayList.cpp` | Method implementations (not fully quoted in exploration — behavior inferred from interface + main) |
| `a1main.cpp` | `main`, menu loop, I/O, complexity commentary |

---

## `Song` class (`Song.h`)

- **Constructor:** `Song(string nm, string art, int len)`
- **Accessors:** `getName()`, `getArtist()`, `getLength()`
- **Private:** `name`, `artist`, `length`

Songs are **values** stored **by value** inside `PlayListNode` (copy on insert).

---

## `PlayListNode` (`PlayList.h`)

Provided **fixed definition** (student must not change):

- `Song song`
- `PlayListNode* next`
- Constructors: `(Song, PlayListNode*)` and `(Song)` with `next = nullptr`

Classic **singly linked list node**.

---

## `PlayList` ADT — public interface (`PlayList.h`)

| Method | Contract (from comments) |
|--------|---------------------------|
| `PlayList()` | Empty list, `head == nullptr` |
| `PlayList(const PlayList& pl)` | **Deep copy** |
| `~PlayList()` | Free all nodes |
| `PlayList& operator=(const PlayList& pl)` | **Assign** — free old, deep copy source; safe on self-assignment |
| `void insert(Song sng, unsigned int pos)` | **PRE:** `0 <= pos <= length` — insert at 0-based index |
| `Song remove(unsigned int pos)` | **PRE:** `0 <= pos < length` — remove and return |
| `void swap(unsigned int pos1, unsigned int pos2)` | **PRE:** valid positions — exchange two nodes’ **songs** or **links** (implementation-dependent) |
| `Song get(unsigned int pos) const` | Return song at index |
| `unsigned int size() const` | Number of elements |

**Private:** `PlayListNode* head`, `unsigned int length`

---

## `a1main.cpp` — user interface

**Menu:**

1. Insert song at position (1-based UX mapped to `pos-1` for ADT)
2. Remove at position
3. Swap two positions
4. Print all (iterates `0..size-1`, calls `get(i)`)
5. Quit

**I/O details:**

- Uses `getline` for name/artist after `cin >> choice` with `cin.ignore()` to consume newlines
- **Position validation loops** re-prompt until valid range
- **Edge cases:** empty list messages; swap requires size > 1

---

## Documented complexity (author comments in `a1main.cpp`)

The file header states:

- **Destructor:** O(n)
- **Copy constructor / assignment:** O(n)
- **insert / remove / get / swap:** O(n) worst case (tail operations traverse full list)
- **size:** O(1) if `length` maintained
- **Print all:** author notes **O(n²)** if each `get(i)` walks from head — **naive indexing** pattern

**Interview angle:** Discuss upgrading to **doubly linked list** or **cursor** for O(i) amortized if frequent random access — or document that `get` could be O(n) and outer loop makes print O(n²).

---

## Implementation expectations (`PlayList.cpp`)

Typical patterns (verify against your file):

- **insert at 0:** update `head`
- **insert at end:** walk to last `next == nullptr`
- **remove:** patch predecessor’s `next` or replace `head`
- **assignment:** check `this == &pl`; clear `*this`; deep copy from `pl`
- **Destructor:** `while (head) { temp = head; head = head->next; delete temp; }`

---

## How to summarize by role

- **Data structures:** Singly linked list, pointer surgery, deep copy semantics
- **C++:** Rule of Three, dynamic allocation per node, exception safety (strong guarantee harder without smart pointers)
- **Complexity:** Tradeoffs of list vs vector (`std::vector` would give O(1) amortized append and O(1) random access)

---

## Possible improvements (discussion only)

- Use **`std::unique_ptr<PlayListNode>`** for automatic memory management
- Provide **iterator** or **`const` correct** accessors returning `const Song&` instead of copies
- Replace manual list with **`std::list<Song>`** in production — but assignment likely forbids STL containers for underlying storage
