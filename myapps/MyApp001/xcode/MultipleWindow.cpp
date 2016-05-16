//
//  MultipleWindow.cpp
//  MyApp001
//
//  Created by HirokiNaganuma on 2016/05/15.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MultipleWindowApp : public App {
public:
    MultipleWindowApp();
    void drawWindow0() { gl::clear( Color::black() ); }
    void drawWindow1() { gl::clear( Color::white() ); }
};
MultipleWindowApp::MultipleWindowApp()
{
    // Connect the windows to their respective signals
    getWindowIndex( 0 )->getSignalDraw().connect( bind( &MultipleWindowApp::drawWindow0, this ) );
    getWindowIndex( 1 )->getSignalDraw().connect( bind( &MultipleWindowApp::drawWindow1, this ) );
}

/*
CINDER_APP( MultipleWindowApp, RendererGl, []( App::Settings *settings ) {
    // prepare the app with 2 small windows
    settings->prepareWindow( Window::Format().size( ivec2( 256 ) ).pos( ivec2( 0, 40 ) ).title( "Window 0" ) );
    settings->prepareWindow( Window::Format().size( ivec2( 256 ) ).pos( ivec2( 0, 320 ) ).title( "Window 1" ) );
})
*/