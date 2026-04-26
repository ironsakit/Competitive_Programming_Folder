/*Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.

Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.

Example 1:

Input: g = [1,2,3], s = [1,1]
Output: 1
Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
Example 2:

Input: g = [1,2], s = [1,2,3]
Output: 2
Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.
*/

#include <bits/stdc++.h>
using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s) {   // O(NlogN + MlogM) N = len(g) M = len(s)
    int children = g.size(), cookies = s.size(), count = 0, child = 0;
    sort(g.begin(), g.end());  // Prima li ordino
    sort(s.begin(), s.end());
    for(int cookie = 0; cookie < cookies && child < children; cookie++){
        if(g[child] <= s[cookie]){  // Così scorrendo i biscotti visto che sono entrambi ordinati non dovrò scorrerlo due volte il vettore dei bambini
            count++;                // Tanto se sono ordinati i biscotti precedenti non soddisferanno mai i bambini attuali
            child++;  // vado avanti coi bambini
        }
    }
    return count;
}

int main()
{
    vector<int> g = {1,2};
    vector<int> s = {1,2, 3};
    int count = findContentChildren(g, s);

    cout << count << endl; // 2
}