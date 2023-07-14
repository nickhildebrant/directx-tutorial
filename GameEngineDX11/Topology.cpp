#include "Topology.h"

Topology::Topology( Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type ) : type( type ) 
{
	
}

void Topology::Bind( Renderer& renderer )
{
	renderer.GetDeviceContext()->IASetPrimitiveTopology( type );
}