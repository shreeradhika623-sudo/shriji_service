# Standard Library

Version: 1.0

---

## Introduction

ShrijiLang kuch built-in utility functions provide karti hai jo lists aur dictionaries ke saath kaam karna simple banati hain.

---

## Length Functions

### ginti()

List ke elements ki sankhya return karta hai.

```sri
mavi nums = [10, 20, 30]

bolo ginti(nums)
```

Output:

```text
3
```

### count()

`ginti()` ka English alias.

```sri
mavi nums = [10, 20, 30]

bolo count(nums)
```

Output:

```text
3
```

---

## Dictionary Functions

### keys()

Dictionary ki saari keys return karta hai.

```sri
mavi user = {
    "name": "Radhe",
    "age": 25
}

bolo keys(user)
```

Output:

```text
[name, age]
```

---

### maan()

Dictionary ke values return karta hai.

```sri
mavi user = {
    "name": "Radhe",
    "age": 25
}

bolo maan(user)
```

Output:

```text
[Radhe, 25]
```

---

### moolya()

`maan()` ka Hindi alias.

```sri
mavi user = {
    "name": "Radhe",
    "age": 25
}

bolo moolya(user)
```

Output:

```text
[Radhe, 25]
```

---

### values()

`maan()` ka English alias.

```sri
mavi user = {
    "name": "Radhe",
    "age": 25
}

bolo values(user)
```

Output:

```text
[Radhe, 25]
```

---

## List Functions

### hatao()

List se element remove karke nayi list return karta hai.

```sri
mavi nums = [10, 20, 30, 40]

nums = hatao(nums, 20)

bolo nums
```

Output:

```text
[10, 30, 40]
```

---

### remove()

`hatao()` ka English alias.

```sri
mavi nums = [10, 20, 30, 40]

nums = remove(nums, 20)

bolo nums
```

Output:

```text
[10, 30, 40]
```

---

## What Did We Learn?

* `ginti()` aur `count()` list length dete hain
* `keys()` dictionary keys return karta hai
* `maan()`, `moolya()` aur `values()` dictionary values return karte hain
* `hatao()` aur `remove()` nayi list return karte hain
* Hindi aur English dono aliases supported hain

---

## Next Step

Continue to:

13_examples.md
