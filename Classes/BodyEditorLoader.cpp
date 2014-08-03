#include "BodyEditorLoader.h"

BodyEditorLoader::BodyEditorLoader(void)
{
	filePath = "";
}

BodyEditorLoader::~BodyEditorLoader(void)
{
}

//BodyEditorLoader::BodyEditorLoader(string str) {
//	if (str == "") printf("file is null");
//	model = readJson(str);
//}

void BodyEditorLoader::attachFixture(b2Body* body, string name, b2FixtureDef fd, float scale) {
	RigidBodyModel rbModel = model.rigidBodies.at(name);
	if (rbModel.name == "") printf("Name ' %s""' was not found.", name.c_str());
	vec.Set(rbModel.origin.x*scale, rbModel.origin.y*scale);
	b2Vec2 origin = vec;
	for (int i=0, n=rbModel.polygons.size(); i<n; i++) {

		//cout<<"polygon #: "<<i<<endl;
		//cout<<endl;
		PolygonModel polygon = rbModel.polygons.at(i);
		int a = polygon.vertices.size();
		b2Vec2 *v = new b2Vec2[polygon.vertices.size()];
		int counter = 0;
		for (int ii=0, nn=polygon.vertices.size(); ii<nn; ii++) {
			b2Vec2 newVec;
			newVec.Set(polygon.vertices.at(ii).x*scale, polygon.vertices.at(ii).y*scale);
			v[ii] = newVec;
				v[ii].Set(v[ii].x - origin.x,v[ii].y - origin.y);//nazib edit
			counter ++;
		}
		polygonShape.Set(v,counter);
		for(int j = 0; j< counter; j++)
		{
			b2Vec2 vv = polygonShape.GetVertex(j);
			//cout<< j << " " <<vv.x <<" --- "<<vv.y<<endl;
		}

		fd.shape= &polygonShape;
		body->CreateFixture(&fd);
		v = NULL;
		delete v;
	}

	for (int i=0, n=rbModel.circles.size(); i<n; i++) {
		CircleModel circle = rbModel.circles.at(i);
		b2Vec2 newVec;
		newVec.Set(circle.center.x*scale,circle.center.y*scale);
		b2Vec2 center = newVec;
		float radius = circle.radius * scale;
		circleShape.m_p = b2Vec2(center.x - origin.x, center.y - origin.y); //nazib edit before center
		circleShape.m_radius = radius;
		fd.shape = &circleShape;
		body->CreateFixture(&fd);
	}
}

string BodyEditorLoader::getImagePath(string name) {
	RigidBodyModel rbModel = model.rigidBodies.at(name);
	if (rbModel.name == "") printf("Name ' %s" "' was not found.", &name);

	return rbModel.imagePath;
}

b2Vec2 BodyEditorLoader::getOrigin(string name, float scale) {
	RigidBodyModel rbModel = model.rigidBodies.at(name);
	if (rbModel.name == "") printf("Name ' %s""' was not found.", &name);
	vec.Set(rbModel.origin.x*scale, rbModel.origin.y*scale);

	return vec;
}

Model BodyEditorLoader::getInternalModel() {
	return model;
}

Model BodyEditorLoader::readJson(string str) {
	Model m;
	std::ifstream fin(str.c_str());
	if(fin == NULL) {cout<<"File Not Found"<<endl; return m;}
	boost::property_tree::ptree rootElem;

	boost::property_tree::ptree bodiesElems;

	boost::property_tree::read_json(fin, rootElem);


	bodiesElems =  rootElem.get_child("rigidBodies");

	BOOST_FOREACH(boost::property_tree::ptree::value_type &bodies, bodiesElems)
	{
		RigidBodyModel rbModel = readRigidBody(bodies.second);
		m.rigidBodies.insert(pair<string, RigidBodyModel>(rbModel.name, rbModel));
	}

	return m;


}

RigidBodyModel BodyEditorLoader::readRigidBody(boost::property_tree::ptree bodyElem) {
	RigidBodyModel rbModel;
	rbModel.name = bodyElem.get<string>("name");
	rbModel.imagePath = bodyElem.get<string>("imagePath");

	boost::property_tree::ptree originElem =  bodyElem.get_child("origin");
	rbModel.origin.x = originElem.get<float>("x");
	rbModel.origin.y = originElem.get<float>("y");

	// polygons

	BOOST_FOREACH(boost::property_tree::ptree::value_type &polygons, bodyElem.get_child("polygons"))
	{
		PolygonModel PolyGon;

		BOOST_FOREACH(boost::property_tree::ptree::value_type &polygon, polygons.second)
		{				
			boost::property_tree::ptree vertex = polygon.second;
			float x = vertex.get<float>("x");	
			float y = vertex.get<float>("y");

			PolyGon.vertices.push_back(b2Vec2(x,y));

		}

		rbModel.polygons.push_back(PolyGon);

	}

	// circles

	boost::property_tree::ptree  circlesElem = bodyElem.get_child("circles");

	BOOST_FOREACH(boost::property_tree::ptree::value_type &circles, circlesElem)
	{
		CircleModel circle;
		circle.center.x = circles.second.get<float>("cx");
		circle.center.y = circles.second.get<float>("cy");
		circle.radius = circles.second.get<float>("r");

		rbModel.circles.push_back(circle);
	}
	return rbModel;
}

void BodyEditorLoader::SetFilePath(string str)
{
	filePath = str;
	if (filePath == "") printf("file is null");
	model = readJson(filePath);
}