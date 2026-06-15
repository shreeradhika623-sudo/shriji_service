# ShrijiLang

ShrijiLang ek educational programming language hai jo programming concepts ko simple aur readable syntax ke saath present karti hai.

Language ka focus learning, experimentation aur concept understanding par hai.

---

# Features

* Variables
* Arithmetic Operations
* Conditions
* Loops
* Functions
* Lists
* Dictionaries
* JSON Support
* CSV Support
* HTTP Support
* Import System

---

# Keywords

| Keyword | Purpose              |
| ------- | -------------------- |
| mavi    | Variable declaration |
| agar    | If condition         |
| warna   | Else condition       |
| jabtak  | While loop           |
| rachna  | Function declaration |
| wapas   | Return value         |
| bolo    | Output               |
| lao     | Import module/file   |
| do      | Export               |
| sahi    | Boolean true         |
| galat   | Boolean false        |
| nahi    | Logical NOT          |
| rukja   | Break loop           |
| chalu   | Continue loop        |

---

# Operators

## Arithmetic

```text
+
-
*
/
%
++
--
```

## Comparison

```text
==
!=
>
<
>=
<=
```

## Logical

```text
&&
||
!
```

## Assignment

```text
=
```

---

# Built-in Data Types

## Number

```sri
mavi age = 18
```

## String

```sri
mavi name = "Hukum"
```

## Boolean

```sri
mavi active = sahi
```

## List

```sri
mavi items = [
    "Laptop",
    "Mouse",
    "Keyboard"
]
```

## Dictionary

```sri
mavi user = {
    "naam": "Shriji",
    "city": "Dongargarh"
}
```

---

# Functions

## User Function

```sri
rachna add(a, b) {

    wapas a + b

}
```

---

# List Functions

```text
ginti()
hatao()
```

Example:

```sri
mavi items = ["A", "B", "C"]

bolo ginti(items)

items = hatao(items, "B")
```

---

# Dictionary Functions

```text
keys()
values()
```

Example:

```sri
bolo keys(user)
bolo values(user)
```

---

# JSON Functions

```text
json_padho()
json_parse()
```

Example:

```sri
mavi text = json_padho("student.json")

mavi data = json_parse(text)

bolo(data["naam"])
```

---

# Example

```sri
mavi age = 20

agar age >= 18 {

    bolo "Adult"

} warna {

    bolo "Minor"

}
```

---

# Status

Current implementation includes:

* Variables
* Conditions
* Loops
* Functions
* Lists
* Dictionaries
* JSON Support
* CSV Support
* HTTP Support
