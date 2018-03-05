# Lecture 1/3/18

## Struct Review

```c
typedef struct _Coord {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} Coord;

Coord a, b, coords[10], *p;
a.x = 5;  a.y = 6;  a.z = 7;
p = &a;
b.x = 3;  b.y = 3;  b.z = 3;

(*p).x = 6;  p->y++;  p->z++;
b = *p;
```

# Lecture 5/3/18

## Memory

### Adressing Memory
- The byte address for an n-byte object must be divisible by N
- Within a byte is a bit-string (how it's interpreted depends on the data type)

## Text encoding

### ASCII
- 7-bit values, using lower 7-bits of a byte (top bit always 0)
- Can map between chars and ints in C

### Unicode (UTF-8)
- 8-bit values, with ability to extend to multi-byte values
- Can encode all human languages plus other symbols
- 32-bit values in a symbol

### Indexing a C array using chars
```c
for (char c = 'a'; c <= 'z'; c++) {
    freg[c-'a'] = 0;
}

for (char c = 'a'; c <= 'z'; c++) {
    printf("%s has freq %d\n", c, freq[c-'a']);
}
```
