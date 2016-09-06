#include "CBRInstance.h"
#include <vector>
#include <algorithm>
#define DivZero(a,b) (b == 0 ? a/0.0001 : a/b)

CBRInstance::CBRInstance()
{
	this->CaseBase = std::vector<CBRCase*>();
	MinInsertionThreshold = 50;
	IdenticalCaseThreshold = 10;
	NearestNeighborDistance = 1500;
	ValidityDistanceThreshold = 10;
	UnclaimedOtherPenalty = 1;
	DistanceWeights = CBRWeightDistance();
	ValueWeights = CBRWeightValue();
}


CBRInstance::~CBRInstance()
{
}

float CBRInstance::DistanceInfo(EntityInfo a, EntityInfo b)
{
	float DistanceTemp = 0;
	float Distance = 0;
	Vector dist = a.Position - b.Position;
	DistanceTemp = DistanceWeights.Position * dist.X;
	Distance += DistanceTemp * DistanceTemp;
	DistanceTemp = DistanceWeights.Position * dist.Y;
	Distance += DistanceTemp * DistanceTemp;
	DistanceTemp = DistanceWeights.Distance * (a.Distance - b.Distance);
	Distance += DistanceTemp * DistanceTemp;
	return sqrt(Distance);
}
bool CBRInstance::AllPairsComp(float * a, float * b)
{
	return a[1] < b[1];
}
//Minimise
float CBRInstance::Distance(CBREnvironment a, CBREnvironment b)
{
	float TempDistance = 0;
	float Distance = 0;
	TempDistance = DistanceInfo(a.Herd, b.Herd);
	Distance += TempDistance * TempDistance;
	//TempDistance = DistanceInfo(a.Self, b.Self);
	//Distance += TempDistance * TempDistance;
	//TempDistance = DistanceInfo(a.Herd, b.Herd);
	//Distance += TempDistance * TempDistance;
	return sqrt(Distance);
}
void CBRInstance::WeightedLinearRegression(std::vector<CBRCase*> cases, int paramx, int paramy, float * intercept, float * gradient, float * error)
{
}
void CBRInstance::Save(std::string loc)
{

}
void CBRInstance::Load(std::string loc)
{

}
CBRCase * CBRInstance::GetCase(CBREnvironment sitrep)
{
	std::vector<ClosePair> NearbyCases;
	float distance = 0;
	for (int i = 0; i < CaseBase.size(); ++i)
	{
		distance = Distance(sitrep, CaseBase.at(i)->EnviromentStart);
		if (distance < NearestNeighborDistance)
		{
			NearbyCases.push_back(ClosePair(distance, i));
		}
	}
	std::sort(NearbyCases.begin(), NearbyCases.end(),ClosePair::SortComp);
	CBRCase * NewCase = new CBRCase();
	NewCase->EnviromentStart = sitrep;
	NewCase->CalculatedValueStart = CalculateValue(sitrep);
	if (NearbyCases.size() == 0)
	{
		NewCase->MutateCases(50);
		std::cout << "Random moves" << std::endl;
	}
	else
	{
		//NewCase->DeltaMovement = CaseBase[NearbyCases.at(0).CloseCase]->DeltaMovement;
		//for (int i = 0; i < CaseBase[NearbyCases.at(0).CloseCase]->Moves.size(); ++i)
		//{
		//	NewCase->Moves.push_back(CaseBase.at(NearbyCases.at(0).CloseCase)->Moves[i]->CopySelf(NULL));
		//}
		if (NearbyCases.at(0).NewDist < IdenticalCaseThreshold)
		{
			NewCase->CopyCaseAction(CaseBase[NearbyCases.at(0).CloseCase]);
			//NewCase->MutateCases(CaseBase[NearbyCases.at(0).CloseCase]->CalculatedValueEnd * 0.01);
			//if (rand() % 2 == 0)
			//{
				//NewCase->RandomiseMoves();
			//}
			if (CaseBase[NearbyCases.at(0).CloseCase]->DeltaValue >= 0)
			{
				NewCase->MutateCases(10);
			}
			NewCase->MutateCases(1);
			std::cout << "Identical case" << std::endl;
		}
		else
		{
			//Use linear regression of moves
			//AdaptionWeightedLinearRegression(NewCase, NearbyCases);
			AdaptionMean(NewCase, NearbyCases);
			//NewCase->MutateCases(20);
			std::cout << "Addapted case" << std::endl;
		}
	}
	if (NewCase->CalculatedValueStart - NewCase->CalculatedValueEnd < 0)
	{
		//NewCase->MutateCases(1);
	}
	return NewCase;
}
void CBRInstance::AdaptionMean(CBRCase * NewCase, std::vector<ClosePair> NearbyCases)
{
	int KClosest = fmin(10,NearbyCases.size());
	int OutParamCount = 2;
	for (int OutParam = 0; OutParam < OutParamCount; ++OutParam)
	{
		NewCase->GetOutputParams(OutParam) = 0;
		for (int i = 0; i < KClosest;++i)
		{
			NewCase->GetOutputParams(OutParam) += CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam);
		}
		NewCase->GetOutputParams(OutParam) /= KClosest;
	}
}
void CBRInstance::AdaptionWeightedLinearRegression(CBRCase * NewCase, std::vector<ClosePair> NearbyCases)
{
	float MeanError = 0;
	int InParamCount = 3;
	int OutParamCount = 2;
	int NearbyCasesCount = NearbyCases.size();
	//NewCase->DeltaMovement = Vector();
	NewCase->MoveNormal = 0;
	NewCase->MoveTowards = 0;
	for (int OutParam = 0; OutParam < OutParamCount; ++OutParam)
	{
		float InParamRsqrdSum = 0;
		for (int InParam = 0; InParam < InParamCount; ++InParam)
		{
			float xw = 0;
			float x = 0;
			float yw = 0;
			float y = 0;
			float a = 0;
			float b = 0;
			float SSres = 0;
			float SStotal = 0;
			float ExpectedY = 0;
			float rsqd = 0;
			float ErrorFactor = 0.001;
			// compute the weighted averages
			for (int i = 0; i < NearbyCasesCount; i++)
			{
				CBRCase * CaseIter = CaseBase[NearbyCases[i].CloseCase];
				xw += CaseIter->EnviromentStart.GetInputParams(InParam) * DivZero(1, CaseIter->CalculatedValueEnd * ErrorFactor);
				yw += CaseIter->GetOutputParams(OutParam) * DivZero(1, CaseIter->CalculatedValueEnd * ErrorFactor);
				x += CaseIter->EnviromentStart.GetInputParams(InParam);
				y += CaseIter->GetOutputParams(OutParam);
			}
			double weightedX = DivZero(xw, x);
			double weightedY = DivZero(yw, y);

			// compute the gradient and intercept
			for (int i = 0; i < NearbyCasesCount; i++)
			{
				CBRCase * CaseIter = CaseBase[NearbyCases[i].CloseCase];
				a += (CaseIter->GetOutputParams(OutParam) - weightedY) * (CaseIter->EnviromentStart.GetInputParams(InParam) - weightedX) * CaseIter->CalculatedValueEnd * ErrorFactor;
				b += (CaseIter->EnviromentStart.GetInputParams(InParam) - weightedX) * (CaseIter->EnviromentStart.GetInputParams(InParam) - weightedX) * CaseIter->CalculatedValueEnd * ErrorFactor;
			}
			double gradient = DivZero(a, b);
			double intercept = (weightedY - weightedX) * gradient;
			//var string = 'y = ' + Math.round(gradient*100) / 100 + 'x + ' + Math.round(intercept*100) / 100;
			//var results = [];
			double Res = 0;
			for (int i = 0; i < NearbyCasesCount; i++)
			{
				CBRCase * CaseIter = CaseBase[NearbyCases[i].CloseCase];
				ExpectedY = (gradient * CaseIter->EnviromentStart.GetInputParams(InParam)) + intercept;
				Res = ((CaseIter->GetOutputParams(OutParam)* DivZero(1, CaseIter->CalculatedValueEnd * ErrorFactor)) - weightedY);
				SSres += Res * Res;
				Res = ((CaseIter->GetOutputParams(OutParam) * DivZero(1, CaseIter->CalculatedValueEnd * ErrorFactor)) - ExpectedY);
				SStotal += Res * Res;
				MeanError += CaseIter->CalculatedValueEnd;
			}
			//MeanError = DivZero(MeanError, NearbyCasesCount);
			rsqd = 1 - DivZero(SSres / yw, SStotal / yw);
			InParamRsqrdSum += rsqd;
			//gradient, intercept, MeanError
			NewCase->GetOutputParams(OutParam) -= rsqd * (intercept + (gradient * NewCase->EnviromentStart.GetInputParams(InParam)));

		}
		NewCase->GetOutputParams(OutParam) /= InParamRsqrdSum;
	}
}
//Needs to minimise
float CBRInstance::CalculateValue(CBREnvironment a)
{
	float Value = 0;
	float ValueTemp = 0;
	//ValueTemp = ValueWeights.DistanceFromClosest * abs(a.Self.DistanceFromClosest);
	ValueTemp = ValueWeights.Distance * abs(a.Herd.Distance);
	Value += ValueTemp * ValueTemp;
	//ValueTemp = ValueWeights.Health * (
	return sqrt(Value);
}
void CBRInstance::FeedBackCase(CBRCase * feedback)
{
	//To start with, find the case it came from
	//Then if the end results are similar add to the validity
	//Otherwise decrement validity
	float ClosestDistance = 0;
	int ClosestCase = -1;
	float NewDist;
	bool Feedbackneeded = false;
	//std::cout << feedback->CalculatedValueEnd << std::endl;
	for (int i = 0; i < CaseBase.size(); ++i)
	{
		if (ClosestCase == -1)
		{
			ClosestCase = i;
			ClosestDistance = Distance(feedback->EnviromentStart, CaseBase.at(i)->EnviromentStart);
		}
		else
		{
			NewDist = Distance(feedback->EnviromentStart, CaseBase.at(i)->EnviromentStart);
			if (abs(NewDist) < abs(ClosestDistance))
			{
				ClosestDistance = NewDist;
				ClosestCase = i;
			}
		}
	}
	if (ClosestCase == -1)
	{
		this->CaseBase.push_back(feedback);
		Feedbackneeded = true;
	}
	else {
		if (ClosestDistance > MinInsertionThreshold)
		{
			this->CaseBase.push_back(feedback);
			Feedbackneeded = true;
		}
		else
		{
			CBRCase * CloesestCase = this->CaseBase.at(ClosestCase);
			//Adapt previouse cases for new enviroment		
			float Dist = Distance(feedback->EnviromentEnd, CloesestCase->EnviromentEnd); 
			if (feedback->CalculatedValueEnd < CloesestCase->CalculatedValueEnd)
			{
				std::cout << "Found Better case" << std::endl;
				delete CloesestCase;
				CaseBase[ClosestCase] = feedback;
				Feedbackneeded = true;
			}/*
			if (Dist < ValidityDistanceThreshold)
			{
				if (CloesestCase->Validity++ > 10)
				{
					CloesestCase->Validity = 10;
				}
				if (feedback->DeltaValue < CloesestCase->DeltaValue + 20)
				{
					//CloesestCase->Validity -= 5;
				}
			}
			else
			{
				--CloesestCase->Validity;
				if (feedback->DeltaValue < CloesestCase->DeltaValue)
				{
					std::cout << "Found Better case" << std::endl;
					delete CloesestCase;
					CloesestCase = feedback;
					Feedbackneeded = true;
				}
				else if (CloesestCase->Validity < 0)
				{
					//std::cout << "Invalid case" << std::endl;
					//delete CloesestCase;
					//this->CaseBase.erase(CaseBase.begin() + ClosestCase);
				}
			}*/
			//}
		}
	}
	if (!Feedbackneeded)
	{
		delete feedback;
	}
}