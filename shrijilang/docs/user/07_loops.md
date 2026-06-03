# Loops

Version: 1.0

---

## What Is A Loop?

Loop ek block of code ko baar-baar chalata hai.

ShrijiLang mein loops ke liye `jabtak` keyword use hota hai.

---

## Basic Loop

```sri
mavi x = 3

jabtak (x > 0) {

    bolo x

    x = x - 1

}
```

Output:

```text
3
2
1
```

---

## How It Works

Step 1:

```text
x = 3
```

Step 2:

```text
3 print hua
```

Step 3:

```text
x = 2
```

Step 4:

```text
2 print hua
```

Step 5:

```text
x = 1
```

Step 6:

```text
1 print hua
```

Condition false hone par loop ruk jata hai.

---

## Loop With Condition

```sri
mavi x = 0

jabtak (x < 3) {

    bolo x

    x = x + 1

}
```

Output:

```text
0
1
2
```

---

## What Did We Learn?

* `jabtak` loop start karta hai
* Condition true hone tak loop chalta hai
* Variable update karna zaroori hota hai

---

## Next Step

Continue to:

08_functions.md
