/* for assignment 1 - plot division boundary*/ 

#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

//activation function
double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}


struct Point2Dd{
    double x,y;
};

struct RGB{int r;int g; int b;};

// round decimal value to 2 decimal digits, return as string
std::string round_str(double var)
{
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << var;
  return stream.str();
}


std::string rgb_to_string(RGB c){
    if ((c.r==-1)&&(c.g==-1)&&(c.b==-1))
    return "transparent";
    std::string out= "\"rgb(" +std::to_string(c.r)+","+ std::to_string(c.g)+","+std::to_string(c.b)+")\"";
    return out;
}

std::string circle(int cx, int cy, int r,RGB stroke,RGB fill){
    return "<circle cx=\"" + std::to_string(cx) + "\" cy=\"" + std::to_string(cy) +   
                                              "\" r=\""   + std::to_string(r)  + 
                                              "\" stroke=" + rgb_to_string(stroke)  +
                                              " fill="+ rgb_to_string(fill)+
                                              " stroke-width=\"1\"/>\n";
}

std::string rect(int x,int y, int w, int h,RGB stroke,RGB fill){
   return"<rect x=\"" + std::to_string(x) +  "\" y=\"" + std::to_string(y) +   
               "\" width=\""   + std::to_string(w)  + "\" height=\""   + std::to_string(h)  + 
                "\" stroke=" + rgb_to_string(stroke)  + " fill="+ rgb_to_string(fill)+
                                              " stroke-width=\"1\"/>\n";
}

std::string line(int x1,int y1, int x2, int y2, RGB stroke,int width){
	return "<line x1=\""+ std::to_string(x1) + "\" x2=\""+ std::to_string(x2) + 
	            "\" y1=\""+ std::to_string(y1) + "\" y2=\""+ std::to_string(y2) +
	            "\" stroke=" + rgb_to_string(stroke) + " stroke-width=\""+ std::to_string(width)+ "\"/>\n";

}


int main(){
    
    // ask user for whole lot
    double b, w0 , w1;
    std::cout<<" For values of b, w0 and w1 you enter program produces .svg file with boundary picture"<<std::endl;
    std::cout<<" Enter value of bias:";
    std::cin>>b;
    std::cout<<" Enter value of w0:";
    std::cin>>w0;
    std::cout<<" Enter value of w1:";
    std::cin>>w1;

    std::vector<Point2Dd> points;
    for (double x0=0; x0<1.001; x0=x0+0.01){
		double x1 = -b/w1 - w0*x0/w1;
        std::cout<<"x0="<<x0<<"  x1="<<x1<<std::endl;
		if ((x1>0.0)&&(x1<1.0)){
           points.push_back({x0,x1});
	   }
	}
   
    
   
     double x_min= 0.0;     double x_max= 1.0;     double y_min= 0.0;     double y_max= 1.0;
  
     double w = 500;      double h = 500;
     double margin = 50;
     double scale_x =  (w-2*margin)/(x_max-x_min);
     double scale_y =  (h-2*margin)/(y_max-y_min);
    
     std::vector<std::string> svg_out; // output svg file
     svg_out.clear();
     svg_out.push_back("<?xml version=\"1.0\" standalone=\"no\"?>\n");
     svg_out.push_back("<svg width=\"500\" height=\"500\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"    xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
            
      //  draw plot boundary
     svg_out.push_back("<rect x=\"0\" y=\"0\" width=\"500\" height=\"700\" stroke=\"black\" fill=\"none\" stroke-width=\"1\"/>\n");
    
     std::string plot_polyline_str = " <polyline points=\"";
        for (unsigned int j = 0 ; j < points.size() ; j++){ 
            double x = margin+points.at(j).x*scale_x;
            double y = h - (margin+points.at(j).y * scale_y);
             plot_polyline_str += std::to_string(x) + " " + std::to_string(y)+" "; 
        }
      plot_polyline_str +=   " \" stroke=\"blue\" fill=\"none\" stroke-width=\"5\"/>\n";
      svg_out.push_back(plot_polyline_str);
      svg_out.push_back( line(margin,h-margin,w-margin,h-margin,{100,100,100},2) );
      svg_out.push_back( line(margin,h-margin,margin,margin,{100,100,100},2) );
      
      svg_out.push_back("<text x=\"5\" y=\""+ std::to_string(h)  +"\" fill=\"black\">"+round_str(x_min)+"</text>\n");
      svg_out.push_back("<text x=\"" + std::to_string(w-margin-10+5) +"\" y=\""+ std::to_string(h)+"\" fill=\"black\">"+round_str(x_max)+"</text>\n");
      svg_out.push_back("<text x=\"250\" y=\""+ std::to_string(h)  +"\" fill=\"black\">"+" x0"+"</text>\n");
       
      svg_out.push_back("<text x=\"5\" y=\""+ std::to_string(margin)  +"\" fill=\"black\">"+ round_str(y_max)+"</text>\n");
      svg_out.push_back("<text x=\"5\" y=\""+ std::to_string(h-margin)  +"\" fill=\"black\">"+round_str(y_min)+"</text>\n");
      svg_out.push_back("<text x=\"5\" y=\""+ std::to_string(250)  +"\" fill=\"black\">"+ "x1"+"</text>\n");
      svg_out.push_back("<text x=\""  + std::to_string(w/2) + "\" y=\""+ std::to_string(h/2)  +"\" fill=\"blue\">"+ "b+w0*x0+w1*x1=0"+"</text>\n");
      
      
      RGB red;  red.r = 255;  red.g=0;  red.b=0;
      RGB green; green.r = 0; green.g=255; green.b=0;
       //RGB blue; blue.r = 0; blue.g=0; blue.b=255;
       
      svg_out.push_back( circle( margin , margin , 15 , green,green) );
      svg_out.push_back( circle(margin,h-margin, 15 , green,green) );
      svg_out.push_back( circle(w-margin,margin, 15 , red,red) );
      svg_out.push_back( circle(w-margin,h-margin, 15 , green, green) );
      svg_out.push_back("</svg>\n");

      std::ofstream fout;
        
      std::cout<<" Enter picture file name. Should end with \".svg\""<<std::endl;
      std::string sfn;
      std::cin>>sfn;        
	  fout.open(sfn,std::ofstream::binary);
      for (std::string s:svg_out){
          fout<<s;
      }
      fout.close();
   

}
