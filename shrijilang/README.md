# SHREE RADHE #
# shriji_lang

# ShrijiLang 🌸

ShrijiLang ek human-friendly programming language hai jo beginners ko programming ko step-by-step samjhane ke liye banayi gayi hai.

Iska janm traditional programming languages ko replace karne ke liye nahi hua tha. Iska objective tha programming ko samajhna, explain karna aur human language ke kareeb lana.

## Philosophy

ShrijiLang ka core idea simple hai:

* Ek problem
* Ek permanent solution
* Full testing
* Fir next problem

Language ka design bhi isi philosophy ko follow karta hai.

## Core Keywords

### Variable Declaration

```sri
mavi age = 20
mavi name = "Shri"
```

### Output

```sri
bolo "Namaste"
bolo age
```

### Conditions

```sri
agar age >= 18 {
    bolo "Adult"
} warna {
    bolo "Minor"
}
```

### Loops

```sri
jabtak count < 10 {
    bolo count
    count = count + 1
}
```

### Functions

```sri
rachna square(x) {
    wapas x * x
}
```

### Boolean Values

```sri
sahi
galat
```

## Current Capabilities

ShrijiLang currently supports:

* Variables
* Arithmetic expressions
* Comparisons
* Logical AND (&&)
* Logical OR (||)
* If / Else
* While loops
* Functions
* Recursion
* Lists
* Dictionaries
* Assignment updates
* Error reporting
* Example generation
* AI command routing

## Error System

ShrijiLang focuses heavily on beginner-friendly errors.

Instead of cryptic compiler messages, it attempts to explain:

* What went wrong
* Why it happened
* What the user should do next

Example:

Input:

```sri
bolo 10 20
```

Output:

```
Do values ke beech operator missing hai
```

This makes debugging easier for new learners.

## Architecture

Major layers:

* Lexer (token generation)
* Parser (AST generation)
* Runtime
* Interpreter
* Error Engine
* Fix Engine
* Intelligence Layer
* AI Router
* Grammar Registry
* Krst Output System

One important architectural decision is that printing is isolated from core execution logic.

Business logic performs computation.

Output is handled separately through the Krst layer.

## Development Philosophy

ShrijiLang was developed through multiple failed attempts.

Several language versions were abandoned before the current architecture emerged.

The project follows a stability-first mindset:

1. Build
2. Crash
3. Learn
4. Redesign
5. Stabilize

Every major crash resulted in architectural improvements.

## Target Users

Primary target:

* Beginners
* Students
* Self learners

The goal is not to create the fastest language.

The goal is to create a language that is easier to understand.

## Current Status

The language is actively evolving.

Recent milestones include:

* Operator error family
* Missing operand detection
* Missing operator detection
* Logical expression support
* Boolean support
* Function system improvements

Focus remains on stability before expansion.

## Vision

ShrijiLang aims to become a small but complete learning ecosystem where a new learner can understand programming concepts without needing to fight compiler complexity from day one.

The project prioritizes clarity over cleverness.

Because understanding comes before optimization.

