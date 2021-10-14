#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
using namespace std;

#define BACKPACK_SPACE 275
#define DNA 12

int value[10] = { 6,7,8,9,10,11,12,13,14,15 };
//string name[10] = { "apple","banana","pineapple","coconut","grape","guava","lemon","orange","kiwi","papaya" };
int space[10] = { 1,2,3,4,5,6,7,8,9,10 };
int decision[DNA][10], decision2[DNA][10];
int sum_value[DNA];
int sum_space[DNA];
int best1_index = -1, best2_index = -1, best1 = 0, best2 = 0;
int best3_index = -1, best4_index = -1, best3 = 0, best4 = 0;
int best5_index = -1, best6_index = -1, best5 = 0, best6 = 0;
int times = 100;

void initialization()
{
	cout << "Initialization :\n\n";
	for (int i = 0; i < DNA; i++)
	{
		cout << "i = " << i << "\n";
		for (int j = 0; j < 10; j++)
		{
			decision[i][j] = rand() % 11;
			cout << decision[i][j] << " ";
			if (decision[i][j] > 0)
			{
				sum_space[i] += space[j]*decision[i][j];
				sum_value[i] += value[j]*decision[i][j];
			}
		}
		cout << endl;
		cout << "sum_space :" << sum_space[i] << "\n";
		cout << "sum_value :" << sum_value[i] << "\n";
		if (sum_space[i] > BACKPACK_SPACE)
		{
			cout << "-------------nope--------------\n";
			sum_space[i] = 0;
			sum_value[i] = 0;
			i--;
		}

	}
	//cout << "\n";
}

void fitness()
{
	cout << "Fitness :" << "\n\n";
	for (int i = 0; i < DNA; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (decision[i][j] > 0)
			{
				sum_space[i] += space[j] * decision[i][j];
				sum_value[i] += value[j] * decision[i][j];
			}
		}
		if (sum_space[i] > BACKPACK_SPACE)
		{
			sum_value[i] = 1;
		}
		cout << "sum_space :" << sum_space[i] << "\n";
		cout << "sum_value :" << sum_value[i] << "\n";
	}
	//cout << "\n";
}

void choose()
{

	for (int i = 0; i < DNA; i++)
	{
		if (best1 < sum_value[i])
		{
			best1 = sum_value[i];
			best1_index = i;
		}
	}

	cout << "best1 :" << best1 << "\n";
	cout << "best1_index :" << best1_index << "\n";

	for (int i = 0; i < DNA; i++)
	{
		if (best2 < sum_value[i] && i != best1_index)
		{
			best2 = sum_value[i];
			best2_index = i;
		}
	}

	cout << "best2 :" << best2 << "\n";
	cout << "best2_index :" << best2_index << "\n\n";

	for (int i = 0; i < DNA; i++)
	{
		if (best3 < sum_value[i] && i != best1_index && i != best2_index)
		{
			best3 = sum_value[i];
			best3_index = i;
		}
	}

	cout << "best3 :" << best3 << "\n";
	cout << "best3_index :" << best3_index << "\n\n";

	for (int i = 0; i < DNA; i++)
	{
		if (best4 < sum_value[i] && i != best1_index && i != best2_index && i != best3_index)
		{
			best4 = sum_value[i];
			best4_index = i;
		}
	}

	cout << "best4 :" << best4 << "\n";
	cout << "best4_index :" << best4_index << "\n\n";

	for (int i = 0; i < DNA; i++)
	{
		if (best5 < sum_value[i] && i != best1_index && i != best2_index && i != best3_index && i!= best4_index)
		{
			best5 = sum_value[i];
			best5_index = i;
		}
	}

	cout << "best5 :" << best5 << "\n";
	cout << "best5_index :" << best5_index << "\n\n";

	for (int i = 0; i < DNA; i++)
	{
		if (best6 < sum_value[i] && i != best1_index && i != best2_index && i != best3_index && i != best4_index && i != best5_index)
		{
			best6 = sum_value[i];
			best6_index = i;
		}
	}

	cout << "best6 :" << best6 << "\n";
	cout << "best6_index :" << best6_index << "\n\n";
}

