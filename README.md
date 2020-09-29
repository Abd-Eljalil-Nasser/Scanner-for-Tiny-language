# Scanner for Tiny language
## Requirments 
- C++ 
- Qt creator 
## Description
The scanning, or lexical analysis, phase of a compiler has the task of reading the source program as a file of characters and dividing it
up into tokens.

### Tokens of the TINY language

#### Reserved Words
###### if                  
###### then                
###### else                
###### end
###### repeat
###### until
###### read
###### write
#### Special Symbols
###### +
###### -
###### *
###### /
###### =
###### <
###### (
###### )
###### ;
###### :=

#### Other 
###### number (1 or more digits)
###### identifier (1 or more letters)

### TINY has the following lexical conventions:
- Comments are enclosed in curly brackets {...}
- White space consists of blanks, tabs, and newlines.

## input 
TINY language snippet code ( multiple lines of code written in TINY language syntax).

## output 
List of ( tokenvalue, tokentype)
### tokentype for all tokens 
###### if     -> IF
###### then   -> THEN         
###### else   -> ELSE
###### end    -> END
###### repeat -> REPEAT
###### until  -> UNTIL
###### read   -> READ
###### write  -> WRITE
###### +      -> Plus
###### -      -> Minus
###### *      -> Multiply 
###### /      -> Division
###### =      -> Equal
###### <      -> Smaller than 
###### (      -> Open Bracket 
###### )      -> Close Bracket 
###### ;      -> Semicolon
###### :=     -> Assign

#### Example:
x , Identifier

:=, assign

4,number

### Test 
