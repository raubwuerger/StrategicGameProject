
Compiles with Visual Studio 2019 and Qt 5.4.2
Compiles with Visual Studio 2013 and Qt 5.4.2
	
Performance:
msvc2013_opengl -> OpenGlWidget
	MapViewInstance = new MapView(this);
	MapViewInstance->setViewport( new QOpenGLWidget(this) );



Basic Development Concepts:

xxxSetting					-> Feste Einstellung, sind in Datei hinterlegt.
xxxConfig					-> Aktuelle Einstellung

ModelHeaderXMLSetting.h		-> Defines XML files header
ModelXXXConfig.h			-> Defines ModelXXX XML file items

ModelXXXSetting.h			-> Defines game settings (How much players, map properties, ...)

MapXXXItems					-> Her Id is the same as the GameXXXItems Id.