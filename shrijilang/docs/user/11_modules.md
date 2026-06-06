# Modules and Imports

Version: 1.0

---

## Why Modules?

Jaise-jaise program bada hota hai, saara code ek file mein rakhna mushkil ho jata hai.

Modules code ko alag files mein organize karne ki suvidha dete hain.

---

## Exporting A Function

Function ko dusri files ke liye available karne ke liye `do` use kiya jata hai.

Example:

```sri
rachna square(x) {

    wapas x * x

}

do square
```

---

## Exporting A Variable

```sri
mavi PI = 3.14

do PI
```

---

## Important Rule

Export karne se pehle symbol declare hona chahiye.

Correct:

```sri
mavi PI = 3.14

do PI
```

Incorrect:

```sri
do PI

mavi PI = 3.14
```

---

## Importing A Module

File:

```sri
rachna square(x) {

    wapas x * x

}

do square
```

Main Program:

```sri
import "math_lib.sri"

bolo square(5)
```

Output:

```text
25
```

---

## Multiple Exports

Module:

```sri
rachna square(x) {

    wapas x * x

}

do square

rachna cube(x) {

    wapas x * x * x

}

do cube
```

Program:

```sri
import "math_lib.sri"

bolo square(5)
bolo cube(3)
```

Output:

```text
25
27
```

---

## What Did We Learn?

* `do` symbol export karta hai
* `import` file load karta hai
* Export declaration ke baad aata hai
* Multiple functions export ki ja sakti hain

---

## Next Step

Continue to:

12_standard_library.md
