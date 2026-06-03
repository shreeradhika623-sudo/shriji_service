# Conditions

Version: 1.0

---

## What Are Conditions?

Conditions program ko decision lene mein madad karti hain.

ShrijiLang mein conditions likhne ke liye `agar` aur `warna` keywords use kiye jaate hain.

---

## Basic Condition

```sri
mavi age = 20

agar (age >= 18) {

    bolo "Adult"

}
```

Output:

```text
Adult
```

---

## If Else

```sri
mavi age = 15

agar (age >= 18) {

    bolo "Adult"

} warna {

    bolo "Minor"

}
```

Output:

```text
Minor
```

---

## Comparison Operators

```text
==    Equal To
!=    Not Equal To
>     Greater Than
<     Less Than
>=    Greater Than Or Equal To
<=    Less Than Or Equal To
```

---

## Even Or Odd Example

```sri
mavi x = 8

agar (x % 2 == 0) {

    bolo "EVEN"

}

agar (x % 2 != 0) {

    bolo "ODD"

}
```

Output:

```text
EVEN
```

---

## What Did We Learn?

* `agar` decision leta hai
* `warna` alternative path deta hai
* Comparison operators conditions mein use hote hain

---

## Next Step

Continue to:

07_loops.md
