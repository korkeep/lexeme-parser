## lexeme-parser
> Simple parsing system implemented in C  

### front.in
```c
(sum + 47) / total
```

### front.c
```c
int main();           /* main: main driver */
int lookup(char ch);  /* lookup: lookup operators and parentheses and return the token */
void addChar();       /* addChar: add nextChar to lexeme */
void getChar();       /* getChar: get the next char of input and determine its class */
void getNonBlank();   /* getNonBlank: call getChar until it returns a non-whitespace char */
int lex();            /* lex: lexical analyzer for arithmetic expressions */
```

### Result
<img title="Result" alt="lexeme-parser" src="https://user-images.githubusercontent.com/20378368/173056618-2d11412b-51d2-410e-8d43-397a817e653c.png" width="300"/>