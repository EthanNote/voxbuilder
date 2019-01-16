#include "CVoxModel.h"



void CVoxModel::resize(int size)
{
	this->size = size;
	this->elements.resize(size*size*size, { -1, 0 });
}

VoxBuffer CVoxModel::build_buffer()
{
	auto buffer = new CVoxBuffer();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++) {
				CVoxElement* element = NULL;
				if ((element = get_element(i, j, k)) && !element->is_empty()) {
					buffer->vertex_array.push_back({ i,j, k,1, element->palette_index, element->face_mask });
				}

			}
	return VoxBuffer(buffer);
}

void CVoxModel::calc_masks()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++) {
				CVoxElement* element = NULL;
				CVoxElement* neighbor = NULL;
				if ((element = get_element(i, j, k)) && !element->is_empty()) {
					element->face_mask = 0;
					if (!(neighbor = get_element(i - 1, j, k)) || neighbor->is_empty()) {
						element->face_mask |= 1;
					}
					if (!(neighbor = get_element(i + 1, j, k)) || neighbor->is_empty()) {
						element->face_mask |= 2;
					}
					if (!(neighbor = get_element(i, j - 1, k)) || neighbor->is_empty()) {
						element->face_mask |= 4;
					}
					if (!(neighbor = get_element(i, j + 1, k)) || neighbor->is_empty()) {
						element->face_mask |= 8;
					}
					if (!(neighbor = get_element(i, j, k - 1)) || neighbor->is_empty()) {
						element->face_mask |= 16;
					}
					if (!(neighbor = get_element(i, j, k + 1)) || neighbor->is_empty()) {
						element->face_mask |= 32;
					}
				}

			}
}

CVoxElement* CVoxModel::get_element(int i, int j, int k)
{
	if (i < 0 || j < 0 || k < 0 || i >= size || j >= size || k >= size) {
		return  0;
	}

	return &elements[k*size*size + j * size + i];
}

CVoxModel::CVoxModel()
{
}


CVoxModel::~CVoxModel()
{
}
