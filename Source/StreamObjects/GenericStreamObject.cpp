﻿#include "StreamStore.h"

GenericStreamObject::GenericStreamObject(const FBModel* ModelPointer, const TSharedPtr<ILiveLinkProvider> StreamProvider) :
	StreamObjectBase(ModelPointer, StreamProvider, { TEXT("Root Only") })
{
	UpdateFromModel();
};

void GenericStreamObject::UpdateFromModel()
{
	BoneNames.SetNum(1);
	BoneNames[0] = FName("Bone01");
	BoneParents.SetNum(1);
	BoneParents[0] = -1;

	Provider->UpdateSubject(SubjectName, BoneNames, BoneParents);
};

void GenericStreamObject::GetStreamData()
{
	if (!bIsActive) return;

	TArray<FTransform> BoneTransforms;

	// Single Bone
	BoneTransforms.Emplace(UnrealTransformFromModel((FBModel*)RootModel));

	// Generic Models have no special properties
	TArray<FLiveLinkCurveElement> CurveData = GetAllAnimatableCurves((FBModel*)RootModel);

	FBTime LocalTime = FBSystem().LocalTime;
	Provider->UpdateSubjectFrame(SubjectName, BoneTransforms, CurveData, LocalTime.GetSecondDouble(), LocalTime.GetFrame());
};