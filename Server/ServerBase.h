#pragma once

#include <Core/utl/async.h>

namespace Emiri
{
	enum SERVER_TYPE
	{
		//SERVER_TYPE_MAIN_WINDOW,
		//SERVER_TYPE_RENDER,
		SERVER_TYPE_PHYSICAL_ASYNC,
		SERVER_TYPE_ANIMATION_ASYNC,
		SERVER_TYPE_UI_ASYNC,
		SERVER_TYPE_AUDIO_ASYNC,
		SERVER_TYPE_NUM,

	};

	class ServerMessage
	{
	public:
		virtual ~ServerMessage() = default;
		virtual SERVER_TYPE GetType() = 0;
		virtual void Run() = 0;
	};

	struct ServerBasePrivate;

	class ServerBase : public utl::task_base
	{
	public:
		explicit ServerBase(SERVER_TYPE st);
		bool RecvMessage(ServerMessage* msg);
		void DoMsg();

		virtual bool Initialize() = 0;
		virtual void ShutDown() = 0;

		static void OneFrameDown();

		static bool InitAll();
		static void ShutDownAll();
		static void BeginUpdateServer();

		static bool all_down;
	private:
		static ServerBasePrivate* s_priv;
		std::mutex msg_lock;
		utl::deque<ServerMessage*> msg_queue;
	};

	void SendIMessage(ServerMessage* msg);

	bool StartServer(SERVER_TYPE st);//TOBEDelete
	
	void ShutDownServer(SERVER_TYPE st);
}