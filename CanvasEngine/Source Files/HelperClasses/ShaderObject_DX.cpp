#pragma once
#include "ShaderObject_DX.h"
#include "RenderSystem_DX.h"

/// <summary>
/// 
/// </summary>
/// <param name="pFilename"></param>
/// <param name="pEntryPoint"></param>
/// <param name="pShaderModel"></param>
/// <param name="pBlobOut"></param>
/// <returns></returns>
HRESULT ShaderObject_DX::CompileShader(const std::wstring & pFilename, const std::string& pEntryPoint, const std::string& pShaderModel, ID3DBlob** const pBlobOut) const
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* errorBlob = nullptr;

	hr = D3DCompileFromFile(pFilename.c_str(), nullptr, nullptr, pEntryPoint.c_str(), pShaderModel.c_str(),
		dwShaderFlags, 0, const_cast<ID3DBlob**>(pBlobOut), &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			errorBlob->Release();
		}
		return hr;
	}
	if (errorBlob) errorBlob->Release();

	return hr;
}

/// <summary>
/// 
/// </summary>
ShaderObject_DX::ShaderObject_DX()
{
}

/// <summary>
/// 
/// </summary>
ShaderObject_DX::~ShaderObject_DX()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pFilename"></param>
/// <param name="pEntryPoint"></param>
/// <param name="pShaderModel"></param>
/// <returns></returns>
HRESULT ShaderObject_DX::CreateVertex(const RenderSystem* pRenderer, const std::wstring & pFilename, const std::string& pEntryPoint, const std::string& pShaderModel)
{
	HRESULT hr = S_OK;

	// Compiles the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShader(pFilename, pEntryPoint, pShaderModel, &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Creates the vertex shader
	ID3D11VertexShader* vertexShader = nullptr;
	hr = reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, mVertex.GetAddressOf());
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the shader input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "INSTANCEPOSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the shader input layout
	ID3D11InputLayout* vertexLayout = nullptr;
	hr = reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device()->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), mLayout.GetAddressOf());
	pVSBlob->Release();
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <param name="pFilename"></param>
/// <param name="pEntryPoint"></param>
/// <param name="pShaderModel"></param>
/// <returns></returns>
HRESULT ShaderObject_DX::CreatePixel(const RenderSystem* pRenderer, const std::wstring & pFilename, const std::string & pEntryPoint, const std::string & pShaderModel)
{
	HRESULT hr = S_OK;

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShader(pFilename, pEntryPoint, pShaderModel, &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Creates the pixel shader
	ID3D11PixelShader* pixelShader = nullptr;
	hr = reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, mPixel.GetAddressOf());
	pPSBlob->Release();
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <param name="pRenderer"></param>
void ShaderObject_DX::Load(const RenderSystem * pRenderer) const 
{
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->VSSetShader(mVertex.Get(), nullptr, 0);
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->IASetInputLayout(mLayout.Get());
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->PSSetShader(mPixel.Get(), nullptr, 0);
}

