//
// Created by Aleksey Timin on 12/17/19.
//

#include <DiscoveryManager.h>
#include <utils/Logger.h>

using eipScanner::DiscoveryManager;
using eipScanner::utils::Logger;
using eipScanner::utils::LogLevel;

int main() {
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(0x202, &wsaData) == 0)
	{
#endif
		Logger::setLogLevel(LogLevel::DEBUG);

		DiscoveryManager discoveryManager("192.168.10.255", 0xAF12, std::chrono::seconds(1));
		auto devices = discoveryManager.discover();

		for (auto& device : devices) {
			Logger(LogLevel::INFO) << "Discovered device: "
				<< device.identityObject.getProductName()
				<< " with address " << device.socketAddress.toString();
		}
#ifdef _WIN32
	}
	WSACleanup();
#endif
}