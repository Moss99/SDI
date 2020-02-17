#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> numberVec;
	for (int i = 0; i<10 ; i++)
	{
		numberVec.push_back(rand() % 100);
	}
	cout << "Vector size: " << numberVec.size()<<"\n\n";

	for (int i = 0; i < numberVec.size(); i++)
	{
		cout <<"Position " << i << ": " << numberVec[i] << endl;
	}

	cout << "===================================================" << endl;

	for (int i = 0; i < 10; i++)
	{
		numberVec.push_back(rand() % 100+154);
	}
	cout << "Vector size: " << numberVec.size() << "\n\n";

	for (int i = 0; i < numberVec.size(); i++)
	{
		cout << "Position " << i << ": " << numberVec[i] << endl;
	}
}
