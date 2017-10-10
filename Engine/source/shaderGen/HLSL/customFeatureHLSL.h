#ifndef _SHADERGEN_HLSL_SHADERFEATUREHLSL_H_
#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#endif
#ifndef _LANG_ELEMENT_H_
#include "shaderGen/langElement.h"
#endif
#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif
#ifndef _FEATUREMGR_H_
#include "shaderGen/featureMgr.h"
#endif
#ifndef _MATERIALFEATURETYPES_H_
#include "materials/materialFeatureTypes.h"
#endif
#ifndef _MATERIALFEATUREDATA_H_
#include "materials/materialFeatureData.h"
#endif

#ifndef CUSTOMSHADERFEATURE_H
#include "shaderGen/customShaderFeature.h"
#endif

class CustomShaderFeatureData;

class CustomFeatureHLSL : public ShaderFeatureHLSL
{
	friend class CustomShaderFeatureData;

	struct VarHolder
	{
		String varName;
		String defaultValue;
		String type;
		bool uniform;
		bool sampler;
		bool texture;
		U32 constNum;
		ConstantSortPosition constSortPos;
		U32 arraySize;

		VarHolder() :
			varName(""),
			type(""),
			defaultValue(""),
			uniform(false), 
			sampler(false), 
			texture(false),
			constNum(0), 
			arraySize(0),
			constSortPos(cspUninit)
		{
		}

		VarHolder(String _varName,String _type, String _defaultValue) :
			uniform(false), sampler(false), texture(false), constNum(0), arraySize(0), constSortPos(cspUninit)
		{
			varName = _varName;
			type = _type;
			defaultValue = _defaultValue;
		}
	};

	Vector<VarHolder> mVars;

public:
	CustomShaderFeatureData* mOwner;

protected:
	MultiLine *meta;

public:

	//****************************************************************************
	// Accu Texture
	//****************************************************************************
	virtual void processVert(Vector<ShaderComponent*> &componentList,
		const MaterialFeatureData &fd);

	virtual void processPix(Vector<ShaderComponent*> &componentList,
		const MaterialFeatureData &fd);

	virtual Material::BlendOp getBlendOp() { return Material::LerpAlpha; }

	virtual Resources getResources(const MaterialFeatureData &fd)
	{
		Resources res;
		res.numTex = 1;
		res.numTexReg = 1;
		return res;
	}

	virtual void setTexData(Material::StageData &stageDat,
		const MaterialFeatureData &fd,
		RenderPassData &passData,
		U32 &texIndex);

	virtual String getName()
	{
		return mOwner->getName();
	}

	void addUniform(String name, String type, String defaultValue, U32 arraySize = 0);
	void addVariable(String name, String type, String defaultValue);
	void addSampler(String name, String type, U32 arraySize = 0);
	void addTexture(String name, String type, String samplerState, U32 arraySize);
	void writeLine(String format, S32 argc, ConsoleValueRef *argv);
};