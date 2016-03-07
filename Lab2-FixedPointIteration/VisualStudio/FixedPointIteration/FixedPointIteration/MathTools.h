#pragma once
class MathTools
{
public:
	MathTools();
	~MathTools();

	void SetInitialValue(){};
	void Run(){};

	double GetResult();

private:
	const double MaxValue = 1E+200;
	const double Delta = 0.001;
	const double MaxNumberOfIterations = 1000;

	int LoopCounter;
	double X;

	bool IsFinished;
};
