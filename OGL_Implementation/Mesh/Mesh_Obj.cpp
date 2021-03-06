/*****************************************************************//**
 * \file   Mesh_Obj.cpp
 * \brief  Mesh_Obj Source code
 * 
 * \author Kevin Pruvost (pruvostkevin0@gmail.com)
 * \date   April, 03 2022
 *********************************************************************/
#include "Mesh_Obj.hpp"

// Project includes
#include "OGL_Implementation\DebugInfo\Log.hpp"

Mesh_Obj::Mesh_Obj(const Obj & obj)
{
	LOG_PRINT(Log::LogMainFileName, "Constructed\n");

	// bind VAO and VBO for drawing vertices
	bindVertices(obj);
	// bind VAO and VBO for drawing faces
	bindFaces(obj);
}

Mesh_Obj::~Mesh_Obj()
{
	LOG_PRINT(Log::LogMainFileName, "Destroyed\n");
}

GLuint Mesh_Obj::GetFacesEBO() const
{
	return 0;
}

bool Mesh_Obj::IsUsingEBO() const
{
	return false;
}

Mesh_Base::DrawMode Mesh_Obj::GetDrawMode() const
{
	return DrawMode::DrawArrays;
}

void Mesh_Obj::bindFaces(const Obj & obj)
{
	// bind VAO
	glBindVertexArray(__facesVAO);

	// bind VBO, buffer data to it
	glBindBuffer(GL_ARRAY_BUFFER, __facesVBO);

	std::vector<GLfloat> data;
	for (const auto & face : obj.faces)
	{
		for (int i = 0; i < 3; i++)
		{
			int vid = face.v[i] - 1;
			int vnid = face.vn[i] - 1;
			int vtid = face.vt[i] - 1;
			data.emplace_back(obj.verticesPos[vid].x);
			data.emplace_back(obj.verticesPos[vid].y);
			data.emplace_back(obj.verticesPos[vid].z);
			data.emplace_back(obj.verticesNormals[vnid].x);
			data.emplace_back(obj.verticesNormals[vnid].y);
			data.emplace_back(obj.verticesNormals[vnid].z);
			data.emplace_back(obj.verticesTextureCoordinates[vtid].x);
			data.emplace_back(obj.verticesTextureCoordinates[vtid].y);
			LOG_PRINT(stdout, "%d: %f\\%f\n", vtid, obj.verticesTextureCoordinates[vtid].x, obj.verticesTextureCoordinates[vtid].y);
		}
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), &data.front(), GL_STATIC_DRAW);

	// set vertex attribute pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));

	// unbind VBO & VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	__facesNVert = GLsizei(data.size() / 8);
}

void Mesh_Obj::bindVertices(const Obj & obj)
{
	// bind VAO
	glBindVertexArray(__verticesVAO);

	// bind VBO, buffer data to it
	glBindBuffer(GL_ARRAY_BUFFER, __verticesVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj.numVertices(), &obj.verticesPos.front(), GL_STATIC_DRAW);

	// set vertex attribute pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// unbind VBO & VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	__verticesNVert = GLsizei(obj.numVertices());
}
