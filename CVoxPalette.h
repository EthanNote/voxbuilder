#pragma once
#include"CVoxMaterial.h"
#include<vector>
using namespace std;


class CVoxPalette
{
public:
	vector<CVoxMaterial> materials;
	CVoxPalette();
	~CVoxPalette();
};

