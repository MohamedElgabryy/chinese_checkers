******************programing language*******************
C++

**********************INPUT SAMPLE**********************
15 5 13 7
13 7 12 7
15 6 11 8
11 8 10 9
17 5 9 10

********************** Minimax **********************
Calculating The Minimax Score Idea: -
1- we are getting the node cord (i.e., the peak Node)
which is opposite to the color who will currently
playing.

2- then we calculate for each ball of the currently
playing color, the distance between it and the cord 
we have already got from step 1.

3-Doing Sum Operation for every abs result we got
from step 2.

Note: We are taking in consideration while calculating
the distance that if the colors was red, green, yellow,
Orange we will use Rows for calculating distance
otherwise, we are using columns.

4-Repeat the three steps for the other color.

5- Getting the difference of both results.
Conclusion 
Sum(abs(Node.Cord - ItsOppositePeekNode.cord) – Sum(abs(OpponentNode.Cord - ItsOppositePeekNode.cord)).

You can Check This in GetHowFar Function.
To Optimize the Game, we Used Alpha-Beta Pruning Algorithm, also we only getting the valid move in calculating the scores.