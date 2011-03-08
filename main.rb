#!E:\ruby\bin
require 'rubygems'
require 'xmlsimple'

def get_file_as_string(filename)
  data = ''
  f = File.open(filename, "r") 
  f.each_line do |line|
    data += line
  end
  return data
end

def dom_search(data,id)
	if data["id"]==id
		return data
	end
	
	data["layer"].each do |layer|
		layer['object'].each do |obj|
			if obj["id"]==id
				return obj
			end
		end
	end
end

def draw_arc( center_x ,center_y, start_angle, end_angle, radius, layer_depth )

	return "axArc("+center_x.to_s+","+center_y.to_s+","+start_angle.to_s+","+end_angle.to_s+","+radius.to_s+","+layer_depth.to_s+");";
	
end

def draw_line(start_x, start_y, end_x,end_y,layer_depth)
	return "axLine("+start_x+","+start_y+","+end_x+","+end_y+","+layer_depth+");"
end

def create_points(group)
	
	points_group ={};
	points_group["size"] = group["object"].length
	
end

def draw_polynomial(points_group,layer_depth)
	points_group = create_points(points_group) 
	
	return "\nstruct struct_points_group_#{points_group["id"]}   #{points_group["id"]} = ax#{points_group["id"]}();\naxPoly(#{points_group["id"]}.x, #{points_group["id"]}.y ,#{points_group["size"]}, #{layer_depth]});"
end

xmlfile = get_file_as_string ARGV[0]

data = XmlSimple.xml_in(xmlfile)

#puts data.inspect

#puts "double layer;";

object_counter = 0; 

definitions = ""
calls = ""

data['layer'].each do |layer|
	layer["object"].each do |obj|
		xtype = obj["xtype"] ;
		if xtype == "arc"
			start_angle	= dom_search(data,obj["startAngle"])
			end_angle 	= dom_search(data,obj["endAngle"])
			center 		= dom_search(data,obj["center"])
			radius 		= dom_search(data,obj["radius"])
			calls +="\n"+draw_arc(center["x"], center["y"],start_angle["value"],end_angle["value"],radius["value"],layer["depth"])
		elsif xtype == "line" 
			start_point = dom_search(data,obj["start"])
			end_point 	= dom_search(data,obj["start"])
			calls += "\n"+draw_line(start_point["x"],start_point["y"],end_point["x"],end_point["y"],layer["depth"]);
			
		elsif xtype == "point"
			
			x = dom_search(data,obj["x"])
			y = dom_search(data,obj["y"])
			calls += "\n"+draw_point(x,y,layer["depth"])
			
		elsif xtype == "polynomial"
			
			points_group = dom_search(data,obj["pointGroup"])
			points = create_points(points_group) 
			definitions +="\n"+points["function_definition_x"] 
			definitions +="\n"+points["function_definition_y"] 
			calls +="\n"+draw_polynomial(points_group,layer["depth"])
		
		end
	end
end


code =<<EOF

\#include <iostream>
\#include <stdio.h>
\#include <math.h>
\#include "aGLX.h"

#{definitions}

void setup() { 

		 glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}


void display() { 
	
		float Rotate =-20.0f;
		glMatrixMode (GL_MODELVIEW);
		

		
		float i =0;
		int flag = 0;
		while(1)
		{
			#{calls}
		}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("Building API");
	setup();
	glutDisplayFunc(display);
	glutMainLoop();
	getchar();
	return 0;

}

EOF
puts code



