Elyssa version 2.0
==================
Elyssa is a project to make a simple program that can solve (almost) any elementary physics problem.

##Features
- Full Single Object support
- Full unconditional Multiple Object support
- Partial conditional Multiple Object support (One condition currently)

I do agree the current console interface is not very user friendly, however, when GUI will be written, there won't be any problem. Anyway, let me introduce you to the Elyssa terminology.

##Terminology
**Object:** A real life object.It *might* have mass, energy, velocity etc, and interact with other objects.The `Single Object Mode` deals with only one object and its properties. The `Multiple Objects Mode` relates multiple objects and compare their properties. For example, if you need to find the final velocity of a car, use single object mode. But to find the recoil velocity of a gun from the momentum of the bullet fired, you have to enable multiple object mode.

**Knowns:** The problem statement specified quantities. In other words, their values are generously supplied by the problem statement.

**Unknown:** The quantity to be determined.

Consider the following problem: *A car accelerates steadily from rest at 4 m/s^2 for 3s. What is its final velocity?*
Here `u=0`, `a=4m/s^2` and `t=3s` are the **knowns** and `v` is the **unknown**.

**e Notation:** A widely used notation for scientific numbers. Here is the rule. `ax10^b` is written as `aeb`. If you are still confused, please look at the following two examples:

```
N=6.02x10^23=6.02e23
G=6.67259x10^-11=6.67259e-11
```

##How to Use
After running, the program writes *(S)ingle Object   (M)ultiple Objects* on the console and expects an input from you. Press `s` or `m` to  enable `Single` or `Multiple` object mode, respectively. 

###Single Object Mode
After pressing `s`, Elyssa will reply, *Number of knowns=* which is self-explanatory. Give her the number and she will tell you to write down the knowns one at a line. the format will be: 

`Known'sName <space> = <space> NumericValue`

For example, to input `a=4m/s^2`, write `a = 4`

**Note: all the inputs must be in SI units. Also, to input scientific numbers, you must use e notation.**

After that Elyssa will print `What to find=` and you have to write the name of the unknown.
The very next line should be the answer. :)

###Sample Problem
Let's solve the previous problem with Elyssa.

Problem: *A car accelerates steadily from rest at 4 m/s^2 for 3s. What is its final velocity?*

####Input
*(S)ingle Object   (M)ultiple Object*

`s`

*Number of Knowns*=`3`

*Write them one at a line*

```
u = 0
a = 4
t = 3
```

*What to find=* `v`
####Output
```
12
(N)ew    (Q)uit
```

If you press `n`, Elyssa will be ready for the next problem. And if you press `q`, the program will be terminated.
###Multiple Object Mode
This time Elyssa will reply, *Number of knowns(for the first object)=* and you have to write the number. And like before, Elyssa will say, `Write them one at a line`. Writing rules are same as previous, but this time you have to write the knowns with a suffixing `1` ie, for mass, write `m1` instead of `m`. 

Similarly write the knowns for the second object, with `2` as suffix.

After that Elyssa will ask if there are any other (algebraic) conditions, for example, like `v1 = v2`. If there are, press `y`, else press `n`.

If you press `y`, Elyssa will ask for the number of such conditions. **Current version supports only one condition.** So press `1` and write down the condition. The format will be:

`LHS <space> = <space> RHS <space>VariablesOfTheEquation (Each separated by a <space>)`

**The current version supports only two varibles. And one variable must be written as a function of other. Here is how it works:**

`v1 = v2+2 v1 v2` //This is valid. `v1`is written as a function of `v2`.

`v1-v2 = 2 v1 v2` //But this is  not. 

When you have written everything correctly, Elyssa will ask `What to find=`. Tell her the quantity's name. The following line should be the result.
####Sample Problem 1
*A 10g bullet is fired from a gun. If the recoil velocity is 5m/s and the mass of the gun is 2kg, find the velocity of the bullet.*

####Input
*(S)ingle Object  (M)ultiple Object*

`m`

*Number of Knowns (for the first object)=* `2`

*Write them one at a line*

```
m1 = 0.01
u1 = 0
```

*Number of Knowns (for the second object)*=`3`

```
m2 = 2
u2 = 0
v2 = 5
```

*Any other conditions?y/n*

`n`

*What to find=* `v1`

####Output
```
-1000
(N)ew (Q)uit
```

####Sample Problem 2
*One edge of a 1.2m copper rod of cross-sectional area 3cm^2 is embeded in 100C boiling water. If the other edge is embeded in 10g of 0C ice, find the necessary time for the ice to melt completely. Given that the thermal conductivity of copper is 385Wm^-1K^-1 and the latent heat of fusion of ice is 336000Jkg^-1.*

####Input
*(S)ingle object	 (M)ultiple objects*

`m`

*Number of knowns (for first object)=* `4`

*Write them one at a line*

````````
d1 = 1.2
A1 = 3e-4
delta_Theta1 = 100
K1 = 385
````````

*Number of knowns (for second object)=* `3`

*Write them one at a line*

````
l_f2 = 336000
m2 = 10e-3
/fusion2 = 1
`````

*Any other conditions?y/n*

`y`

*Number of conditions=*`1`

*Write them one at a line*

*Fromat: Equation <space> variable1 <space> variable2*

`Q1 = delta_Q2 Q1 delta_Q2`

*What to find=*`t1`

####Output
```
349.091
(N)ew	(Q)uit
```
##License
Elyssa is published under GPL version 3. See the `LICENSE` for details.
##The Author
Elyssa is designed, developed and maintained by Adib Hasan (Neehan).

[Contact with the developer](http://www.facebook.com/phlembac.hidden)
