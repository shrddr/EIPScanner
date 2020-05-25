//
// Created by Aleksey Timin on 11/18/19.
//

#include <system_error>
#ifdef _WIN32
#define CAST_CHAR (char *)
#define CAST_CCHAR (const char *)
#include <Winsock2.h>
#include <ws2tcpip.h>
#else
#define CAST_CHAR
#define CAST_CCHAR
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include "utils/Logger.h"
#include "UDPSocket.h"

namespace eipScanner {
namespace sockets {
	using eipScanner::utils::Logger;
	using eipScanner::utils::LogLevel;




	UDPSocket::UDPSocket(std::string host, int port)
		: UDPSocket(EndPoint(host, port)){

	}

	UDPSocket::UDPSocket(EndPoint endPoint)
			: BaseSocket(EndPoint(std::move(endPoint))) {

		_sockedFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (_sockedFd < 0) {
			throw std::system_error(errno, std::generic_category());
		}

		Logger(LogLevel::DEBUG) << "Opened socket fd=" << _sockedFd;
	}

	UDPSocket::~UDPSocket() {
		Logger(LogLevel::DEBUG) << "Close socket fd=" << _sockedFd;
#ifdef _WIN32
		shutdown(_sockedFd, SD_BOTH);
		closesocket(_sockedFd);
#else
		shutdown(_sockedFd, SHUT_RDWR);
		close(_sockedFd);
#endif
	}

	void UDPSocket::Send(const std::vector <uint8_t> &data) const {
		Logger(LogLevel::TRACE) << "Send " << data.size() << " bytes from UDP socket #" << _sockedFd << ".";

		auto addr = _remoteEndPoint.getAddr();
		int count = sendto(_sockedFd, CAST_CCHAR data.data(), data.size(), 0,
				(struct sockaddr *)&addr, sizeof(addr));
		if (count < data.size()) {
			throw std::system_error(errno, std::generic_category());
		}
	}

	std::vector<uint8_t> UDPSocket::Receive(size_t size) const {
		std::vector<uint8_t> recvBuffer(size);

		auto len = recvfrom(_sockedFd, CAST_CHAR recvBuffer.data(), recvBuffer.size(), 0, NULL, NULL);
		if (len < 0) {
#ifdef _WIN32
			throw std::system_error(WSAGetLastError(), std::generic_category());
#else
			throw std::system_error(errno, std::generic_category());
#endif			
		}

		return recvBuffer;
	}

	std::vector<uint8_t> UDPSocket::ReceiveFrom(size_t size, EndPoint& endPoint) const {
		std::vector<uint8_t> recvBuffer(size);
		struct sockaddr_in addr;
		socklen_t addrFromLength = sizeof(addr);
		auto len = recvfrom(_sockedFd, CAST_CHAR recvBuffer.data(), recvBuffer.size(), 0, (struct sockaddr*)&addr, &addrFromLength);
		if (len < 0) {
			throw std::system_error(errno, std::generic_category());
		}

		endPoint = EndPoint(addr);
		return recvBuffer;
	}
}
}
