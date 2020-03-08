# include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;



void step4(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros);
void step5(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros);
void step6(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros);


void PrintMatrix(const vector<vector<int>> mat)
{
	cout << "------------------------------------------------" << endl;
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------" << endl;
}

void PrintMatrixB(const vector<vector<bool>> mat)
{
	cout << "------------------------------------------------" << endl;
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------" << endl;
}


void PrintThings(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros)
{
	cout << "Cost : " << endl;
	PrintMatrix(Cost);
	cout << "StarZeros : " << endl;
	PrintMatrixB(StarZeros);
	cout << "PrimeZeros : " << endl;
	PrintMatrixB(PrimeZeros);
	cout << "CoveredRow : { ";
	for (int index : CoveredRow)
	{
		cout << index << " ";
	}
	cout << " }" << endl;
	cout << "CoveredCol : { ";
	for (int index : CoveredCol)
	{
		cout << index << " ";
	}
	cout << " }" << endl;
}

int GetMaxCost_Matrix(const vector<vector<int>> Cost)
{
	vector<int> maxCost_inRow;
	for (vector<int> Row : Cost)
	{
		maxCost_inRow.push_back(*max_element(Row.begin(), Row.end()));
	}
	return *max_element(maxCost_inRow.begin(), maxCost_inRow.end());
}

void step3(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros)
{
	//step 3
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			if (StarZeros[i][j] == true)
			{
				CoveredCol.push_back(j);
			}
		}
	}
	sort(CoveredCol.begin(), CoveredCol.end());
	CoveredCol.erase(unique(CoveredCol.begin(), CoveredCol.end()), CoveredCol.end());
	if (CoveredCol.size() == MatrixSize)
	{
		cout << "@@@@ 3 @@@@" << endl;
		PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
		//종료
		return;
	}
	else
	{
		cout << "@@@@ 3 @@@@" << endl;
		PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
		step4(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
	}
}

