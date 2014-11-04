##Parser 1.0 beta
This program parses a given given mathematical expression. Currently supports `+ - * / ^` and `()`.
###Definitions
####Unknown 
Stands for unknown variable like `x,y,z`. The default Unknown is `x`. Currently this beta version supports single unknown variable. If I get spare-time in future, which is highly unlikely, I might add multiple variable support.

####Known 
A variable that has a specific given value. For example, consider the following problem: "Given that `y=2, z=3,` evaluate `y^2+x*z`." The answer is `3x+4`. Here `x` is the Unknown, and `y` and `z` are Knowns. The default unknowns are `y=1` and `z=3`. Of course you can change the values of `y,z` or even add more knowns in the parser.ini.

####Expression
Whatever you want to evaluate. *Note*, even though I said whatever, I meant a *meaningful* expression. You can't just ask my program to evaluate `m^2*(x+3)` without defining m! Another thing to keep in mind. This is a beta version and I haven't included any error handling function. So DO NOT USE EXTRA BRACES, ROOTS, LOGARITHM, TRIGONOMETRIC (OR  ANY) FUNCTIONS. They'll put my program's deductive resaoning in a chaos and it 'may' behave in a way that even I don't understand.  To be more explicit, the following expressions are all malformed:

`x((x+3))/3`    //Extra braces

`x(1(x+3)/3`    //Braces are not properly closed

`sqrt(x^2)+1`   //Roots

`xy(x^2+1)`     //`xy` isn't separed by a `*`. So my program things `xy` is a variable. But it is not defined! <Brain Crashes> 
The correct version would be `x*y(x^2+1)` Note that you can omit the * operator only before or after a parenthesis. So writing x(x+1)(x+2) is completely valid.

###Sample input and output(s):

####Input

`x/(x-5)^4*(x+1)*0.25+y^2/x+z`

####Output

`+3x^5 -59x^4 +430.25x^3 -1349.75x^2 +1375x +625`

`------------------------------`

`+x^5 -20x^4 +150x^3 -500x^2 +625x`
