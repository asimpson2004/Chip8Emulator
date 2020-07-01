#ifndef _ASCII_RENDERER_INTERFACE_H_
#define _ASCII_RENDERER_INTERFACE_H_

class ASCIIRenderer;

class AsciiRendererInterface
{
public:
	virtual void Render(ASCIIRenderer* pRenderer) = 0;
};

#endif
