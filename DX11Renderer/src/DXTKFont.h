#pragma once

#include <unordered_map>

#include "Resources.h"
#include "DXTK\SpriteFont.h"
#include "DXTK\SpriteBatch.h"

enum class fontType
{
	playpretend_25,
	playpretend_20,
	squarefont_17,
	squarefont_21,
	squarefont_24,
	squarefont_29,
	esamanru_Light_50,
	esamanru_Light_30
};

/// <summary>
/// DXTK를 이용한 텍스트 출력
/// 
/// 완성형밖에 안된다는데..
/// DirectWrite버전도 제공해야겠다.
/// 
/// 2021.03.04 LeHideOffice
/// </summary>
class DXTKFont
{
public:
	DXTKFont();
	~DXTKFont();

	void Create();

	void DrawTest();
	void DrawTextColor(int x, int y, DirectX::XMFLOAT4 color, TCHAR* text,int scaleamount = 1,...);
	void DrawTextColor(int x, int y, DirectX::XMFLOAT4 color,fontType type, TCHAR* text,int scaleamount = 1,...);

private:
	DirectX::SpriteBatch* m_pSpriteBatch;
	DirectX::SpriteFont* m_pSpriteFont;

	// 저장된 폰트들
	std::unordered_map<fontType, DirectX::SpriteFont*> font;

	// 그냥 사용하면 뎁스 문제가 생긴다.
	Resource<ID3D11RasterizerState> m_RasterizerState;
	Resource<ID3D11DepthStencilState> m_DepthStencilState;
	Resource<ID3D11BlendState> m_BlendState;
};

/*

추가 할 것
자간, 장평, 줄 간격 고려한 멀티라인 그리기

WriteFactory를 이용한 창 변환에도 깔끔한 폰트

*/