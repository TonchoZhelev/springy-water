
#include "IndexBuffer.h"
#include "ErrorChecking.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCALL(glGenBuffers(1, &m_RendererID));
	setData(data, count);
}

IndexBuffer::IndexBuffer()
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCALL(glGenBuffers(1, &m_RendererID));
}

void IndexBuffer::setData(const unsigned int* data, unsigned int count)
{
	m_Count = count;
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}