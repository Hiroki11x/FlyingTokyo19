#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "runtime_app.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Button {
public:
    Button(){};
    Button( const string &name, const Rectf &rect );
    void draw();
protected:
    string mName;
    Rectf mBounds;
    params::InterfaceGlRef mParams;//ofxGuiみたいなやつ

    //Guiでいじるやつ
    Color	mClearColor, mCircleColor;
    vec3	mCirclePosition;
    float	mCircleSize;
};

Button::Button( const string &name, const Rectf &rect )
: mName( name ), mBounds( rect )
{
    // subscribe to mouse down event of the app window
    // oFにもイベントはあるけど、こっちの方が標準的に使われてる気がする
    app::getWindow()->getSignalMouseDown().connect( [this]( app::MouseEvent event ) {
        // Check if the mouse is inside the bounds of this button
        //これだけで、ボタンの内部にクリックされた点があるか判定できる
        if( mBounds.contains( event.getPos() ) ) {
            app::console() << "Button " << mName << " clicked!" << std::endl;
        }
    });
}
void Button::draw()
{
    gl::drawSolidRect( mBounds );
    gl::drawStringCentered( mName, mBounds.getCenter() );
}

//----------------------------------------------------------

class MyApp001App : public App {
  public:
    MyApp001App();
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void drawWindow0() { gl::clear( Color::black() ); }
    void drawWindow1() { gl::clear( Color::white() ); }
//    Button mButton;
};

MyApp001App::MyApp001App(){
//    getWindowIndex( 0 )->getSignalDraw().connect( bind( &MyApp001App::drawWindow0, this ) );
//    getWindowIndex( 1 )->getSignalDraw().connect( bind( &MyApp001App::drawWindow1, this ) );
}

void MyApp001App::setup()
{
//    mButton = Button("button",Rectf(vec2(70),vec2(30)));
}

void MyApp001App::mouseDown( MouseEvent event )
{
}

void MyApp001App::update()
{
    getWindow()->setTitle( to_string( (int) getAverageFps() ) + " fps" );
}

void MyApp001App::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
//    mButton.draw();
    gl::drawSolidRect( Rectf( 30, 30, 300, 100 ) );
}


CINDER_RUNTIME_APP( MyApp001App, RendererGl, []( App::Settings *settings ) {
//    auto displays = Display::getDisplays();
//    settings->setDisplay( displays.size() > 1 ? displays[1] : displays[0] );
//    settings->prepareWindow( Window::Format().size( ivec2( 256 ) ).pos( ivec2( 0, 40 ) ).title( "Window 0" ) );
//    settings->prepareWindow( Window::Format().size( ivec2( 256 ) ).pos( ivec2( 0, 320 ) ).title( "Window 1" ) );

})
//上記はlambda式で記述以下と等価
/*
 void mySettings( App::Settings *settings )
 {
 settings->setWindowSize( ivec2( 200, 60 ) );
 settings->setTitle( "App Settings" );
 settings->setResizable( false );
 }
 CINDER_RUNTIME_APP( AppSettings, RendererGl, mySettings )
 */