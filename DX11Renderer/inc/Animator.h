#pragma once

struct MeshPosFrame
{
	float3 pos;
	float time;
};

struct MeshRotFrame
{
	float3 rot;
	float time;
};

struct MeshScaleFrame
{
	float3 scale;
	float time;
};

struct MeshAnimClip
{
	string name;
	vector<MeshPosFrame*>			posFrames;
	vector<MeshRotFrame*>			rotFrames;
	vector<MeshScaleFrame*>		scaleFrames;
	bool hasPosInfo, hasRotInfo, hasScaleInfo;
};

class Animator
{
public:
	Animator();
	~Animator();

	void AddAnimClip(MeshAnimClip* animClip);

	void Update();
private:
	void FlipFrame();
public:
	void SetCurrentClip(string clipName);
	void SetTransform(Transform* t) { this->refTransform = t; }

private:

	float playRate;

	Transform* refTransform = nullptr;

	void SetCurrentFrameLerped();
	float posTimeElapsed = 0.0f, posTimeGap = 0.0f;
	float rotTimeElapsed = 0.0f, rotTimeGap = 0.0f;
	float scaleTimeElapsed = 0.0f, scaleTimeGap = 0.0f;
	const float switchTimeGap;

	//보간된 현재 데이터
	MeshPosFrame currentPosFrame = {};//사용할 데이터
	MeshRotFrame currentRotFrame = {};//사용할 데이터
	MeshScaleFrame currentScaleFrame = {};//사용할 데이터

	//보간을 위한 데이터들
	MeshPosFrame* prevPosFrame = nullptr;
	MeshRotFrame* prevRotFrame = nullptr;
	MeshScaleFrame* prevScaleFrame = nullptr;

	MeshPosFrame* nextPosFrame = nullptr;
	MeshRotFrame* nextRotFrame = nullptr;
	MeshScaleFrame* nextScaleFrame = nullptr;

	UINT posFrameIndex = 0;
	UINT rotFrameIndex = 0;
	UINT scaleFrameIndex = 0;

	MeshPosFrame posTemp = {};//애니메이션 바뀔 때 저장할 임시 매트릭스
	MeshRotFrame rotTemp = {};//애니메이션 바뀔 때 저장할 임시 매트릭스
	MeshScaleFrame scaleTemp = {};//애니메이션 바뀔 때 저장할 임시 매트릭스

	MeshAnimClip* currentAnimClip = nullptr;
	
	unordered_map<string, MeshAnimClip*> animClips;
};