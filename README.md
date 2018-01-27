# Circuit-Simulator
Read input variable into an array
Read output variable into an array
Read logic symbol and store the operation into the corresponding temp variable – using linked list
(always use linked list)

1.	Read the input variable and output variable from variable file, store them into linked list
2.	Get the value of the input from the data file.
3.	Close variable file, then read it again, jump the first two lines
4.	Do the evaluation based on the relation:
a.	AND: valueOf(a)&valueOf(b)
b.	OR: valueOf(a)|valueOf(b)
c.	NOT: ~valueOf(a)
d.	MUX: store first num into index;  
create a int boolean[index] to store the Boolean number;
Read the next index number and store them into Boolean array;
Generate gray code
Get the value of the function based on the gray code
e.	DECODER: 
i.	Read the first value
ii.	Create a corresponding Boolean array
iii.	Generate a gray code based on the first value
iv.	Based on the Boolean array and the gray code, get value to the variable.
