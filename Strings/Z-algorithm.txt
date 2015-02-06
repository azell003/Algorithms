#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

/*
Author: Alfredo Zellek

Z-algorithm: This allows us to compute the z-function for some text T, where z is defined as: 

z[i] = longest substring starting at position i > 0, such that it is also a prefix of T.

We also define a z-box to be the start and end of a z-substring (a substring that satisfies the z-function definition). 
Thus a z-box is defined by a pair of numbers (L, R). Where L and R are the Left and Right bounds of the z-box respectively. 

To compute the z-function at position i, we assume that we've calculated the values for z[1],...,z[i - 1] and we have the
(L, R) of the rightmost z-box. Then, we compute the z-function in one pass of the string.

We have a few cases to deal with:

Case 1: What if i > R? that is, what if the value we want to calculate is outside the rightmost z-box?
 	     ___________            
	    |           |        
------------+-----------+---------------
            L           R     i

Then we can't use the z-box to help us out at all. We need to do character by character comparison of the substring
starting at i with the prefix of the string. (i.e. compare s[0...] with s[i...])
Here we set L = i and R = i + (length of match). 

Case 2: What if i is inside the rightmost z-box? we have a few cases to cover here, but first some definitions. 

Let i' be the position in the prefix z-box that corresponds with the position of i in the rightmost z-box, as shown below. 
From this we can see that: 

i' = i - L

Let B be the substring that goes from position i (and by definition i') to the end of the z-box. The length of B is then 

|B| = R - i + 1

 ______________            ______________
|  B  |  |  B  |y         |        |  B  |x
+--------------+----------+--------------+----
         i'               L        i     R


so, if i is inside the z-box, we have i' we can compare it to. 

Case 2a: What if z[i'] < |B|? Then z[i] = z[i']

In this case, z[i'] is completely inside the z-box, and since the prefix z-box is a copy of the rightmost z-box, we must 
have that z[i] = z[i'].
Here, we leave L and R unchanged. We don't make a larger z-box. 

case 2b: What if z[i'] > |B|? Then z[i] = |B| = R - i + 1

Here we have the case that z[i'] is larger than |B| and so extends outside of the z-box, and, of course, matches the prefix.
Consider that the character right after the prefix z-box to be y, and the one right after the rightmost z-box to be x.
If x = y, then we should have a larger z-box, and the R value we have should be larger, but it is not! so, x =/= y. 
So, we only have a match from i to R - i + 1. hence, z[i] = R - i + 1.
Here, we set L = i and R = |B|.

case 2c: what if z[i'] = |B|? We need to do character by character comparision after the initial matching of size |B|.

 ______________            ______________
|  B  |w |  B  |y         |        |  B  |x
+--------------+----------+--------------+----
         i'               L        i     R

As in case 2b, consider x, y, z to be the values after the rightmost z-box, the prefix z-box, and the matching prefix.
Then, since z[i'] = |B|, we must have w =/= y, and we must also have y =/= x (by the same argument in case 2b). But 
what about the relation between x and w? we don't know! we must do a character by character comparison to determine z[i].
Here, we set L = i and R = |B|, and do comparison. 

*/

string s;
int z[100001];

void Zbuild(int len)
{
	int L = 0, R = 0;
	for(int i = 1; i < len; i++)
	{
		if(i > R)
		{
			L = R = i; 
			while(R < len && s[R] == s[R - L]) R++;
			z[i] = R - L; 
			R--;
		}
		else
		{
			int ip = i - L, B = R - i + 1;
			if(z[ip] < B) 
				z[i] = z[ip];
			else
			{
				L = i;
				while(R < len && s[R] == s[R - L]) R++;
				z[i] = R - L;
				R--; 
			}
		}
	}
}

void Zbuild2(int len)
{
	int L = 0, R = 0;
	for(int i = 1; i < len; i++)
	{
		if(i > R || z[i - L] >= R - i + 1) 		
		{
			L = i;
			R = max(R, i);
			while(s[R] == s[R - L]) R++;
			z[i] = R - L;
			R--;
		}
		else 
			z[i] = z[i - L];
	}
}

int main()
{
	cin >> s; 
	string P = "aba";
	s = P + "#" + s;
	int len = s.length(), lenp = P.length();
	Zbuild(len);
	for(int i = lenp; i < len; i++)
		if(z[i] == lenp)
			printf("Match found at %d\n", i - lenp - 1);
			
	return 0;
}
