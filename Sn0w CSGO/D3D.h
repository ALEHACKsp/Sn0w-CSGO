#pragma once

namespace D3D
{
	//EndScene Prototype
	typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

	void** InitD3D();

	namespace Hook
	{
		void APIENTRY HookFunc(LPDIRECT3DDEVICE9 o_pDevice);

		static BYTE EndSceneBytes[7];
		static tEndScene oEndScene;
	}
}