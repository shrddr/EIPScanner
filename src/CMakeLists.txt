include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE_FILES
        cip/connectionManager/ForwardCloseRequest.cpp
        cip/connectionManager/ForwardOpenRequest.cpp
        cip/connectionManager/ForwardOpenResponse.cpp

        cip/CipRevision.cpp
        cip/EPath.cpp
        cip/MessageRouterRequest.cpp
        cip/MessageRouterResponse.cpp
        cip/CipString.cpp

        eip/CommonPacket.cpp
        eip/CommonPacketItem.cpp
        eip/CommonPacketItemFactory.cpp
        eip/EncapsPacket.cpp
        eip/EncapsPacketFactory.cpp

        fileObject/FileObjectEmptyState.cpp
        fileObject/FileObjectLoadedState.cpp
        fileObject/FileObjectNonExistentState.cpp
        fileObject/FileObjectState.cpp
        fileObject/FileObjectUploadInProgressState.cpp

        sockets/BaseSocket.cpp
        sockets/EndPoint.cpp
        sockets/TCPSocket.cpp
        sockets/UDPBoundSocket.cpp
        sockets/UDPSocket.cpp

        utils/Logger.cpp
        utils/Buffer.cpp

        vendor/ra/powerFlex525/DPIFaultManager.cpp
        vendor/ra/powerFlex525/DPIFaultObject.cpp
        vendor/ra/powerFlex525/DPIFaultCode.cpp
        vendor/ra/powerFlex525/DPIFaultParameter.cpp

        BaseObject.cpp
        ConnectionManager.cpp
        DiscoveryManager.cpp
        FileObject.cpp
        IdentityObject.cpp
        IOConnection.cpp
        MessageRouter.cpp
        ParameterObject.cpp
        SessionInfo.cpp)

add_library(EIPScanner SHARED ${SOURCE_FILES})
add_library(EIPScannerS STATIC ${SOURCE_FILES})

SET_TARGET_PROPERTIES(EIPScanner PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

if (WIN32)
        add_definitions(-DNOGDI)
        target_link_libraries(EIPScanner ws2_32)
endif (WIN32)

set_target_properties(
        EIPScanner
        PROPERTIES
        VERSION ${EIPSCANNER_FULL_VERSION}
        SOVERSION ${EIPSCANNER_MAJOR_VERSION})

install(TARGETS EIPScanner EIPScannerS
        LIBRARY
            DESTINATION lib
        ARCHIVE
            DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/
        DESTINATION include/EIPScanner
        FILES_MATCHING PATTERN "*.h*")
