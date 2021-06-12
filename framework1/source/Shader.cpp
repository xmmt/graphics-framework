#include <Shader.hpp>

#include <wrl.h>
#include <d3dcompiler.h>

using namespace GraphicsFramework;

Shader::Shader(ID3D11Device* device)
    : device_{ device } {
}

Microsoft::WRL::ComPtr<ID3DBlob> Shader::compileFromFile(std::string_view fileName, std::span<D3D_SHADER_MACRO> macro, std::string_view entryName, std::string_view shaderModel) {
    Microsoft::WRL::ComPtr<ID3DBlob> errorCode;
    Microsoft::WRL::ComPtr<ID3DBlob> byteCode;

    auto res = D3DCompileFromFile(
      std::wstring(fileName.cbegin(), fileName.cend()).c_str(),
      macro.empty() ? nullptr : macro.data(),
      nullptr, // include,
      entryName.data(),
      shaderModel.data(),
#if _DEBUG
      D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG_NAME_FOR_BINARY,
#else
      D3DCOMPILE_OPTIMIZATION_LEVEL3,
#endif
      0,
      byteCode.GetAddressOf(),
      errorCode.GetAddressOf());

    if (FAILED(res)) {
        // If the shader failed to compile it should have written something to the error message.
        if (errorCode) {
            char* compileErrors = (char*)(errorCode->GetBufferPointer());
            throw std::runtime_error(std::format("Shader compile error: {}, file: {}", compileErrors, fileName));
        }
        // If there was  nothing in the error message then it simply could not find the shader file itself.
        else {
            throw std::runtime_error(std::format("Shader compile error, maybe missing file: {}", fileName));
        }
    }

#if _DEBUG
    Microsoft::WRL::ComPtr<ID3DBlob> pPDB;
    D3DGetBlobPart(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), D3D_BLOB_PDB, 0, pPDB.GetAddressOf());
    Microsoft::WRL::ComPtr<ID3DBlob> pPDBName;
    D3DGetBlobPart(byteCode->GetBufferPointer(), byteCode->GetBufferSize(), D3D_BLOB_DEBUG_NAME, 0, pPDBName.GetAddressOf());
    struct ShaderDebugName {
        uint16_t Flags;      // Reserved, must be set to zero.
        uint16_t NameLength; // Length of the debug name, without null terminator.
                             // Followed by NameLength bytes of the UTF-8-encoded name.
                             // Followed by a null terminator.
                             // Followed by [0-3] zero bytes to align to a 4-byte boundary.
    };
    auto pDebugNameData = reinterpret_cast<const ShaderDebugName*>(pPDBName->GetBufferPointer());
    auto pName = reinterpret_cast<const char*>(pDebugNameData + 1);
    D3DWriteBlobToFile(pPDB.Get(), std::wstring(pName, pName + pDebugNameData->NameLength).c_str(), true);
#endif

    return byteCode;
}

Microsoft::WRL::ComPtr<ID3DBlob> Shader::compileSource(
  std::span<std::byte> sourceCode,
  std::span<D3D_SHADER_MACRO> macro,
  std::string_view entryName,
  std::string_view shaderModel) {
    //static_assert(false, "not implemented");
    throw std::runtime_error("not implemented");
}

VertexShader::VertexShader(ID3D11Device* device)
    : Shader{ device } {
}

void VertexShader::initWithSourceCode(
  std::span<std::byte> sourceCode,
  std::span<D3D_SHADER_MACRO> macro,
  std::string_view entryName,
  std::string_view shaderModel) {
    auto res = compileSource(sourceCode, macro, entryName, shaderModel);
    if (FAILED(device_->CreateVertexShader(
          res->GetBufferPointer(),
          res->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create vertex shader");
    }
}

void VertexShader::initWithSourceCode(
  std::string_view fileName,
  std::span<D3D_SHADER_MACRO> macro,
  std::string_view entryName,
  std::string_view shaderModel) {
    auto res = compileFromFile(fileName, macro, entryName, shaderModel);
    if (FAILED(device_->CreateVertexShader(
          res->GetBufferPointer(),
          res->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create vertex shader");
    }
}

void VertexShader::initWithByteCode(ID3DBlob* byteCode) {
    if (FAILED(device_->CreateVertexShader(
          byteCode->GetBufferPointer(),
          byteCode->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create vertex shader");
    }
}

void VertexShader::initWithByteCode(std::string_view fileName) {
    Microsoft::WRL::ComPtr<ID3DBlob> byteCode;
    if (FAILED(D3DReadFileToBlob(
          std::wstring(fileName.cbegin(), fileName.cend()).c_str(),
          byteCode.GetAddressOf()))) {
        throw std::runtime_error(std::format("can not read vertex bytecode, file: {}", fileName));
    }
    if (FAILED(device_->CreateVertexShader(
          byteCode->GetBufferPointer(),
          byteCode->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create vertex shader");
    }
}

PixelShader::PixelShader(ID3D11Device* device)
    : Shader{ device } {
}

void PixelShader::initWithSourceCode(
  std::span<std::byte> sourceCode,
  std::span<D3D_SHADER_MACRO> macro,
  std::string_view entryName,
  std::string_view shaderModel) {
    auto res = compileSource(sourceCode, macro, entryName, shaderModel);
    if (FAILED(device_->CreatePixelShader(
          res->GetBufferPointer(),
          res->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create pixel shader");
    }
}

void PixelShader::initWithSourceCode(
  std::string_view fileName,
  std::span<D3D_SHADER_MACRO> macro,
  std::string_view entryName,
  std::string_view shaderModel) {
    auto res = compileFromFile(fileName, macro, entryName, shaderModel);
    if (FAILED(device_->CreatePixelShader(
          res->GetBufferPointer(),
          res->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create pixel shader");
    }
}

void PixelShader::initWithByteCode(ID3DBlob* byteCode) {
    if (FAILED(device_->CreatePixelShader(
          byteCode->GetBufferPointer(),
          byteCode->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create pixel shader");
    }
}

void PixelShader::initWithByteCode(std::string_view fileName) {
    Microsoft::WRL::ComPtr<ID3DBlob> byteCode;
    if (FAILED(D3DReadFileToBlob(
          std::wstring(fileName.cbegin(), fileName.cend()).c_str(),
          byteCode.GetAddressOf()))) {
        throw std::runtime_error(std::format("can not read pixel bytecode, file: {}", fileName));
    }
    if (FAILED(device_->CreatePixelShader(
          byteCode->GetBufferPointer(),
          byteCode->GetBufferSize(),
          nullptr, shader_.GetAddressOf()))) {
        throw std::runtime_error("can not create pixel shader");
    }
}