#pragma once
#include <list>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <Box2D/Box2D.h>
#include <fstream>

#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;

class CircleModel;
class Model;
class PolygonModel;
class RigidBodyModel;

class CircleModel
{
public:
	CircleModel(void){}
	~CircleModel(void){}

	b2Vec2 center;
	float radius;
};

class Model
{
public:
	Model(void){}
	~Model(void){}

	map <string, RigidBodyModel> rigidBodies;
};

class PolygonModel
{
public:
	PolygonModel(void){}
	~PolygonModel(void){}

	vector<b2Vec2> vertices;
	b2Vec2 *buffer;
};

class RigidBodyModel
{
public:
	RigidBodyModel(void){}
	~RigidBodyModel(void){}

	string name;
	string imagePath;
	b2Vec2 origin;
	vector<PolygonModel> polygons;
	vector<CircleModel> circles;
};

class BodyEditorLoader
{
public:
	BodyEditorLoader(void);
	~BodyEditorLoader(void);

	//BodyEditorLoader(string str);	

	void attachFixture( b2Body* body, string name, b2FixtureDef fd, float scale);
	string getImagePath(string name);
	b2Vec2 getOrigin(string name, float scale);
	Model getInternalModel();
	Model readJson(string str);

	RigidBodyModel readRigidBody(boost::property_tree::ptree bodyElem);
	void SetFilePath(string str);

private:
	Model model;
	list <b2Vec2> vectorPool;

	b2PolygonShape polygonShape;
	b2CircleShape circleShape;
	b2Vec2 vec;

	string filePath;
};

