SET( EXTENSION_NAME "Extensions_Sky")

ADD_LIBRARY( ${EXTENSION_NAME}
  Sky/SkyBox.cpp
  Sky/SkyDome.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  Extensions_PropertyList
)
