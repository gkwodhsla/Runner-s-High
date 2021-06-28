#include"Item.hpp"


float itemCoords[] =
{ -1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,//여기까지 밑면
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	0.0f,1.0f,0.0f,//여기까지 앞면
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 뒷면
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 오른면
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 왼면


};


float itemColor[] =
{
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,

	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,

	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,

	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,

	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,

	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f,
	1.0f,0.95f,0.0f


};
Item::Item(ITEM_DIRECTION initDirection)
{
	if (initDirection == ITEM_DIRECTION::LEFT)
		ItemXpos= -7.0f;
	else if (initDirection == ITEM_DIRECTION::MIDDLE)
		ItemXpos = 0.0f;
	else ItemXpos = 7.0f;
	ItemYpos = 0.0f;
	ItemZpos = -15.0f;
	rads = 0.0f;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBOC);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(itemCoords), itemCoords, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOC);

	glBufferData(GL_ARRAY_BUFFER, sizeof(itemColor), itemColor, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(1);
}
void Item::draw(GLint modelTransformLocation)
{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(ItemXpos, ItemYpos, ItemZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(1.5f, 2.0f, 1.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(rads), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 18);
}
bool Item::update(float velocity)
{
	rads += velocity / 2.0f;
	ItemZpos += 0.05f*velocity;
	if (ItemZpos >= 6.0f)
		return true;
	return false;
}
Item::~Item()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Item::initMatrix()
{
	glLoadIdentity();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transMatrix[i][j] = 0.0f;
		}
	}
	transMatrix[0][0] = 1.0f;
	transMatrix[1][1] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[3][3] = 1.0f;

}
