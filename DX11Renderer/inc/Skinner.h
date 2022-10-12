#pragma once

class Skinner : public lukasG::Component
{
private:
	struct Data
	{
		Matrix data[100];
	}bones;
	Resource<ID3D11Buffer> animBuffer;
public:
	Matrix* Matrixes() { return bones.data; }
	ID3D11Buffer** AnimBuffer() { return animBuffer; }

public:
	Skinner(InstancingObject* object);
	Skinner();
	~Skinner();

	void Update();

	vector<InstancingObject*>* refBones;
	vector<Instance*>* refInsts;
	void ConnectRefBones(vector<Instance*>* bones);
	vector<Matrix> skinWorldTMInv;

	Matrix* instanceTest;
};