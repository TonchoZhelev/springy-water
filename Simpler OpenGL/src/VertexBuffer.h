#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();

	~VertexBuffer();

	void setData(const void* data, unsigned int size) const;

	void Bind() const;
	void Unbind() const;
};
