#include "ServerBase.h"
#include <Core/utl/memory.h>
#include <Core/logger/Logger.h>
#include <synchapi.h>
#include <handleapi.h>

namespace Emiri
{
	struct ServerBasePrivate
	{
		SYNCHRONIZATION_BARRIER barrier;
		HANDLE down_event;
		HANDLE begin_semaphore;
	};
}

Emiri::ServerBasePrivate* Emiri::ServerBase::s_priv = nullptr;

void Emiri::ServerBase::OneFrameDown()
{
	if (TRUE == EnterSynchronizationBarrier(&s_priv->barrier, SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY))
	{
		if (FALSE == SetEvent(s_priv->down_event))
		{
			LOG_ERROR("SetEvent Error");
		}
	}
}

bool Emiri::ServerBase::InitAll()
{
	s_priv = utl::make_pointer<ServerBasePrivate>();

	InitializeSynchronizationBarrier(&s_priv->barrier, static_cast<LONG>(SERVER_TYPE_NUM), -1);
	s_priv->begin_semaphore = CreateSemaphoreW(nullptr, 0, static_cast<LONG>(SERVER_TYPE_NUM), nullptr);
	s_priv->down_event = CreateEventW(nullptr, TRUE, FALSE, nullptr);


	
	return true;
}

void Emiri::ServerBase::ShutDownAll()
{
	DeleteSynchronizationBarrier(&s_priv->barrier);
	CloseHandle(s_priv->down_event);
	CloseHandle(s_priv->begin_semaphore);

	utl::free_pointer(s_priv);
}

void Emiri::ServerBase::BeginUpdateServer()
{
	ReleaseSemaphore(s_priv->begin_semaphore, static_cast<LONG>(SERVER_TYPE_NUM), nullptr);
}

void Emiri::ServerBase::EndUpdateServer()
{
	WaitForSingleObject(s_priv->down_event, INFINITE);
}