void step4(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros)
{
	//step 4
	vector<int> CopyCoveredRow = CoveredRow;
	vector<int> CopyCoveredCol = CoveredCol;
	for (int i = 0; i < MatrixSize; i++)
	{
		auto iterR = find(CopyCoveredRow.begin(), CopyCoveredRow.end(), i);
		if (iterR == CopyCoveredRow.end())
		{
			for (int j = 0; j < MatrixSize; j++)
			{
				auto iterC = find(CopyCoveredCol.begin(), CopyCoveredCol.end(), j);
				if (iterC == CopyCoveredCol.end())
				{
					if (Cost[i][j] == 0)
					{
						PrimeZeros[i][j] = true;
						auto iterStarRow = find(StarZeros[i].begin(), StarZeros[i].end(), true);

						if (iterStarRow == StarZeros[i].end())
						{
							cout << "@@@@ 4 @@@@" << endl;
							PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
							step5(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
							return;
						}
						else
						{
							CoveredRow.push_back(i);
							int removeCol = distance(StarZeros[i].begin(), iterStarRow);
							auto removeColIter = find(CoveredCol.begin(), CoveredCol.end(), removeCol);
							CoveredCol.erase(removeColIter);

						}
					}
				}

			}
		}
	}
	cout << "@@@@ 4 @@@@" << endl;
	PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
	step6(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
}

void PrimeCheck(int MatrixSize, vector<vector<bool>> StarZeros, vector<vector<bool>>PrimeZeros,
	vector<vector<bool>> CopyStarZeros, vector<vector<bool>> CopyPrimeZeros, int I);

void StarCheck(int MatrixSize, vector<vector<bool>> StarZeros, vector<vector<bool>>PrimeZeros,
	vector<vector<bool>> CopyStarZeros, vector<vector<bool>> CopyPrimeZeros, int J )
{
	for (int i = 0; i < MatrixSize; i++)
	{
		if (CopyStarZeros[i][J] == true)
		{
			StarZeros[i][J] = false;
			cout << "@@@@ StarCheck @@@@" << endl;
			PrintMatrixB(StarZeros);
			PrimeCheck(MatrixSize, StarZeros, PrimeZeros, CopyStarZeros, CopyPrimeZeros, i);
			
			return;
		}
	}
	return;
}

void PrimeCheck(int MatrixSize, vector<vector<bool>> StarZeros, vector<vector<bool>>PrimeZeros,
	vector<vector<bool>> CopyStarZeros, vector<vector<bool>> CopyPrimeZeros,  int I)
{
	for (int j = 0; j < MatrixSize; j++)
	{
		if (CopyPrimeZeros[I][j] == true)
		{
			StarZeros[I][j] = true;
			cout << "@@@@ Primecheck @@@@" << endl;
			PrintMatrixB(StarZeros);
			StarCheck(MatrixSize, StarZeros, PrimeZeros, CopyStarZeros, CopyPrimeZeros, j);
			
			return;
		}
	}
	cout << "end : can not be end at PrimeCheck" << endl;
	return;
}

void step5(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros)
{
	vector<vector<bool>> CopyStarZeros = StarZeros;
	vector<vector<bool>> CopyPrimeZeros = PrimeZeros;
	int I;
	int J;
	bool NewZero = false;
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			if (CopyPrimeZeros[i][j] == true)
			{
				for (int k = 0; k < MatrixSize; k++)
				{
					if (CopyStarZeros[i][k] == true)
					{
						break;
					}
					if (k + 1 == MatrixSize)
					{
						NewZero = true;
						StarZeros[i][j] = true;
						I = i;
						J = j;
					}
				}
			}
		}
	}
	if (NewZero == false)
	{
		cout << "@@@@ 5 @@@@" << endl;
		PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
		step6(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
	}
	else
	{
		StarCheck(MatrixSize, StarZeros, PrimeZeros, CopyStarZeros, CopyPrimeZeros, J);
		CoveredCol.clear();
		CoveredRow.clear();
		for (int i = 0; i < MatrixSize; i++)
		{
			PrimeZeros[i].clear();
			PrimeZeros[i].assign(MatrixSize, false);
		}
		cout << "@@@@ 5 @@@@" << endl;
		PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
		step3(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
	}
}

//void step5(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
//	vector<vector<bool>> PrimeZeros)
//{
//	vector<vector<bool>> CopyStarZeros = StarZeros;
//	vector<vector<bool>> CopyPrimeZeros = PrimeZeros;
//	bool NewZero = false;
//	for (int i = 0; i < MatrixSize; i++)
//	{
//		for (int j = 0; j < MatrixSize; j++)
//		{
//			if (CopyPrimeZeros[i][j] == true)
//			{
//				for (int k = 0; k < MatrixSize; k++)
//				{
//					if (CopyStarZeros[i][k] == true)
//					{
//						break;
//					}
//					if (k + 1 == MatrixSize)
//					{
//						NewZero = true;
//						StarZeros[i][j] = true;
//					}
//				}
//			}
//			if (NewZero == true)
//			{
//				for (int k = 0; k < MatrixSize; k++)
//				{
//					if (CopyStarZeros[k][j] == true)
//					{
//						StarZeros[k][j] == false;
//						for (int l = 0; l < MatrixSize; l++)
//						{
//							if (CopyPrimeZeros[k][l] == true)
//							{
//								StarZeros[k][l] = true;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	if (NewZero == false)
//	{
//		cout << "@@@@ 5 @@@@" << endl;
//		PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
//		step6(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
//	}
//	else
//	{
//		CoveredCol.clear();
//		CoveredRow.clear();
//		for (int i = 0; i < MatrixSize; i++)
//		{
//			PrimeZeros[i].clear();
//			PrimeZeros[i].assign(MatrixSize, false);
//		}
//		cout << "@@@@ 5 @@@@" << endl;
//		PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
//		step3(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
//	}
//}

void step6(vector<vector<int>> Cost, int MatrixSize, vector<int> CoveredRow, vector<int> CoveredCol, vector<vector<bool>> StarZeros,
	vector<vector<bool>> PrimeZeros)
{
	//6단계
	bool first = true;
	int minCost;
	for (int i = 0; i < MatrixSize; i++)
	{
		auto iterR = find(CoveredRow.begin(), CoveredRow.end(), i);
		if (iterR == CoveredRow.end())
		{
			for (int j = 0; j < MatrixSize; j++)
			{
				auto iterC = find(CoveredCol.begin(), CoveredCol.end(), j);
				if (iterC == CoveredCol.end())
				{
					if (first == true)
					{
						first = false;
						minCost = Cost[i][j];
					}
					else if (minCost > Cost[i][j])
					{
						minCost = Cost[i][j];
					}
				}
			}
		}
	}
	for (int coveredRow : CoveredRow)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			Cost[coveredRow][j] += minCost;
		}
	}
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			auto iterC = find(CoveredCol.begin(), CoveredCol.end(), j);
			if (iterC == CoveredCol.end())
			{
				Cost[i][j] -= minCost;
			}
		}

	}
	cout << "@@@@ 6 @@@@" << endl;
	PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
	step4(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
}

