#Elyssa 1.5
Elyssa is a project to make simple program that can solve elementary physics problems.

##Features
- Full Single Object support
- Full unconditional Multiple Object support
- Partial conditional Multiple Object support (One condition currently)

##How to use:
Well, I do agree the current console interface is not very user friendly, however, when GUI will be written, there won't be any problem. Anyway, letme introduce you to the Elyssa terminology.

###Terminology
**Object:** A real life object.It *might* have mass, energy, velocity and interact with other objects.The `Single Object Mode` deals with only one object and its properties. The `Multiple Objects Mode` relates multiple objects and compare their properties. For example, if you need to find the velocity of a car, use single object mode. But if you want this program to find the recoil velocity of a gun, you have to enable multiple object mode.

**Knowns:** The problem statement specified quantities. In other words, their values are generously supplied by the problem statement.
**Unknown:** The quantity to be determined.

Consider the following problem: *A car accelerates steadily from rest at 4 m/s^2 for 3s. What is its final velocity?*
Here `u=0`, `a=4m/s^2` and `t=3s` are the **knowns** and `v` is the **unknown**.

###Course of events
After running, the program writes *(S)ingle Object   (M)ultiple Objects* on the console and expects an input from you. Press `s` or `m` to  enable `Single` or `Multiple` object mode, respectively. 

###Single Object Mode

###Sample Problem
*A 10g bullet is fired from a gun. If the recoil velocity is 5m/s and the mass of the gun is 2kg, find the velocity of the bullet.*

####Input
*Number of Knowns*=`5`

*Write them one at a line*

`m1 = 0.01`

`m2 = 2`

`u1 = 0`

`u2 = 0`

`v2 = 5`

*What to find=* `v1`

####Output
*-1000*



*(N)ew (Q)uit*
