# emoticon-language

#### A really unintuitive language where everything is done with emoticons...

Not much is implemented right now, but basic integer assignment and comments are working.

Example:
```
(#_#) single line comment

(#_#)--* 
      this is a multi-line comment
*--(#_#) 

o \(^-^)/ 5   (#_#) Assignment: o = 5  untyped integer creation 

[>*_*]>--*    (#_#) Function definition 

    O \(^-^)/ 5    

*--<[*_*<]

[>*_*]> (#_#) Function call
```

Will produce in a c file:
```
int o = 5 ;

void a322902113347406966() {
  int O = 5 ;
}

a322902113347406966();
```
Function calls produce jumbled up c-function names because the name "*_*" wouldn't compile. So my easy solution is just to hash the string and use that as the name in c. 
