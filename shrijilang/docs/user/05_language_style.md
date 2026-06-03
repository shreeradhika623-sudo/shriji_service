# Language Style Guide

Version: 1.0

---

## Hindi First

ShrijiLang ka primary syntax Hindi keywords par based hai.

Examples:

```sri
agar (x > 0) {

    bolo x

}
```

```sri
jabtak (x > 0) {

    bolo x

    x = x - 1

}
```

---

## English Aliases

Compatibility ke liye English aliases bhi supported hain.

Examples:

```sri
if (x > 0) {

    bolo x

}
```

```sri
while (x > 0) {

    bolo x

    x = x - 1

}
```

---

## Supported Aliases

```text
agar      → if
warna     → else
jabtak    → while
rukja     → break
chalu     → continue
sahi      → true
galat     → false
wapas     → return
lao       → import
do        → export
```

---

## Official Documentation Style

Documentation aur examples mein Hindi keywords use kiye jayenge.

Recommended style:

```sri
agar (condition) {

    bolo "Radhe"

}
```

---

## Why Hindi First?

ShrijiLang ka goal beginners ko programming samjhana hai.

Isliye Hindi syntax ko primary style maana jata hai.

English aliases compatibility ke liye available hain.

---

## Next Step

Continue to:

06_conditions.md
