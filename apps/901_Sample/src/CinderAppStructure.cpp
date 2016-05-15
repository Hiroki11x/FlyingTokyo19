#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderApp : public App {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void mouseDown( MouseEvent event ) override;
};

void CinderApp::setup()
{
}
void CinderApp::update()
{
}
void CinderApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}
void CinderApp::mouseDown( MouseEvent event )
{
}


CINDER_APP( CinderApp, RendererGl )
