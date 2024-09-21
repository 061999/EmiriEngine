#include "ServerBase.h"
#include <array>
#include <cassert>
#include <Core/utl/memory.h>

static struct
{
	std::array<Emiri::ServerBase*, Emiri::SERVER_TYPE_NUM> servers;
}global{};

Emiri::ServerBase::ServerBase(Emiri::SERVER_TYPE st)
{
	assert(global.servers[st] == nullptr);
	global.servers[st] = this;
}

bool Emiri::ServerBase::RecvMessage(Emiri::ServerMessage* msg)
{
	std::lock_guard<std::mutex> lg{ msg_lock };
	msg_queue.push_back(msg);

	return true;
}

void Emiri::ServerBase::DoMsg()
{
	utl::deque<ServerMessage*> jobs;
	
	if (false == msg_queue.empty())
	{
		std::lock_guard<std::mutex> lg{ msg_lock };
		if (false == msg_queue.empty())
		{
			jobs = msg_queue;
			msg_queue.clear();
		}
	}

	if (false == jobs.empty())
	{
		for (auto item : jobs)
		{
			item->Run();
			utl::free_pointer(item);
		}
	}
}

void Emiri::SendIMessage(ServerMessage* msg)
{
	assert(global.servers[msg->GetType()] != nullptr);
	global.servers[msg->GetType()]->RecvMessage(msg);
}

bool Emiri::StartServer(SERVER_TYPE st)
{
	assert(global.servers[st] != nullptr);
	return global.servers[st]->Initialize();
}

void Emiri::ShutDownServer(SERVER_TYPE st)
{
	assert(global.servers[st] != nullptr);
	global.servers[st]->ShutDown();
}

