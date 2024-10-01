//
// Created by primal on 24-9-21.
//
#include "ServerBase.h"
#include <pthread.h>
#include <semaphore.h>

namespace Emiri
{
    struct ServerBasePrivate
    {
        pthread_barrier_t barrier;
        sem_t begin_semaphore;
    };
}

bool Emiri::ServerBase::all_down;

Emiri::ServerBasePrivate *Emiri::ServerBase::s_priv = nullptr;

void Emiri::ServerBase::OneFrameDown()
{
    if (PTHREAD_BARRIER_SERIAL_THREAD == pthread_barrier_wait(&s_priv->barrier))
    {
        all_down = true;
    }
}

bool Emiri::ServerBase::InitAll()
{
    sem_init(&(s_priv->begin_semaphore), 0, 0);

    return true;
}

void Emiri::ServerBase::BeginUpdateServer()
{
    all_down = false;
    for (int i = 0; i < static_cast<int>(SERVER_TYPE_NUM); ++i)
    {
        sem_post(&(s_priv->begin_semaphore));
    }
}