void crossover()
{
	cout << "Crossover :\n\n";
	for (int i = 0; i < DNA; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i % 6 == 0)
			{
				decision2[i][j] = decision[best1_index][j];
				cout << decision2[i][j] << " ";
			}
			else if (i % 6 == 1)
			{
				decision2[i][j] = decision[best2_index][j];
				cout << decision2[i][j] << " ";
			}
			else if (i % 6 == 2)
			{
				decision2[i][j] = decision[best3_index][j];
				cout << decision2[i][j] << " ";
			}
			else if (i % 6 == 3)
			{
				decision2[i][j] = decision[best4_index][j];
				cout << decision2[i][j] << " ";
			}
			else if (i % 6 == 4)
			{
				decision2[i][j] = decision[best5_index][j];
				cout << decision2[i][j] << " ";
			}
			else if (i % 6 == 5)
			{
				decision2[i][j] = decision[best6_index][j];
				cout << decision2[i][j] << " ";
			}
			if (j == 9)
			{
				//cout << "\n";
			}
		}
	}
	//cout << "\n";

	for (int j = 5; j < 10; j++)
	{
		int tmp1 = -1, tmp2 = -1, tmp3 = -1;
		tmp1 = decision2[6][j];
		decision2[6][j] = decision2[7][j];
		decision2[7][j] = tmp1;

		tmp2 = decision2[8][j];
		decision2[8][j] = decision2[9][j];
		decision2[9][j] = tmp2;

		tmp3 = decision2[10][j];
		decision2[10][j] = decision2[11][j];
		decision2[11][j] = tmp3;
	}
}

void mutation()
{
	cout << "Mutation :\n\n";

	decision2[6][rand() % 10] = rand() % 11; 
	decision2[6][rand() % 10] = rand() % 11;
	decision2[6][rand() % 10] = rand() % 11;
	decision2[6][rand() % 10] = rand() % 11;
	decision2[7][rand() % 10] = rand() % 11;
	decision2[7][rand() % 10] = rand() % 11;
	decision2[7][rand() % 10] = rand() % 11;
	decision2[7][rand() % 10] = rand() % 11;
	decision2[8][rand() % 10] = rand() % 11;
	decision2[8][rand() % 10] = rand() % 11;
	decision2[8][rand() % 10] = rand() % 11;
	decision2[8][rand() % 10] = rand() % 11;
	decision2[9][rand() % 10] = rand() % 11;
	decision2[9][rand() % 10] = rand() % 11;
	decision2[9][rand() % 10] = rand() % 11;
	decision2[9][rand() % 10] = rand() % 11;
	decision2[10][rand() % 10] = rand() % 11;
	decision2[10][rand() % 10] = rand() % 11;
	decision2[10][rand() % 10] = rand() % 11;
	decision2[10][rand() % 10] = rand() % 11;
	decision2[11][rand() % 10] = rand() % 11;
	decision2[11][rand() % 10] = rand() % 11;
	decision2[11][rand() % 10] = rand() % 11;
	decision2[11][rand() % 10] = rand() % 11;


	for (int i = 0; i < DNA; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			decision[i][j] = decision2[i][j];
			cout << decision2[i][j] << " ";
		}
		//cout << "\n";
	}
}


int main()
{
	//srand(time(NULL));
	initialization();
	for (int i = 0; i < times; i++)
	{
		cout << "²Ä" << i + 1 << "¥N\n";
		if (i != 0)
		{
			fitness();
		}
		choose();
		crossover();
		mutation();
		/*if (best1 == best2 && best2 == best3 && best3 == best4 && best4 == best5 && best5 == best6 && best6 == 620)
		{
			break;
		}*/
		best1 = 0, best2 = 0, best1_index = -1, best2_index = -1;
		for (int k = 0; k < DNA; k++)
		{
			sum_space[k] = 0;
			sum_value[k] = 0;
		}
	}
	return 0;
}