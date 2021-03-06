#include "floodingvisual.h"
#include "tbvectordata.h"

DM_DECLARE_NODE_NAME(FloodingVisual, Sewer)

FloodingVisual::FloodingVisual()
{
	radius = 2;
	scaling = 1;
	view_junctions = DM::View("JUNCTION", DM::NODE, DM::READ);
	view_junctions.addAttribute("flooding_V", DM::Attribute::DOUBLE, DM::READ);
	view_junction_flooding = DM::View("JUNCTION_VISUAL", DM::FACE, DM::WRITE);
	view_junction_flooding.addAttribute("flooding_V", DM::Attribute::DOUBLE, DM::WRITE);
	view_junction_flooding.addAttribute("color_r", DM::Attribute::DOUBLE, DM::WRITE);
	view_junction_flooding.addAttribute("color_g", DM::Attribute::DOUBLE, DM::WRITE);
	view_junction_flooding.addAttribute("color_b", DM::Attribute::DOUBLE, DM::WRITE);
	view_junction_flooding.addAttribute("color_alpha", DM::Attribute::DOUBLE, DM::WRITE);

	std::vector<DM::View> datastream;
	datastream.push_back(view_junctions);
	datastream.push_back(view_junction_flooding);
	this->addParameter("radius", DM::DOUBLE, &radius);
	this->addParameter("scaling", DM::DOUBLE, &scaling);
	this->addData("city", datastream);
}

void FloodingVisual::run() 
{
	DM::System * city = this->getData("city");

	std::vector<DM::Component*> junctions = city->getAllComponentsInView(view_junctions);

	double max_flooding = 0;

	foreach(DM::Component* cmp, junctions)
	{
		DM::Node * n = (DM::Node*)cmp;
		double flooding_volume = n->getAttribute("flooding_V")->getDouble();
		if (flooding_volume > max_flooding)
			max_flooding = flooding_volume;
	}


	foreach(DM::Component* cmp, junctions)
	{
		DM::Node * n = (DM::Node*)cmp;
		double flooding_volume = n->getAttribute("flooding_V")->getDouble();

		if (flooding_volume > 0) 
		{
			std::vector<DM::Node> circle = TBVectorData::CreateCircle(n, radius, 6);

			std::vector<DM::Node*> circle_face;
			foreach (DM::Node n, circle)
				circle_face.push_back(city->addNode(n));

			DM::Face * visual = city->addFace(circle_face, view_junction_flooding);
			visual->addAttribute("flooding_V", flooding_volume * scaling);

			visual->addAttribute("color_r",flooding_volume / max_flooding/2.+0.5);
			visual->addAttribute("color_g",0);
			visual->addAttribute("color_b",0);
			visual->addAttribute("color_alpha",1);

		}

	}
}
