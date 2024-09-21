//
// Created by primal on 24-9-21.
//
#pragma once

#ifndef DXRENDERCONTEXT_H
#define DXRENDERCONTEXT_H

#include <Render/RenderContext.h>

namespace Emiri
{
    class DxRenderContext : public RenderContext
    {
        bool Initialize() override;
        void Shutdown() override;
    };
}


#endif //DXRENDERCONTEXT_H