#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX

	#include "Windows.h"
	#include "WinSock2.h"
	#include "Ws2tcpip.h"
	typedef int socklen_t;
	//typedef char* receiveBufer_t;
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <netdb.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <unistd.h>
	//typedef void* receiveBufer_t;
	typedef int SOCKET;
	const int NO_ERROR = 0;
	const int INVALID_SOCKET = -1;
	const int WSAECONNRESET = ECONNRESET;
	const int WSAEWOULDBLOCK = EAGAIN;
	const int SOCKET_ERROR = -1;
#endif

#include "memory"

#include "vector"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;

class RoboCat;
class GameObject;

#include "RoboMath.h"

#include "StringUtils.h"
#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SocketUtil.h"

#include "ByteSwap.h"
#include "LinkingContext.h"
#include "MemoryBitStream.h"

#include "TransmissionData.h"
#include "InFlightPacket.h"
#include "AckRange.h"
#include "DeliveryNotificationManager.h"

#include "InputAction.h"
#include "InputState.h"
#include "Move.h"
#include "MoveList.h"

#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "RoboCat.h"
#include "World.h"
#include "Timing.h"
#include "Mouse.h"
#include "Yarn.h"
#include "StringUtils.h"
#include "ScoreBoardManager.h"

#include "WeightedTimedMovingAverage.h"
#include "ReplicationCommand.h"
#include "NetworkManager.h"
#include "Engine.h"

#include <stdio.h>
#include <stdarg.h>
#include <sys/timeb.h>
#include <time.h>
#include "log.h"
