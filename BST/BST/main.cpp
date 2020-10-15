#include "BSTree.h"
#include <ctime>
using namespace std;

int main()
{
	clock_t clock_start, clock_end;
	double total_time;
	clock_start = clock();
	BSTree<int> bst(10);
	bst += 9;
	bst += 14;
	bst += 11;
	bst += 15;
	bst += 7;
	bst -= 7;

	bst.in_order();

	cout << "\n" << "bst的最大值：" << bst.maximum() << endl;
	cout << "bst的最小值：" << bst.minimum() << endl;
	clock_end = clock();
	total_time = (double)(clock_end - clock_start) / CLOCKS_PER_SEC;
	cout << "\n一共花费处理器时间：" << total_time << endl;
	return 0;
}