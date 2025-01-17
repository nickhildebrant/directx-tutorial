#pragma once
#include <math.h>
#include "Drawable.h"

template<class T>
class TestPoly : public Drawable {
public:
	TestPoly( Renderer& renderer, std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist )
		:
		r( rdist( rng ) ), droll( ddist( rng ) ), dpitch( ddist( rng ) ), dyaw( ddist( rng ) ), dphi( odist( rng ) ),
		dtheta( odist( rng ) ), dchi( odist( rng ) ), chi( adist( rng ) ), theta( adist( rng ) ), phi( adist( rng ) )
	{}

	float wrap_angle( float theta )
	{
		const float PI = 3.1415926535897932f;
		const float modded = fmod( theta, 2.0f * PI );
		return modded >  PI ? ( modded - 2.0f * PI ) : modded;
	}

	void Update( float dt ) noexcept
	{
		roll = wrap_angle(roll + droll * dt);
		pitch = wrap_angle( pitch + dpitch * dt );
		yaw = wrap_angle( yaw + dyaw * dt );
		theta = wrap_angle( theta + dtheta * dt );
		phi = wrap_angle( phi + dphi * dt );
		chi = wrap_angle( chi + dchi * dt );
	}

	DirectX::XMMATRIX GetTransformXM() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw( pitch, yaw, roll ) *
			DirectX::XMMatrixTranslation( r, 0.0f, 0.0f ) *
			DirectX::XMMatrixRotationRollPitchYaw( theta, phi, chi );
	}

protected:
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};