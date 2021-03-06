#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CameraUi.h"
#include "cinder/ObjLoader.h"
#include "cinder/Rand.h"

#include <cereal/archives/binary.hpp>
#include "CinderCereal.h"
#define RUNTIME_APP_CEREALIZATION

#include "Watchdog.h"
#include "CinderImGui.h"
#include "runtime_app.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class TestProjectApp : public App {
public:
    void setup() override;
    void update() override;
    void draw() override;

    void mouseDown( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;
    void mouseWheel( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
    void keyUp( KeyEvent event ) override;
    void resize() override;
    void fileDrop( FileDropEvent event ) override;

    void cleanup() override;

    virtual void save( cereal::BinaryOutputArchive &ar );
    virtual void load( cereal::BinaryInputArchive &ar );

    float				mBackground;
    vec4				mBackgroundColor;

    gl::GlslProgRef		mGlslProg;
    gl::BatchRef		mBatch, mPlane;
    gl::Texture2dRef	mTexture;

    CameraPersp			mCamera;
    CameraUi			mCameraUi;
};

void TestProjectApp::setup()
{
    // Initialize the Camera and its UI
    mCamera = CameraPersp( getWindowWidth(), getWindowHeight(), 50.0f, 0.1f, 100.0f );
    mCamera.lookAt( vec3(5,2,0), vec3(0) );
    mCameraUi = CameraUi( &mCamera );

    // load texture
    // 後でどう適応されてるかイマイチわからないけど、loadTextureみたいなので使う
    mTexture = gl::Texture2d::create( loadImage( loadAsset( "iceland.jpg" ) ) );

    // initialize ui
    ui::initialize();


    // create advanced batch
    // Create my data
    vector<vec3> positions;
    vector<ColorA> colors;
    for( size_t i = 0; i < 1000000; ++i ) {//particle作る際の初期ランダム生成
        positions.push_back( randVec3() * randFloat( 0, 100 ) );//スカラをかけてる
        colors.push_back( ColorA( randFloat( 0.6f, 1.0f ), randFloat( 0.1f, 0.3f ), randFloat( 0.6f, 1.0f ), 0.7f ) );
    }

    // Describe the data in terms of what it is, what dimensions it has, etc
    //1. 座標に関して
    auto positionsLayout = geom::BufferLayout();
    positionsLayout.append( geom::POSITION, 3, 0, 0 );

    //2. 色に関して
    auto colorsLayout = geom::BufferLayout();
    colorsLayout.append( geom::COLOR, 4, 0, 0 );

    // Upload my data to the GPU through a VBO
    auto positionsVbo = gl::Vbo::create( GL_ARRAY_BUFFER, positions );//<- Vectorを突っ込む
    auto colorsVbo = gl::Vbo::create( GL_ARRAY_BUFFER, colors );//<- Vectorを突っ込む

    // Link everything together in a VboMesh
    // GPUにあげたデータをvboMeshとして統合的な
    auto vboMesh	= gl::VboMesh::create( positions.size(), GL_POINTS,
                                          {
                                              { positionsLayout, positionsVbo },
                                              { colorsLayout, colorsVbo }
                                          } );

    // create a shader
    //glslProgはGlslProgRef型で準備、この領域?(shader)にvboMeshぶちこむのかな？
    auto glslProg	= gl::getStockShader( gl::ShaderDef().color() );

    // linking my shader to my vbo mesh
    //batchとしてshaderとmeshをリンク
    mBatch			= gl::Batch::create( vboMesh, glslProg );

    mBackgroundColor = vec4(0.5f);
}

void TestProjectApp::update()
{


}
void TestProjectApp::draw()
{

    gl::clear( Color::black() );//ofBackground(0);

    gl::ScopedMatrices scopedMatrices; //ofPushMatrix();
    gl::ScopedDepth	scopedDepth( true ); //ofEnableDepthTest();
    gl::setMatrices( mCamera ); //cam.begin(); -> cam.end()書かなくて良い

    gl::ScopedBlendAdditive scopedBlend; //ofEnableBlendMode(hoge)みたいな
    gl::ScopedTextureBind scopedTex0( mTexture ); //<-これ何
    gl::ScopedColor scopedColor( ColorA::gray( 1.0f, 0.2f ) ); //ofSetColor(...)

    mBatch->draw();//fbo.draw()的な
}

void TestProjectApp::mouseDown( MouseEvent event )
{
    mCameraUi.mouseDown( event );
}
void TestProjectApp::mouseUp( MouseEvent event )
{
    mCameraUi.mouseUp( event );
}
void TestProjectApp::mouseWheel( MouseEvent event )
{
    mCameraUi.mouseWheel( event );
}
void TestProjectApp::mouseMove( MouseEvent event )
{
}
void TestProjectApp::mouseDrag( MouseEvent event )
{
    mCameraUi.mouseDrag( event );
}

void TestProjectApp::keyDown( KeyEvent event )
{
}
void TestProjectApp::keyUp( KeyEvent event )
{
}
void TestProjectApp::resize()
{
}
void TestProjectApp::fileDrop( FileDropEvent event )
{
}

void TestProjectApp::cleanup()
{
}

void TestProjectApp::save( cereal::BinaryOutputArchive &ar )
{
}
void TestProjectApp::load( cereal::BinaryInputArchive &ar )
{
}

CINDER_RUNTIME_APP( TestProjectApp, RendererGl, App::SettingsFn()
#ifndef DISABLE_RUNTIME_COMPILED_APP
                   // The interpreter needs to know about the blocks we are using
                   ,[] ( cling::Interpreter *interpreter ) {
                       // We need to find the path starting from the location of the app
                       auto appRoot = getAppPath().parent_path().parent_path().parent_path();
                       auto cinderRoot = appRoot.parent_path().parent_path() / "cinder";
                       auto blocksFolder = cinderRoot / "blocks";

                       // Header-only blocks are easily added by just providing the include path
                       interpreter->AddIncludePath( ( blocksFolder / "SimplexNoise/include" ).string() );
                       interpreter->AddIncludePath( ( blocksFolder / "SpacePartitioning/include" ).string() );
                       interpreter->AddIncludePath( ( blocksFolder / "Watchdog/include" ).string() );

                       // Some blocks requires the main include folder but also the include folder of the library it wraps
                       interpreter->AddIncludePath( ( blocksFolder / "Cinder-Cereal/include" ).string() );
                       interpreter->AddIncludePath( ( blocksFolder / "Cinder-Cereal/lib/cereal/include" ).string() );

                       // Some other blocks with .cpp files might be a bit more tricky especially when
                       // there's some #defines that need to be processed before the rest like in Cinder-ImGui
                       auto imguiFolder = blocksFolder / "Cinder-ImGui";
                       interpreter->AddIncludePath( ( imguiFolder / "lib/imgui" ).string() );
                       interpreter->AddIncludePath( ( imguiFolder / "include" ).string() );
                       interpreter->loadFile( ( imguiFolder / "include/CinderImGui.h" ).string(), false );
                       interpreter->enableRawInput();
                       interpreter->declare( ci::loadString( ci::loadFile( imguiFolder / "lib/imgui/imgui_draw.cpp" ) ) + "\n" + ci::loadString( ci::loadFile( imguiFolder / "lib/imgui/imgui.cpp" ) ) + "\n" + ci::loadString( ci::loadFile( imguiFolder / "src/CinderImGui.cpp" ) ) );
                       interpreter->enableRawInput( false );
                   }
#endif
)
