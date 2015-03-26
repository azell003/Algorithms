/*
Author: Alfredo Zellek

Brief Description of Fenwick Tree (Summary of Peter M. Fenwick's paper)

Idea: An integer can be expressed as the sum of the appropriate powers of 2, so we should also be able to 
express a cumulative sum as the sum of a set of appropriate 'subfrequencies'. 

We base the subfrequency size on the least significant bit of the index we're looking at. For example, 
for index i = 6, we have that 6 in binary is 110. Here, the least significant bit occurs at position 1
and contributes 2^1 = 2 to the number 6. Hence, it will also contribute the sum of 2 values to our cumulative frequency.

In other words, The cumulative subfrequency stored at each index i is equivalent a[i - 2^k + 1] + ... + a[i]
where k is position of the least significant bit in i. (Since each node stores the value of 2^k items from the original list)

This indexing method allows us to compute cumulative sums for any index in logarithmic time. We simply choose an index
we want to sum up to, let's say 6, add the value we have at that index to our total (total = a[5..6]), strip the least
significant digit to get 4 as our new index, and repeat until we hit 0 as our index. (total = a[1...4] + a[5..6])
Hence, we've computed the cumulative sum up to 6. 

how about updating? to update we just choose the index we want to update, and update the tree in a way such that all the 
nodes that would be affected by the updated index get updated as well. We just reverse the operation we did for doing 
the cumulative sum. Instead of subtracting the least significant bit, we add it. This hits all the nodes that need
to be updated.

The cumulative sum and updating methods actually create two symmetric trees on the same set of data. One for updating, and
one for cumulative sums. (the updating tree is a mirror image of the cumulative sum tree)
*/

#include <iostream>
using namespace std;

const int N = 10000;

int n, tree[N]; // indexed starting at 1

void update(int idx, int val)
{
	while(idx <= n)
	{
		tree[idx] += val;
		idx += idx & (-idx);
	}
}

// Range Sum Query from 1 to idx
int get(int idx)
{
	int res = 0; 
	while(idx > 0)
	{
		res += tree[idx];
		idx -= idx & (-idx);
	}
	return res;
}

int rsq(int a, int b)
{
	return get(b) - get(a - 1);
}

int main() 
{
	n = 5;
	update(1, 1);
	update(2, 2);
	update(3, 3);
	cout << get(3) << endl;
	return 0;
}
