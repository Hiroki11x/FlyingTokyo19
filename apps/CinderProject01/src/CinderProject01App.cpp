#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "runtime_app.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProject01App : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void CinderProject01App::setup()
{
}

void CinderProject01App::mouseDown( MouseEvent event )
{
}

void CinderProject01App::update()
{
}

void CinderProject01App::draw()
{
	gl::clear( Color( 0, 0, 1 ) );
}

//if you want to runtime compile
//Change CINDER_APP to CINDER_RUNTIME_APP
CINDER_RUNTIME_APP( CinderProject01App, RendererGl )
