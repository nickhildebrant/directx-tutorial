#include "Light.h"
#include "ImGUI/imgui.h"

Light::Light( Renderer& renderer, float radius ) : sphereMesh(renderer, radius), constantBuffer(renderer)
{
	Reset();
}

void Light::SpawnControlWindow() noexcept
{
	if ( ImGui::Begin( "Light" ) )
	{
		ImGui::Text( "Position" );

		ImGui::SliderFloat( "X", &bufferData.position.x, -30.0f, 30.0f, "%.01f" );
		ImGui::SliderFloat( "Y", &bufferData.position.y, -30.0f, 30.0f, "%.01f" );
		ImGui::SliderFloat( "Z", &bufferData.position.z, -30.0f, 30.0f, "%.01f" );

		ImGui::Text( "Intensity/Color" );
		ImGui::SliderFloat( "Intensity", &bufferData.diffuseIntensity, 0.01f, 2.0f, "%.2f", 2 );
		ImGui::ColorEdit3( "Diffuse Color", &bufferData.diffuseColor.x );
		ImGui::ColorEdit3( "Ambient", &bufferData.ambientColor.x );

		ImGui::Text( "Falloff" );
		ImGui::SliderFloat( "Constant", &bufferData.attenuationConstant, 0.05f, 10.0f, "%.2f", 4 );
		ImGui::SliderFloat( "Linear", &bufferData.attenuationLinear, 0.0001f, 4.0f, "%.4f", 8 );
		ImGui::SliderFloat( "Quadratic", &bufferData.attenuationQuadradic, 0.0000001f, 10.0f, "%.7f", 10 );

		if ( ImGui::Button( "Reset" ) )
		{
			Reset();
		}
	}

	ImGui::End();
}

void Light::Reset() noexcept
{
	bufferData =
	{
		{ 0.0f, 4.0f, 7.5f, 1.0f },
		{ 0.15f, 0.15f, 0.15f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,
	};
}

void Light::Draw( Renderer& renderer ) const noexcept
{
	sphereMesh.SetPosition( bufferData.position );
	sphereMesh.Draw( renderer );
}

void Light::Bind( Renderer& renderer, DirectX::FXMMATRIX view ) const noexcept
{
	auto bufferCopy = bufferData;
	const auto position = DirectX::XMLoadFloat4( &bufferData.position );

	DirectX::XMStoreFloat4( &bufferCopy.position, DirectX::XMVector4Transform( position, view ) );

	constantBuffer.Update( renderer, bufferCopy );
	constantBuffer.Bind( renderer );
}