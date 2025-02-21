#pragma once

class CViewSetup
{
public:
	CViewSetup()
	{
		aspectRatio = 0.0f;
		renderToSubrectOfLargerScreen = false;
		doBloomAndToneMapping = true;
		Ortho = false;
		offCenter = false;
		cacheFullSceneState = false;
		viewToProjectionOverride = false;
		stereoEye = 0;
	}

	int			x;
	int			unscaledX;
	int			y;
	int			unscaledY;
	int			Width;
	int			unscaledWidth;
	int			height;
	int			stereoEye;
	int			unscaledHeight;
	bool		Ortho;
	float		orthoLeft;
	float		orthoTop;
	float		orthoRight;
	float		orthoBottom;
	float		Fov;
	float		fovViewmodel;
	Vector3		Origin;
	Vector3		Angles;
	float		Near;
	float		Far;
	float		nearViewmodel;
	float		farViewmodel;
	bool		renderToSubrectOfLargerScreen;
	float		aspectRatio;
	bool		offCenter;
	float		offCenterTop;
	float		offCenterBottom;
	float		offCenterLeft;
	float		offCenterRight;
	bool		doBloomAndToneMapping;
	bool		cacheFullSceneState;
	bool        viewToProjectionOverride;
	byte		viewToProjection;
};