void HungarianAlgo(vector<vector<int>> Cost, const int N, const int M, const int Mode, int & TotalCost, vector<int> AssignmentIndex)
{
	//정방향으로 만들기
	if (N < M)
	{
		int maxCost = GetMaxCost_Matrix(Cost);
		for (int i = 0; i < M - N; i++)
		{
			vector<int> fictionalRow(M, maxCost);
			Cost.push_back(fictionalRow);
		}
	}
	else if (N > M)
	{
		int maxCost = GetMaxCost_Matrix(Cost);
		for (int i = 0; i < N - M; i++)
		{
			for (vector<int> Row : Cost)
			{
				Row.push_back(maxCost);
			}
		}
	}
	PrintMatrix(Cost);

	int MatrixSize = Cost.size();

	//row에서 가장 작은 값 빼주기
	for (int i = 0; i < MatrixSize; i++)
	{
		int minCost = *min_element(Cost[i].begin(), Cost[i].end());
		for (int j = 0; j < MatrixSize; j++)
		{
			Cost[i][j] -= minCost;
		}
	}
	PrintMatrix(Cost);

	////colum에서 가장 작은 값 빼주기
	//for (int j = 0; j < matrixSize; j++)
	//{
	//	vector<int> colum;
	//	for (vector<int> Row : Cost)
	//	{
	//		colum.push_back(Row[j]);
	//	}
	//	int minCost = *min_element(colum.begin(), colum.end());
	//	for (int i = 0; i < matrixSize; i++)
	//	{
	//		Cost[i][j] -= minCost;
	//	}
	//}
	//PrintMatrix(Cost);

	vector<int> CoveredRow;
	vector<int> CoveredCol;
	vector<vector<bool>> StarZeros(MatrixSize, vector<bool>(MatrixSize, false));
	vector<vector<bool>> PrimeZeros(Cost.size(), vector<bool>(Cost.size(), false));

	//step 2
	for (int i = 0; i < MatrixSize; i++)
	{
		int check = 0;
		for (int j = 0; j < MatrixSize; j++)
		{
			if (Cost[i][j] == 0)
			{
				StarZeros[i][j] = true;
				check = 1;
				break;
			}
		}
		if (check)
		{
			break;
		}
	}
	PrintThings(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);

	step3(Cost, MatrixSize, CoveredRow, CoveredCol, StarZeros, PrimeZeros);
	for (int i = 0; i < MatrixSize; i++)
	{
		for (int j = 0; j < MatrixSize; j++)
		{
			if (StarZeros[i][j] == true)
			{
				AssignmentIndex.push_back(j);
			}
		}
	}
}

void main()
{
	int N;
	int M;
	int Mode;
	string strInput;
	vector<vector<int>> OriginMatrix;
	int TotalCost;
	vector<int> AssignmentIndex;

	cout << "Enter the number of worker(N): ";
	cin >> N;
	cout << "Enter the number of job(M): ";
	cin >> M;
	getchar(); //"\n" 무시하기 위해서

	for (int i = 0; i < N; i++)
	{
		vector<int> newRow;
		getline(cin, strInput);

		string strNum = "";
		for (int j = 0; j < strInput.length(); j++)
		{

			if (strInput.at(j) == ' ')
			{
				newRow.push_back(atoi(strNum.c_str()));
				strNum = "";
			}
			else
			{
				strNum += strInput.at(j);
				continue;
			}
		}
		newRow.push_back(atoi(strNum.c_str()));
		OriginMatrix.push_back(newRow);
	}

	if (OriginMatrix.size() != N)
	{
		cout << "Input error : not mached colum size" << endl;
		return;
	}
	for (vector<int> row : OriginMatrix)
	{
		if (row.size() != M)
		{
			cout << "Input error : not mached row size" << endl;
			return;
		}
	}

	Mode = 0;
	HungarianAlgo(OriginMatrix, N, M, Mode, TotalCost, AssignmentIndex);
	cout << "AssignmentIndex : { ";
	for (int index : AssignmentIndex)
	{
		cout << index << " ";
	}
	cout << " }" << endl;



}