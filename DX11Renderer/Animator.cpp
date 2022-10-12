#include "pch_dx_11.h"
#include "Animator.h"

Animator::Animator()
	:switchTimeGap(1.0f), playRate(8.0f)//여기
{
}

Animator::~Animator()
{
}

void Animator::Update()
{
	//정해진 시간이 지나면 다음 프레임으로
	FlipFrame();

	//manipulate transform
	SetCurrentFrameLerped();
	float timeElapsed = playRate * DELTA;
	//add times
	if (currentAnimClip->hasPosInfo)
		posTimeElapsed += timeElapsed;
	if (currentAnimClip->hasRotInfo)
		rotTimeElapsed += timeElapsed;
	if (currentAnimClip->hasScaleInfo)
		scaleTimeElapsed += timeElapsed;
}

void Animator::FlipFrame()
{
	//pos
	if (currentAnimClip->hasPosInfo)
	{
		if (posTimeElapsed > posTimeGap)
		{
			posTimeElapsed = 0.0f;
			prevPosFrame = nextPosFrame;
			posFrameIndex = (posFrameIndex + 1) % currentAnimClip->posFrames.size();
			nextPosFrame = currentAnimClip->posFrames[posFrameIndex];
			posTimeGap = nextPosFrame->time - prevPosFrame->time > 0 ? nextPosFrame->time - prevPosFrame->time : switchTimeGap;
		}
	}

	//rot
	if (currentAnimClip->hasRotInfo)
	{
		if (rotTimeElapsed > rotTimeGap)
		{
			rotTimeElapsed = 0.0f;
			prevRotFrame = nextRotFrame;
			rotFrameIndex = (rotFrameIndex + 1) % currentAnimClip->rotFrames.size();
			nextRotFrame = currentAnimClip->rotFrames[rotFrameIndex];
			rotTimeGap = nextRotFrame->time - prevRotFrame->time > 0 ? nextRotFrame->time - prevRotFrame->time : switchTimeGap;
		}
	}

	//scale
	if (currentAnimClip->hasScaleInfo)
	{
		if (scaleTimeElapsed > scaleTimeGap)
		{
			scaleTimeElapsed = 0.0f;
			prevScaleFrame = nextScaleFrame;
			scaleFrameIndex = (scaleFrameIndex + 1) % currentAnimClip->scaleFrames.size();
			nextScaleFrame = currentAnimClip->scaleFrames[scaleFrameIndex];
			scaleTimeGap = nextScaleFrame->time - prevScaleFrame->time > 0 ? nextScaleFrame->time - prevScaleFrame->time : switchTimeGap;
		}
	}
}

//애니메이션이 바뀔 때
void Animator::SetCurrentClip(string clipName)
{
	if (currentAnimClip->name != clipName)
	{
		//저장할 데이터 저장해 놓고
		//pos
		posTemp = currentPosFrame;
		prevPosFrame = &posTemp;
		//rot
		rotTemp = currentRotFrame;
		prevRotFrame = &rotTemp;
		//scale
		scaleTemp = currentScaleFrame;
		prevScaleFrame = &scaleTemp;

		//switch clip
		currentAnimClip = animClips.at(clipName);

		//pos
		if (currentAnimClip->posFrames.size() > 0)
		{
			nextPosFrame = currentAnimClip->posFrames[0];
			posTimeGap = switchTimeGap;
			posTimeElapsed = 0.0f;
			posFrameIndex = 0;
		}
		//rot
		if (currentAnimClip->rotFrames.size() > 0)
		{
			nextRotFrame = currentAnimClip->rotFrames[0];
			rotTimeGap = switchTimeGap;
			rotTimeElapsed = 0.0f;
			rotFrameIndex = 0;
		}
		//scale
		if (currentAnimClip->scaleFrames.size() > 0)
		{
			nextScaleFrame = currentAnimClip->scaleFrames[0];
			scaleTimeGap = switchTimeGap;
			scaleTimeElapsed = 0.0f;
			scaleFrameIndex = 0;
		}
	}
}

void Animator::AddAnimClip(MeshAnimClip* animClip)
{
	animClips.insert(make_pair(animClip->name, animClip));
	animClip->hasPosInfo = animClip->posFrames.size() > 0;
	animClip->hasRotInfo = animClip->rotFrames.size() > 0;
	animClip->hasScaleInfo = animClip->scaleFrames.size() > 0;

	if (animClips.size() == 1)
	{
		//Set initial clip
		currentAnimClip = animClips.at(animClip->name);
		//pos
		if (animClip->hasPosInfo)
		{
			prevPosFrame = animClip->posFrames[0];
			currentPosFrame = *prevPosFrame;
			posTemp = currentPosFrame;
			posFrameIndex = (posFrameIndex + 1) % currentAnimClip->posFrames.size();
			nextPosFrame = currentAnimClip->posFrames[posFrameIndex];
			posTimeGap = nextPosFrame->time - prevPosFrame->time;
			posTimeElapsed = 0.0f;
		}
		//rot
		if (animClip->hasRotInfo)
		{
			prevRotFrame = animClip->rotFrames[0];
			currentRotFrame = *prevRotFrame;
			rotTemp = currentRotFrame;
			rotFrameIndex = (rotFrameIndex + 1) % currentAnimClip->rotFrames.size();
			nextRotFrame = currentAnimClip->rotFrames[rotFrameIndex];
			rotTimeGap = nextRotFrame->time - prevRotFrame->time;
			rotTimeElapsed = 0.0f;
		}
		//scale
		if (animClip->hasScaleInfo)
		{
			prevScaleFrame = animClip->scaleFrames[0];
			currentScaleFrame = *prevScaleFrame;
			scaleTemp = currentScaleFrame;
			scaleFrameIndex = (scaleFrameIndex + 1) % currentAnimClip->scaleFrames.size();
			nextScaleFrame = currentAnimClip->scaleFrames[scaleFrameIndex];
			scaleTimeGap = nextScaleFrame->time - prevScaleFrame->time;
			scaleTimeElapsed = 0.0f;
		}
	}
}

void Animator::SetCurrentFrameLerped()
{
	float ratio = 0.0f;
	//////////////////////////////////pos
	if (currentAnimClip->hasPosInfo)
	{
		ratio = posTimeElapsed / posTimeGap;

		currentPosFrame.pos.x = prevPosFrame->pos.x * (1 - ratio) + nextPosFrame->pos.x *ratio;
		currentPosFrame.pos.y = prevPosFrame->pos.y * (1 - ratio) + nextPosFrame->pos.y * ratio;
		currentPosFrame.pos.z = prevPosFrame->pos.z * (1 - ratio) + nextPosFrame->pos.z * ratio;

		refTransform->pos = currentPosFrame.pos;
	}

	///////////////////////////////////////////////rot
	if (currentAnimClip->hasRotInfo)
	{
		ratio = rotTimeElapsed / rotTimeGap;

		XMVECTOR prevQuat = XMQuaternionRotationRollPitchYaw(prevRotFrame->rot.x, prevRotFrame->rot.y, prevRotFrame->rot.z);
		XMVECTOR nextQuat = XMQuaternionRotationRollPitchYaw(nextRotFrame->rot.x, nextRotFrame->rot.y, nextRotFrame->rot.z);

		XMVECTOR lerped = XMQuaternionSlerp(prevQuat, nextQuat, ratio);

		JWMath::QuatToEuler(refTransform->rot.x, refTransform->rot.y, refTransform->rot.z,
			move(lerped.m128_f32[0]),
			move(lerped.m128_f32[1]),
			move(lerped.m128_f32[2]),
			move(lerped.m128_f32[3])
		);

	}
}
