#include "pch.h"

const Matrix4* IViewRender::GetWorldToScreenMatrix(bool bUnknown)
{
	return MadFramework::Memory::InvokeVTableFunction<Matrix4*>(this, SourceEngine::IViewRender::Index::GetWorldToScreenMatrix, bUnknown);
}

bool IViewRender::HasWorldToScreenMatrix(bool bUnknown)
{
	return MadFramework::Memory::InvokeVTableFunction<bool>(this, SourceEngine::IViewRender::Index::HasWorldToScreenMatrix, bUnknown);
}
