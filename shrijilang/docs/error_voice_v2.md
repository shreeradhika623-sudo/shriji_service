SHRI ERROR VOICE V2

RULE 1
User galat nahi hai.
Shri ko input samajhne me dikkat hui hai.

BAD:
Syntax Error

GOOD:
Mujhe ye line samajhne me dikkat hui.

------------------------------------------------

RULE 2
Problem se pehle recovery.

BAD:
Variable define nahi hai

GOOD:
Mujhe ye variable abhi tak nahi mila.
Pehle ise bana lete hain.

------------------------------------------------

RULE 3
Compiler tone nahi.
Guide tone.

BAD:
Invalid token

GOOD:
Ye symbol mujhe samajh nahi aaya.

------------------------------------------------

RULE 4
Har error ka goal:
User ko next step batana.

Error
↓
Explanation
↓
Recovery

------------------------------------------------

RULE 5
Shri user ke opposite side nahi hai.

Wrong:
User vs Compiler

Correct:
User + Shri vs Problem

CURRENT AUDIT STATUS

REVIVED

1.
E_PARSE_EMPTY_EXPRESSION
STATUS: ACTIVE

Before:
bad token

After:
empty expression

--------------------------------

2.
E_PARSE_BRACKET_EXTRA
STATUS: ACTIVE

Before:
bad token

After:
extra closing bracket

--------------------------------

3.
E_RUNTIME_UNDEFINED_VAR
STATUS: ACTIVE

Before:
E_ASSIGN_01 bucket

After:
Dedicated runtime bucket

--------------------------------

WRONG DIAGNOSIS FIXED

1.
List EOF

Before:
expected ','

After:
missing ]

--------------------------------

2.
Dict EOF

Before:
expected ','

After:
missing }

--------------------------------

VOICE PHILOSOPHY

User ne galti nahi ki.

User ne input diya.

Agar Shri samajh nahi paayi,
to Shri explain karegi,
recovery batayegi,
aur next step degi.

Model:

User + Shri
vs
Problem

NOT

User
vs
Compiler
