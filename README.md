	KMP算法是用于在主字符串中快速查找模式字符串的算法。
	它的快速表现在它具有跳跃式的移动模式字符串并与主串字符比较的特点，在某种情况下这比传统的一格一格地移动模式字符串并于主串字符比较的速度快很多。
	所谓的某种情况指的是仅当模式串于主串之间存在许多部分匹配的情况。
	KMP算法的最大特点是指示主串的指针不需要回溯，整个匹配过程中对主串仅需从头至尾扫描一遍，无需回头重读。
	下面举一个例子来大致了解一下KMP是如何匹配模式串的：
	例如，主串：ababcabcacbab，模式串：abcac。
	第一趟匹配：
		ababcabcacbab
		abc
		第一次匹配都是从头开始的匹配，此时可以看到模式串中的第3个字符和主串中的第3个字符已经匹配不上了。
		设定变量i用来指示主串中于模式串中不匹配的字符的位置，此时i=3。
		设定变量j用来指示模式串中和主串不同字符的位置，此时j=3.
	第二趟匹配，模式串整体向右移动，使得模式串的开头的a对齐主串中i=3的位置：
		ababcabcacbab
		  abcac
		此时可以发现主串中第7个位置的‘b'和模式串中的’c'不匹配，此时i=7，j=5
	第三趟匹配，模式串再向右移动，使得模式串中的‘b'对准主串中i=7的位置：
		ababcabcacbab
		     abcac
		此时发现模式串能完全匹配到主串中的内容了。此时i=11，j=6  
	于是问题来了，当主串中第i个字符和模式串中第j个字符不匹配时，模式串应该向右移动多少个格子呢？为回答这个问题就先看一下这个推论：
	假设主串为s(1)s(2)...s(n)，模式串为p(1)p(2)...p(m)，其中(i)代表下标i。
	如果出现s(i)<>p(j)时，假设此时存在第k(k<j)个字符，模式串向右移动使得第k个字符应该和主串中第i个字符进行比较，那么必定存在：
		p(1)p(2)...p(k-1)==s(i-k+1)s(i-k+2)...s(i-1)					(formula 1)
	而已经得到的部分匹配的结果是：
		p(j-k+1)p(j-k+2)...p(j-1)==s(i-k+1)s(i-k+2)...s(i-1)			(formula 2)
	于是可以得到这样的等式：
		p(1)p(2)...p(k-1)==p(j-k+1)p(j-k+2)...p(j-1)					(formula 3)
	若令next[j]=k，则next[j]表明当模式串中第j个字符和主串中第i个字符不匹配后在模式串中需要和主串中第i个字符继续比较的位置。
	接下来的问题是如何计算next[j]的值呢？首先确定一下next[1]等于多少。
	当j=1时，也就是j指示的是模式串中第一个字符。如果模式串中的第一个字符就已经无法和主串中的第i个字符匹配的时候，这时模式串中不可能存在第k(k<1)的字符和主串中第i个字符继续比较，所以能得到如下等式：
		next[1]=0														(formula 4)
	此时该做的是主串中的i=i+1，然后模式串中第1个字符再和主串中现在的第i个字符继续比较。
	如果此时已经知道next[j]=k，又该如何计算next[j+1]值呢？这要分2种情况来讨论：
	情况1---p(k)==p(j)：
		由(formula 3)的等式可以得到如下等式：
			p(1)p(2)...p(k-1)p(k)==p(j-k+1)p(j-k+2)...p(j-1)p(j)
		由此可知如果p(j+1)不能和主串中的i位置的字符匹配的话，必定要把模式串中p(k+1)和主串中i位置的字符继续比较，因为模式串中从1到k的字符都能匹配主串中第i个字符前的k个字符。所以能得到如下等式：
			next[j+1]=next[j]+1											(formula 5)
	情况2---p(k)<>p(j):
		这就说明在模式串中存在不等式：
			p(1)p(2)...p(k)<>p(j-k+1)p(j-k+2)...p(j)
		此时已经存在了p(1)p(2)...p(k-1)==p(j-k+1)p(j-k+2)...p(j-1)。当涉及到模式串中元素互相比较的情形，我们也可以同时把模式串当成主串看待。
		当p(j)<>p(k)时应将模式向右滑动至以模式中的第next[k]个字符和主串中的第j个字符相比较。
		若next[k]=k'，且p(j)==p(k')，则说明在主串中第j+1个字符之前存在一个长度为k'的最长子串和模式串中从首字符开始长度为k'的子串相等，即：
			p(1)...p(k')==p(j-k'+1)...p(j)		(1<k'<k<j)				(formula 6)
		这就是说next[j+1]=k'+1，即：
			next[j+1]=next[k]+1											(formula 7)
		同理，若p(j)<>p(k')，则将模式继续向右滑动直至将模式中第next[k']个字符和p(j)对齐，......，以次类推，直至p(j)和模式中某个字符匹配成功为止，若找到的话就能知道：
			next[j+1]=next[next[...k]...]+1								(formula 8)
		若递归查找到最后还是不存在任何k'(1<k'<j)满足等式(formula 6)，也就是最后终止于next[1]==0，则：
			next[j+1]=1													(formula 9)
	通过以上对next[j+1]计算的总结（关注formula 4、5、7、8、9），我们可以通过一个例子来计算模式中每一个字符位置对应的next值。例如：
		j：		1	2	3	4	5	6	7	8
		模式：		a	b	a	a	b	c	a	c
		经过计算得到：
		next[j]：	0	1	1	2	2	3	1	2
	解释：
		首先next[1]=0
		然后由于next[1]==0，根据(formula 9)，得出next[2]=1
		然后p(2)==b，next[2]==1，p(1)==a，p(2)<>p(1)，next[1]==0，根据(formula 9)，得出next[3]=1
		然后p(3)==a，next[3]==1，p(1)==a，p(3)==p(1)，根据(formula 5)，得出next[4]=2
		然后p(4)==a，next[4]==2，p(2)==b，p(4)<>p(2)，next[2]==1，p(1)==a，p(4)==p(1)，根据(formula 7或8)，得出next[5]=next[next[4]]+1=next[2]+1=1+1=2
		然后p(5)==b，next[5]==2，p(2)==b，p(5)==p(2)，根据(formula 5)，得出next[6]=next[5]+1=2+1=3
		然后p(6)==c，next[6]==3，p(3)==a，p(6)<>p(3)，next[3]==1，p(1)==a，p(6)<>p(1)，next[1]==0，根据(formula 9)，得出next[7]=1
		然后p(7)==a，next[7]==1，p(1)==a，p(7)==p(1)，根据(formula 5)，得出next[8]=next[7]+1=1+1=2
	尽管KMP算法匹配模式串的时间复杂度已经达到O(n+m)，比传统的O(n*m)要好得多（其中m是模式串的长度，n是主串的长度），然而有一种情况还需要优化算法，例如模式串为aaaab和主串为aaabaaaab的情况。
	根据KMP算法很容易得出：
		j：		1	2	3	4	5
		模式：		a	a	a	a	b
		next[j]：	0	1	2	3	4
		由于主串中i==4的位置和模式中j==4的位置的字符不相等，由next[j]的指示还需要分别进行i==4跟j==3,j==2,j==1这3次比较。
		实际上，因为模式中第1、2、3个字符和第4个字符都相等，因此不需要再和主串中第4个字符相比较，可以直接进行i==5和j==1时的字符比较。
		优化方案：由next[j]==k，如果p(j)==p(k)，那就直接next[j]=next[k]，其实就相当于j=next[j]。优化后得到nextval结果如下：
		j：		1	2	3	4	5
		模式：		a	a	a	a	b
		next[j]：	0	1	2	3	4
		nextval[j]：	0	0	0	0	4

	所以在编写KMP算法时重点是要实现模式串中的nextval的计算过程。

